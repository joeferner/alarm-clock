EESchema Schematic File Version 2
LIBS:alarm-clock
LIBS:alarm-clock-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RASPBERRYPI2 P1
U 1 1 56DE2A03
P 2000 2000
F 0 "P1" H 2000 3287 60  0000 C CNN
F 1 "RASPBERRYPI2" H 2000 3181 60  0000 C CNN
F 2 "" H 1800 1200 60  0000 C CNN
F 3 "" H 1800 1200 60  0000 C CNN
F 4 "NA" H 2000 2000 60  0001 C CNN "inventoryId"
	1    2000 2000
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR2
U 1 1 56DE2AC7
P 1100 3100
F 0 "#PWR2" H 1100 3150 40  0001 C CNN
F 1 "GNDPWR" H 1100 3020 40  0001 C CNN
F 2 "" H 1100 3100 60  0000 C CNN
F 3 "" H 1100 3100 60  0000 C CNN
	1    1100 3100
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR12
U 1 1 56DE2B29
P 2900 3100
F 0 "#PWR12" H 2900 3150 40  0001 C CNN
F 1 "GNDPWR" H 2900 3020 40  0001 C CNN
F 2 "" H 2900 3100 60  0000 C CNN
F 3 "" H 2900 3100 60  0000 C CNN
	1    2900 3100
	1    0    0    -1  
$EndComp
NoConn ~ 2800 2300
NoConn ~ 1200 2300
$Comp
L +5V #PWR11
U 1 1 56DE2BCA
P 2900 800
F 0 "#PWR11" H 2900 890 20  0001 C CNN
F 1 "+5V" H 2893 929 30  0000 C CNN
F 2 "" H 2900 800 60  0000 C CNN
F 3 "" H 2900 800 60  0000 C CNN
	1    2900 800 
	1    0    0    -1  
$EndComp
Text Label 3400 1300 2    60   ~ 0
DEBUGRX
Text Label 3400 1400 2    60   ~ 0
DEBUGTX
Text Label 9000 3700 0    60   ~ 0
RADIOINT
Text Label 9000 3800 0    60   ~ 0
RADIORST
Text Label 9000 3900 0    60   ~ 0
SDA
Text Label 9000 4000 0    60   ~ 0
SCL
Wire Wire Line
	1200 1400 1100 1400
Wire Wire Line
	1100 1400 1100 3100
Wire Wire Line
	1200 2200 1100 2200
Connection ~ 1100 2200
Wire Wire Line
	1200 2900 1100 2900
Connection ~ 1100 2900
Wire Wire Line
	2800 1200 2900 1200
Wire Wire Line
	2900 1200 2900 3100
Wire Wire Line
	2800 2600 2900 2600
Connection ~ 2900 2600
Wire Wire Line
	2800 2400 2900 2400
Connection ~ 2900 2400
Wire Wire Line
	2800 1900 2900 1900
Connection ~ 2900 1900
Wire Wire Line
	2800 1600 2900 1600
Connection ~ 2900 1600
Wire Wire Line
	2900 1100 2800 1100
Wire Wire Line
	2900 800  2900 1100
Wire Wire Line
	2800 1000 2900 1000
Connection ~ 2900 1000
Wire Wire Line
	3400 1300 2800 1300
Wire Wire Line
	2800 1400 3400 1400
Text Label 4100 4550 2    60   ~ 0
DEBUGTX
Text Label 4100 4650 2    60   ~ 0
DEBUGRX
Text Label 700  6350 0    60   ~ 0
BOOT0
Text Label 4100 3650 2    60   ~ 0
LIGHT
Wire Wire Line
	9000 3700 9600 3700
Wire Wire Line
	9600 3800 9000 3800
Wire Wire Line
	9000 3900 9600 3900
Wire Wire Line
	9600 4000 9000 4000
$Sheet
S 9600 3300 700  1900
U 56E42CF2
F0 "Audio" 60
F1 "alarm-clock-audio.sch" 60
F2 "RADIOINT" O L 9600 3700 60 
F3 "RADIORESET" I L 9600 3800 60 
F4 "AUDIOSEL" I L 9600 3500 60 
F5 "RADIOSCL" I L 9600 4000 60 
F6 "RADIOSDA" B L 9600 3900 60 
F7 "RADIORCLK" I L 9600 4100 60 
F8 "RPIDCLK" I L 9600 4300 60 
F9 "RPIDOUT" I L 9600 4400 60 
F10 "RPIDFS" I L 9600 4500 60 
F11 "DACRANGE" I L 9600 4700 60 
F12 "DACDEEM" I L 9600 4800 60 
F13 "MUTE" I L 9600 5000 60 
F14 "STBY" I L 9600 5100 60 
$EndSheet
Text Label 9000 3500 0    60   ~ 0
AUDIOSEL
Wire Wire Line
	9600 3500 9000 3500
