# Grades all four topic folders using their answer keys.

$ErrorActionPreference = "Stop"
$root = $PSScriptRoot
$topics = @("Open Hashing", "Closed Hashing", "Bit Vectors", "Priority Queue")
$failedTopics = 0

foreach ($topic in $topics) {
    Write-Host ""
    Write-Host ("#" * 20 + " " + $topic + " " + "#" * 20) -ForegroundColor Cyan
    & (Join-Path $root "$topic\run_tests.ps1")
    if ($LASTEXITCODE -ne 0) {
        $failedTopics++
    }
}

Write-Host ""
if ($failedTopics -eq 0) {
    Write-Host "ALL TOPICS PASSED" -ForegroundColor Green
    exit 0
}

Write-Host "$failedTopics topic(s) had failures." -ForegroundColor Red
exit 1
