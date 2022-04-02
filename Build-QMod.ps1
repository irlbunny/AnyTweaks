Param(
    [Parameter(Mandatory=$false)]
    [Switch] $Clean
)

& $PSScriptRoot/Build-Binary.ps1 -Clean:$Clean
if ($LASTEXITCODE -ne 0) {
    echo "Failed to build binary, exiting..."
    exit $LASTEXITCODE
}

$ModFile = "./mod.json"
$ModJson = Get-Content $ModFile -Raw | ConvertFrom-Json

$FileList = @($ModFile)

$CoverImage = "./" + $modJson.coverImage
if ((-not ($CoverImage -eq "./")) -and (Test-Path $CoverImage)) { 
    $FileList += , $CoverImage
}

foreach ($Mod in $ModJson.modFiles) {
    $Path = "./build/" + $Mod
    if (-not (Test-Path $Path)) {
        $Path = "./extern/libs/" + $Mod
    }

    $FileList += $Path
}

foreach ($Lib in $ModJson.libraryFiles) {
    $Path = "./extern/libs/" + $Lib
    if (-not (Test-Path $Path)) {
        $Path = "./build/" + $Lib
    }

    $FileList += $Path
}

$FileList += "./content"
$ArchiveName = "anytweaks_v" + $ModJson.version + ".qmod"
$TempArchiveName = $ArchiveName + ".zip"

Compress-Archive -Path $FileList -DestinationPath $TempArchiveName -Force
Move-Item $TempArchiveName $ArchiveName -Force
