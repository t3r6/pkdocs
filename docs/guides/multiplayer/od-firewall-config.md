# Firewall Configuration for Painkiller Overdose Multiplayer Server

You may need to create the firewall inbound and outbound rules for the game via TCP and UDP protocols. Inbound rules are required so that the client can connect to your server while outbound rules are required for the Painkiller game to advertise its server to `openspy.net` master servers and send packets to the client properly. From my experience, I did not have to configure the OS firewall at all.

Here is the scheme that shows where the firewall can filter the traffic.

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

The Painkiller Overdose game has 3 EXE files `Overdose.exe`, `OverdoseEditor.exe`, and `OverdoseServer.exe`. We will mostly use `Overdose.exe` for the dedicated server but it is desirable to create rules for all 3 of them since they all can be used to host a server.

I'll describe the configuration of the Windows Defender Firewall only.

## Windows Defender Firewall

The rule can be added manually but the quickest way is to add those Windows Defender Firewall rules via Powershell in the Administrator mode (change the path to your game directory):

```
$pkOverdosePath = "C:\Games\Painkiller Overdose\Overdose.exe"
$pkOverdoseEditorPath = "C:\Games\Painkiller Overdose\OverdoseEditor.exe"
$pkOverdoseServerPath = "C:\Games\Painkiller Overdose\OverdoseServer.exe"
```

### Inbound rules

```
New-NetFirewallRule -Program "$pkOverdosePath" -DisplayName "Painkiller Overdose TCP" -Description "Painkiller Overdose TCP" -Protocol TCP -Direction Inbound -Profile Public -Action Allow
```

```
New-NetFirewallRule -Program "$pkOverdosePath" -DisplayName "Painkiller Overdose UDP" -Description "Painkiller Overdose UDP" -Protocol UDP -Direction Inbound -Profile Public -Action Allow
```

```
New-NetFirewallRule -Program "$pkOverdoseEditorPath" -DisplayName "Painkiller Overdose Editor TCP" -Description "Painkiller Overdose Editor TCP" -Protocol TCP -Direction Inbound -Profile Public -Action Allow
```

```
New-NetFirewallRule -Program "$pkOverdoseEditorPath" -DisplayName "Painkiller Overdose Editor UDP" -Description "Painkiller Overdose Editor UDP" -Protocol UDP -Direction Inbound -Profile Public -Action Allow
```

```
New-NetFirewallRule -Program "$pkOverdoseServerPath" -DisplayName "Painkiller Overdose Console Server TCP" -Description "Painkiller Overdose Console Server TCP" -Protocol TCP -Direction Inbound -Profile Public -Action Allow
```

```
New-NetFirewallRule -Program "$pkOverdoseServerPath" -DisplayName "Painkiller Overdose Console Server UDP" -Description "Painkiller Overdose Console Server UDP" -Protocol UDP -Direction Inbound -Profile Public -Action Allow
```

### Outbound rules

```
New-NetFirewallRule -Program "$pkOverdosePath" -DisplayName "Painkiller Overdose TCP" -Description "Painkiller Overdose TCP" -Protocol TCP -Direction Outbound -Profile Public -Action Allow
```

```
New-NetFirewallRule -Program "$pkOverdosePath" -DisplayName "Painkiller Overdose UDP" -Description "Painkiller Overdose UDP" -Protocol UDP -Direction Outbound -Profile Public -Action Allow
```

```
New-NetFirewallRule -Program "$pkOverdoseEditorPath" -DisplayName "Painkiller Overdose Editor TCP" -Description "Painkiller Overdose Editor TCP" -Protocol TCP -Direction Outbound -Profile Public -Action Allow
```

```
New-NetFirewallRule -Program "$pkOverdoseEditorPath" -DisplayName "Painkiller Overdose Editor UDP" -Description "Painkiller Overdose Editor UDP" -Protocol UDP -Direction Outbound -Profile Public -Action Allow
```

```
New-NetFirewallRule -Program "$pkOverdoseServerPath" -DisplayName "Painkiller Overdose Console Server TCP" -Description "Painkiller Overdose Console Server TCP" -Protocol TCP -Direction Outbound -Profile Public -Action Allow
```

```
New-NetFirewallRule -Program "$pkOverdoseServerPath" -DisplayName "Painkiller Overdose Console Server UDP" -Description "Painkiller Overdose Console Server UDP" -Protocol UDP -Direction Outbound -Profile Public -Action Allow
```

Go to `Control Panel\System and Security\Windows Defender Firewall` -> `Advanced settings` to check the created rules.