Text Label 4100 6250 2    60   ~ 0
AUDIOSEL
Text Label 4100 5450 2    60   ~ 0
RADIOINT
Text Label 1000 5750 0    60   ~ 0
RADIORST
$Sheet
S 9600 2800 700  200 
U 56E4CEE0
F0 "Power" 60
F1 "alarm-clock-power.sch" 60
$EndSheet
Wire Wire Line
	2800 1800 3400 1800
Text Label 3400 1800 2    60   ~ 0
TFTRS
Text Label 600  1900 0    60   ~ 0
TFTMOSI
Text Label 3400 2100 2    60   ~ 0
TFTCS
Text Label 600  2100 0    60   ~ 0
TFTSCLK
Text Label 3400 2000 2    60   ~ 0
TFTRST
Text Label 6700 1500 2    60   ~ 0
TFTBL
Text Label 600  2000 0    60   ~ 0
TSDOUT
Text Label 600  1200 0    60   ~ 0
TSPENIRQ
Text Label 3400 2200 2    60   ~ 0
TSCS
Wire Wire Line
	3400 2200 2800 2200
Wire Wire Line
	3400 2100 2800 2100
Wire Wire Line
	2800 2000 3400 2000
Wire Wire Line
	3400 1500 2800 1500
Wire Wire Line
	600  1900 1200 1900
Wire Wire Line
	1200 2000 600  2000
Wire Wire Line
	600  2100 1200 2100
Wire Wire Line
	1200 1200 600  1200
Text Label 600  1600 0    60   ~ 0
BOOT0
Text Label 600  1500 0    60   ~ 0
PISTMRST
Wire Wire Line
	1200 1500 600  1500
Text Label 5100 5500 0    60   ~ 0
PISTMRST
Text Label 9000 4100 0    60   ~ 0
RADIORCLK
Text Label 4100 5850 2    60   ~ 0
SDA
Text Label 4100 5750 2    60   ~ 0
SCL
Text Label 4100 4950 2    60   ~ 0
RADIORCLK
Wire Wire Line
	9600 4100 9000 4100
Text Label 9000 4300 0    60   ~ 0
RPIDCLK
Text Label 9000 4400 0    60   ~ 0
RPIDOUT
Text Label 9000 4500 0    60   ~ 0
RPIDFS
Wire Wire Line
	9600 4300 9000 4300
Wire Wire Line
	9000 4400 9600 4400
Wire Wire Line
	9600 4500 9000 4500
Text Label 3400 1500 2    60   ~ 0
RPIDCLK
Text Label 3400 2900 2    60   ~ 0
RPIDOUT
Text Label 600  2700 0    60   ~ 0
RPIDFS
Wire Wire Line
	1200 2700 600  2700
Wire Wire Line
	3400 2900 2800 2900
Wire Wire Line
	1200 1600 600  1600
$Comp
L RASPBERRYPI2 P2
U 1 1 575A581F
P 5300 2000
F 0 "P2" H 5300 3287 60  0000 C CNN
F 1 "TFT" H 5300 3181 60  0000 C CNN
F 2 "" H 5100 1200 60  0000 C CNN
F 3 "" H 5100 1200 60  0000 C CNN
F 4 "NA" H 5300 2000 60  0001 C CNN "inventoryId"
	1    5300 2000
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR15
U 1 1 575A5D0A
P 4400 3100
F 0 "#PWR15" H 4400 3150 40  0001 C CNN
F 1 "GNDPWR" H 4400 3020 40  0001 C CNN
F 2 "" H 4400 3100 60  0000 C CNN
F 3 "" H 4400 3100 60  0000 C CNN
	1    4400 3100
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR20
U 1 1 575A5D5D
P 6200 3100
F 0 "#PWR20" H 6200 3150 40  0001 C CNN
F 1 "GNDPWR" H 6200 3020 40  0001 C CNN
F 2 "" H 6200 3100 60  0000 C CNN
F 3 "" H 6200 3100 60  0000 C CNN
	1    6200 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2600 6100 2600
Wire Wire Line
	6200 1200 6200 3100
Wire Wire Line
	6100 1900 6200 1900
