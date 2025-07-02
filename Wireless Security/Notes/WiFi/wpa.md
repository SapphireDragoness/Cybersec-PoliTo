#  WPA

802.11i is the successor to WEP:

- defines the concept of Robust Security Network: integrity protection and encryption is based on AES
- defines an optional protocol called TKIP (Temporal Key Integrity Protocol): integrity protection is based on Michael 1(and not CRC-32), encryption is still based on RC4, but WEP problems have been avoided -> runs on old hardware

The first is WPA2, the second WPA.

## 802.1X Authentication Model

It defines the encapsulation of the Extensible Authentication Protocol (EAP) over IEEE 802 standard, which is also known as EAPoL (EAP over LAN).

It consist of three main parties:

- **supplicant**: requests access to the services (wants to connect to the network)
- **authenticator**: controls access to the services (controls the state of a port)
- **authentication server**: authorizes access to the services

1. the  supplicant authenticates itself to the authentication server
2. if the authentication is successful, the authentication server instructs the authenticator to switch the port on
3. the authentication server informs the supplicant that access is allowed

One more thing is added to the basic 802.1X model in 802.11i: successful authentication results not only in switching the port on, but also in a session key between the mobile device and the authentication server.

## Protocols – EAP, EAPOL, and RADIUS

### EAP  (Extensible Authentication Protocol) 

EAP is the carrier protocol designed to transport the messages of real authentication protocols, like TLS.

EAP has four types of messages:

- EAP request: carries messages from the supplicant to the authentication server
- EAP response: carries messages from the authentication server to the supplicant
- EAP success: signals successful authentication
- EAP failure: signals authentication failure

STA <-> auth server

### EAPOL (EAP over LAN)

EAPoL encapsulates EAP messages into LAN protocol, and is used to carry EAP messages between the STA and the AP.

STA <-> AP

### RADIUS (Remote Access Dial-In User Service)

RADIUS carries EAP messages between the AP and the auth server. It is mandated by WPA and optional for RSN.

AP <-> auth server

## Auth Protocols – LEAP, EAP-TLS, PEAP, EAP-SIM

**LEAP** is a lighter version of EAP developed by Cisco.

**EAP-TLS**: only the TLS Handshake Protocol is used, and TLS master secret becomes the session key.

**PEAP**: TLS Handshake without client authentication and then  client authentication protected by the secure channel.

**EAP-SIM**: extended GSM authentication in WiFi context, uses SIM

## 802.11i Access Control

WPA supports two authenticated key management protocols:

- WPA-personal: uses a pre-shared key (PSK) for authentication
- WPA-enterprise: requires centralised RADIUS authentication server

## Keys and Key Management

### Pairwise Master Key (PMK)

Used to derive all other keys. Can be:

- preshares (WPA personal)
- negotiated (WPA enterprise)

### Pairwise Transient Key (PTK)

Used for encryption and integrity checks in unicast user data, and to protect 4-way handshake.

It is computed by combining:

- PMK
- AP nonce
- STA nonce
- AP MAC address
- STA MAC address

into a pseudo-random function.

The PTK is transient because every time a client associates with the AP, a new PTK is derived.

### Group Master Key (GMK) and Group Transient Key (GTK)

The GMK is generated randomly within the AP. The GTK is then derived (in the AP) from the GMK. The GTK is used for broadcast message transmissions between STA and AP.

## Four-way Handshake

Goal: prove that AP also knows the PMK (result of authentication) -> mutual authentication!

### Step 1: AP -> STA

- AP generates random nonce: Anonce
- AP sends Anonce to STA

The Anonce is sent unencrypted!

### Step 2: STA -> AP

- STA generates random nonce: Snonce
- STA computes the PTK using Anonce, Snonce, AP MAC and STA MAC
- STA sends Snonce and MIC (Message Integrity Code) computed using KCK (Key Confirmation Key), which is half of the PTK

MIC prevents message tampering.

### Step 3: AP -> STA

- AP computes PTK using Anonce, Snonce, AP MAC and STA MAC
- AP validates MIC by computing KCK and comparing received MIC with computed MIC
- AP generates GTK
- AP sends GTK, replay counter and MIC to STA and asks STA to install PTK and GTK

This message is encrypted and proves the AP also knows the PMK.

### Step 4: STA -> AP

- STA validates MIC by computing KCK and comparing received MIC with computed MIC
- STA decrypts and installs GTK and PTK
- STA sends ACK to AP, unencrypted but with MIC

On ACK received, AP verifies MIC and installs PTK and GTK

