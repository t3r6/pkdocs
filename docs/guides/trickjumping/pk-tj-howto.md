# How to play trick jump maps online

!!! Note
    This guide describes the steps for the original Painkiller and the official PK++ mods.

No trick jump mods for Painkiller Black Edition multiplayer were released as of now so you have to play using the default game modes. That's how the old custom Painkiller trick jump maps were designed. There was an attempt to add a Race gamemode to PK++ 1.2.5 but it was never finished.

Now we have an alternative - `DM_RACE` maps.

## Maps

Painkiller currently has only 2 trick jump [**maps**](https://www.moddb.com/games/painkiller/addons/trickjump-and-race-maps-for-painkiller) and their variations (`DM_RACE`, `DM`, `RACE`):

- `DM_JumpMap_01` by shadow
- `DM_Mandra_RUN` by Mandragora

## Race maps in FFA

The modern and convenient way to play trickjump maps is by using `DM_RACE` maps. Such maps are compatible with any server and any client.

### `DM_RACE` maps

I created `DM_RACE` maps with custom scripts that can be played in the usual FFA mode.

Just run the `DM_RACE` map the usual way in the FFA mode.

The only thing that you may need to change when playing those is disabling `RocketFix`:

```
/callvote rocketfix 0
```

If you are stuck or want to reset your position, type in the console:

```
/kill
```

## Race maps in Warmup (outdated)

Back in the day, Painkiller `DM` trickjump maps were played in Warmup.

### Warmup types

There are 2 types of warmups in Painkiller which is a bit confusing: **WarmUp** and **Warmup**.

- **WarmUp** is sort of a waiting room. It is limited in time and does not give you all the weapons.

- **Warmup** (where 'up' is in a lower case) does not have time limit unless you click *Ready* and gives you all the weapons.

You need a game mode that supports DM maps and Warmup. Those are Team Deathmatch, Duel, and Last Man Standing.

**Duel** only supports 2 players at a time and **Team Deathmatch** has a distracting Warmup HUD so **Last Man Standing** is preferable.

### Prerequisites

A server should have the following settings:

- `Cfg.NoWarmup = false` which is `false` by default. The `false` parameter enables the Warmup.

- `Cfg.UserGameMode = true` which is `true` by default. This allows you to vote a game mode.

### How to play

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

8. *Optional*. You can enable an alternative way of doing rocket jumps with the **Forward Rocket Jump** standard Painkiller feature. This will allow you to use special button that performs a rocket jump in one click. Forward Rocket Jump is usually turned off on PK++ servers. Run the following command to enable it:

    `/callvote allowforwardrj 1`

## Race maps in the Race mode (outdated)

Currently, those `RACE` maps can only be played in [PK++ by Thresher](https://www.moddb.com/mods/painkiller-pk-archive/downloads/pk-12-revised-race-mode-by-thresher).

1. Install the usual PK++ 1.2.1.64 first.

2. Copy .pak files from the Builds folder of this archive to `..\Painkiller\Data`

3. Copy maps from the Maps directory to `..\Painkiller\Data`

4. Create a game shortcut with the following parameter: `..\Painkiller\Bin\Painkiller.exe -lscripts PKplusplus_1.2_004.pak`
where you can use a different `.pak` version as well.

5. Run map `RACE_Psycho` in the RACE mode.

6. Kick all bots

    ```
    /botminplayers 0
    /kickallbots
    ```

7. Change the map:

    ```
    /callvote map RACE_JumpMap_01
    ```

## Tips

You can enable speed meter by typing `/speedmeter 1` via the in-game console to track your speed. Use additional HUD scripts to track the [movement keys](pk-hud-movement-compass.md).

## Links

[Trickjump **maps**](https://www.moddb.com/games/painkiller/addons/trickjump-and-race-maps-for-painkiller)

[PK++ RACE](https://www.moddb.com/mods/painkiller-pk-archive/downloads/pk-12-revised-race-mode-by-thresher)