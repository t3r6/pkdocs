# Setup Painkiller Overdose Windows server

Painkiller Overdose does not have an official Linux server so it's only possible to host a server on Windows. This is one of the reasons that no one hosts servers for this game nowadays.

This guide will give you step-by-step instructions on how to set up the Painkiller Overdose Windows server and play with your friends.

Here is a brief description of the game releases. The official international versions of the game were:

- 66.2 [Demo](https://www.moddb.com/games/painkiller-overdose/downloads/painkiller-overdose-single-and-multiplayer-demo)
- 75.3
- 84.4

These are the only recommended versions to host your server.

There also were several versions in-between 75.3 and 84.4 from the local publishers but the additional singleplayer and multiplayer game content was only introduced in 84.4.

This unofficial version of the [**patch**](https://www.moddb.com/games/painkiller-overdose/downloads/painkiller-overdose-patch-753-to-84) will upgrade your game to 84.4 from 75.3 and it already incorporates the Gamespy fix.

It's also worth mentioning the competition multiplayer mod called [**PROverdose**](https://www.moddb.com/games/painkiller-overdose/downloads/proverdose-03) made by OriOn and PrimeviL which was intended to be similar to PK++ for the original Painkiller.

At the time of writing, PROverdose only supports Overdose 66.2 (Demo) and 75.3, thus if you have the game from GOG or Steam, you need to downgrade it to 75.3 with this [**patch**](https://www.moddb.com/games/painkiller-overdose/downloads/painkiller-overdose-downgrade-patch-from-844-to-753) to be able to play Overdose multiplayer with the PROverdose mod (optional).

## Windows Server Setup

The server setup includes the following steps:

* Router configuration
* Windows Firewall configuration (optional)
* Openspy configuration
* Server launching
* PROverdose setup (optional)

### [Router configuration](router-config.md)

If you use a router, you need to forward a port to the Overdose server. The game's default port is `4974` but you can change it to another one. I highly recommend reserving a local IP address for this purpose. Please refer to this [**guide**](router-config.md) for more information on the router configuration.

I'll take the local IP `192.168.0.104` in further examples.

### [Firewall configuration]((od-firewall-config.md))

This step is not always required. In my case, all worked without this configuration. However, you may need to create firewall inbound and outbound rules for the game via TCP and UPD protocols. Refer to this [**information**](od-firewall-config.md) for more details.

