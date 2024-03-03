# Setup Painkiller Black Edition multiplayer client

To join a Painkiller multiplayer server, some conditions should be met:

* Painkiller game version is 1.64 (Black Edition)
* PK++ 1.3 mod is installed
* A client connects to OpenSpy master server
* A client should have a unique CD key
* A client should have all the required multiplayer maps installed

## Game servers

1. Most of the Painkiller gameservers are on OpenSpy now and can be tracked [here](http://beta.openspy.net/en/server-list/painkiller).
2. A couple of hidden Playgound servers can be connected to directly:

    ```
    212.42.38.178:3455
    212.42.38.178:3456
    ```
3. There are some servers on the Radmin VPN network.

## Quick start

The quick start part of the guide describes the fastest way to get into the Painkiller Black Edition multiplayer.

> You don't need to have a full game in this case.

1. Download the `Painkiller 1.64 Lite` multiplayer client [here](https://www.moddb.com/games/painkiller/downloads/painkiller-164-lite-latest-multiplayer-client). This version of the game is already preconfigured for online play.
2. Unpack the archive.
3. Go to the `..\Painkiller_1.64_Lite\Bin` folder and run the game via the `PKPlus1.3.bat` file. Allow Windows to launch the file if it's asking to launch an application from an unknown publisher. This BAT will launch the `PK++ 1.3` mod required for most online servers.
4. In the game menu, go to `Multiplayer` -> `Player Settings` and click on `CD key`.
5. Remove the previous CD key and enter something random, like `3875-f802-f704-1d3e`. Mind the format `xxxx-xxxx-xxxx-xxxx`, where `x` is a number or a letter. While OpenSpy does not check the validity of your key, game servers may check its format and uniqueness. If you don't do this step, servers might kick you out when joining.
6. Go to `Multiplayer` -> `Join Game` and click on the `Internet` tab, find a server and `Join` the game.
7. A couple of additional hidden Playground servers can be found on the `Favourites` tab.
8. For further questions, join the Painkiller discord community [here](https://discord.gg/wWTv9YA).

## Full setup

This part of the guide describes the full game multiplayer configuration in case you have a complete Painkiller Black Edition game.