Connection ~ 6200 2600
Wire Wire Line
	6100 1600 6200 1600
Connection ~ 6200 1900
Wire Wire Line
	6700 1500 6100 1500
Wire Wire Line
	6100 1200 6200 1200
Connection ~ 6200 1600
Wire Wire Line
	4500 1400 4400 1400
Wire Wire Line
	4400 1400 4400 3100
Wire Wire Line
	4500 2900 4400 2900
Connection ~ 4400 2900
Wire Wire Line
	4500 2200 4400 2200
Connection ~ 4400 2200
$Comp
L +5V #PWR19
U 1 1 575A6210
P 6200 800
F 0 "#PWR19" H 6200 890 20  0001 C CNN
F 1 "+5V" H 6193 929 30  0000 C CNN
F 2 "" H 6200 800 60  0000 C CNN
F 3 "" H 6200 800 60  0000 C CNN
	1    6200 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 800  6200 1100
Wire Wire Line
	6200 1000 6100 1000
Wire Wire Line
	6200 1100 6100 1100
Connection ~ 6200 1000
Text Label 4000 1200 0    60   ~ 0
TSPENIRQ
Wire Wire Line
	4500 1200 4000 1200
Text Label 4000 1000 0    60   ~ 0
RPI3V3
Text Label 600  1000 0    60   ~ 0
RPI3V3
Wire Wire Line
	4500 1000 4000 1000
Wire Wire Line
	1200 1000 600  1000
Text Label 4000 1900 0    60   ~ 0
TFTMOSI
Text Label 4000 2000 0    60   ~ 0
TSDOUT
Text Label 4000 2100 0    60   ~ 0
TFTSCLK
Wire Wire Line
	4500 1900 4000 1900
Wire Wire Line
	4000 2000 4500 2000
Wire Wire Line
	4500 2100 4000 2100
Text Label 6700 2200 2    60   ~ 0
TSCS
Text Label 6700 2100 2    60   ~ 0
TFTCS
Text Label 6700 2000 2    60   ~ 0
TFTRST
Wire Wire Line
	6700 2000 6100 2000
Wire Wire Line
	6100 2100 6700 2100
Wire Wire Line
	6700 2200 6100 2200
Text Label 6700 1800 2    60   ~ 0
TFTRS
Wire Wire Line
	6700 1800 6100 1800
Text Label 4000 1800 0    60   ~ 0
RPI3V3
Wire Wire Line
	4500 1800 4000 1800
Text Label 600  1800 0    60   ~ 0
RPI3V3
Wire Wire Line
	1200 1800 600  1800
$Comp
L R R2
U 1 1 575A7DEB
P 6250 7100
F 0 "R2" H 6307 7130 30  0000 L CNN
F 1 "4K7" H 6307 7070 30  0000 L CNN
F 2 "kicadlib:RESC2012X100N" H 6250 7100 60  0001 C CNN
F 3 "" H 6250 7100 60  0000 C CNN
F 4 "456" H 6250 7100 60  0001 C CNN "inventoryId"
	1    6250 7100
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 575A7E8A
P 6650 7100
F 0 "R3" H 6707 7130 30  0000 L CNN
F 1 "4K7" H 6707 7070 30  0000 L CNN
F 2 "kicadlib:RESC2012X100N" H 6650 7100 60  0001 C CNN
F 3 "" H 6650 7100 60  0000 C CNN
F 4 "456" H 6650 7100 60  0001 C CNN "inventoryId"
	1    6650 7100
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR21
U 1 1 575A7EF4
P 6250 6800
F 0 "#PWR21" H 6250 6890 20  0001 C CNN
F 1 "+3.3V" H 6243 6929 30  0000 C CNN
F 2 "" H 6250 6800 60  0000 C CNN
F 3 "" H 6250 6800 60  0000 C CNN
	1    6250 6800
	1    0    0    -1  
$EndComp
Text Label 6050 7400 0    60   ~ 0
SDA
Text Label 6450 7400 0    60   ~ 0
SCL
Wire Wire Line
	6050 7400 6250 7400
Wire Wire Line
	6250 7400 6250 7200
Wire Wire Line
	6250 6800 6250 7000
Wire Wire Line
	6650 7000 6650 6850
Wire Wire Line
	6650 6850 6250 6850
Connection ~ 6250 6850
Wire Wire Line
	6650 7400 6650 7200
Wire Wire Line
	6450 7400 6650 7400
