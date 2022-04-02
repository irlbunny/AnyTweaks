if (Test-Path "./ndkpath.txt") {
    $NDKPath = Get-Content ./ndkpath.txt
} else {
    $NDKPath = $ENV:ANDROID_NDK_HOME
}

$NDKStack = "$NDKPath/ndk-stack"
if (-not ($PSVersionTable.PSEdition -eq "Core")) {
    $NDKStack += ".cmd"
}

if ($args.Count -eq 0) {
    Get-Content ./log.txt | & $NDKStack -sym ./build/debug/ > log_unstripped.txt
} else {
    Get-Content $args[0] | & $NDKStack -sym ./build/debug/ > "$($args[0])_unstripped.txt"
}
