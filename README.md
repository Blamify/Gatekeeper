# Gatekeeper
A Halo Infinite mod and local offline server.

Currently this mod only supports the following builds of Halo Infinite.  
Sept-2021 Flight build 7414570 (SHA-1 5A36B8772B076D40F2A837F2DB0F72AB21B78134).

Virgil and Superintendent are two parts of the same product, one will not function correctly without the other.  
Virgil is the game mod itself, the game will need to be patched to load this module.  
Superintendent is the server that allows access to the game.

### Notice:
This repository as well as the mod does not provide any of the Halo Infinite flight content required for this mod to function, this content must have been legally acquired during the closed flight periods of Halo Infinite. Asking for such content is strictly prohibited.  
All mock server response files are obtained from a release build of Halo Infinite and modified.

### Patching:
This step must be done for both source and release builds (only once).  
Open HaloInfinite.exe in a hex editor of your choice.  
Search for the text value of "USER32" (without the quotes).  
Replace it with the text value of "VIRGIL" (without the quotes).

### Building from source:
This project requires Visual Studio 2017 (or above) and OpenSSL v1.1.1 (for certificate creation).  
I have included precompiled binaries for Minhook and OpenSSL for project compiling.  
Open ".\Superintendent\OpenSSL\" then run makeCert.bat and makeDomain.bat (both as admin).  
During certificate creation, make sure the "CommonName" is set to "anvillocalhost.com" (without the quotes).  
Copy both cert.pem and key.pem to ".\x64\Release\".  
Build the project and copy to your Halo Infinite flight directory.

### Releases:
These can be found in the "Releases" section of this repo.  
Every release will include a generic certificate which will be installed as root.  
The domain name of the server will also be added to the Window's Hosts file.  
Simply download the current release build and extract the contents to your Halo Infinite flight directory.  
Run Setup.bat (as admin), make sure to delete (or rename) steam_api64.dll, and start Superintendent.exe.  
Start HaloInfinite.exe and make sure you have output in the server console window.  
Once logged in, select custom games, select your map, and hit play.

### Accessing Forge:
Open ".\Cache\Gamemodes\" and rename Slayer.bin to something else.  
Then rename Forge.bin to Slayer.bin.  
Select custom games, select your map, and hit play.

### Known Issues:
Every time the game is closed Superintendent needs to be restarted prior to re-launching the game, otherwise you will be logged into Halo with a null account.  
Attempting to select forge at the main menu usually crashes the game (Spamming it will sometimes get you in).  
If you do access the forge menu, it will simply default to custom games anyways.
