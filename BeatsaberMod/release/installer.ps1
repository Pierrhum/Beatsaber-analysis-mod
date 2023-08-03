$modFiles = "libbeatsaber-analysis-mod.so", "libbeatsaber-hook_3_14_0.so", "libcodegen.so", "libcustom-types.so", "libmodloader.so", "libquestui.so"

foreach ($fileName in $modFiles) {
    & adb push content/$fileName /sdcard/Android/data/com.beatgames.beatsaber/files/mods/$fileName
}

if ($LASTEXITCODE -ne 0) {
    Write-Output "Failed to install, exiting..."
    exit $LASTEXITCODE
} else {
    Write-Output "Installation completed, restarting beatsaber..."
    & content/restart-game.ps1
}

