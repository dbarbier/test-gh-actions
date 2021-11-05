# Workaround recurrent failures with "choco install doxygen"
$package = 'doxygen.install'
$url  = 'https://www.doxygen.nl/files/doxygen-1.9.2-setup.exe'
$sha256 = 'd006d98902c71e2eb493677add65eb220de2355196bfb05ca79f60fc55d1251e'

Import-Module C:\ProgramData\chocolatey\helpers\chocolateyInstaller.psm1
Install-ChocolateyPackage $package 'exe' '' $url -Checksum $sha256 -ChecksumType 'sha256' -Verbose
