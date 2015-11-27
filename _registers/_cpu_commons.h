#ifndef _CPU_COMM__H_
#define _CPU_COMM__H_

#include "Arduino.h"
#include <pins_arduino.h>

#if defined (__AVR__)
	#define cbi(reg, bitmask) *reg &= ~bitmask
	#define sbi(reg, bitmask) *reg |= bitmask
	//#define pulse_high(reg, bitmask) sbi(reg, bitmask); cbi(reg, bitmask);
	//#define pulse_low(reg, bitmask) cbi(reg, bitmask); sbi(reg, bitmask);

	//#define cport(port, data) port &= data
	//#define sport(port, data) port |= data

	#define swap(type, i, j) {type t = i; i = j; j = t;}

	#define fontbyte(x) pgm_read_byte(&cfont.font[x])  

	#define regtype volatile uint8_t
	#define regsize uint8_t


//sure way to detect DUE
#elif defined(ARDUINO_ARCH_SAM) && !defined(TEENSYDUINO) && !defined(ARDUINO_ARCH_SAMD) && !defined(ESP8266) && !defined(ARDUINO_ARCH_STM32F2)

	#define cbi(reg, bitmask) *reg &= ~bitmask
	#define sbi(reg, bitmask) *reg |= bitmask
	//#define pulse_high(reg, bitmask) sbi(reg, bitmask); cbi(reg, bitmask);
	//#define pulse_low(reg, bitmask) cbi(reg, bitmask); sbi(reg, bitmask);

	//#define cport(port, data) port &= data
	//#define sport(port, data) port |= data

	#define swap(type, i, j) {type t = i; i = j; j = t;}

	#define fontbyte(x) cfont.font[x]  

	#define regtype volatile uint32_t
	#define regsize uint32_t
	#define PROGMEM


    #define pgm_read_byte(x)        (*((char *)x))
//  #define pgm_read_word(x)        (*((short *)(x & 0xfffffffe)))
    #define pgm_read_word(x)        ( ((*((unsigned char *)x + 1)) << 8) + (*((unsigned char *)x)))
    #define pgm_read_byte_near(x)   (*((char *)x))
    #define pgm_read_byte_far(x)    (*((char *)x))
//  #define pgm_read_word_near(x)   (*((short *)(x & 0xfffffffe))
//  #define pgm_read_word_far(x)    (*((short *)(x & 0xfffffffe)))
    #define pgm_read_word_near(x)   ( ((*((unsigned char *)x + 1)) << 8) + (*((unsigned char *)x)))
    #define pgm_read_word_far(x)    ( ((*((unsigned char *)x + 1)) << 8) + (*((unsigned char *)x))))
    #define PSTR(x)  x
	#if defined F
		#undef F
	#endif
	#define F(X) (X)

//teensy' ARM
#elif defined(TEENSYDUINO)

	//#define pulse_high(reg, bitmask) sbi(reg, bitmask); cbi(reg, bitmask);
	//#define pulse_low(reg, bitmask) cbi(reg, bitmask); sbi(reg, bitmask);

	//#define cport(port, data) port &= data
	//#define sport(port, data) port |= data

	#define swap(type, i, j) {type t = i; i = j; j = t;}

	#define fontbyte(x) cfont.font[x]  

	#define regtype volatile uint8_t
	#define regsize uint8_t



#elif defined(ESP8266)

//#define cbi(reg, bitmask) digitalWrite(bitmask, LOW)
//#define sbi(reg, bitmask) digitalWrite(bitmask, HIGH)
//#define pulse_high(reg, bitmask) sbi(reg, bitmask); cbi(reg, bitmask);
//#define pulse_low(reg, bitmask) cbi(reg, bitmask); sbi(reg, bitmask);

//#define cport(port, data) port &= data
//#define sport(port, data) port |= data

#define swap(type, i, j) {type t = i; i = j; j = t;}

#define fontbyte(x) cfont.font[x]  

#define regtype volatile uint32_t
#define regsize uint32_t
	
#endif	

#endif
