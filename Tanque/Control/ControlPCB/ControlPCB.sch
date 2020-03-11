EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Device:CP1 C1
U 1 1 5E66116B
P 3450 2350
F 0 "C1" H 3565 2396 50  0000 L CNN
F 1 "220uF" H 3565 2305 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D12.5mm_P7.50mm" H 3450 2350 50  0001 C CNN
F 3 "~" H 3450 2350 50  0001 C CNN
	1    3450 2350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0101
U 1 1 5E663AA5
P 3650 3100
F 0 "#PWR0101" H 3650 2950 50  0001 C CNN
F 1 "+5V" H 3665 3273 50  0000 C CNN
F 2 "" H 3650 3100 50  0001 C CNN
F 3 "" H 3650 3100 50  0001 C CNN
	1    3650 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5E664495
P 3750 3450
F 0 "#PWR0102" H 3750 3200 50  0001 C CNN
F 1 "GND" H 3755 3277 50  0000 C CNN
F 2 "" H 3750 3450 50  0001 C CNN
F 3 "" H 3750 3450 50  0001 C CNN
	1    3750 3450
	1    0    0    -1  
$EndComp
$Comp
L ControlPCB-rescue:nRF24L01+-nrf24l01+ U1
U 1 1 5E66D267
P 5050 2250
F 0 "U1" H 5050 2765 50  0000 C CNN
F 1 "nRF24L01+" H 5050 2674 50  0000 C CNN
F 2 "RF_Module:nRF24L01_Breakout" H 5050 2350 50  0001 C CNN
F 3 "DOCUMENTATION" H 5050 2200 50  0001 C CNN
	1    5050 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 2050 4200 2050
$Comp
L Switch:SW_DPST SW2
U 1 1 5E670ECC
P 5000 3100
F 0 "SW2" H 5000 3425 50  0000 C CNN
F 1 "SW_DPST" H 5000 3334 50  0000 C CNN
F 2 "" H 5000 3100 50  0001 C CNN
F 3 "~" H 5000 3100 50  0001 C CNN
	1    5000 3100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DPST SW3
U 1 1 5E671C8E
P 6050 3350
F 0 "SW3" H 6050 3675 50  0000 C CNN
F 1 "SW_DPST" H 6050 3584 50  0000 C CNN
F 2 "" H 6050 3350 50  0001 C CNN
F 3 "~" H 6050 3350 50  0001 C CNN
	1    6050 3350
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DPST SW1
U 1 1 5E671EA4
P 4800 3800
F 0 "SW1" H 4800 4125 50  0000 C CNN
F 1 "SW_DPST" H 4800 4034 50  0000 C CNN
F 2 "" H 4800 3800 50  0001 C CNN
F 3 "~" H 4800 3800 50  0001 C CNN
	1    4800 3800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DPST SW4
U 1 1 5E671FD4
P 6500 2600
F 0 "SW4" H 6500 2925 50  0000 C CNN
F 1 "SW_DPST" H 6500 2834 50  0000 C CNN
F 2 "" H 6500 2600 50  0001 C CNN
F 3 "~" H 6500 2600 50  0001 C CNN
	1    6500 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 3700 4600 3900
Wire Wire Line
	5000 3900 5000 3700
Wire Wire Line
	4800 3200 4800 3000
Wire Wire Line
	5850 3450 5850 3250
Wire Wire Line
	6250 3250 6250 3450
Wire Wire Line
	6300 2700 6300 2500
Wire Wire Line
	6700 2500 6700 2700
$Comp
L MCU_Module:Arduino_Leonardo A1
U 1 1 5E6661F9
P 2350 3000
F 0 "A1" H 2350 4181 50  0000 C CNN
F 1 "Arduino_Leonardo" H 2350 4090 50  0000 C CNN
F 2 "Keebio-Parts:ArduinoProMicro-ZigZag" H 2350 3000 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/ArduinoBoardLeonardo" H 2350 3000 50  0001 C CNN
	1    2350 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 3450 4200 3450
Wire Wire Line
	4200 2050 4200 3450
Wire Wire Line
	4300 2200 3900 2200
Wire Wire Line
	2450 4100 3450 4100
Wire Wire Line
	3450 4100 3450 3450
Wire Wire Line
	3450 3450 3750 3450
Connection ~ 3750 3450
Wire Wire Line
	4300 2350 3750 2350
Wire Wire Line
	3750 2350 3750 1500
Wire Wire Line
	3750 1500 1400 1500
Wire Wire Line
	1400 1500 1400 3300
Wire Wire Line
	1400 3300 1850 3300
Wire Wire Line
	5200 3000 5200 3200
$Comp
L power:+3.3V #PWR0103
U 1 1 5E66A4C3
P 3650 2750
F 0 "#PWR0103" H 3650 2600 50  0001 C CNN
F 1 "+3.3V" H 3665 2923 50  0000 C CNN
F 2 "" H 3650 2750 50  0001 C CNN
F 3 "" H 3650 2750 50  0001 C CNN
	1    3650 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2200 3900 2750
Wire Wire Line
	3900 2750 3650 2750
Wire Wire Line
	4300 2500 4300 4600
Wire Wire Line
	4300 4600 1550 4600
Wire Wire Line
	1550 4600 1550 3400
Wire Wire Line
	1550 3400 1850 3400
$EndSCHEMATC
