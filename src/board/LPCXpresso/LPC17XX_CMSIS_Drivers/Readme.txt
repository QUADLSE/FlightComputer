This project is static library project adapted from the original file:

LPC17xx CMSIS-Compliant Standard Peripheral Firmware Driver Library (GNU, Keil, IAR) (Jan 28, 2011) 
(http://ics.nxp.com/support/documents/microcontrollers/zip/lpc17xx.cmsis.driver.library.zip)

Available at the NXP Website.

The intention of this project is to make a CodeRed Project ready to build and link in other applications.

Author: Alan Kharsansky
Release date: February 2, 2011

Como usar cada parte:

============================================
CMSIS
============================================
Includes path:
	- Core/CM3/CoreSupport
	- Core/CM3/DeviceSuppport/NXP/LPC17xx

Libraries:
	Debug/LPC17XX_CMSIS_Drivers

Using:
#include "LPC17XX.h"

============================================
Drivers
============================================
Includes path:
	- Drivers/include

Libraries:
	Debug/LPC17XX_CMSIS_Drivers


Using:
#include "lpc17xx_i2c.h"  //i.e


============================================
DSP_Lib
============================================
Includes path:
	- Core/DSP_Lib/Include

Libraries:
	Debug/LPC17XX_CMSIS_Drivers

Using:
#include "arm_math.h"
