# Hack Painkiller 2004 Linux Game Server Binary

[pkserver](https://www.moddb.com/games/painkiller/downloads/painkiller-linux-server-164-full-openspy) Linux binary has very limited capabilities.

It seems that it can only accept `+interface` and `+private` parameters.

Alternatively, you can indicate the corresponding interface parameter `Cfg.NetworkInterface` in the `config.ini` without passing `+interface` to the binary.

On the other hand, `Cfg.PublicServer` does not seem to affect `pkserver` at all and only works when passed explicitly to the binary via the `+private` parameter.

The main drawback of `pkserver` is that it cannot accept custom `LScripts.pak` and custom `config.ini`.

Since the game code is closed, we cannot fix it programmatically. However, we can hack the binary with the Hex editor.

!!! Note
    Examine the `pkserver` directory. Pay attention that Linux is case-sensitive, unlike Windows. Developers linked `bin` to `Bin` and `data` to `Data`:

        ```
        [login@shell opt]$ cd pkserver
        [login@shell pkserver]$ ls -al

        total 20
        drwxr-xr-x 5 painkiller     painkiller     4096 Jun 12 06:38 .
        drwxrwxr-x 4 painkiller     painkiller     4096 Jun 12 06:50 ..
        lrwxrwxrwx 1 painkiller     painkiller        3 Feb  4  2005 bin -> Bin
        drwxr-xr-x 2 painkiller     painkiller     4096 Jun 11 14:05 Bin
        lrwxrwxrwx 1 painkiller     painkiller        4 Mar 25  2005 data -> Data
        drwxr-xr-x 7 painkiller     painkiller     4096 Jun 11 14:05 Data
        drwxr-xr-x 2 100999 100999 4096 Jun 12 06:38 pkserver

        ```

## Hack config

### Using Hex editor

If you want to use a different `config.ini` with your binary, do the following:

1. Copy the `pkserver` binary with a different name, for example, `pkserver13`.

2. Open the copied and renamed `pkserver13` file with any Hex editor and replace `config.ini` with `conf13.ini`.

    !!! Warning 
        The length of the `config.ini` name should be the same - 6 letters or less.
        For instance, you can name it as `conf13.ini` but you cannot name it `myconfig.ini`.
        If the config name is less than 6 letters, you need to replace it with consequent binary nulls.
        The size of the file should not be changed.

3. Save the file. Now the `pkserver13` binary will only accept a config with the name `conf13.ini` located in the `pkserver/Bin` directory.

### Using Binary Block Editor

An alternative way of hacking is to use the [bbe](https://linux.die.net/man/1/bbe) Linux tool.

Download the tool and run the following commands:

```
bbe -e 's/config.ini/conf13.ini/' pkserver > pkserver13
chmod 755 pkserver13
```

## Hack LScripts

`lscripts.pak` is a soft link to `LScripts.pak`. The game checks for `LScripts.pak`, but loads `lscripts.pak`.

Let's assume, you want to use a custom `LScript3.pak` with the custom `pkserver13` binary.

You can either create a symlink from `lscript3.pak` to `LScript3.pak` and replace all instances of `lscripts.pak` with `lscript3.pak` and `LScripts.pak` with `LScript3.pak` in the `pkserver13` binary.

However, I suggest replacing both `LScripts.pak` and `lscripts.pak` with `LScript3.pak`. No symlinks will be required in this case and the game will load the correct package.

### Using Hex editor

1. Copy the `pkserver` binary with a different name, for example, `pkserver13`.

2. Open the copied and renamed `pkserver13` file with any Hex editor and replace all `LScripts.pak` and `lscripts.pak` instances with `LScript3.pak`.

    !!! Warning 
        The length of the `LScripts.pak` name should be the same - 8 letters or less.
        For instance, you can name it as `LScript3.pak` but you cannot name it `MyLScripts.pak`.
        If the config name is less than 8 letters, you need to replace it with consequent binary nulls.
        The size of the file should not be changed.

### Using Binary Block Editor

```
bbe -e 's/LScripts.pak/LScript3.pak/' pkserver > pkserver_temp
bbe -e 's/lscripts.pak/LScript3.pak/' pkserver_temp > pkserver13_temp
mv pkserver13_temp pkserver13
chmod 755 pkserver13
```

## Change GameSpy to OpenSpy

If you have the original `pkserver` binary, the same way you can replace all instances of `gamespy.com` with `openspy.net`.
