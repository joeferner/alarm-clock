
### SPI Connections

|  SI473x   | STM32 |
|:---------:|:-----:|
|   SDIO    | MOSI  |
|   GPO1    | MISO  |
|   SCLK    | SCK   |
|  #SEN/CS  | GPIO  |
|  #RESET   | GPIO  |
| GPO2/#INT | GPIO  |

On startup GPO1 and GPO2 must be driven high to select SPI.

### i2c Connections

|  SI473x   | STM32  |
|:---------:|:------:|
|  SDIO     | SDA    |
|  SCLK     | SCL    |
|  #SEN     | HI/LOW |
|  #RESET   | GPIO   |
| GPO2/#INT | GPIO   |

On startup GPO1 and GPO2 must be driven high to select SPI.
