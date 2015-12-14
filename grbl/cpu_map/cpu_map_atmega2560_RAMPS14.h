/*
  cpu_map_atmega2560.h - CPU and pin mapping configuration file
  Part of Grbl

  Copyright (c) 2012-2015 Sungeun K. Jeon

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

/* This cpu_map file serves as a central pin mapping settings file for AVR Mega 2560 with RAMPS 1.4*/


#ifdef GRBL_PLATFORM
#error "cpu_map already defined: GRBL_PLATFORM=" GRBL_PLATFORM
#endif


#define GRBL_PLATFORM "Atmega2560_RAMPS14"

// Serial port pins
#define SERIAL_RX USART0_RX_vect
#define SERIAL_UDRE USART0_UDRE_vect

// Increase Buffers to make use of extra SRAM
//#define RX_BUFFER_SIZE		256
//#define TX_BUFFER_SIZE		128
//#define BLOCK_BUFFER_SIZE	36
//#define LINE_BUFFER_SIZE	100

// Define step pulse output pins. Changed for Ramps
#define STEP_DDR      DDRA
#define STEP_PORT     PORTA
#define STEP_PIN      PINA
#define X_STEP_BIT    2 // Not realy used
#define Y_STEP_BIT    3 // Not realy used
#define Z_STEP_BIT    4 // Not realy used
#define STEP_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits

// Define step direction output pins. Changed for Ramps
#define DIRECTION_DDR     DDRA
#define DIRECTION_PORT    PORTA
#define DIRECTION_PIN     PINA
#define X_DIRECTION_BIT   5 // Not realy used
#define Y_DIRECTION_BIT   6 // Not realy used
#define Z_DIRECTION_BIT   7 // Not realy used
#define DIRECTION_MASK ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits

// Define stepper driver enable/disable output pin. Changed for Ramps
#define STEPPERS_DISABLE_DDR   DDRB
#define STEPPERS_DISABLE_PORT  PORTB
#define STEPPERS_DISABLE_BIT   7 // Not realy used
#define STEPPERS_DISABLE_MASK (1<<STEPPERS_DISABLE_BIT)

// Define homing/hard limit switch input pins and limit interrupt vectors. 
// NOTE: All limit bit pins must be on the same port
#define LIMIT_DDR       DDRB
#define LIMIT_PORT      PORTB
#define LIMIT_PIN       PINB
#define X_LIMIT_BIT     3 // Ramps PB3 ( MISO/PCINT3 ) Digital pin 50 (MISO) ->Ramps AUX-3 pin 3
#define Y_LIMIT_BIT     2 // Ramps PB2 ( MOSI/PCINT2 ) Digital pin 51 (MOSI) ->Ramps AUX-3 pin 4
#define Z_LIMIT_BIT     1 // Ramps PB1 ( SCK/PCINT1 ) Digital pin 52 (SCK) -> Ramps AUX-3 pin 5
#define LIMIT_INT       PCIE0  // Pin change interrupt enable pin
#define LIMIT_INT_vect  PCINT0_vect 
#define LIMIT_PCMSK     PCMSK0 // Pin change interrupt register
#define LIMIT_MASK ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits

// Define spindle enable and spindle direction output pins.
#define SPINDLE_ENABLE_DDR      DDRH
#define SPINDLE_ENABLE_PORT     PORTH
#define SPINDLE_ENABLE_BIT      3 // MEGA2560 Digital Pin 6
#define SPINDLE_DIRECTION_DDR   DDRE
#define SPINDLE_DIRECTION_PORT  PORTE
#define SPINDLE_DIRECTION_BIT   3 // MEGA2560 Digital Pin 5

// Define flood and mist coolant enable output pins.
// NOTE: Uno analog pins 4 and 5 are reserved for an i2c interface, and may be installed at
// a later date if flash and memory space allows.
#define COOLANT_FLOOD_DDR     DDRH
#define COOLANT_FLOOD_PORT    PORTH
#define COOLANT_FLOOD_BIT     5 // MEGA2560 Digital Pin 8
#ifdef ENABLE_M7 // Mist coolant disabled by default. See config.h to enable/disable.
#define COOLANT_MIST_DDR    DDRH
#define COOLANT_MIST_PORT   PORTH
#define COOLANT_MIST_BIT    6 // MEGA2560 Digital Pin 9
#endif  

// Define user-control CONTROLs (cycle start, reset, feed hold) input pins.
// NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
#define CONTROL_DDR       DDRK
#define CONTROL_PIN       PINK
#define CONTROL_PORT      PORTK
#define RESET_BIT         0  // MEGA2560 Analog Pin 8
#define FEED_HOLD_BIT     1  // MEGA2560 Analog Pin 9
#define CYCLE_START_BIT   2  // MEGA2560 Analog Pin 10
#define SAFETY_DOOR_BIT   3  // MEGA2560 Analog Pin 11
#define CONTROL_INT       PCIE2  // Pin change interrupt enable pin
#define CONTROL_INT_vect  PCINT2_vect
#define CONTROL_PCMSK     PCMSK2 // Pin change interrupt register
#define CONTROL_MASK ((1<<RESET_BIT)|(1<<FEED_HOLD_BIT)|(1<<CYCLE_START_BIT)|(1<<SAFETY_DOOR_BIT))
#define CONTROL_INVERT_MASK CONTROL_MASK // May be re-defined to only invert certain control pins.

// Define probe switch input pin.
#define PROBE_DDR       DDRK
#define PROBE_PIN       PINK
#define PROBE_PORT      PORTK
#define PROBE_BIT       3  // MEGA2560 Analog Pin 11
#define PROBE_MASK      (1<<PROBE_BIT)

// Start of PWM & Stepper Enabled Spindle
#ifdef VARIABLE_SPINDLE
  // Advanced Configuration Below You should not need to touch these variables
  // Set Timer up to use TIMER4B which is attached to Digital Pin 7
  #define PWM_MAX_VALUE     65535.0
  #define TCCRA_REGISTER		TCCR2A
  #define TCCRB_REGISTER		TCCR2B
  #define OCR_REGISTER		  OCR2B
  
  #define COMB_BIT			    COM2B1
  #define WAVE0_REGISTER		WGM20
  #define WAVE1_REGISTER		WGM21
  #define WAVE2_REGISTER		WGM22
  #define WAVE3_REGISTER		WGM23
  
  #define SPINDLE_PWM_DDR		DDRH
  #define SPINDLE_PWM_PORT  PORTH
  #define SPINDLE_PWM_BIT		6 // MEGA2560 Digital Pin 9
#endif // End of VARIABLE_SPINDLE

// MOD GRBL for Cyclone

#define PROBE_PIN 18 // Z endstop
#define XLIM_PIN 3
#define YLIM_PIN 14

#define X_STEP_PIN         54 //PF0 ( ADC0 )
#define X_DIR_PIN          55 //PF1 ( ADC1 )
#define X_ENABLE_PIN       38 //PD7 ( T0 )

#define Y_STEP_PIN         60 //PF6 ( ADC6 )
#define Y_DIR_PIN          61 //PF7 ( ADC7 )
#define Y_ENABLE_PIN       56 //PF2 ( ADC2 )

#define Z_STEP_PIN         46 //PL3 ( OC5A )
#define Z_DIR_PIN          48 //PL1 ( ICP5 )
#define Z_ENABLE_PIN       62 //PK0 ( ADC8/PCINT16 )

#define SPINDLE_ENABLE_PIN 10
#define SPINDLE_DIRECTION_PIN 9
#define COOLANT_FLOOD_PIN 8
