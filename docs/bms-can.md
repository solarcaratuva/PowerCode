# BMS CAN

## CAN Buses

| CAN Bus | Use |
| :---: | :---:|
| 1 | Custom CAN Messages |
| 2 | Battery Cell Broadcast |

## CAN Settings

| Setting | Value |
| :---: | :---: |
| Baud Rate | 500 kbps |
| OBDII ECU Identifier | 0x7E3 |
| Battery Cell Broadcast Identifier | 0x36 |

See the Orion BMS software manual for descriptions and limits for all CAN Settings.

## CAN Messages

| Message # | Description | Length (bytes) | ID | Priority | Rate (ms) |
| :---: | :---: | :---: | :---: | :---: |  :---: |
| 1 | Errors | 3 | 0x01 | Highest | 24 |
| 2 | Battery Status | 7 | 0x02 | Middle | 16 |
| 3 | BPS Status | 7 | 0x03 | Lowest | 8 |

### Message 1 Structure

| Field | Length (bytes) | Byte Location | Units |
| :---: | :---: | :---: | :---: |
| Custom Flag 0 | 1 | 0 | N/A |
| Custom Flag 1 | 1 | 1 | N/A |
| Custom Flag 2 | 1 | 2 | N/A |

### Message 2 Structure

| Field | Length (bytes) | Byte Location | Units |
| :---: | :---: | :---: | :---: |
| Pack Current | 2 | 0-1 | 0.1 A |
| Pack Voltage | 2 | 2-3 | 0.1 V |
| Pack SOC | 1 | 4 | 0.5% |
| Highest Temperature | 1 | 5 | 1 C |
| Average Temperature | 1 | 6 | 1 C |

**Note:** SOC stands for State of Charge.

### Message 3 Structure

| Field | Length (bytes) | Byte Location | Units |
| :---: | :---: | :---: | :---: |
| Relay Status | 1 | 0 | N/A |
| Pack CCL | 2 | 1-2 | 1 A |
| Pack DCL | 2 | 3-4 | 1 A |
| Current Limit Status | 2 | 5-6 | N/A |

**Note:** CCL stands for Charge Current Limit, DCL stands for Discharge Current Limit.

### Special Fields

The fields listed as unitless contain boolean status or error codes packed into bytes.

See the Orion BMS software manual for interpreting individual boolean fields.

#### Custom Flags

The fields labelled as Custom Flags are 8 bit error messages where each bit is a boolean corresponding to an error code.

There are 21 error codes total.

See the Orion BMS software manual for interpreting error codes.

| Field | Bit 7 (MSB) | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 (LSB) |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| Custom Flag 0 | `P0A02` | `P0A01` | `P0AC0` | `P0A04` | `P0AFA` | `P0A80` | `P0A00` | `P0A1F` |
| Custom Flag 1 | `P0A06` | `P0A05` | `P0AA6` | `P0560` | `U0100` | `P0A9C` | `P0A81` | `P0A03` |
| Custom Flag 2 | N/A | N/A | N/A | `P0A0B` | `P0A0A` | `P0A09` | `P0A08` | `P0A07` |

#### Relay Status

The Relay Status field is an 8 bit status message where each bit is a boolean corresponding to a relay control pin or signal status.

For all of these values, a "1" signifies that the signal or relay in question is enabled or active (high). A "0" indicates that it is inactive or off (low).

See the Orion BMS software manual for interpreting status names.

| Field | Bit 7 (MSB) | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 (LSB) |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| Relay Status | Is-Charging Signal Status | Is-Ready Signal Status | Always-On Signal Status | Multi-Purpose Output Status | Malfunction Indicator | Charger Safety | Charge Relay | Discharge Relay |

#### Current Limit Status

The Current Limit Status field is a 14 bit status message where each bit is a boolean corresponding to a reason for why a current limit (either CCL or DCL) is being reduced by the BMS from the maximum allowable current.

See the Orion BMS software manual for interpreting status names.

| Bit | Reason |
| :---: | :--- |
| 0 | DCL reduced due to Low SOC |
| 1 | DCL reduced due to High Cell Resistance |
| 2 | DCL reduced due to Temperature |
| 3 | DCL reduced due to Low Cell Voltage |
| 4 | DCL reduced due to Low Pack Voltage |
| 5 | N/A |
| 6 | DCL and CCL reduced due to Voltage Failsafe  |
| 7 | DCL and CCL reduced due to Communication Failsafe |
| 8 | N/A  |
| 9 | CCL reduced due to High SOC |
| 10 | CCL reduced due to High Cell Resistance |
| 11 | CCL reduced due to Temperature |
| 12 | CCL reduced due to High Cell Voltage |
| 13 | CCL reduced due to High Pack Voltage |
| 14 | CCL reduced due to Charger Latch |
| 15 | CCL reduced due to Alternate Current Limit (MPI)  |

**Note:** Having one or more of these limiting reasons active is common and does not indicate that there is a problem with the battery pack or BMS. 
