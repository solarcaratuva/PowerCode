# PowerCode

Developing embedded code for the Power Team PCB. The MCU we are using is STM32F413ZH.

## PCB Design

All information about the current PCB Design can be found [here](https://github.com/solarcaratuva/PowerSystem).

## STM32 Code

A list of pin names used by MbedOS for our MCU can be found [here](https://os.mbed.com/platforms/ST-Nucleo-F413ZH/).

Important pins for us:

| STM Pin Name | MbedOS Pin Name(s) | Function |
| :---: | :---: | :--- |
| PB0 | `PB_0`/`LED1` | BMS Error |
| PB7 | `PB_7`/`LED2` | CAN Error |
| PB14 | `PB_14`/`LED3` | Unused LED |
| PC13 | `PC_13`/`BUTTON1` | Unused Button |
| PD0 | `PD_0` | CAN1 (BMS) Receivier |
| PD1 | `PD_1` | CAN1 (BMS) Transmitter |
| PB12 | `PB_12` | CAN2 (Main) Receivier |
| PB13 | `PB_13` | CAN2 (Main) Transmitter |
| PG9 | `PG_9`/`D0` | DC-DC ON |
| PG14 | `PG_14`/`D1` | Unused Digital I/O |
| PF15 | `PF_15`/`D2` | Unused Digital I/O |
| PE13 | `PE_13`/`D3` | Unused Digital I/O |
| PF14 | `PF_14`/`D4` | Unused Digital I/O |
| PE11 | `PE_11`/`D5` | Unused Digital I/O |
| PE9 | `PE_9`/`D6` | Unused Digital I/O |
| PF13 | `PF_13`/`D7` | Unused Digital I/O |
| PF12 | `PF_12`/`D8` | Unused Digital I/O |
| PD15 | `PD_15`/`D9` | Unused Digital I/O |
| PD14 | `PD_14`/`D10` | Unused Digital I/O |
| PA7 | `PA_7`/`D11` | Unused Digital I/O |
| PA6 | `PA_6`/`D12` | Unused Digital I/O |
| PA5 | `PA_5`/`D13` | Unused Digital I/O |
| PB9 | `PB_9`/`D14` | Unused Digital I/O |
| PB8 | `PB_8`/`D15` | Unused Digital I/O |
| PA3 | `PA_3`/`A0` | AUX Voltage |
| PC0 | `PC_0`/`A1` | DC-DC Voltage |
| PC3 | `PC_3`/`A2` | Unused Analog I/O |
| PC1 | `PC_1`/`A3` | Unused Analog I/O |
| PC4 | `PC_4`/`A4` | Unused Analog I/O |
| PC5 | `PC_5`/`A5` | Unused Analog I/O |

**Note:** the LEDs for Power ON, AUX ON, DC-DC ON, and AUX/DC-DC being used can be directly connected to the power supply / relay driving it.

## Documentation

[BMS CAN](docs/bms-can.md): Structure and format of CAN communication from the Orion BMS.