$Sheet
S 9600 1600 700  900 
U 575AB703
F0 "Environment" 60
F1 "alarm-clock-environment.sch" 60
F2 "SHTSDA" B L 9600 1700 60 
F3 "SHTSCL" I L 9600 1800 60 
F4 "SHTALERT" O L 9600 1900 60 
F5 "SHTRESET" I L 9600 2000 60 
F6 "LIGHT" O L 9600 2200 60 
F7 "WAKELIGHT" I L 9600 2400 60 
$EndSheet
Text Label 9000 1700 0    60   ~ 0
SDA
Text Label 9000 1800 0    60   ~ 0
SCL
Wire Wire Line
	9600 1700 9000 1700
Wire Wire Line
	9600 1800 9000 1800
Wire Wire Line
	9600 2200 9000 2200
Text Label 9000 2200 0    60   ~ 0
LIGHT
Text Label 9000 1900 0    60   ~ 0
SHTALERT
Text Label 9000 2000 0    60   ~ 0
SHTRESET
Wire Wire Line
	9600 1900 9000 1900
Wire Wire Line
	9000 2000 9600 2000
Text Label 4100 5650 2    60   ~ 0
SHTALERT
Text Label 4100 5550 2    60   ~ 0
SHTRESET
Text Label 4100 4450 2    60   ~ 0
TFTBL
Text Label 9000 4700 0    60   ~ 0
DACRANGE
Text Label 9000 4800 0    60   ~ 0
DACDEEM
Text Label 9000 5000 0    60   ~ 0
MUTE
Text Label 9000 5100 0    60   ~ 0
STBY
Wire Wire Line
	9000 4700 9600 4700
Wire Wire Line
	9600 4800 9000 4800
Wire Wire Line
	9000 5000 9600 5000
Wire Wire Line
	9600 5100 9000 5100
Text Label 4100 6550 2    60   ~ 0
DACRANGE
Text Label 4100 6650 2    60   ~ 0
DACDEEM
Text Label 4100 6450 2    60   ~ 0
MUTE
Text Label 4100 6350 2    60   ~ 0
STBY
$Comp
L STM32-48PIN U1
U 1 1 576986B6
P 2450 5250
F 0 "U1" H 2475 7137 60  0000 C CNN
F 1 "STM32-48PIN" H 2475 7031 60  0000 C CNN
F 2 "" H 2850 5250 60  0000 C CNN
F 3 "" H 2850 5250 60  0000 C CNN
F 4 "375" H 2450 5250 60  0001 C CNN "inventoryId"
	1    2450 5250
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR4
U 1 1 57698FDB
P 1400 3550
F 0 "#PWR4" H 1400 3640 20  0001 C CNN
F 1 "+3.3V" H 1396 3678 30  0000 C CNN
F 2 "" H 1400 3550 60  0000 C CNN
F 3 "" H 1400 3550 60  0000 C CNN
	1    1400 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 4050 1500 4050
Wire Wire Line
	1400 3550 1400 4050
Wire Wire Line
	1500 3950 1400 3950
Connection ~ 1400 3950
Wire Wire Line
	1500 3850 1400 3850
Connection ~ 1400 3850
Wire Wire Line
	1500 3750 1400 3750
Connection ~ 1400 3750
Wire Wire Line
	1500 3650 1400 3650
Connection ~ 1400 3650
$Comp
L GNDPWR #PWR5
U 1 1 576993A6
P 1400 6950
F 0 "#PWR5" H 1400 7000 40  0001 C CNN
F 1 "GNDPWR" H 1400 6870 40  0001 C CNN
F 2 "" H 1400 6950 60  0000 C CNN
F 3 "" H 1400 6950 60  0000 C CNN
	1    1400 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 6550 1400 6550
Wire Wire Line
	1400 6550 1400 6950
Wire Wire Line
	1500 6650 1400 6650
Connection ~ 1400 6650
Wire Wire Line
	1500 6750 1400 6750
Connection ~ 1400 6750
Wire Wire Line
	1500 6850 1400 6850
Connection ~ 1400 6850
$Comp
L GNDPWR #PWR14
U 1 1 5769989C
P 4250 5450
F 0 "#PWR14" H 4250 5500 40  0001 C CNN
F 1 "GNDPWR" H 4250 5370 40  0001 C CNN
F 2 "" H 4250 5450 60  0000 C CNN
F 3 "" H 4250 5450 60  0000 C CNN
	1    4250 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 5350 4250 5350
Wire Wire Line
	4250 5350 4250 5450
