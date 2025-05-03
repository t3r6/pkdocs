# How to play trick jump maps online

!!! Note
    This guide describes the steps for the original Painkiller and the official PK++ 1.2 and PK++ 1.3 mods.

No trick jump mods for Painkiller Black Edition multiplayer were released as of now so you have to play using the default game modes. That's how the old custom Painkiller trick jump maps were designed. There was an attempt to add a Race gamemode to PK++ 1.2.5 but it was never finished.

## Maps

Painkiller currently has only 2 trick jump [maps](https://www.moddb.com/games/painkiller/addons/trickjump-and-race-maps-for-painkiller) and their variations:

- `DM_JumpMap_01` by shadow
- `DM_Mandra_RUN` by Mandragora

## Warmup types

There are 2 types of warmups in Painkiller which is a bit confusing: **WarmUp** and **Warmup**.

- **WarmUp** is sort of a waiting room. It is limited in time and does not give you all the weapons.

- **Warmup** (where 'up' is in a lower case) does not have time limit unless you click *Ready* and gives you all the weapons.

You need a game mode that supports DM maps and Warmup. Those are Team Deathmatch, Duel, and Last Man Standing.

**Duel** only supports 2 players at a time and **Team Deathmatch** has a distracting Warmup HUD so **Last Man Standing** is preferable.

## Prerequisites

!!! Note
    Trick jump maps better work on clean servers without PK++. However, it's still possible to complete such maps on a PK++ server.

A server should have the following settings:

- `Cfg.NoWarmup = false` which is `false` by default. The `false` parameter enables the Warmup.

- `Cfg.UserGameMode = true` which is `true` by default. This allows you to vote a game mode.

## How to play

1. Join the server with the enabled Warmup.
2. Vote a gamemode (`lms` stands for **Last Man Standing**) in the game console (backtick key):

    `/callvote gamemode lms`

    Other players should acknowledge the change and type:

    `/vote yes`

3. Once the server changed the gamemode, vote for a map:

    `/callvote map dm_jumpmap_01`

4. The Warmup damage is disabled by default in the original Painkiller game, if the server runs PK++, vote to disable the Warmup damage:

    `/callvote warmupdamage 0`

5. If you stuck or want to reset your position, type in the console:

    `/kill`

6. If you accidentally clicked that you are *Ready* and Warmup is reset, you'll need to reload a map:

    `/callvote reloadmap`

7. *Recommended*. You can change the way you gain speed and height from rocket jumps by turning off the **RocketFix** PK++ feature. RocketFix is usually enabled on PK++ servers. Although it's still possible to beat race maps with RocketFix on, turning off this fix on a trick jump server could immensely help in finishing those maps. Run the following command to disable it:

    `/callvote rocketfix 0`

8. *Optional*. You can disble PK++ feature ProPlus. This feature is enabled on PK++ servers by default and it reduces the jump height a little and how rockets work in general. Run the following command to disable it:

    `/callvote proplus 0`

9. *Optional*. You can enable an alternative way of doing rocket jumps with the **Forward Rocket Jump** standard Painkiller feature. This will allow you to use special button that performs a rocket jump in one click. Forward Rocket Jump is usually turned off on PK++ servers. Run the following command to enable it:

    `/callvote allowforwardrj 1`

## Tips

You can enable speed meter by typing `/speedmeter 1` via the in-game console to track your speed. Use additional HUD scripts to track the [movement keys](pk-hud-movement-compass.md).
