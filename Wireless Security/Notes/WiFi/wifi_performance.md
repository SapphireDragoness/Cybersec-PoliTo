# WiFi Performance

## 802.11 comparison table

| Standard     | Max Speed (Mbps) | Frequency Band(s) | Channel Bandwidth | Modulation Type(s)                     |
|--------------|------------------|--------------------|--------------------|----------------------------------------|
| 802.11a      | 54               | 5 GHz              | 20 MHz             | OFDM                                    |
| 802.11b      | 11               | 2.4 GHz            | 22 MHz             | DSSS, CCK                               |
| 802.11g      | 54               | 2.4 GHz            | 20 MHz             | OFDM (fallback to DSSS/CCK)            |
| 802.11n      | 600              | 2.4 / 5 GHz        | 20 / 40 MHz        | OFDM + MIMO                             |
| 802.11ac     | 6,933            | 5 GHz              | 20 / 40 / 80 / 160 MHz | OFDM + MIMO + 256-QAM              |
| 802.11ad     | 6,760            | 60 GHz             | 2.16 GHz           | SC, OFDM                                |
| 802.11ax     | ~9,600           | 2.4 / 5 / 6 GHz    | 20 / 40 / 80 / 160 MHz | OFDMA + MIMO + 1024-QAM          |
| 802.11be     | ~46,000          | 2.4 / 5 / 6 GHz    | 20 to 320 MHz      | OFDMA + MIMO + 4096-QAM                 |

## Goodput

Given the capacity C at the physical layer, we define the goodput as the speed at which useful data (stripped of protocol headers) is received at the application layer:

$$G=\frac{useful\_data}{transfer\_time}<C$$

Several components can reduce goodput:

- shared physical link with other protocols and congestion
- errors, packet drops...
- protocol overhead

Theoretical maximum throughput (or maximum goodput):

$$G<\mu_{protocol}C$$

## Impact of Protocol Headers

- TCP adds 20 bytes of overhead and segments data stream
- IPv4 adds 20 bytes of overhead
- Ethernet adds 38 bytes: 8 (trailer + SoF) + 6 (MAC) + 6(MAC) + 2 (Type) + 4 (CRC) + 12 (IPG)

So 58 bytes of overhead. Each packet contains 1460 bytes of data, thus the packet efficiency is:

$$\mu_{TCP}\leq\frac{data}{transmitted\_data}=\frac{1460}{160+58}=94,2\%$$

## How to Compute Minimum Transfer Time

### Method 1

From bandwidth curve graph get **efficiency** by intersecting modulation and MDSU.

**Goodput G** is: $\frac{message\_length}{message\_length+overhead}\times efficiency$

**Minimum transfer time** is: $\frac{filesize\_in\_bits}{G}$

### Method 2

From TMT curve graph get **TMT** by intersecting modulation and MDSU.

**Goodput G** = TMT.

**Minimum transfer time** is: $\frac{filesize\_in\_bits}{G}$