NoConn ~ 1500 4250
NoConn ~ 1500 4750
Text Label 4100 4350 2    60   ~ 0
BUTTON0
Text Label 4100 5150 2    60   ~ 0
BUTTON1
Text Label 4100 5250 2    60   ~ 0
BUTTON2
Text Label 4100 6150 2    60   ~ 0
BUTTON3
NoConn ~ 3450 6850
NoConn ~ 3450 3750
NoConn ~ 3450 3850
NoConn ~ 3450 3950
NoConn ~ 3450 4050
NoConn ~ 3450 4150
Text Label 4100 4250 2    60   ~ 0
WAKELIGHT
Wire Wire Line
	4100 4250 3450 4250
Wire Wire Line
	3450 4350 4100 4350
Wire Wire Line
	3450 5150 4100 5150
Wire Wire Line
	4100 5250 3450 5250
Wire Wire Line
	3450 6150 4100 6150
Wire Wire Line
	3450 6250 4100 6250
Wire Wire Line
	4100 6350 3450 6350
Wire Wire Line
	3450 6450 4100 6450
Wire Wire Line
	4100 6550 3450 6550
Wire Wire Line
	3450 6650 4100 6650
Wire Wire Line
	3450 4450 4100 4450
Wire Wire Line
	4100 4550 3450 4550
Wire Wire Line
	3450 4650 4100 4650
NoConn ~ 1500 5850
Wire Wire Line
	1500 5750 1000 5750
Text Label 4100 4750 2    60   ~ 0
SWDIO
Text Label 4100 4850 2    60   ~ 0
SWCLK
Text Label 4900 4500 0    60   ~ 0
SWDIO
Text Label 4900 4300 0    60   ~ 0
SWCLK
Wire Wire Line
	4100 4750 3450 4750
Wire Wire Line
	4100 4850 3450 4850
Wire Wire Line
	4100 4950 3450 4950
Wire Wire Line
	3450 5450 4100 5450
Wire Wire Line
	3450 5550 4100 5550
Wire Wire Line
	4100 5650 3450 5650
Wire Wire Line
	3450 5750 4100 5750
Wire Wire Line
	4100 5850 3450 5850
NoConn ~ 3450 5950
NoConn ~ 3450 6050
Wire Wire Line
	4100 3650 3450 3650
Wire Wire Line
	700  6350 1500 6350
Text Label 4900 4600 0    60   ~ 0
SWSTMRST
Text Label 1000 6150 0    60   ~ 0
STMRST
Text Label 5100 5400 0    60   ~ 0
STMRST
Wire Wire Line
	1500 6150 1000 6150
$Comp
L R R1
U 1 1 5769FAA2
P 1100 6650
F 0 "R1" H 1157 6680 30  0000 L CNN
F 1 "10K" H 1157 6620 30  0000 L CNN
F 2 "kicadlib:RESC2012X100N" H 1100 6650 60  0001 C CNN
F 3 "" H 1100 6650 60  0000 C CNN
F 4 "299" H 1100 6650 60  0001 C CNN "inventoryId"
	1    1100 6650
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR3
U 1 1 5769FD0E
P 1100 6950
F 0 "#PWR3" H 1100 7000 40  0001 C CNN
F 1 "GNDPWR" H 1100 6870 40  0001 C CNN
F 2 "" H 1100 6950 60  0000 C CNN
F 3 "" H 1100 6950 60  0000 C CNN
	1    1100 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 6750 1100 6950
Wire Wire Line
	1100 6550 1100 6350
