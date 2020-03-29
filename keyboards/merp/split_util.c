#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <string.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "split_util.h"
#include "matrix.h"
#include "keyboard.h"
#include "config.h"
#include "timer.h"
#include "tlc59711.h"

#ifdef USE_I2C
#  include "i2c.h"
#else
#  include "serial.h"
#endif

volatile bool isLeftHand = true;
extern matrix_row_t* matrix_get(void);
extern bool matrix_was_on(matrix_row_t* matrix, uint8_t row, uint8_t col);

static matrix_row_t matrix_old[MATRIX_ROWS];

static void setup_handedness(void) {
  #ifdef EE_HANDS
    isLeftHand = eeprom_read_byte(EECONFIG_HANDEDNESS);
  #else
    // I2C_MASTER_RIGHT is deprecated, use MASTER_RIGHT instead, since this works for both serial and i2c
    #if defined(I2C_MASTER_RIGHT) || defined(MASTER_RIGHT)
      isLeftHand = !has_usb();
    #else
      isLeftHand = has_usb();
    #endif
  #endif
}

static void keyboard_master_setup(void) {
    return;
#ifdef USE_I2C
    i2c_master_init();
#else
    serial_master_init();
#endif
}

static void keyboard_slave_setup(void) {
  timer_init();
#ifdef USE_I2C
    i2c_slave_init(SLAVE_I2C_ADDRESS);
#else
    serial_slave_init();
#endif
}

bool has_usb(void) {
   return false;
   USBCON |= (1 << OTGPADE); //enables VBUS pad
   _delay_us(5);
   return (USBSTA & (1<<VBUS));  //checks state of VBUS
}

void split_keyboard_setup(void) {
   setup_handedness();
   tlc59711_init();

   if (has_usb()) {
      keyboard_master_setup();
   } else {
      keyboard_slave_setup();
   }
   sei();
}

void keyboard_slave_loop(void) {
   matrix_init();

   while (1) {
       // Keep a copy of the old matrix so we can see what has changed as qmk
       // is not actually running because of the infinite loop
       memcpy(matrix_old, matrix_get(), MATRIX_ROWS*sizeof(matrix_row_t));
       matrix_slave_scan();
       for(int row=0; row<MATRIX_ROWS; row++) 
           for(int column=0; column<MATRIX_COLS; column++) {
               bool isOn = matrix_is_on(row, column);
               bool wasOn = matrix_was_on(matrix_old, row, column);
               if (isOn!=wasOn) {
                   keyrecord_t record;
                   record.event.pressed = isOn;
                   record.event.key.row = row;
                   record.event.key.col = column;
                   tlc59711_process_matrix(0, &record);

               }

           }
      /* matrix_was_on(0, 0); */
   }
}

// this code runs before the usb and keyboard is initialized
void matrix_setup(void) {
    split_keyboard_setup();

    if (!has_usb()) {
        keyboard_slave_loop();
    }
}
