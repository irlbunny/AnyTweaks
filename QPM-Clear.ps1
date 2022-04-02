qpm-rust clear
if (Test-Path -Path "build") {
    Remove-Item build -R
}