Connection ~ 1100 6350
$Comp
L C C3
U 1 1 576A04D8
P 1900 7400
F 0 "C3" H 1978 7430 30  0000 L CNN
F 1 "0.1uF" H 1978 7370 30  0000 L CNN
F 2 "kicadlib:CAPC2012X100N" H 1900 7400 60  0001 C CNN
F 3 "" H 1900 7400 60  0000 C CNN
F 4 "465" H 1900 7400 60  0001 C CNN "inventoryId"
	1    1900 7400
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 576A0C18
P 2150 7400
F 0 "C4" H 2228 7430 30  0000 L CNN
F 1 "0.1uF" H 2228 7370 30  0000 L CNN
F 2 "kicadlib:CAPC2012X100N" H 2150 7400 60  0001 C CNN
F 3 "" H 2150 7400 60  0000 C CNN
F 4 "465" H 2150 7400 60  0001 C CNN "inventoryId"
	1    2150 7400
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 576A0CB2
P 2400 7400
F 0 "C5" H 2478 7430 30  0000 L CNN
F 1 "0.1uF" H 2478 7370 30  0000 L CNN
F 2 "kicadlib:CAPC2012X100N" H 2400 7400 60  0001 C CNN
F 3 "" H 2400 7400 60  0000 C CNN
F 4 "465" H 2400 7400 60  0001 C CNN "inventoryId"
	1    2400 7400
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 576A0D4F
P 2650 7400
F 0 "C6" H 2728 7430 30  0000 L CNN
F 1 "0.1uF" H 2728 7370 30  0000 L CNN
F 2 "kicadlib:CAPC2012X100N" H 2650 7400 60  0001 C CNN
F 3 "" H 2650 7400 60  0000 C CNN
F 4 "465" H 2650 7400 60  0001 C CNN "inventoryId"
	1    2650 7400
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 576A0DEF
P 2900 7400
F 0 "C7" H 2978 7430 30  0000 L CNN
F 1 "0.1uF" H 2978 7370 30  0000 L CNN
F 2 "kicadlib:CAPC2012X100N" H 2900 7400 60  0001 C CNN
F 3 "" H 2900 7400 60  0000 C CNN
F 4 "465" H 2900 7400 60  0001 C CNN "inventoryId"
	1    2900 7400
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR7
U 1 1 576A0F14
P 1900 7550
F 0 "#PWR7" H 1900 7600 40  0001 C CNN
F 1 "GNDPWR" H 1900 7470 40  0001 C CNN
F 2 "" H 1900 7550 60  0000 C CNN
F 3 "" H 1900 7550 60  0000 C CNN
	1    1900 7550
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR8
U 1 1 576A0FAC
P 2150 7550
F 0 "#PWR8" H 2150 7600 40  0001 C CNN
F 1 "GNDPWR" H 2150 7470 40  0001 C CNN
F 2 "" H 2150 7550 60  0000 C CNN
F 3 "" H 2150 7550 60  0000 C CNN
	1    2150 7550
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR9
U 1 1 576A1044
P 2400 7550
F 0 "#PWR9" H 2400 7600 40  0001 C CNN
F 1 "GNDPWR" H 2400 7470 40  0001 C CNN
F 2 "" H 2400 7550 60  0000 C CNN
F 3 "" H 2400 7550 60  0000 C CNN
	1    2400 7550
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR10
U 1 1 576A10F2
P 2650 7550
F 0 "#PWR10" H 2650 7600 40  0001 C CNN
F 1 "GNDPWR" H 2650 7470 40  0001 C CNN
F 2 "" H 2650 7550 60  0000 C CNN
F 3 "" H 2650 7550 60  0000 C CNN
	1    2650 7550
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR13
U 1 1 576A1195
P 2900 7550
F 0 "#PWR13" H 2900 7600 40  0001 C CNN
F 1 "GNDPWR" H 2900 7470 40  0001 C CNN
F 2 "" H 2900 7550 60  0000 C CNN
F 3 "" H 2900 7550 60  0000 C CNN
	1    2900 7550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 7500 2900 7550
Wire Wire Line
	2650 7500 2650 7550
Wire Wire Line
	2400 7500 2400 7550
Wire Wire Line
	2150 7500 2150 7550
Wire Wire Line
	1900 7500 1900 7550
$Comp
L +3.3V #PWR6
U 1 1 576A181F
P 1900 7150
F 0 "#PWR6" H 1900 7240 20  0001 C CNN
F 1 "+3.3V" H 1896 7278 30  0000 C CNN
F 2 "" H 1900 7150 60  0000 C CNN
F 3 "" H 1900 7150 60  0000 C CNN
	1    1900 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 7300 1900 7150
Wire Wire Line
	2900 7300 2900 7200
Wire Wire Line
	2900 7200 1900 7200
Connection ~ 1900 7200
Wire Wire Line
	2150 7300 2150 7200
Connection ~ 2150 7200
Wire Wire Line
	2400 7300 2400 7200
Connection ~ 2400 7200
Wire Wire Line
	2650 7300 2650 7200
Connection ~ 2650 7200
$Comp
L XTAL X1
U 1 1 576A2216
P 1200 5200
F 0 "X1" V 1170 5288 30  0000 L CNN
F 1 "8MHz" V 1230 5288 30  0000 L CNN
F 2 "kicadlib:XTAL8045X200N" H 1200 5200 60  0001 C CNN
F 3 "" H 1200 5200 60  0000 C CNN
F 4 "488" H 1200 5200 60  0001 C CNN "inventoryId"
	1    1200 5200
	0    1    1    0   
