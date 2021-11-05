# Workaround server failures: MikTeX installation randomly fails
$wc = New-Object System.Net.WebClient;
$maxAttempts=5;
$attemptCount=0;
Do {
  $attemptCount++;
  Try {
    $wc.DownloadFile("https://miktex.org/download/win/miktexsetup-x64.zip",
                     "miktexsetup-x64.zip")
  } Catch [Exception] {
    Write-Host $_.Exception | format-list -force
  }
} while (((Test-Path "miktexsetup-x64.zip") -eq $false) -and ($attemptCount -le $maxAttempts))

# Extract archive
7z e miktexsetup-x64.zip

# Download MikTeX packages
.\miktexsetup_standalone.exe --local-package-repository=C:\miktex-repository --package-set=essential download
# Install MikTeX packages
.\miktexsetup_standalone.exe --verbose --local-package-repository=C:\miktex-repository --package-set=essential --modify-path --shared install
# Should not be needed, autoinstall is the default
# C:\Program Files\MiKTeX\miktex\bin\x64\initexmf --admin --verbose --set-config-value='[MPM]AutoInstall=1'
