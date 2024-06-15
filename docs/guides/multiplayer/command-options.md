# Painkiller Command Line Options

The information was taken from [pkeuro](https://www.pkeuro.net/?p=249) and updated.

## Plus parameters

```
+connect [xx.xx.xx.xx]
+playrecording [demo name]
+dedicatedserver
+private
+name [player name]
+map [map name]
+interface [xx.xx.xx.xx]
+speed [0,1,2,3]
+port [xxxx]
+maxfps [xx]
+password [xxxxxx]
+hwclass [tnl, nv20, nv25, r200, nv30, nv40]
```

### Description

`+connect` is used to connect to a server as soon as you launch the game.<br>
`+playrecording` is supposed to play a demo when you launch the game.<br>
`+dedicatedserver` launches a dedicated server. It is the same as `-dedicated`. The Linux `pkserver` binary already has the `+dedicatedserver` parameter enabled by default when you launch it.<br>
`+private` makes the server not be seen on GameSpy/OpenSpy.<br>
`+name` sets the player's name when you connect to the server.<br>
`+map` sets a server map as you launch the game. This parameter is absent in the `pkserver` binary.<br>
`+interface` is a very important parameter. You indicate an IP of the interface which has access to the Internet.<br>
`+speed` is your connection speed: 0=modem, 1=ISDN, 2=Cable/ADSL, 3=LAN/T1.<br>
`+port` runs a multiplayer game on a specific port (default 3455).<br>
`+maxfps` limits max FPS in multiplayer (default 125). FPS affects the physics of the game.<br>
`+password` sets the server password.<br>
`+hwclass` is a hardware class. This parameter configures the quality of the game shaders. For example, `tnl` will load shaders of lower quality.<br>

!!! Note
    When launched, the official `pkserver` Linux binary automatically runs with the hardcoded `+dedicatedserver +map +port` parameters.

## Dash parameters

Additional commands for the Windows binary. These commands do not work with the official Linux `pkserver` binary:

```
-start
-dedicated
-cfg [config name; example, config.ini]
-script [example, FS.ExtractPack('')]
-lscripts [pak with scripts; example, LScripts.pak]
-profile [user]
-game editorgame
```

### Description

`-start` immediately starts a multiplayer match when you run a dedicated server.<br>
`-dedicated` launches a dedicated server. It is the same as `+dedicatedserver` but only works on Windows.<br>
`-cfg` sets a name for a custom `config.ini` file. That's where the server configuration is stored. Put the custom file into the game's `Bin` directory or indicate a relative path to it.<br>
`-script` is a helper tool to run some embedded scripts via the painkiller binary. For example, you can pack and extract the `.pak` archives.<br>
`-lscripts` sets the path to custom game scripts.<br>
`-profile` is the Windows user profile.<br>
`-game editorgame` is leftover from the alpha version of Painkiller. It does nothing.<br>