$EndComp
Wire Wire Line
	1050 5450 1500 5450
Wire Wire Line
	1200 5450 1200 5350
Wire Wire Line
	1050 4950 1500 4950
Wire Wire Line
	1200 4950 1200 5050
$Comp
L C C1
U 1 1 576A24DF
P 950 4950
F 0 "C1" V 1118 4950 30  0000 C CNN
F 1 "18pF" V 1058 4950 30  0000 C CNN
F 2 "kicadlib:CAPC2012X100N" H 950 4950 60  0001 C CNN
F 3 "" H 950 4950 60  0000 C CNN
F 4 "388" H 950 4950 60  0001 C CNN "inventoryId"
	1    950  4950
	0    -1   -1   0   
$EndComp
$Comp
L C C2
U 1 1 576A269E
P 950 5450
F 0 "C2" V 1118 5450 30  0000 C CNN
F 1 "18pF" V 1058 5450 30  0000 C CNN
F 2 "kicadlib:CAPC2012X100N" H 950 5450 60  0001 C CNN
F 3 "" H 950 5450 60  0000 C CNN
F 4 "388" H 950 5450 60  0001 C CNN "inventoryId"
	1    950  5450
	0    -1   -1   0   
$EndComp
$Comp
L GNDPWR #PWR1
U 1 1 576A27EE
P 750 5550
F 0 "#PWR1" H 750 5600 40  0001 C CNN
F 1 "GNDPWR" H 750 5470 40  0001 C CNN
F 2 "" H 750 5550 60  0000 C CNN
F 3 "" H 750 5550 60  0000 C CNN
	1    750  5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  4950 750  4950
Wire Wire Line
	750  4950 750  5550
Wire Wire Line
	850  5450 750  5450
Connection ~ 750  5450
Connection ~ 1200 5450
Connection ~ 1200 4950
$Comp
L ST-SWD P3
U 1 1 57699012
P 5800 4700
F 0 "P3" H 5800 5350 60  0000 L CNN
F 1 "ST-SWD" H 5800 4550 60  0000 L CNN
F 2 "" H 5500 4600 60  0000 C CNN
F 3 "" H 5500 4600 60  0000 C CNN
F 4 "NA" H 5800 4700 60  0001 C CNN "inventoryId"
	1    5800 4700
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR17
U 1 1 576998FE
P 5400 4800
F 0 "#PWR17" H 5400 4850 40  0001 C CNN
F 1 "GNDPWR" H 5400 4720 40  0001 C CNN
F 2 "" H 5400 4800 60  0000 C CNN
F 3 "" H 5400 4800 60  0000 C CNN
	1    5400 4800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR16
U 1 1 576999A2
P 5400 4100
F 0 "#PWR16" H 5400 4190 20  0001 C CNN
F 1 "+3.3V" H 5393 4229 30  0000 C CNN
F 2 "" H 5400 4100 60  0000 C CNN
F 3 "" H 5400 4100 60  0000 C CNN
	1    5400 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 4400 5400 4400
Wire Wire Line
	5400 4400 5400 4800
Wire Wire Line
	5500 4200 5400 4200
Wire Wire Line
	5400 4200 5400 4100
Wire Wire Line
	5500 4300 4900 4300
Wire Wire Line
	4900 4500 5500 4500
Wire Wire Line
	5500 4600 4900 4600
NoConn ~ 5500 4700
$Comp
L P03 P4
U 1 1 576992BE
P 5800 5200
F 0 "P4" H 6028 5053 60  0000 L CNN
F 1 "RESETSEL" H 6028 4947 60  0000 L CNN
F 2 "" H 5800 5200 60  0000 C CNN
F 3 "" H 5800 5200 60  0000 C CNN
F 4 "NA" H 5800 5200 60  0001 C CNN "inventoryId"
	1    5800 5200
	1    0    0    -1  
$EndComp
Text Label 5100 5300 0    60   ~ 0
SWSTMRST
Wire Wire Line
	5600 5300 5100 5300
Wire Wire Line
	5100 5400 5600 5400
Wire Wire Line
	5600 5500 5100 5500
