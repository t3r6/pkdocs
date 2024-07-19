# Router Configuration for Painkiller Multiplayer Server

Routers vary in configuration so I'll describe the router configuration on my TP-Link router.

Basically, you need to allow the incoming connection from a client to your server on an indicated port. The default port for the original **Painkiller** is `3455` and for **Painkiller Overdose** it is `4974`. However, you can change a port in the game.

Home routers do not usually block any outgoing traffic but firewalls can so you may need to create the firewall inbound and outbound rules for the game via TCP and UDP protocols. Inbound rules are required so that the client can connect to your server while outbound rules are required for the Painkiller game to advertise its server to `openspy.net` master servers and send packets to the client properly. From my experience, I did not have to configure the OS firewall at all.

The scheme shows how the traffic flows from a client to a server.

``` mermaid
flowchart BT
  A{{Client}} -->|50.153.139.143:3455| B[Router External IP];
  B -->|192.168.0.104:3455| C[OS Firewall];
  C -->|TCP, UDP| D{{Server Internal IP}};
  D --> E[OS Firewall];
  E -->|TCP, UDP| F[Router External IP];
  F -.-> A;
  F -.-> J([openspy.net]);
  J -.-> A;
```

*From the scheme above let's assume that `50.153.139.143` is your external IP address, `3455` is the default Painkiller port, `192.168.0.104` is the IP address of your local server*.

## Configuration

In the following instruction, we will reserve the internal IP address and forward a Painkiller/Overdose port to it.

1. Open Windows `CMD`/`Powershell` or Linux Terminal and type in the `hostname` command to find out your PC name. Alternatively for Windows, the hostname can be checked in the Windows System properties.
2. Access your router. In my case, it is `http://192.168.0.1/` via a web browser. It may vary depending on your router model.
3. Click `DHCP` -> `DHCP Clients` and locate your PC hostname. You'll see something like this:

    | ID | Client name | Mac address       | Assigned IP address | Address lease time |
    |----|-------------|-------------------|---------------------|--------------------|
    | 1  | MyPC        | 09-9A-D9-48-6C-DC | 192.168.0.104       | 01:21:48           |

    !!! Note
        You may have a different assigned IP address and the Mac address.

4. Go to `DHCP` -> `IP reservations`, click `Add` and assign an IP address to the Mac address of your PC:

    | ID | Mac address       | Reserved IP address | Status  |
    |----|-------------------|---------------------|---------|
    | 1  | 09-9A-D9-48-6C-DC | 192.168.0.104       | Enabled |

5. Restart your router. Then if you go back to `DHCP` -> `DHCP Clients`, you'll see that the `Address lease time` is permanent for `192.168.0.104`.

6. Now go to `Port Forwarding` -> `Virtual servers` -> `Add` and forward a port to the internal IP address of your PC server for TCP and UDP protocols (usually opening UPD protocol will be enough):

    | ID | Service port | Internal port | IP address    | Protocol | Status  |
    |----|--------------|---------------|---------------|----------|---------|
    | 1  | 3455         | 3455          | 192.168.0.104 | TCP      | Enabled |
    | 2  | 3455         | 3455          | 192.168.0.104 | UDP      | Enabled |
    | 3  | 4974         | 4974          | 192.168.0.104 | TCP      | Enabled |
    | 4  | 4974         | 4974          | 192.168.0.104 | UDP      | Enabled |

    !!! Note
        Some routers have the `All` option under `Protocol` that includes both TCP and UDP.

        The default port for **Painkiller** is `3455` and for **Painkiller Overdose** it is `4974`.

7. Check the connection. I will not go into the details but the UDP connection can be checked with `nc`/`ncat` and `nmap` (change the IP address and the port accordingly):

    ```
    ncat -vnzu 50.153.139.143 3455
    ```

    The result will look similar to this:

    ```
    Connection to 50.153.139.143 3455 port [udp/*] succeeded!
    ```

    or

    ```
    Ncat: UDP packet sent successfully
    ```

    Scan the port with `nmap`:

    ```
    nmap -sU -v -p 3455 50.153.139.143
    ```

    The port should be open in the response:

    ```
    PORT     STATE         SERVICE
    3455/udp open|filtered prsvp
    ```
