# PsPcSdk Emulator
This utility allows you to bypass the PlayStation Network account login requirement for various Sony-published games on PC.

Now that Sony has made Playstation Network accounts optional on PC, you can use this utility to obtain the benefits of a PSN account without creating one.

__NOTE__: This does not work for the online components of those games. Do not use it for that purpose.

## Tested Games
The utility has been tested on the Steam versions of the following games:
- God of War: Ragnarök
- Horizon Zero Dawn: Remastered
- Until Dawn
- LEGO Horizon Adventures
- Marvel's Spider-Man 2

All these games work out of the box with PsPcSdk Emulator.

## How to Use
Follow the instructions for your platform to install PsPcSdk Emulator.

### Windows
1. Go to the [releases page](https://github.com/LNDF/PsPcSdkEmulator/releases/latest).
1. Download the `version.dll` file from the latest version.
1. Place the file in the same folder as the executable of the game. See below on how to find the game executable.
1. Run the game. You will no longer see the PlayStation Login prompt.

### Linux
1. Go to the [releases page](https://github.com/LNDF/PsPcSdkEmulator/releases/latest).
1. Download the `version.dll` file from the latest version.
1. Place the file in the same folder as the executable of the game. See below on how to find the game executable.
1. Right-click the game on Steam and select Properties.
1. In the Launch Options box, enter: `WINEDLLOVERRIDES="version=n,b" %command%`
1. Run the game. You will no longer see the PlayStation Login prompt.

### How to Find the Game Executable
1. Right-click the game on Steam and select Properties.
1. Click on the LOCAL FILES tab.
1. Click Browse Local Files...
1. You will find a file with the game icon and the `.exe` extension. That is the executable file.

__IMPORTANT__ note on Unreal Engine games (Until Dawn and LEGO Horizon Adventures): Unreal Engine games store the real game executable in a different location. You can identify Unreal Engine games because they usually have an `Engine` folder, another folder with the name of the project (`Glow` for LEGO Horizon Adventures and `Bates` for Until Dawn), and an executable file. In Unreal Engine games, the real executable is located under the folder with the project name, then `Binaries`, and then `Win64`. Place `version.dll` there.

### Custom DLL loader (advanced users)
PsPcSdk Emulator supports being loaded by an external DLL loader. Just rename `version.dll` to something else an point the DLL loader to it.

This can be useful when loading multiple mods that use the same DLL name (`version.dll` in this case).

## How it works
All the source code is located under `PsPcSdkEmulator/src/` and the project is dividen in several parts.

### Loader
Located in the `loader` folder, this part of PsPcSdk Emulator is responsable for making the game load this implementation of the Playstation SDK insteed of the one provided by Sony. To achive that, Microsoft Detours is used to hook some Win32 functions.

### SDK
The `sdk` folder provides stubs and some implementations of the Playstation SDK functions. Once the loader makes the game load PsPcSdk Emulator as if it was the Playstation SDK, the game links against this implementations insteed of the original ones.

### Net (pss-cloud.net / PSNAccountLinking library)
Playstation games on PC are built with a Playstation account linking library (`PSNAccountLinking`) which is responsable for linking Steam and PSN accounts. `PSNAccountLinking` relies on `pss-cloud.net` for account linking. Inside the `net` folder there is a local HTTP server that is started when the game calls the `scePsPcInitializeInternal()` SDK function. That HTTP server emulates `pss-cloud.net` telling the game that a PSN account is already linked to the Steam account and accepting any new link requqests. Additionaly, WinHttp functions are hooked so that requests to `pss-cloud.net` are redirected to the local HTTP server.

## Building
1. Clone this repository.
1. Open the solution in Visual Studio (built on 2022).
1. Build the project. It will automatically sign the built DLL with a fake certificate.
1. The DLL can be found on `x64/{Debug/Release}/PsPcSdkEmulator.dll` rename it to `version.dll` to use it.

### Recreating the Fake Certificate
A fake certificate is required for PsPcSdk Emulator to load in place of the official PlayStation SDK. You can regenerate it by running the `RunMakeCert.bat` script inside the project folder. The new certificate will be saved to `/src/loader/cert.pfx` and will automatically be used to sign when building.

## Contributing
Just submit a PR. There are some things to improove:
* Write actual implementations of the currently stubbed functions.
* Verify that the HTTP responses for Until Dawn are correct, since the game uses different endpoints.
* Improve the structure and add features to the current code (custom Online id for the PSN account, track trophie completion...)

## License
This project is licensed under the **Mozilla Public License 2.0**.
You are free to use, modify, and distribute this project, as long as you comply with the terms of MPL-2.0.
See the [LICENSE](./LICENSE) file for details.

### Third-Party Dependencies
This project uses **Microsoft Detours**, which is licensed under the **MIT License**.  
You can see the license [here](./PsPcSdkEmulator/external/detours/LICENSE).

## Libraries Used
PsPcSdk Emulator uses [Microsoft Detours](https://github.com/microsoft/Detours) for hooking Windows functions.

## Credits
To the author of the nopcpssdk mod for God of War: Ragnarök. I took some ideas from that mod about the DLL loading process. Also, nopcpssdk was the reason I made this project, as it showed that it could be done. I'm not naming him here since he deleted the mod.

Nixxes for leaving some logging enabled on Horizon Zero Dawn Remastered. It helped.
