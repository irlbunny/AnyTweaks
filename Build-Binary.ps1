Param(
    [Parameter(Mandatory=$false)]
    [Switch] $Clean
)

if (($Clean.IsPresent) -and (Test-Path -Path "build")) {
    Remove-Item build -R
}
if (($Clean.IsPresent) -or (-not (Test-Path -Path "build"))) {
    $OutDir = new-item -Path build -ItemType Directory
}

cd build
& cmake -G "Ninja" -DCMAKE_BUILD_TYPE="RelWithDebInfo" ../
& cmake --build .
cd ..
