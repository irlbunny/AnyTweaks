Param(
    [Parameter(Mandatory=$false)]
    [Switch] $UseDebug,

    [Parameter(Mandatory=$false)]
    [Switch] $Clean,

    [Parameter(Mandatory=$false)]
    [Switch] $File
)

& $PSScriptRoot/Build-Binary.ps1 -Clean:$Clean
if ($LASTEXITCODE -ne 0) {
    echo "Failed to build binary, exiting..."
    exit $LASTEXITCODE
}

if ($UseDebug -eq $true) {
    $FileName = Get-ChildItem lib*.so -Path "build/debug" -Name
} else {
    $FileName = Get-ChildItem lib*.so -Path "build/" -Name
}

& adb push build/$FileName /sdcard/Android/data/com.beatgames.beatsaber/files/mods/$FileName

& $PSScriptRoot/Restart-Game.ps1
