/*
  ArduCAM.h - Arduino library support for CMOS Image Sensor
  Copyright (C)2011-2015 ArduCAM.com. All right reserved
  
  Basic functionality of this library are based on the demo-code provided by
  ArduCAM.com. You can find the latest version of the library at
  http://www.ArduCAM.com

  Now supported controllers:
		-	OV7670
		-	MT9D111
		-	OV7675
		-	OV2640
		-	OV3640
		-	OV5642
		-	OV7660
		-	OV7725
		- MT9M112		
		- MT9V111
		- OV5640		
		- MT9M001			
		- MT9T112
		- MT9D112
				
	We will add support for many other sensors in next release.
	
  Supported MCU platform
 		-	Theoretically support all Arduino families
  		-	Arduino UNO R3			(Tested)
  		-	Arduino MEGA2560 R3		(Tested)
  		-	Arduino Leonardo R3		(Tested)
  		-	Arduino Nano			(Tested)
  		-	Arduino DUE				(Tested)
  		- Arduino Yun				(Tested)  		
  		-	Raspberry Pi			(Tested)
  		- ESP8266-12				(Tested)  	
		- Teensy 3.0				(compile)
		- Teensy LC					(compile)
		- Teensy 3.1/3.2			(compile)

  If you make any modifications or improvements to the code, I would appreciate
  that you share the code with me so that I might include it in the next release.
  I can be contacted through http://www.ArduCAM.com

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*------------------------------------
	Revision History:
	2012/09/20 	V1.0.0	by Lee	first release 
	2012/10/23  V1.0.1  by Lee  Resolved some timing issue for the Read/Write Register	
	2012/11/29	V1.1.0	by Lee  Add support for MT9D111 sensor
	2012/12/13	V1.2.0	by Lee	Add support for OV7675 sensor
	2012/12/28  V1.3.0	by Lee	Add support for OV2640,OV3640,OV5642 sensors
	2013/02/26	V2.0.0	by Lee	New Rev.B shield hardware, add support for FIFO control 
															and support Mega1280/2560 boards 
	2013/05/28	V2.1.0	by Lee	Add support all drawing functions derived from UTFT library 			
	2013/08/24	V3.0.0	by Lee	Support ArudCAM shield Rev.C hardware, features SPI interface and low power mode.
								Support almost all series of Arduino boards including DUE.	
	2014/03/09  V3.1.0  by Lee  Add the more impressive example sketches. 
								Optimise the OV5642 settings, improve image quality.
								Add live preview before JPEG capture.
								Add play back photos one by one	after BMP capture.
	2014/05/01  V3.1.1  by Lee  Minor changes to add support Arduino IDE for linux distributions.	
	2014/09/30  V3.2.0  by Lee  Improvement on OV5642 camera dirver.			
	2014/10/06  V3.3.0  by Lee  Add OV7660,OV7725 camera support.			
	2015/02/27  V3.4.0  by Lee  Add the support for Arduino Yun board, update the latest UTFT library for ArduCAM.			
	2015/06/09  V3.4.1  by Lee	Minor changes and add some comments		
	2015/06/19  V3.4.2  by Lee	Add support for MT9M112 camera.			
	2015/06/20  V3.4.3  by Lee	Add support for MT9V111 camera.			
	2015/06/22  V3.4.4  by Lee	Add support for OV5640 camera.										
	2015/06/22  V3.4.5  by Lee	Add support for MT9M001 camera.		
	2015/08/05  V3.4.6  by Lee	Add support for MT9T112 camera.	
	2015/08/08  V3.4.7  by Lee	Add support for MT9D112 camera.							
	2015/09/20  V3.4.8  by Lee	Add support for ESP8266 processor.
	2015/11/25  V3.4.9  added support for Teensy's (by sumotoy), fixed small errors, cleaned code.
--------------------------------------*/


#ifndef ArduCAM_H
#define ArduCAM_H

#include "Arduino.h"
#include <pins_arduino.h>
#include <Wire.h>
#include <SPI.h>


#include "_registers/_cpu_commons.h"
#include "_registers/_sensorsDefinitions.h"
#include "memorysaver.h"

class ArduCAM
{
	public:
		ArduCAM();
		ArduCAM(byte model,int CS);
		void begin(bool spiInit=true,bool wireInit=true);
		void InitCAM();
		
		void flush_fifo(void);
		void start_capture(void);
		void clear_fifo_flag(void);
		uint8_t read_fifo(void);
		
		uint8_t read_reg(uint8_t addr);
		void write_reg(uint8_t addr, uint8_t data);

		uint32_t read_fifo_length(void);
		void set_fifo_burst(void);
		void set_bit(uint8_t addr, uint8_t bit);
		void clear_bit(uint8_t addr, uint8_t bit);
		uint8_t get_bit(uint8_t addr, uint8_t bit);
		void set_mode(uint8_t mode);
		
		int wrSensorRegs(const struct sensor_reg*);
		int wrSensorRegs8_8(const struct sensor_reg*);
		int wrSensorRegs8_16(const struct sensor_reg*);
		int wrSensorRegs16_8(const struct sensor_reg*);
		int wrSensorRegs16_16(const struct sensor_reg*);
		
		byte wrSensorReg(int regID, int regDat);
		byte wrSensorReg8_8(int regID, int regDat);
		byte wrSensorReg8_16(int regID, int regDat);
		byte wrSensorReg16_8(int regID, int regDat);
		byte wrSensorReg16_16(int regID, int regDat);
		
		byte rdSensorReg8_8(uint8_t regID, uint8_t* regDat);
		byte rdSensorReg16_8(uint16_t regID, uint8_t* regDat);
		byte rdSensorReg8_16(uint8_t regID, uint16_t* regDat);
		byte rdSensorReg16_16(uint16_t regID, uint16_t* regDat);
		
		void OV2640_set_JPEG_size(uint8_t size);
		void OV5642_set_JPEG_size(uint8_t size);
		void set_format(byte fmt);
		
		int bus_write(int address, int value);
		uint8_t bus_read(int address);	
		void	startSend(bool cont=true) {if (cont) startTransaction(); _CS_LOW(); }
		void	endSend(bool cont=true) {if (cont) endTransaction(); _CS_HIGH(); }
		uint8_t sendData(uint8_t val){return _sendData(val);}
	protected:
		regtype *P_CS;
		regsize B_CS;
  		byte m_fmt;
		byte sensor_model;
		byte sensor_addr;

		void _CS_LOW(void)
		__attribute__((always_inline)) {
			#if defined(TEENSYDUINO)
				digitalWriteFast(B_CS,LOW);
			#elif defined(ESP8266)
				digitalWrite(B_CS,LOW);
			#else
				cbi(P_CS, B_CS);
			#endif
		}
		
		void _CS_HIGH(void)
		__attribute__((always_inline)) {
			#if defined(TEENSYDUINO)
				digitalWriteFast(B_CS,HIGH);
			#elif defined(ESP8266)
				digitalWrite(B_CS,HIGH);
			#else
				sbi(P_CS, B_CS);
			#endif
		}
		
		void startTransaction(void)
		__attribute__((always_inline)) {
			#if defined(SPI_HAS_TRANSACTION)
				SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
			#endif
		}
		
		void endTransaction(void)
		__attribute__((always_inline)) {
			#if defined(SPI_HAS_TRANSACTION)
				SPI.endTransaction();
			#endif
		}
		
		uint8_t _sendData(uint8_t val)
		__attribute__((always_inline)) {
			uint8_t ret = 0;
			ret = SPI.transfer(val);
			return ret;
		}

};

#endif