## Attacks Against WPA

### Brute Force

The WPA/WPA2 4-Way Handshake can be attacked via brute-force or dictionary attacks. These attacks don’t exploit weaknesses in the handshake protocol itself, but rather weaknesses in how the PMK is derived (such as a weak passphrase).

What the attacker needs:

- four-way handshake packets
- SSID of the network
- offline cracking tools

In WPA2-personal, the password is converted to PMK via PBKDF2. With an 8-character alphanumeric password, only $2^{48}$ guesses are needed.

## Integrity and Confidentiality in TKIP Mode

TKIP still uses RC4 and the core function so that it can be backward compatible to legacy devices, but it corrects the flaws in WEP so that the security is enhanced in three aspects:

- CRC-32 is still applied as the ICV to the message, but a 64-bit MIC is also computed and appended to the message. The MIC is computed using a function named Michael (a keyed hash function)
- The IV space is increased to 48 bits in TKIP to prevent IV reuse. The IV is also used as a sequence counter to prevent replay attacks
- TKIP applies per-packet keys instead of using the pre-shared key to prevent attacks based on weak keys. The packet key is a hash of the PTK + IV (packet sequence number)

In addition, TKIP implements a key mixing function that combines the secret root key (PTK) with the initialization vector before passing it to the RC4 cipher initialization (not just simple concatenation as done in WEP).

### TKIP Weaknesses

TKIP is vulnerable to a MIC key recovery attack that, if successfully executed, permits an attacker to transmit and decrypt arbitrary packets on the network being attacked:

- this attack is an extension of the WEP chop-chop attack
- because CRC-32 is an insecure checksum mechanism, an attacker can guess individual bytes of a packet, and the wireless access point will confirm or deny whether or not the guess is correct
- however, with TKIP, the attacker must wait for at least 60 seconds after an incorrect guess because if two incorrect Michael MIC codes are received within 60 seconds, the access point will implement countermeasures, meaning it will rekey the TKIP session key, thus changing future keystreams

## Integrity and Confidentiality in AES-CCMP Mode

AES-CCMP mode is the standard encryption protocol for use with the WPA2 standard:

- CCMP uses Counter Mode with CBC-MAC (CCM) for data confidentiality
- CCMP uses CBC-MAC for authentication and integrity
- CCMP encryption is based on AES processing and uses a 128-bit key and a 128-bit block size (block mode)

## KRACK Attack on WPA2

During the 4-Way Handshake, the client installs the Pairwise Transient Key (PTK) after receiving message 3.

However, message 3 can be replayed. If it is, some clients will reinstall the same PTK, resetting associated variables like nonces and replay counters.

Attack flow:

1. STA connects to Wi-Fi, handshake proceeds as normal.
2. Attacker captures and blocks Message 4 (STA to AP).
3. AP thinks Message 4 was lost, so it resends Message 3.
4. Some vulnerable clients reinstall the PTK again upon receiving the replayed Message 3. This also resets the packet nonce counter.
5. Now, when the victim sends data:
   - The encryption key is the same.
   - The nonce is reused.
6. Attacker captures multiple encrypted packets with reused nonce/key.
7. Attacker decrypts packets, possibly injects fake ones.

## Opportunistic Wireless Encryption

OWE is meant to encrypt traffic in open or public networks. It uses the Diffie-Hellman algorithm and HKDF to establish PMK -> no predetermined password!

OWE flow:

1. Client and AP exchange public keys (Elliptic Curve Diffie-Hellman).
2. Each derives a shared secret.
3. This secret is used to derive a Pairwise Master Key (PMK).
4. The rest of the handshake (4-Way) proceeds as if WPA2-Personal was used, but without a PSK.
5. All traffic is encrypted with AES-CCMP (or GCMP) per-client.

OWE by itself does not offer mutual authentication.

## Simultaneous Authentication of Equals (SAE)

SAE provides more robust password-based authentication, even when the password is "weak". It also protects against bruteforce attacks.

SAE is based on elliptic-curve Diffie-Hellman. Because the PSK generated in the SAE process is for authentication only, the protocol offers forward secrecy!

SAE is just OWE but with a password:

1. STA computes random x, AP computes random y
2. STA computes $g^x$ (where g is derived as a function of password (and MAC addrs)), and AP computes $g^y$
3. STA and AP exchange public keys
4. From the public keys, AP and STA can compute common secret
5. PMK is a hash of the common secret and other labels
6. Four-way handshake proceeds as usual

SAE does not prevent online dictionary attack, but it makes it impractical.