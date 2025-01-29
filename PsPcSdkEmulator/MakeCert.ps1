<#
    This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
    If a copy of the MPL was not distributed with this file, you can obtain one at
    https://mozilla.org/MPL/2.0/.

    Copyright (c) 2025 Lander Gallastegi (LNDF)
#>

$ErrorActionPreference = "Stop"

# Define variables
$CertSubject = "CN=Sony Interactive Entertainment LLC"
$CertFriendlyName = "Sony Interactive Entertainment LLC"
$CertEKU = "1.3.6.1.5.5.7.3.3"
$CertPassword = "PsPcSdk Emulator"
$CertRelativePath = "src\loader\cert.pfx"
$CertAbsolutePath = Join-Path -Path (Get-Location) -ChildPath $CertRelativePath

# Ensure the target directory exists
$CertDirectory = Split-Path -Path $CertAbsolutePath -Parent
if (-not (Test-Path -Path $CertDirectory)) {
    Write-Host "Creating directory: $CertDirectory"
    New-Item -ItemType Directory -Path $CertDirectory | Out-Null
}

# Check if a certificate with the same subject already exists
Write-Host "Checking for existing certificates with the same subject..."
$ExistingCert = Get-ChildItem Cert:\CurrentUser\My | Where-Object { $_.Subject -eq $CertSubject }
if ($ExistingCert) {
    Write-Host "Existing certificate found. Deleting it to avoid duplicates..."
    Remove-Item -Path "Cert:\CurrentUser\My\$($ExistingCert.Thumbprint)" -Force
}

# Create the self-signed certificate
Write-Host "Creating self-signed certificate..."
$Certificate = New-SelfSignedCertificate `
    -Subject $CertSubject `
    -CertStoreLocation Cert:\CurrentUser\My `
    -KeyUsage DigitalSignature `
    -Type CodeSigning `
    -FriendlyName $CertFriendlyName `
    -NotAfter (Get-Date).AddYears(100) `
    -TextExtension @("2.5.29.37={text}$CertEKU") `
    -KeyExportPolicy Exportable

# Export the certificate as a .pfx file
if (Test-Path -Path $CertAbsolutePath) {
    Write-Host "Existing PFX file found. Overwriting: $CertAbsolutePath"
    Remove-Item -Path $CertAbsolutePath -Force
}

Write-Host "Exporting certificate to $CertAbsolutePath..."
$SecurePassword = ConvertTo-SecureString -String $CertPassword -Force -AsPlainText
Export-PfxCertificate `
    -Cert $Certificate `
    -FilePath $CertAbsolutePath `
    -Password $SecurePassword

Write-Host "Certificate successfully created and stored at: $CertAbsolutePath"
