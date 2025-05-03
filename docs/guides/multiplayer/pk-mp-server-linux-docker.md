# Painkiller 2004 Linux Game Server in Docker

> You can find the code [here](https://github.com/t3r6/pkserver-docker/).

The goal of the project was to make the 32-bit Painkiller Linux server work on most 64-bit Linux operating systems without any hassle.

Docker fits this purpose because it isolates containers from the host system.

!!! Warning
    Before you start to launch a server, please note that in order to see servers advertised on OpenSpy directly in the game browser, you need a patched Painkiller client DLL. Please check the details [**here**](./gamespy-openspy.md).

## Overview

1. Binary Hacks. The original Linux `pkserver` binary from People Can Fly is very limited. It starts with the hardcoded `+dedicatedserver +map +port` parameters which cannot be overriden and only accepts the `+interface` and `+private` command line options. You are not able to pass custom `-lscripts` and `-cfg`. However, it's possible hack the `pkserver` binary to accept custom `LScripts.pak` and `config.ini`. The method is described [here](../hacking/hack-linux-bin.md).
This Docker image contains that binary hack.

2. Docker environment variables. The Docker image also has a script that allows to pass the `Cfg_` environment variables to the Docker container that will override parameters in the default `config.ini` with the similar names. For example, you can pass the `Cfg_ServerPort` variable and it will override the `Cfg.ServerPort` parameter in the `config.ini` file.

3. Outdated `gamespy.com` was replaced with `openspy.net` in the binary as well.

4. The Docker image contains LScripts for PK++ 1.2 and PK++ 1.3 competition [**mods**](https://www.moddb.com/mods/pk).

    > PK++ 1.2 is compatible with the original Painkiller while PK++ 1.3 server requires a client to have PK++ 1.3 mod installed.

5. Added semi-official competitive maps Meatless and Blink.

!!! Note
    The Painkiller server listens on `3455` UDP port by default. The game also listens on the `3578` UDP port for LAN discovery. If you increment your multiplayer port by one, like in `3456`, the LAN port will also be incremented by the game automatically to `3579`.
    You only need to publish the LAN port in Docker if you run a clent and a server on the same machine which is unlikely.

## Environment

> A Docker container is a running instance of a Docker image. When you run a Docker image, it becomes a Docker container.

This Docker image can be used on most 64-bit Linux distributions.

I tested Docker containers on Ubuntu 22.04.4 LTS on Virtual Box 7.0.18 with Bridged Adapter and promiscuous mode. The containers were also launched on a production Ubuntu 24.04 LTS server.

## Supported Architectures

* Linux AMD64 (x86-64)
* Linux ARM64

The Docker image is based on Debian. Unlike Ubuntu, Debian still has a very good support for 32-bit applications on AMD64 and ARM64 OS.

## Prerequisites

* [Docker Engine with Docker Compose](https://docs.docker.com/engine/install/)
* Optional: [QEMU](https://www.qemu.org/download/) for multi-platform builds

!!! Warning
    [Podman](https://podman.io/docs/installation) and [Podman Compose](https://github.com/containers/podman-compose) are not recommended due to potential issues with the default bridge network. Moreover, Podman doesn't directly manage restart policies and instead depends on systemd since Podman does not have its own deamon. However, Podman woks fine with the host network plugin. Pay attention that Docker cannot see Podman images and vice versa so better stick to one tool.

The Docker installation guides are a bit confusing. It's enough to install Docker Engine. Docker Desktop is only for systems with GUI and is optional.

1. Install Docker Engine. Here is the guide for [Ubuntu](https://docs.docker.com/engine/install/ubuntu/). The Docker Compose plugin is already included in the default Docker plugin list.

2. Don't forget the [Linux post-installation steps](https://docs.docker.com/engine/install/linux-postinstall/) to manage Docker as a non-root user.

3. Check that the Docker daemon is running:

    ```
    sudo systemctl status docker.service
    ```

!!! Note
    QEMU emulation is only necessary if you want to build an ARM64 image on a AMD64 machine.

## Quick start with Docker Compose

Docker Compose is a fast and convenient way to declaratively configure multiple containers. It uses [YAML](https://docs.ansible.com/ansible/latest/reference_appendices/YAMLSyntax.html) configuration file that have strict indentations. You can run multiple servers with one command, no additional scripts are required.

The `docker-compose.yml` is provided in the repository as a template. Most parameters are preconfigured.

!!! Note
    Pay attention to the `Cfg_ServerPort` variable or the `Cfg.ServerPort` parameter in the `config.ini` file. The port should be different for each server. If you, for example, run several servers on the same port, other containers will crash.

> **Issue**: Docker Compose mounts files as folders.<br>
**Solution**: indicate the path to the custom file with dot/slash, for instance: `source: ./DM_K3Inzane.pkm`.

1. Copy the `docker-compose.yml` file from the [repository](https://github.com/t3r6/pkserver-docker) to your host.

2. Make necessary changes. For example, leave only one server.

3. Open necessary ports on your system.

4. Run the following command in the same directory:

    ```
    docker compose up -d
    ```

    It will launch preconfigured server/servers.

    !!! Note
        You can also rename and specify a custom file while running docker compose:

        ```
        docker compose -f painkiller-docker-compose.yml up -d
        ```

5. Stop and remove the servers:

    ```
    docker compose down
    ```

    Or

    ```
    docker compose -f painkiller-docker-compose.yml down
    ```

> That's the bare minimum you need to know to launch your servers. The below profound information is necessary to understand how Docker works, how to manage it, what solutions were implemented in the Docker image, and how to build your own Docker image.

## Quick start with Docker

By default, Docker uses the [bridge network](https://docs.docker.com/network/drivers/bridge/) wich has its own subnet range. This network requires you to publish ports. Alternatively, you can use the [host network](https://docs.docker.com/network/drivers/host/) which uses the IP addresses of your host network. You don't need to publish ports in case of the host network. However, you may need to pass `+interface` or `Cfg_NetworkInterface` to the Docker container if you have multiple interfaces on your host. This will tell the `pkserver` binary to run on a particular IP address that has access to the internet.

### Docker default bridge network

!!! Warning
    Podman may not work properly with the bridge network plugin. I recommend using Docker with this type of network.

!!! Note
    The Docker image is published to Docker Hub and to GitHub Container Registry.
    Use the one which is more convenient for you:

    `ghcr.io/t3r6/pkserver:main`<br>
    `docker.io/painkillergameclassic/pkserver:main`

1. Start a server with the `ffa` name. This command will automatically pull the Docker image from Docker Hub and start a Docker container on your machine. The LAN port `3578` is published as an example and is not required:

    ```
    docker run --rm --name ffa -itd -p 3455:3455/udp -p 3578:3578/udp docker.io/painkillergameclassic/pkserver:main
    ```

    !!! Note
        `--rm` means that the container will be removed once you stop it.<br>
        `--name ffa` assignes the `ffa` name to the container.<br>
        `-it` improves the interaction with the container.<br>
        `-d` detaches your container to the background so it does not occupy your terminal session.<br>
        `-p` publishes the UDP port in our case. The host port is mapped to the container port.<br>

2. Check that the container with the pkserver is running:

    ```
    $ docker container ls

    CONTAINER ID   IMAGE                                 COMMAND           CREATED         STATUS         PORTS                                                 NAMES

    e9191538423b   painkillergameclassic/pkserver:main   "entrypoint.sh"   8 seconds ago   Up 7 seconds   0.0.0.0:3455->3455/udp, :::3455->3455/udp, 3578/udp   ffa

    ```

    Check the port the container is running on:

    ```
    $ ss -tuln | grep 3455

    udp   UNCONN 0      0            0.0.0.0:3455       0.0.0.0:*
    udp   UNCONN 0      0               [::]:3455          [::]:*
    ```

3. Open and forward the default Painkiller 3455 port in your firewall if required. For example, if you run a server on a Virtual machine. Please check this [**guide**](./router-config.md) on port forwarding. I suggest opening several ports beforehand in case of multiple servers: 3455, 3456, 3457.

4. Modify your firewall, iptables, AppArmor, SeLinux if you amended them before and blocked traffic. For example, open a range of ports on Ubuntu:

    ```
    sudo ufw allow 3455:3457/udp
    ```

5. Check if your game is advertised on [OpenSpy](https://openspy.net/server-list/painkiller).

6. Open the Painkiller game client and join a server.

    !!! Note
        It's likely that you won't see your own server in the in-game browser if you run the server and the clinet on the same machine so join it via IP.
        ```
        /connect ip
        ```

7. Stop the container named `ffa`:

    ```
    docker container stop ffa
    ```

8. Remove the stopped container. Usually, this is not required since the `--rm` option removes the conatainer once you stop it. However, in some cases your container could get stuck so better double-check. Run the following command to check the failed containers:

    ```
    docker container ls -a
    ```

    Remove the failed containers:

    ```
    docker container prune
    ```

### Docker host network

Docker and Podman work equally well on this type of network.

In case you have any issues with the default Docker bridge network, like errors connected with [NATNEG](https://github.com/openspy/openspy-core/issues/21), try the Docker host network. In this case, you'll need to indicate the IP of your network adapter that has access to the internet if you have multiple devices (192.168.0.106 in my example). Run the following command to check the network interfaces:

```
~$ ip --brief address show

lo               UNKNOWN        127.0.0.1/8 ::1/128 
enp0s3           UP             192.168.0.106/24 fe80::91ee:4f1b:1582:d667/64 
docker0          UP             172.17.0.1/16 fe80::42:78ff:fecd:b400/64 
```

It's the IP address of the `enp0s3` interface in my case.

Launch a Docker container with the following command:

```
docker run --rm --name ffa -itd -e Cfg_NetworkInterface="192.168.0.106" --net=host docker.io/painkillergameclassic/pkserver:main
```

Alternative command:

```
docker run --rm --name ffa -itd --net=host docker.io/painkillergameclassic/pkserver:main +interface 192.168.0.106
```

### Running on a different port

In case you need to run a game on a different port, use Docker port mapping and the `Cfg_ServerPort` variable.

!!! Warning
    Note that Painkiller GameSpy backend is outdated which can cause issues with the [NATNEG](https://wiki.tockdom.com/wiki/Network_Protocol/Server/mariokartwii.natneg.gs.nintendowifi.net) protocol. Thus, we must map the same Docker ports on the container and the host and also change the port in the Painkiller config.ini.
    For instance, with this command the client will get errors when connecting to your server via the in-game browser:
    ```
    docker run --rm --name ctf -itd -p 3456:3455/udp  docker.io/painkillergameclassic/pkserver:main
    ```
    Pay attention that we map the `3456` port on the host to the `3455` Docker container port. The clinet will get the following error:
    ```
    NAT Negotiation error: Partnet did not register with the NAT Negotiation Server
    ```
    Nevertheless, a clinet should be able to connect to your server by running manually the `/connect ip:port` command in the game console.

    It seems that the game tells OpenSpy that it is up on port `3455`, while `3456` port is mapped from the docker engine to the host system, but this is not an address translation, but simply a port mapping. Apparently, NATNEG is trying to negotiate through port `3455` when the negotiation should be through `3456`.

The below commands work and do not produce connection errors.

#### Custom ports with the Docker default bridge network

```
docker run --rm --name ffa -itd -p 3456:3456/udp -e Cfg_ServerPort="3456" docker.io/painkillergameclassic/pkserver:main
```

#### Custom ports with the Docker host network

```
docker run --rm --name ffa -itd -e Cfg_ServerPort="3456" -e Cfg_NetworkInterface="192.168.0.106" --net=host docker.io/painkillergameclassic/pkserver:main
```

## Building

### Build Docker image from a Dockerfile

1. Clone or download the github [repository](https://github.com/t3r6/pkserver-docker).

2. Modify files if required. You can put additional maps, modify `config.ini`, hack `pkserver` binary beforehand, add your own scripts, make amendments to the Dockerfile.

3. Run the following command:

    ```
    docker build . --no-cache -t pkserver:v1
    ```

    !!! Note
        `dot` is an indication that you build the Docker image from the Dockerfile in this directory.<br>
        `-t/--tag` is the name of your future local Docker image.<br>
        `--no-cache` does not use cache.<br>

    To build from a Dockerfile with a custom name:

    ```
    docker build -f custom.Dockerfile . --no-cache -t pkserver:v1
    ```

4. Check the built Docker images:

    ```
    docker image ls
    ```

### Run a server after the build

1. Start a server with the `ffa` name:

    ```
    docker run --rm --name ffa -itd -p 3455:3455/udp pkserver:v1
    ```

2. Check that the container with the server is running:

    ```
    docker container ls
    ```

    !!! Note
        If you don't see a container with this command, try to run:

        ```
        docker container ls -a
        ```

        It's high likey that your container exited with an error. You'll need to investigate the error, make fixes and re-build the image again.

3. Stop the `ffa` container:

    ```
    docker container stop ffa
    ```

### Push your image to the container registry

You should be registered to either [GitHub](https://docs.github.com/en/packages/working-with-a-github-packages-registry/working-with-the-container-registry) or [Docker Hub](https://hub.docker.com/).

1. Register in any of the mentioned services.

2. Re-tag your Docker image with:

    ```
    docker image tag pkserver:v1 yourregistryname/pkserver:v1
    ```

3. Log in to the registry:

    ```
    docker login
    ```

4. Push your image to the registry:

    ```
    docker push yourregistryname/pkserver:v1
    ```

## Run containers with different parameters

### Using config variables

You can pass variables to the container instead of modifying the `config.ini` file. Each variable corresponds to the `Cfg` parameter in `config.ini` and should start with `Cfg_`. The letter case does not matter, except for special `PKS_` variables.
For example, `Cfg.ServerPort` corresponds to `CFG_SERVERPORT` or `Cfg_ServerPort`, `Cfg.NetworkInterface` to `CFG_NETWORKINTERFACE` or `Cfg_NetworkInterface`. However, `PKS_LSCRIPTS` should be passed with capital letters only. Let's start a `PK++ 1.3` server on a `3456` port:

```
docker run --rm --name ffa -itd -p 3456:3456/udp -e Cfg_ServerPort="3456" -e PKS_LSCRIPTS='PKPlus13.pak' docker.io/painkillergameclassic/pkserver:main
```

### Run a server with a custom config

#### Bind a custom host config to the default pkserver config

Docker containers are ephemeral. It means that when you restart a container, all the information will be lost and you start from scratch. If you are NOT going to use the `Cfg_` variables with a container, you need to bind a `config.ini` file from the outside to the Docker container. The simplest way would be to use the [bind mounts](https://docs.docker.com/storage/bind-mounts/) Docker feature. As an alternative, you can use the Docker volumes but I found this method inconvenient for the Painkiller server management since you cannot insert data directly into a volume without copying it to a container.

1. Copy `./pkserver/Bin/config.ini` from the repository to your host, for example, to `${HOME}/my_pkserver/config.ini`.

2. Make sure the file has the right permissions:

    ```
    chmod 664 config.ini
    ```

3. You can leave the file as is or rename it whatever you like. Let's rename it to `config_ffa.ini`.

4. Run the server with the following commands. You bind `config_ffa.ini` on your host machine to `config.ini` in the Docker container:

    ```
    export PKS_CFG_SOURCE="${HOME}/my_pkserver/config_ffa.ini"
    docker run --rm --name ffa -itd --mount type=bind,source=${PKS_CFG_SOURCE},target=/opt/pkserver/Bin/config.ini -p 3455:3455/udp docker.io/painkillergameclassic/pkserver:main
    ```

#### Bind a custom host config to the custom pkserver config

!!! Note
    This hack is outdated.

1. Modify `${HOME}/my_pkserver/config.ini` to your needs and rename this file to something like `conctf.ini`.

    !!! Warning
        When the `PKS_CFG` variable is used, you can only give a custom name to `config.ini` with the exact 6 letter size because scripts in this image hacks the binary, for example, you can rename it to `conffa.ini`, `conctf.ini` but you cannot name it `myconfig.ini`.

2. Run the server with the following commands:

    ```
    export PKS_CFG_SOURCE="${HOME}/my_pkserver/conctf.ini"
    docker run --rm --name ffa -itd -e PKS_CFG="conctf.ini" --mount type=bind,source=${PKS_CFG_SOURCE},target=/opt/pkserver/Bin/conctf.ini -p 3455:3455/udp docker.io/painkillergameclassic/pkserver:main
    ```

    If you connect to the Docker container, there will be `conctf.ini` inside the `/opt/pkserver/Bin` directory. The `pkserver` binary will use `conctf.ini` instead of the default `config.ini` file:

    ```
    painkiller@2d2e79d33500:/opt/pkserver$ ls Bin/
    conctf.ini  config.ini  id.bin  pkserver

    ```

### Run a server with custom LScripts

#### Run PK++

The Docker image has 2 custom packages: `./pkserver/Data/PKPlus12.pak` for `PK++ 1.2` and `./pkserver/Data/PKPlus13.pak` for `PK++ 1.3`.

!!! Warning
    Note that unlike PK++ 1.2, PK++ 1.3 is not backward compatible with the original Painkiller.
    A client should run PK++ 1.3 to connect to the PK++ 1.3 server.

In order to run a specific version of the mod, pass the package name to the CLI via the `PKS_LSCRIPTS` Docker variable:

```
docker run --rm --name ffa -itd -p 3455:3455/udp -e PKS_LSCRIPTS='PKPlus13.pak' docker.io/painkillergameclassic/pkserver:main
```

#### Run a custom server mod

It is possible to use LScripts packs with custom names; however, you'll need to either bind them using bind mounts, copy to volumes, or add them to `./pkserver/Data/` and rebuild the Docker image.

!!! Warning
    You can only give a custom name to `LScripts.pak` with the exact 8 letter size because it's a hack, for example, you can rename it to `LScript3.pak` but you cannot name it `MyLScripts.pak`.

1. Make sure the file has the right permissions:

    ```
    chmod 664 LScript3.pak
    ```

2. Run the custom pak with this command:

    ```
    export PKS_LSCRIPTS_SOURCE="${HOME}/my_pkserver/LScript3.pak"
    docker run --rm --name ffa -itd -p 3455:3455/udp -e PKS_LSCRIPTS="LScript3.pak" --mount type=bind,source=${PKS_LSCRIPTS_SOURCE},target=/opt/pkserver/Data/LScript3.pak docker.io/painkillergameclassic/pkserver:main
    ```

### Run a server with custom maps

Let's say you put a custom map to `${HOME}/my_pkserver/DM_K3Inzane.pkm` on your host machine:

1. Make sure the file has the right permissions:

    ```
    chmod 664 DM_K3Inzane.pkm
    ```

2. Bind a map from the host to the Docker container with this command:

    ```
    export MAP1_SOURCE="${HOME}/my_pkserver/DM_K3Inzane.pkm"
    docker run --rm --name ffa -itd -p 3455:3455/udp --mount type=bind,source=${MAP1_SOURCE},target=/opt/pkserver/Data/DM_K3Inzane.pkm docker.io/painkillergameclassic/pkserver:main
    ```

    !!! Note
        You can't bind multiple maps with one command as Docker does not support wildcards with bind mounts. Each map should be bound one by one. It can be simplified with Docker Compose.

## Run multiple containers based on the same image

You can run multiple server instances based on the same image by giving them different names and passing different ports. Setting the `Cfg_ServerPort` variable is the most convenient way.

Let's say I want to launch 3 servers (FFA, DUEL, CTF) on different ports using the same Docker image. The examples are simplified since I don't pass any additional configuration variables and don't use any bind mounts:.

1. Run the containers:

    ```
    docker run --rm --name ffa -itd -p 3455:3455/udp docker.io/painkillergameclassic/pkserver:main
    ```

    ```
    docker run --rm --name duel -itd -e Cfg_ServerPort="3456" -p 3456:3456/udp docker.io/painkillergameclassic/pkserver:main
    ```

    ```
    docker run --rm --name ctf -itd -e Cfg_ServerPort="3457" -p 3457:3457/udp docker.io/painkillergameclassic/pkserver:main
    ```

2. Check the containers are running:

    ```
    docker container ls
    ```

    Check if there are failed containers:

    ```
    docker container ls -a
    ```

3. Stop and delete all containers:

    ```
    docker stop $(docker ps -a -q)
    docker rm $(docker ps -a -q)
    ```

## Using Docker volumes

This is an alternative to bind mounts. I find this way of managing the Painkiller server redundant since it will take additional space of your hard drive and prevents your configs from being "clean".

If you need your files to be persisted independently of the container state and bind mounts are not the option, you need to use the [Docker volumes](https://docs.docker.com/storage/volumes/).

The default Docker anonymous volumes get deleted automatically when you remove the Docker container. That's not what you want.

Named Volumes allow you to save your server data independently of the container state and mount them to other containers.

1. Create a named volume:

    ```
    docker volume create pk-data-ffa
    ```

2. Start a container with a volume:

    ```
    docker run --rm --name ffa -itd -p 3455:3455/udp --mount source=pk-data-ffa,target=/opt/pkserver docker.io/painkillergameclassic/pkserver:main
    ```

3. Remove the resources:

    ```
    docker container stop ffa

    docker volume rm pk-data-ffa
    ```

It is not advised to copy and delete files directly from Docker volumes. In order to add files, you need to use the [docker cp](https://docs.docker.com/reference/cli/docker/container/cp/) command. If you want to delete them, you'll need to log in to the container and remove the files from there.

## Managing server logs and stats

This step is useful if you need to keep logs and you don't use Docker volumes.

To manage `pkserver` logs and stats, you need to create a cron job that periodically copies LOG and TXT files from a container to your host.

`pkserver` keeps them in the `/opt/pkserver/Bin/` directory. In this example, we copy LOG and TXT files from the container with the `ffa` name to the `HOME` directory on the host:

```
docker exec ffa bash -c 'tar -cf - /opt/pkserver/Bin/*.log /opt/pkserver/Bin/*.txt' | tar --strip-components 3 -C ${HOME} -xvf -
```

## Managing server resources

### Resource limits

`pkserver` has memory leaks. It is advised to set [RAM limits](https://docs.docker.com/config/containers/resource_constraints/) on a container (250 MB for Duels and not more than 400 MB for FFA):

```
docker run --rm --name ffa -itd -p 3455:3455/udp --memory="400m" docker.io/painkillergameclassic/pkserver:main
```

Check the container stats:

```
docker stats
```

Exit stats with `Ctrl + C`.

### Restart policy

!!! Note
    Restart policy option only works with `docker` by default. If you want to use restart policies with `podman`, you need to run `podman generate systemd --restart-policy container_id` or find another workaround.

A restart policy is useful to keep your Docker containers up even after the system reboot.

Set the container [restart policy](https://docs.docker.com/config/containers/start-containers-automatically/):

```
docker run --name ffa -itd -p 3455:3455/udp --memory="400m" --restart always docker.io/painkillergameclassic/pkserver:main
```

If you container got stuck in a loop of restarts, run this command to turn off the restart policy:

```
docker update --restart=no ffa
```

## Mini Dockerfile

This image is for rare cases. It is a solution when you want to run a "classic" server but you have issues with installing 32-bit packages on your system.

This is merely a wrapper around the `pkserver` package. It is implied that you have the full [pkserver](https://www.moddb.com/games/painkiller/downloads/painkiller-linux-server-164-full-openspy) package on your host and use Docker bind mounts to mount every folder to the Docker container.

1. Building:

    ```
    docker build -f mini.Dockerfile . --no-cache -t pkserver-mini:v1
    ```

2. Launching. Since the Linux Painkiller server has soft links, you need to bind them to the Docker container as well. Let's assume you installed `pkserver` to the `${HOME}/pkserver/` directory:

    ```
    docker run --rm -it --name mini -p 3455:3455/udp --mount type=bind,source="${HOME}"/pkserver/Bin,target=/opt/pkserver/Bin --mount type=bind,source="${HOME}"/pkserver/bin,target=/opt/pkserver/bin --mount type=bind,source="${HOME}"/pkserver/Data,target=/opt/pkserver/Data --mount type=bind,source="${HOME}"/pkserver/data,target=/opt/pkserver/data pkserver-mini:v1
    ```

## Debug a container

1. Pass the `+private` parameter to test Docker containers without exposing them to OpenSpy:

    ```
    docker run --rm --name ffa -itd -p 3455:3455/udp docker.io/painkillergameclassic/pkserver:main +private
    ```

2. To gracefully stop your server so that it won't dangle on OpenSpy, you need to attach to your container and run the `/quit` command:

    ```
    docker container attach ${container_name}
    ```

    To detach again, press `CTRL + P` followed by `CTRL + Q`.

3. You can enter your container with:

    ```
    docker exec -it ${container_name} bash
    ```

    To exit a container, type:

    ```
    exit
    ```

4. Enter a failed container by changing Docker entrypoint:

    ```
    docker run -it --entrypoint=bash ${container_name}
    ```

5. Log in to a container as a root:

    ```
    docker exec -it -u 0 ffa bash
    ```

    You can then install all the required tools in the container with:

    ```
    apt-get update && apt-get install
    ```

6. To ping from a container, you need to enable some [container capabilities](https://docs.docker.com/engine/reference/run/#runtime-privilege-and-linux-capabilities). Add `--cap-add=IPC_LOCK --cap-add=NET_RAW` as a command line options when starting a new container:

    ```
    docker run --rm --name ffa -itd --cap-add=IPC_LOCK --cap-add=NET_RAW -p 3455:3455/udp docker.io/painkillergameclassic/pkserver:main
    ```

7. To copy inside/outside containers use [docker cp](https://docs.docker.com/reference/cli/docker/container/cp/).

8. Clean your system from all Docker user packages:

    ```
    docker system prune -a
    ```
