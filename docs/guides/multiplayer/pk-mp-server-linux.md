# Setup Painkiller Black Edition Linux Multiplayer Dedicated Server

!!! Warning
    This setup was tested on Ubuntu 22.04. Some 32-bit packages were removed from Ubuntu 24.04 repositories so you'll need to download and install them manually but it's not within the scope of this guide.

*A short remark for a beginner*. A server is a computer (host) that provides information to other computers called clients. So when you create a game, your PC is a "server" and those who join it are the "clients".

This guide implies that you are familiar with Linux OS.

The People Can Fly videogame company provided an official Linux server for Painkiller. It's more stable than the Windows server and it's much cheaper to host, that's why all the dedicated servers are mostly on Linux. However, this binary is 32-bit and has its own drawbacks which we'll discuss below.

The official packages for the Linux server are **Painkiller Linux Server 1.62** and its patch **Painkiller Linux Server 1.64 Update** provided as separate TAR archives. The **pkserver** binary was integrated with the outdated GameSpy server discovery network.

It's not convenient to work with those official packages so I made a combined pack based on the official ones.

## Prerequisites

Your Linux OS should support 32-bit applications.

1. Log in to your server.

2. Prepare Ubuntu 22.04 server to accept 32-bit architecture since `pkserver` was compiled for 32-bit systems. You may need to run this command as a root with `sudo`:

    ```
    dpkg --add-architecture i386
    ```

3. Install additional 32-bit packages. You may need to run the commands as a root with `sudo`:

    ```
    apt-get update
    apt-get install -y zlib1g:i386 libncurses5:i386 libstdc++5:i386
    ```

## Installation

1. Download the Painkiller Linux server package [here](https://www.moddb.com/games/painkiller/downloads/painkiller-linux-server-164-full-openspy). This pack already has a modified `pkserver` binary that advertises its servers to OpenSpy.

    !!! Note
        If you want to use clean official packages, they can be downloaded [here](https://www.patches-scrolls.com/painkiller.php). In this case, you'll need an extra step of replacing all the GameSpy instances in a binary or modifying an `/etc/hosts` file which is described in the [GameSpy to OpenSpy](gamespy-openspy.md) guide.

2. Connect to your server and upload the archive with an FTP program like Total Commander or `scp` to a Linux directory, for example, `/opt`.

3. Go to your `/opt` directory:

    ```
    [login@shell ~]$ cd /opt
    ```

4. Unpack the files:

    ```
    [login@shell opt]$ tar -zxfv pkserver_linux_1.64_openspy.tar.gz
    ```

5. You'll get the `pkserver` directory. Remove the archive:

    ```
    [login@shell opt]$ ls
    pkserver_linux_1.64_openspy.tar.gz pkserver
    ```

    ```
    [login@shell opt]$ rm pkserver_linux_1.64_openspy.tar.gz
    ```

6. Examine the `pkserver`directory. Pay attention that Linux is case-sensitive, unlike Windows. `bin` is linked to `Bin` and `data` is linked to `Data`. It was done this way so you can easily navigate and feel it like in Windows:

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

7. Enter the `Bin` directory with `cd`:

    ```
    [login@shell pkserver]$ cd Bin
    ```

8. Run `ls` to see two files: `config.ini` – the server settings, `pkserver` – executable file.

    ```
    [login@shell Bin]$ ls
    config.ini  pkserver
    ```

9. Find out which network interface in your server has access to the Internet:

    ```
    $ ip --brief address show
    lo               UNKNOWN        127.0.0.1/8 ::1/128
    enp0s3           UP             192.168.0.106/24 fe80::91ee:4f1b:1582:d667/64
    ```

    !!! Note
        If your server is behind NAT, like in this example, forward the necessary port (the default port in Painkiller is `3455`) like it's described in this [guide](router-config.md).

10. Make sure you don't have any firewall rules preventing a client from connecting to your server and so that the game port is not occupied:

    ```
    netstat -tuplen
    iptables -L -vn
    ```

    Also, make sure that your provider is not blocking certain IP ranges.

11. Start `pkserver` with the `+interface` parameter. Enter the IP address of the network interface that has access to the Internet:

    ```
    [login@shell Bin]$ ./pkserver +interface 192.168.0.106
    Free For All
    >

    ```

    !!! Note
        It is possible to run `pkserver` without the `+interface` parameter; however, in this case, you'll need to replace all your localhosts in your `/etc/hosts` file with your interface `192.168.0.106`. This is not recommended. Example:

        ```
        $ cat /etc/hosts
        # 127.0.0.1     localhost
        # 127.0.1.1     VirtualBox
        192.168.0.106   painkiller
        ```

    !!! Note
        Under the hood, `pkserver` automatically uses `+dedicatedserver +map +port` parameters. You won't be able to override those.
        Moreover, this binary does not accept the "-" options, like `-config` or `-lscripts`. This is an oversight by the developers.

12. You can connect to your server either via the local IP (if there is a NAT configuration) or the public IP. The port can be omitted if it is default 3544:

    ```
    /connect 192.168.0.106:3544
    ```

13. To stop the server enter the command `/exit`:

    ```
    >
    /exit
    [login@shell Bin]$
    ```

## Install PK++ (Painkiller competition mod)

1. Download [**PK++**](https://www.moddb.com/mods/pk). You can either use PK++ 1.3 which has more features or PK++ 1.2.1.64 which is more stable and compatible with the original.

    !!! Warning
        if you want your server to be compatible with the original 1.64 client as well as PK++ 1.3 client, you need a PK++ 1.2 server.

        PK++ 1.3 server requires a PK++ 1.3 client and is not compatible with the default 1.64 or PK++ 1.2 client.

2. Since `pkserver` binary does not accept the `-lscripts` parameter, you have to replace `LScripts.pak` with the renamed `PKPlus.pak` from PK++. Hacking `pkserver` binary is also possible but it's out of the scope of this guide. 

    Download the PK++ `PKPlus.pak`, rename it and replace the original `LScripts.pak` with it in the `pkserver/Data` directory. It can be done with one command in Linux:

    ```
    mv PKPlus.pak /opt/pkserver/Data/LScripts.pak
    ```

3. Start the server and you'll see bots:

    ```
    [login@shell Bin]$ ./pkserver +interface 192.168.0.106
    Free For All
    Grrr has entered the arena.
    Grrr is ready.
    Rumbraugh has entered the arena.
    Rumbraugh is ready.
    Rumbraugh is now in team: Red.
    Grrr is now in team: Blue.
    Match Started.
    >

    ```

## Configure rcon

**RCON** is a tool to manage a game server.

When you play Painkiller you can use it in the game.

In the configuration file `config.ini` that's on the server and in `config.ini` that's on your PC, configure the same password in `Cfg.RconPass` to have admin privileges. Type in `/rcon` in the console to use it, examples:

*change a map*
```
/rcon map DM_Lockout
```

*restart a map*
```
/rcon restartmap
```
