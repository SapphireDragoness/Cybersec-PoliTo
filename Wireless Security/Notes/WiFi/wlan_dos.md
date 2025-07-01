# DoS in WLAN

There are two main types of DoS in 802.11:

- L1: RF Attacks or Jamming the wireless spectrum - disruption occurs when signal-to-noise ratio reaches a certain level
- L2: Protocol-based attacking - the higher layers of communication (Identity and Media-access control)

## Identity Vulnerabilities

802.11 nodes are identified at MAC layer by unique address as wired nodes are, though frames are not authenticated: an attacker can change his MAC address and spoof other nodes. This leads to three kinds of attacks:

- disassociation attack
- deauthentication attack
- power saving mode attack

## Disassociation Attack

The disassociation frame can be spoofed, causing the AP to disassociate the client.

## Deauthentication Attack

An attacker can spoof the deauthentication message causing the communication between AP and client to suspend, causing a DoS. The attack can be executed on individual client or all clients:

- individual clients: attacker spoofs client’s address telling AP to deauthenticate them
- all clients attacker spoofs AP telling all clients to deauthenticate

Solutions:

- delay honoring Deauthentication request: requires no protocol changes and is backwards compatible
- create a "signature" to validate the client deauthentication request: SNR, sequence number can be part of the signature

Deauthentication is more effective than Disassociation, as it requires 2 RTTs to resume communication, instead of 1.

## Media Access Vulnerabilities

Attacker can send signal before every SIFS slot to clog the channel.

## NAV Vulnerability

In RTS/CTS, a client first sends a RTS, which includes a duration (NAV period). The duration indicates the number of microseconds for which the channel is reserved, and is tracked per node via Network Allocation Vector (NAV). Nodes are allowed to transmit when NAV reaches 0.

An attacker can forge packets with large durations. When NAV is broadcasted by AP, no node can transmit.

Solution: determine maximum reasonable NAV values for all frames (legitimate duration values are small).

## Attacks on Power Saving

Nodes can sleep to conserve energy, and the AP will buffer clients’ packets until requested with a poll message. 

TIM (traffic indication map) is a periodic packet sent by AP to notify client of buffered data.

Three possible attacks:

- attacker spoofs on behalf of AP the TIM message: client could think there is no data and go back to sleep
- attacker forges management sync packets: causes  client to fall out of sync with AP
- attacker spoofs on behalf of the client: AP sends data while client is sleeping