NoConn ~ 1200 1300
NoConn ~ 1200 1100
NoConn ~ 1200 1700
NoConn ~ 1200 2500
NoConn ~ 1200 2600
NoConn ~ 1200 2800
NoConn ~ 2800 2800
NoConn ~ 2800 2700
NoConn ~ 2800 2500
NoConn ~ 2800 1700
NoConn ~ 4500 1300
NoConn ~ 4500 1100
NoConn ~ 6100 1300
NoConn ~ 6100 1400
NoConn ~ 6100 1700
NoConn ~ 6100 2300
NoConn ~ 6100 2500
NoConn ~ 6100 2700
NoConn ~ 6100 2800
NoConn ~ 6100 2900
NoConn ~ 4500 2800
NoConn ~ 4500 2700
NoConn ~ 4500 2600
NoConn ~ 4500 2500
NoConn ~ 4500 2300
NoConn ~ 4500 1700
NoConn ~ 4500 1600
NoConn ~ 4500 1500
$Comp
L P05 P5
U 1 1 5769A3CF
P 5800 6300
F 0 "P5" H 6028 6553 60  0000 L CNN
F 1 "BUTTONS" H 6028 6447 60  0000 L CNN
F 2 "" H 5800 6300 60  0000 C CNN
F 3 "" H 5800 6300 60  0000 C CNN
F 4 "NA" H 5800 6300 60  0001 C CNN "inventoryId"
	1    5800 6300
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR18
U 1 1 5769A542
P 5500 6400
F 0 "#PWR18" H 5500 6450 40  0001 C CNN
F 1 "GNDPWR" H 5500 6320 40  0001 C CNN
F 2 "" H 5500 6400 60  0000 C CNN
F 3 "" H 5500 6400 60  0000 C CNN
	1    5500 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 6300 5500 6300
Wire Wire Line
	5500 6300 5500 6400
Text Label 5100 5900 0    60   ~ 0
BUTTON0
Text Label 5100 6000 0    60   ~ 0
BUTTON1
Text Label 5100 6100 0    60   ~ 0
BUTTON2
Text Label 5100 6200 0    60   ~ 0
BUTTON3
Wire Wire Line
	5600 5900 5100 5900
Wire Wire Line
	5100 6000 5600 6000
Wire Wire Line
	5600 6100 5100 6100
Wire Wire Line
	5100 6200 5600 6200
Wire Wire Line
	6100 2400 6200 2400
Connection ~ 6200 2400
Text Label 4000 2400 0    60   ~ 0
TSINT
Wire Wire Line
	4000 2400 4500 2400
Text Label 600  2400 0    60   ~ 0
TSINT
Wire Wire Line
	1200 2400 600  2400
Text Label 9000 2400 0    60   ~ 0
WAKELIGHT
Wire Wire Line
	9600 2400 9000 2400
$Comp
L MECH M1
U 1 1 577E5634
P 7250 5900
F 0 "M1" H 7250 5900 60  0000 L CNN
F 1 "Mounting Holes" H 7450 5900 60  0000 L CNN
F 2 "" H 7250 5900 60  0000 C CNN
F 3 "" H 7250 5900 60  0000 C CNN
F 4 "NA" H 7250 5900 60  0001 C CNN "inventoryId"
	1    7250 5900
	1    0    0    -1  
$EndComp
$Comp
L MECH M2
U 1 1 577E5A07
P 7250 6000
F 0 "M2" H 7250 6000 60  0000 L CNN
F 1 "Mounting Holes" H 7450 6000 60  0000 L CNN
F 2 "" H 7250 6000 60  0000 C CNN
F 3 "" H 7250 6000 60  0000 C CNN
F 4 "NA" H 7250 6000 60  0001 C CNN "inventoryId"
	1    7250 6000
	1    0    0    -1  
$EndComp
$Comp
L MECH M3
U 1 1 577E5ABD
P 7250 6100
F 0 "M3" H 7250 6100 60  0000 L CNN
F 1 "Mounting Holes" H 7450 6100 60  0000 L CNN
F 2 "" H 7250 6100 60  0000 C CNN
F 3 "" H 7250 6100 60  0000 C CNN
F 4 "NA" H 7250 6100 60  0001 C CNN "inventoryId"
	1    7250 6100
	1    0    0    -1  
$EndComp
$Comp
L MECH M4
U 1 1 577E5AC3
P 7250 6200
F 0 "M4" H 7250 6200 60  0000 L CNN
F 1 "Mounting Holes" H 7450 6200 60  0000 L CNN
F 2 "" H 7250 6200 60  0000 C CNN
F 3 "" H 7250 6200 60  0000 C CNN
F 4 "NA" H 7250 6200 60  0001 C CNN "inventoryId"
	1    7250 6200
	1    0    0    -1  
$EndComp
$EndSCHEMATC
