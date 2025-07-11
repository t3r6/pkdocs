# Setup Painkiller Black Edition multiplayer client

To join a Painkiller multiplayer server, some conditions should be met:

* Painkiller game version is 1.64 (Black Edition).
* [PK++ 1.3](https://www.moddb.com/games/painkiller/downloads/pkplusplus13-unofficial-update) mod is installed.
* A client connects to OpenSpy master server.
* A client should have a unique CD key.
* A client should have all the required multiplayer maps installed. Must-have custom maps are `DM_1v1_meatless` and `DM_Blink`.

## Game servers

Most of the Painkiller gameservers are on OpenSpy now and can be tracked [**here**](https://openspy.net/server-list/painkiller).

## Quick start

The quick start part of the guide describes the fastest way to get into the Painkiller Black Edition multiplayer.

> You don't need to have a full game in this case.

1. Download the `Painkiller 1.64 Lite` multiplayer client [**here**](https://www.moddb.com/games/painkiller/downloads/painkiller-164-lite-latest-multiplayer-client). This version of the game is already preconfigured for online play.
2. Unpack the archive.
3. Go to the `..\Painkiller_1.64_Lite\Bin` folder and run the game via the `PKPlus1.3.bat` file. Allow Windows to launch the file if it's asking to launch an application from an unknown publisher. This BAT will launch the `PK++ 1.3` mod required for most online servers.
4. Change the CD key. In the game menu, go to `Multiplayer` -> `Player Settings` and click on `CD key`. Remove the previous CD key and enter something random, like `3875-f802-f704-1d3e`. Mind the format `xxxx-xxxx-xxxx-xxxx`, where `x` is a number or a letter. While OpenSpy does not check the validity of your key, game servers may check its format and uniqueness. If you don't do this step, servers might kick you out when joining.
5. Go to `Multiplayer` -> `Join Game` and click on the `Internet` tab, find a server and `Join` the game.
6. For further questions, join the Painkiller Discord community [**here**](https://discord.gg/wWTv9YA).

## Full setup

This part of the guide describes the full game multiplayer configuration in case you have a complete Painkiller Black Edition game.

1. Move from GameSpy to OpenSpy to be able to see servers on the in-game browser list. To use OpenSpy, you can either replace all instances of **gamespy.com** with **openspy.net** in `Bin/Engine.dll` and `Bin/Editor/Engine.dll` or modify the Windows `hosts` file. This [**guide**](gamespy-openspy.md) will give you more detailed information on how to do it.
2. Most servers have `PK++ 1.2` mod installed; hovewer, some have `PK++ 1.3`. It is a competitive mod made for tournaments. Starting from the `1.3` version of this mod, it's incompatible with the vanilla Painkiller Black Edition 1.64. It means that you also need to install and run this mod as a client. You can download `PK++ 1.3.1u Open Beta` [**here**](https://www.moddb.com/games/painkiller/downloads/pkplusplus13-unofficial-update)

3. Once `PK++ 1.3` is installed and GameSpy is fixed, create a shortcut with the following property:

    ```
    C:\...\Painkiller\Bin\Painkiller.exe -lscripts pkplus.pak
    ```

    Alternatively, you can create a BAT file in the game `Bin` directory with the following content:

    ```
    Painkiller -lscripts pkplus.pak
    ```

    Run the game via the shortcut. You should see a black CPL menu logo if the `PK++ 1.3` mod was run successfully.

4. Change the CD key. In the game menu, go to `Multiplayer` -> `Player Settings` and click on `CD key`. Remove the previous CD key and enter something random, like `3875-f802-f704-1d3e`. Mind the format `xxxx-xxxx-xxxx-xxxx`, where `x` is a number or a letter. While OpenSpy does not check the validity of your key, game servers may check its format and uniqueness. If you don't do this step, servers might kick you out when joining.
5. Install a multiplayer map pack. Since Painkiller does not have a map auto-download feature, so you need to have some custom maps installed beforehand. A lot of custom multiplayer maps for Painkiller can be found on ModDB. You can use this [**map package**](https://www.moddb.com/games/painkiller/addons/painkiller-multiplayer-deadzone-mappack) as a starter (this mappack is occasionally updated so check if a new version of it has been realeased to be aligned with the servers). PKM maps should be put into the game `Data` directory.
6. Go to `Multiplayer` -> `Join Game` and click on the `Internet` tab, find a server and `Join` the game.
7. Adding servers to the `Favourites` tab. Choose a server and click the `Add to Favourites` button and this server will appear on the `Favourites` tab.

8. Useful settings and console commands:

    * Set maxfps 125 in console for consistent physics when playing locally (it affects jumps and jumppads):

    ```
    /setmaxfps 125
    ```

    * To turn off the default Warmup time, modify `\Bin\config.ini`:

    ```
    Cfg.WarmUpTime = 0
    ```

    * Common console voting commands:

    ```
    /maplist
    /callvote map mapname
    /callvote gamemode gamemodename
    /vote yes
    /ready
    ```

    > where gamemodename: `ffa/tdm/pcf/tlb/voosh/ctf/lms/duel`

9. For further questions, join the Painkiller Discord community [**here**](https://discord.gg/wWTv9YA).