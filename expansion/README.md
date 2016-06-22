
PCB Features:
  - Light level
  - FM/Weather Tuner (Si4737)
  - i2S Audio DAC (NXP UDA1334ATS)
  - Audio Amplifier (STMicro TDA7266)
  - Temperature/Humidity sensor (SHT30-DIS-B)
  - Power distribution
  - Buttons
  - wake up light

Requirements

|    Device      | Requirements | Description          |
|:--------------:|:------------:|:---------------------|
| Debug/ICP      | 1-USART      | Debug and bootloader |
| SHT30-DIS      | 1-EXTIO      | Alert                |
|                | 1-GPIO       | Reset                |
|                | 1-i2C        | Address 0x44         |
| Light Sensor   | 1-Analog In  |                      |
| TFT            | 1-PWM        | Backlight            |
| Si4737         | 1-PWM        | Radio CLK 32.768kHz  |
|                | 1-EXTIO      | Interrupt            |
|                | 1-i2C        | Address 0x11         |
|                | 1-GPIO       | Reset                |
| NXP-UDA1334ATS | 1-GPIO       | De-emphasis          |
|                | 1-GPIO       | DAC Range            |
| ST-TDA7266     | 1-GPIO       | Mute                 |
|                | 1-GPIO       | Stand By             |
| Audio Select   | 1-GPIO       | Audio Select         |
| Wake up light  | 1-PWM        |                      |
| Buttons        | 4-GPIO       |                      |

i2C

|  Device   | Address |
|:---------:|:-------:|
| SHT30-DIS |  0x44   |
| Si4737    |  0x11   |
