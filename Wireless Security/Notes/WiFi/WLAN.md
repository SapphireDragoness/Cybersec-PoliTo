# WLAN: WiFi

## Key Features of the 802.11 protocol

Before a mobile station can send traffic through an AP, it must be in the appropriate connection state:

- Neither authenticated nor associated
- Authenticated but not yet associated
- Authenticated and associated

802.11 authentication is the first step in network attachment. It  requires a mobile device (station) to establish its identity with an AP. No No data encryption or security is available at this stage.

Once authentication is complete, mobile devices can associate (register) with an AP/router to gain full access to the network. Association allows the AP/router to record each mobile device so that frames are properly delivered. A station can only associate with one AP/router at a time.

Data exchange can happen only after the authentication and association are completed, using CSMA/CA.

## Authentication and Association

Authentication and association process:

1. AP (optionally) broadcasts beacon frames to advertise the SSID of the WLAN to wireless clients. Beacon frames are sent periodically by an access point.
2. Probes are used by the STA to find a WLAN network. Probes are sent by client stations on multiple channels. A client can also send a probe with no SSID specified, and all access points that receive the probe will respond except those with broadcast SSID disabled. The access point responds with a probe response that includes the SSID, supported data rates and security standard.
3. Once a WLAN is found, the STA performs the Authentication and Association processes for establishing the data link with AP.
4. A STA must first authenticate with one (or more) AP(s). Authentication can happen with multiple APs in case of an infrastructure with multiple APs (Extended Service Set).
5. Once authenticated, it then associates with ONE (and only one) AP.

Authentication can be:

- open system: first, an authentication request is sent from the STA that contains the station ID (typically the MAC address); next, an authentication response from the AP with a success or failure message
- shared key: a shared key, or passphrase, is manually set on both the mobile device and the AP/router

Association process:

- STA sends an Association Request
- AP processes the Association Request and decides if a client request should be allowed
- When an AP/router grants association, it responds with a status code of 0 (successful) and the Association ID (AID),  used to identify the station for delivery of buffered frames when power-saving is enabled
- Failed Association Requests include only a status code, and the procedure ends

## CSMA/CA

CSMA/CA handles the hidden terminal problem:

- B, A can hear each other
- B, C can hear each other
- A, C cannot hear each other, so A, C are unaware of their interference at B

802.11 doesn't perform collision avoidance due to weak received signals (fading), so it must avoid collision altogheter.

802.11 sender:

1. if the channel is sensed idle for a certain amount of time (DIFS), then transmit entire frame
2. if the channel is sensed busy, then start random backoff time: timer counts down while channel idle transmit when timer expires
3. if no ACK, increase backoff interval and repeat step 2

802.11 receiver: 

1. if frame is received, then return ACK after a certain amount of time (SIFS)

To avoid collisions completely, a channel can be reserved:

1. Sender first transmits small request-to-send (RTS) packets to BS using CSMA
2. BS broadcasts clear-to-send CTS in response to RTS

## Advanced Capabilities

### Rate Adaptation

Base station and mobile dynamically change transmission rate (physical layer modulation technique) as mobile moves, SNR varies.

### Power Management

If node tells AP it's going to sleep, AP knows not to transmit frames to this node.

Beacon frame contains a list of mobiles with AP-to-mobile frames waiting to be sent. The node will stay awake if there are AP-to-mobile frames to be sent; otherwise sleeps again until the next beacon frame.