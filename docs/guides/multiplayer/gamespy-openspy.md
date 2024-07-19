# Replace GameSpy with OpenSpy

Since GameSpy master servers were shut down in 2013, the OpenSpy community worked on supporting games dependent on GameSpy master servers. Painkiller and Painkiller Overdose are supported by OpenSpy.

GameSpy (now OpenSpy) is required to advertise your game server online. This will allow players to see your server in their in-game browser and join it without knowing its IP address and port. Otherwise, you would have to type in the IP and port manually in the game to join a server and add it to `Favourites` for convenience.

There are two ways to make the game understand the transition from GameSpy to OpenSpy:

* Modify the `hosts` file (not recommended).
* Modify game DLL files and Painkiller Linux `pkserver` binary.

!!! Warning
    Modifying DLL files is the recommended way since IP addresses are subject to change.
    This change should be done on both the server and the client side.

## Hosts file

The location of the `hosts` file:

* Windows - `C:\Windows\System32\drivers\etc\hosts`
* Linux - `/etc/hosts`

We need to redirect GameSpy hostnames to OpenSpy IP addresses. Add the following lines to the `hosts` file.

!!! Warning
    IP addresses are subject to change. If you want to know the current OpenSpy IP's, you need to ping or dig each of the below subdomains within the openspy.net domain. For example:

    ```
    dig painkiller.master.openspy.net +short
    server1.openspy.net.
    134.122.16.249
    ```

* For Painkiller (`painkiller` subdomain):

```
134.122.16.249 painkiller.master.gamespy.com
134.122.16.249 painkiller.available.gamespy.com
134.122.16.249 painkiller.ms0.gamespy.com
134.122.16.249 painkiller.ms1.gamespy.com
134.122.16.249 painkiller.ms2.gamespy.com
134.122.16.249 painkiller.ms3.gamespy.com
134.122.16.249 painkiller.ms4.gamespy.com
134.122.16.249 painkiller.ms5.gamespy.com
134.122.16.249 painkiller.ms6.gamespy.com
134.122.16.249 painkiller.ms7.gamespy.com
134.122.16.249 painkiller.ms8.gamespy.com
134.122.16.249 painkiller.ms9.gamespy.com
134.122.16.249 painkiller.ms10.gamespy.com
134.122.16.249 painkiller.ms11.gamespy.com
134.122.16.249 painkiller.ms12.gamespy.com
134.122.16.249 painkiller.ms13.gamespy.com
134.122.16.249 painkiller.ms14.gamespy.com
134.122.16.249 painkiller.ms15.gamespy.com
134.122.16.249 painkiller.ms16.gamespy.com
134.122.16.249 painkiller.ms17.gamespy.com
134.122.16.249 painkiller.ms18.gamespy.com
134.122.16.249 painkiller.ms19.gamespy.com
134.122.16.249 painkiller.ms20.gamespy.com
167.99.14.87 painkiller.natneg1.gamespy.com
157.230.90.177 painkiller.natneg2.gamespy.com
134.122.16.249 painkiller.natneg3.gamespy.com
167.99.14.87 motd.gamespy.com
```

* For Painkiller Overdose (`painkillerod` subdomain):

```
134.122.16.249 painkillerod.master.gamespy.com
134.122.16.249 painkillerod.available.gamespy.com
134.122.16.249 painkillerod.ms0.gamespy.com
134.122.16.249 painkillerod.ms1.gamespy.com
134.122.16.249 painkillerod.ms2.gamespy.com
134.122.16.249 painkillerod.ms3.gamespy.com
134.122.16.249 painkillerod.ms4.gamespy.com
134.122.16.249 painkillerod.ms5.gamespy.com
134.122.16.249 painkillerod.ms6.gamespy.com
134.122.16.249 painkillerod.ms7.gamespy.com
134.122.16.249 painkillerod.ms8.gamespy.com
134.122.16.249 painkillerod.ms9.gamespy.com
134.122.16.249 painkillerod.ms10.gamespy.com
134.122.16.249 painkillerod.ms11.gamespy.com
134.122.16.249 painkillerod.ms12.gamespy.com
134.122.16.249 painkillerod.ms13.gamespy.com
134.122.16.249 painkillerod.ms14.gamespy.com
134.122.16.249 painkillerod.ms15.gamespy.com
134.122.16.249 painkillerod.ms16.gamespy.com
134.122.16.249 painkillerod.ms17.gamespy.com
134.122.16.249 painkillerod.ms18.gamespy.com
134.122.16.249 painkillerod.ms19.gamespy.com
134.122.16.249 painkillerod.ms20.gamespy.com
167.99.14.87 painkillerod.natneg1.gamespy.com
157.230.90.177 painkillerod.natneg2.gamespy.com
134.122.16.249 painkillerod.natneg3.gamespy.com
167.99.14.87 motd.gamespy.com
```

## Modify DLL files and Painkiller Linux `pkserver` binary

If you choose this method, you don't need to add anything to the `hosts` file.

There is a prepared patch for [Painkiller](https://www.moddb.com/games/painkiller/downloads/painkiller-164-multiplayer-gamespy-fix) and [Overdose](https://www.moddb.com/games/painkiller-overdose/downloads/painkiller-overdose-gamespy-fix). Just replace the DLL's in your game folder.

If you want to modify the files manually, follow the steps below. Here is the [**guide**](http://beta.openspy.net/en/howto/generic/painkiller) but it is general and is not a perfect fit for Painkiller.

GameSpy is mentioned in the following files:

* Painkiller

```
..\Painkiller\Bin\Engine.dll
..\Painkiller\Bin\Editor\Engine.dll
```

* Painkiller Linux Dedicated Server

```
../pkserver/Bin/pkserver
```

* Painkiller Overdose

```
..\Overdose\Bin\OverdoseEngine.dll
..\Overdose\Bin\OverdoseEngineEditor.dll
..\Overdose\Bin\OverdoseEngineServer.dll
```

!!! Note
    You don't really need any Hex editor to modify those DLL files. Nonetheless, you need an editor that supports various encodings like Notepad++. Standard Windows Notepad is not suitable for this purpose. Use Hex editors otherwise.

Open the DLL file or the `pkserver` Linux binary with Notepad++ and replace all instances of **gamespy.com** with **openspy.net**. Save the file.

Make sure the size of DLL's should not have changed. If it's changed, it means that the encoding was not interpreted correctly by the editor. In this case, you can try using the `HEX-Editor` plugin for Notepad++ or another Hex editor program.
