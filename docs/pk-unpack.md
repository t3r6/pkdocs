# Unpack and Pack Painkiller/Necrovision game resources

> Painkiller has two types of package formats: **.pak** and **.pkm**.

These are basically the same types of archives with the difference that **.pak** files are loaded by the game automatically during start and **.pkm** must be indicated for the game to load.<br>
Thus custom multiplayer maps are usually packed with the **.pkm** extension.

#### There are several ways to unpack Painkiller/Necrovision game resources:

* Imbedded game tools (using FS.ExtractPack)
* [PainFull Extractor](https://www.moddb.com/games/painkiller/downloads/painfull-extractor-v132) program (outdated; no source code)
* [PainKillerExtractor](https://github.com/t3r6/painkiller-extractor) program (outdated; source code available)
* [Dragon UnPACKer](https://www.elberethzone.net/dragon-unpacker.html) (open source)
* [QuickBMS](http://aluigi.altervista.org/quickbms.htm) (open source)

#### And currenly there is only one way to pack Painkiller/Necrovision game resources back using:

* Imbedded game tools (using FS.CreatePack)

## Imbedded game tools

People Can Fly video game development studio provided tools for unpacking and packing resources.

### Unpack files from .pak or .pkm archive via CLI

**Powershell** (can accept relative path to the output file):
```psh
.\painkiller.exe -script FS.ExtractPack"('../Data/DM_Test.pkm','../../Test')"
```
**Windows cmd** (need to indicate full path to the output file):
```cmd
.\painkiller.exe -script FS.ExtractPack('../Data/DM_Test.pkm','C:/Users/User/FullPath/Games/Painkiller/Test')
```

### To pack files back to the .pak or .pkm archive via CLI

**Powershell** (can accept relative path to the output file):
```psh
.\painkiller.exe -script FS.CreatePack"('../Data/DM_Test.pkm','../../Test',true)"
```
**Windows cmd** (need to indicate full path to the output file):
```cmd
.\painkiller.exe -script FS.CreatePack('../data/MyPack.pkm','path/to/files/',true)
```

## Dragon UnPACKer

Dragon UnPACKer is an open source tool for unpacking game resources. Currenly, it fully supports Painkiller **.pak** files but cannot unpack **.pkm** by default. To unpack **.pkm** files with Dragon UnPACKer you need to temporarily rename **.pkm** file to **.pak**. For example, rename `DM_Blink.pkm` to `DM_Blink.pak` and Dragon UnPACKer will allow you to extract `DM_Blink.pak` resource in this case.
