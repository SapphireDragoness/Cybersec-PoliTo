# WEP

## How not to secure a WLAN

- MAC authentication is useless: MAC are sent in broadcast in clear text (sniffing)+ MAC can be cloned (replay)
- Static IP addresses are useless: IP addresses are sent in clear text (sniffing) => easy to find and use a valid IP address
- SSID hiding is useless: SSID are sent in clear text in probe request/response and association response
- Smart antenna placement and hiding is useless: attackers have infinite resources and use much more powerful devices than yours

The only solutiion is cryptography.

## Wired Equivalent Privacy Goals

WEP is a set of security schemes introduced as part of the original IEEE 802.11 wireless networking standard in September 1997. It was intended to  protect wireless confidentiality comparable with that of a traditional wired network and intended to achieve the following security goals:

- **message confidentiality** via encryption
- **access control** via shared password authentication
- **data integrity** via checksum

### Properties of the WEP Algorithm

- **Reasonably strong**: The security afforded by the algorithm relies on the difficulty of discovering the secret key through a brute-force attack. This in turn is related to the length of the secret key (usually expressed in bits) and the frequency of changing keys. However, it may be an easier problem to discover k through statistical methods if the key sequence remains fixed and significant quantities of ciphertext are available to the attacker. WEP avoids this by frequently changing the IV and hence k.
- **Self-synchronizing**: Provided by the IV. This property is critical for a data-link level encryption algorithm, with "best effort" delivery and packet loss rates that can be high.  An algorithm that assumes reliable delivery to maintain synchronization between sender and receiver would not provide acceptable performance.
- **Efficient**: The WEP algorithm is very efficient in comparison to traditional block ciphers.  It uses few resources and can be implemented efficiently in either hardware or software.
- **Free IP**
- **Exportable**

## WEP Access Control

Two authentication methods can be used with WEP:

- open system authentication
- shared key authentication

WEP requires the STA to be authenticated by the AP before association. The authentication process is based on a simple challenge-response protocol.

1. The client sends an authentication request to the access point.
2. The access point replies with a clear-text challenge.
3. The client encrypts the challenge-text using the configured WEP key and sends it back in another authentication request.
4. The access point decrypts the response. If this matches the challenge text, the access point sends back a positive reply.

Once authenticated, the STA can send an association request and the AP will respond with an association response.

Open system is more secure than shared key, as keys are used only for frame encryption and not for authentication!

## WEP Integrity and Confidentiality

WEP utilizes Cyclic Redundancy Check (CRC)-32 checksum to provide **data integrity** to WLAN transmissions: an Integrity Check Value (ICV) is added to each frame.

WEP **confidentiality** is provided by encrypting message before transmission. The cryptographic encryption algorithm is RC4 algorithm, the same as the one for WEP authentication process.

RC4 is initialized with the shared secret. For each message to be sent:

- RC4 produces a pseudo-random byte sequence
- the pseudo-random byte sequence is XORed to the message

It is ESSENTIAL that each message is encrypted with a different key stream. The RC4 generator is initialized with the shared secret and an IV:

- Shared secret is the same for each message
- 24-bit IV changes for every message

## Key Management

Two kinds of keys are allowed by the standard:

- Default key (also called shared key, group key, multicast key, broadcast key)
- Key mapping keys (also called individual key, per-station key, unique key)

The default key is a group key, and group keys need to be changed when a member leaves the group (e.g. change the password).

WEP supports multiple default keys to help the smooth change of keys:

- One of the keys is called the active key -> used to encrypt messages
- Any key can be used to decrypt messages

The message header contains a key ID that allows the receiver to find out which key should be used to decrypt the message.

## WEP Security Problems

The following is a list of security problems in WEP:

- authentication is one-way only: only STA has to authenticate itself to AP
- the same shared secret key is used for both authentication and encryption
- possible collisions due to the simplicity of CRC-32
- IV can be reused and keys can be weak
- lacks a centralized controller to manage large number of STAs

### WEP flaws – Authentication and Access Control

Authentication in WEP is based on a challenge-response protocol:

- AP sends a plaintext challenge $r$ to STA
- STA responds by encrypting the challenge: $IV|r\oplus K$ ($K$ is a 128-bit RC4 output on IV and the shared secret)

An attacker can compute $r\oplus(r\oplus K)=K$, then it can reuse the same $K$ to impersonate STA later.

### Rogue Access Point

A fake AP can impersonate a real AP and intercept all traffic.

If the AP uses open system authentication, all the attacker needs to do is to broadcast the same SSID with stronger signal.

If the AP uses shared key WEP, the attacker has to crack the key.

### WEP flaws – Integrity and replay protection

There’s no replay protection at all, and the CRC can be exploited.

CRC is a linear function with respect to XOR: $CRC(X\oplus Y) = CRC(X) \oplus CRC(Y)$

If a CRC-32 valid plaintext is XORed with a ciphertext, the modified message will pass the ICV check after decryption:

- attacker observes $(M | CRC(M)) \oplus K$ where $K$ is the RC4 output
- for any $\Delta M$, the attacker can compute $CRC(\Delta M)$
- $((M | CRC(M)) \oplus K) \oplus (\Delta M | CRC(\Delta M)) = ((M \oplus \Delta M) | (CRC(M) \oplus CRC(\Delta M))) \oplus K = ((M \oplus \Delta M) | CRC(M \oplus \Delta M)) \oplus K$

An attacker can then mount the following attacks:

- change IP destination address to D2 (reroute attack)
- TCP payload discover (check if ACK is sent back -> TCP CRC correct => discover 1 bit of payload)

### ChopChop attack

Given an encrypted packet, the attacker can recover the original content by altering one byte at a time.

1. Capture a WEP-encrypted packet (e.g., an ARP packet).
2. Strip the last byte of the encrypted packet.
3. Guess the value of the missing last plaintext byte (brute-force through all 256 possibilities).
4. For each guess:
   - Adjust the ICV (Integrity Check Value) accordingly.
   - Re-encrypt the modified packet using the same IV.
   - Inject the packet into the network.
   - Observe the AP's response: if accepted, the guess was correct, if rejected, try the next guess.
5. Repeat the process one byte earlier in the packet until you’ve decrypted the whole packet.

### IV Reuse

IVs are only 24 bits, so there are only $2^{24}$ unique IVs. Collisions occur when an IV is reused and so the same RC4 key stream is used to encrypt the data.

This allows an attacker to build a decryption table for statistical attacks

### Weak Key

For some seed values, the beginning of RC4 output isn't random: if a weak key is used, the first few bytes of the output reveals a lot of information about the key, so breaking the key is a lot easier.
