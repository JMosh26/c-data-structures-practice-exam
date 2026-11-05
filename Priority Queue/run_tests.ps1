<#
.SYNOPSIS
    Compiles a C solution and grades it against this folder's test cases.

.DESCRIPTION
    With no arguments, this script grades the answer key in .\solutions.
    Use -Problem and -Source to grade your own attempt.

.EXAMPLE
    .\run_tests.ps1

.EXAMPLE
    .\run_tests.ps1 -Problem P1 -Source .\starter\P1.c

.NOTES
    Exit code 0 means every test passed; 1 means at least one test or
    compilation failed; 2 means the script was called incorrectly.
#>

param(
    [string]$Problem = "all",
    [string]$Source = ""
)

$ErrorActionPreference = "Stop"

$root = $PSScriptRoot
$compiler = "gcc"
$tempDir = Join-Path ([System.IO.Path]::GetTempPath()) ("codechum_" + [guid]::NewGuid().ToString("N"))

function Normalize-Output {
    param([string]$Text)

    if ($null -eq $Text) {
        return ""
    }

    $text = $Text -replace "`r`n", "`n"
    $lines = $text -split "`n"
    $result = @()
    foreach ($line in $lines) {
        $result += $line.TrimEnd()
    }
    return (($result -join "`n").TrimEnd())
}

function Shorten-Text {
    param([string]$Text, [int]$Limit = 400)

    if ($Text.Length -le $Limit) {
        return $Text
    }
    return $Text.Substring(0, $Limit) + "..."
}

if (-not (Get-Command $compiler -ErrorAction SilentlyContinue)) {
    Write-Host "Error: '$compiler' was not found on PATH." -ForegroundColor Red
    exit 2
}

if ($Problem -ne "all") {
    $Problem = $Problem.ToUpper()
}

if ($Problem -eq "all" -and -not [string]::IsNullOrWhiteSpace($Source)) {
    Write-Host "Error: -Source needs a specific -Problem (P1, P2, or P3)." -ForegroundColor Red
    exit 2
}

$problems = @()
if ($Problem -eq "all") {
    $problems = @(Get-ChildItem (Join-Path $root "tests") -Directory |
        Sort-Object Name |
        ForEach-Object { $_.Name })
} else {
    $problems = @($Problem)
}

New-Item -ItemType Directory -Path $tempDir | Out-Null

$totalPass = 0
$totalFail = 0

try {
    foreach ($p in $problems) {
        $testDir = Join-Path $root "tests\$p"

        if (-not (Test-Path -LiteralPath $testDir)) {
            Write-Host "Unknown problem '$p'." -ForegroundColor Red
            $totalFail++
            continue
        }

        if ([string]::IsNullOrWhiteSpace($Source)) {
            $srcPath = Join-Path $root "solutions\$p.c"
        } else {
            $srcPath = $Source
            if (-not [System.IO.Path]::IsPathRooted($srcPath)) {
                $srcPath = Join-Path (Get-Location).Path $srcPath
            }
        }

        if (-not (Test-Path -LiteralPath $srcPath)) {
            Write-Host "Source not found: $srcPath" -ForegroundColor Red
            $totalFail++
            continue
        }

        $exe = Join-Path $tempDir "$p.exe"

        Write-Host ""
        Write-Host "== $p  ($([System.IO.Path]::GetFileName($srcPath))) =="

        $previousPreference = $ErrorActionPreference
        $ErrorActionPreference = "Continue"
        $compileOutput = & $compiler -std=c11 -O2 -Wall -Wextra -o $exe $srcPath 2>&1
        $compileExit = $LASTEXITCODE
        $ErrorActionPreference = $previousPreference

        if ($compileExit -ne 0) {
            Write-Host "  COMPILE ERROR" -ForegroundColor Red
            foreach ($line in $compileOutput) {
                Write-Host "  $($line.ToString())"
            }
            $totalFail++
            continue
        }

        if ($compileOutput) {
            foreach ($line in $compileOutput) {
                Write-Host "  [warning] $($line.ToString())" -ForegroundColor Yellow
            }
        }

        $tests = @(Get-ChildItem -LiteralPath $testDir -Filter "*.in" | Sort-Object Name)
        if ($tests.Count -eq 0) {
            Write-Host "  No test cases found." -ForegroundColor Yellow
            $totalFail++
            continue
        }

        $problemPass = 0
        $problemFail = 0

        foreach ($test in $tests) {
            $name = [System.IO.Path]::GetFileNameWithoutExtension($test.Name)
            $expectedPath = [System.IO.Path]::ChangeExtension($test.FullName, ".out")

            if (-not (Test-Path -LiteralPath $expectedPath)) {
                Write-Host "  [SKIP] $name (missing .out file)" -ForegroundColor Yellow
                $problemFail++
                continue
            }

            $stdoutPath = Join-Path $tempDir "stdout.txt"
            $stderrPath = Join-Path $tempDir "stderr.txt"

            if (Test-Path -LiteralPath $stdoutPath) {
                Remove-Item -LiteralPath $stdoutPath -Force
            }
            if (Test-Path -LiteralPath $stderrPath) {
                Remove-Item -LiteralPath $stderrPath -Force
            }

            $proc = Start-Process -FilePath $exe `
                -RedirectStandardInput $test.FullName `
                -RedirectStandardOutput $stdoutPath `
                -RedirectStandardError $stderrPath `
                -NoNewWindow -PassThru

            $finished = $proc.WaitForExit(5000)

            if (-not $finished) {
                try { $proc.Kill() } catch { }
                $proc.WaitForExit()
                Write-Host "  [FAIL] $name (time limit exceeded)" -ForegroundColor Red
                $problemFail++
                continue
            }

            $actual = ""
            if (Test-Path -LiteralPath $stdoutPath) {
                $actual = Get-Content -LiteralPath $stdoutPath -Raw
            }

            $expected = Get-Content -LiteralPath $expectedPath -Raw

            $actualNorm = Normalize-Output $actual
            $expectedNorm = Normalize-Output $expected

            if ($actualNorm -eq $expectedNorm) {
                Write-Host "  [PASS] $name" -ForegroundColor Green
                $problemPass++
            } else {
                Write-Host "  [FAIL] $name" -ForegroundColor Red
                $problemFail++
                Write-Host "         expected: $(Shorten-Text $expectedNorm)"
                Write-Host "         actual:   $(Shorten-Text $actualNorm)"

                if (Test-Path -LiteralPath $stderrPath) {
                    $err = Get-Content -LiteralPath $stderrPath -Raw
                    if (-not [string]::IsNullOrWhiteSpace($err)) {
                        Write-Host "         stderr:   $(Shorten-Text $err.Trim())" -ForegroundColor Yellow
                    }
                }
            }
        }

        Write-Host "  $p result: $problemPass/$($tests.Count) passed"
        $totalPass += $problemPass
        $totalFail += $problemFail
    }
} finally {
    if (Test-Path -LiteralPath $tempDir) {
        Remove-Item -LiteralPath $tempDir -Recurse -Force -ErrorAction SilentlyContinue
    }
}

Write-Host ""
Write-Host "Total: $totalPass passed, $totalFail failed"

if ($totalFail -gt 0) {
    exit 1
}
exit 0
