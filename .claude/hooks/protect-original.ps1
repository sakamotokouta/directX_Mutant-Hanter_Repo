# Blocks Claude Code from mutating archive/original/**.
# Receives Claude Code hook JSON on stdin.

$raw = [Console]::In.ReadToEnd()
if ([string]::IsNullOrWhiteSpace($raw)) { exit 0 }

try {
    $call = $raw | ConvertFrom-Json
} catch {
    exit 0
}

function Deny([string]$reason) {
    @{
        hookSpecificOutput = @{
            hookEventName = "PreToolUse"
            permissionDecision = "deny"
            permissionDecisionReason = $reason
        }
    } | ConvertTo-Json -Depth 6
    exit 0
}

$tool = [string]$call.tool_name
$projectDir = $env:CLAUDE_PROJECT_DIR
if ([string]::IsNullOrWhiteSpace($projectDir)) { $projectDir = (Get-Location).Path }

try {
    $archiveRoot = [System.IO.Path]::GetFullPath((Join-Path $projectDir 'archive\original')).TrimEnd([char[]]@('\','/'))
} catch {
    exit 0
}

function Is-InOriginal([string]$path) {
    if ([string]::IsNullOrWhiteSpace($path)) { return $false }
    try {
        $full = [System.IO.Path]::GetFullPath($path).TrimEnd([char[]]@('\','/'))
        if ($full.Equals($archiveRoot, [System.StringComparison]::OrdinalIgnoreCase)) { return $true }
        return $full.StartsWith($archiveRoot + [System.IO.Path]::DirectorySeparatorChar, [System.StringComparison]::OrdinalIgnoreCase)
    } catch {
        return $false
    }
}

if ($tool -eq 'Write' -or $tool -eq 'Edit') {
    $path = [string]$call.tool_input.file_path
    if (Is-InOriginal $path) {
        Deny "archive/original is an immutable portfolio baseline. Create changes outside the original snapshot."
    }
    exit 0
}

if ($tool -eq 'Bash' -or $tool -eq 'PowerShell') {
    $command = [string]$call.tool_input.command
    if ([string]::IsNullOrWhiteSpace($command)) { exit 0 }
    $normalized = $command.Replace('\','/')

    if ($normalized -notmatch '(?i)archive/original') { exit 0 }

    # Conservative mutation patterns. Reading/diffing/hash commands remain allowed.
    $mutationPatterns = @(
        '(?i)(^|[;&|]\s*)(rm|rmdir|mv|truncate|touch)\b',
        '(?i)\bsed\s+-[^\r\n]*i\b',
        '(?i)\bperl\s+-[^\r\n]*pi\b',
        '(?i)\btee\b',
        '(?i)\bRemove-Item\b',
        '(?i)\bMove-Item\b',
        '(?i)\bRename-Item\b',
        '(?i)\bSet-Content\b',
        '(?i)\bAdd-Content\b',
        '(?i)\bOut-File\b',
        '(?i)\bgit\s+(checkout|restore|clean|reset)\b'
    )

    foreach ($pattern in $mutationPatterns) {
        if ($command -match $pattern) {
            Deny "Shell mutation targeting archive/original is blocked. The original snapshot must remain immutable."
        }
    }
}

exit 0
