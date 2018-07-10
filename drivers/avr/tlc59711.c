/*
 * TLC59711 LED driver interface
 *
 * Version 1.0  - July 2018
 * Author: Hristo (hristo.staykov@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "tlc59711.h"
#include <stdlib.h>
#include <stdbool.h>
#include "pincontrol.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "wait.h"
#include "debug.h"
#include "matrix.h"
#include "LUFA/Drivers/Peripheral/SPI.h"


#define ROW_SHIFTER ((uint8_t)1)
#define max(a,b) \
	({ __typeof__ (a) _a = (a); \
	 __typeof__ (b) _b = (b); \
	 _a > _b ? _a : _b; })
void updateLEDMatrix(matrix_row_t* matrix);
#define TLC59711_NUM_DRIVERS 3
#define TLC59711_NUM_COLUMNS 6
#define TLC59711_NUM_ROWS    5

uint8_t ledState[TLC59711_NUM_ROWS][TLC59711_NUM_COLUMNS];
uint8_t ledStateOld[TLC59711_NUM_ROWS][TLC59711_NUM_COLUMNS];
uint8_t ledStateRaw[TLC59711_NUM_DRIVERS*12];
/// Mapping between LED in physical grid and LED order in hardware
uint8_t ledAddress[TLC59711_NUM_ROWS][TLC59711_NUM_COLUMNS] = {
  {11, 0, 2, 34, 35, 24},
  {7, 1, 3, 32, 33, 25},
  {6, 5, 4, 31, 30, 29},
  {23, 22, 21, 12, 13, 14},
  {20, 19, 18, 17, 16, 15}
};

void tlc59711_init() {
    memset(ledState, 0, TLC59711_NUM_ROWS*TLC59711_NUM_COLUMNS);
    memset(ledStateOld, 0, TLC59711_NUM_ROWS*TLC59711_NUM_COLUMNS);
    memset(ledStateRaw, 0, TLC59711_NUM_DRIVERS*12);
    ledState[2][2] = 100;

    pinMode(B7, PinDirectionOutput);
    digitalWrite(B7, PinLevelLow);

    // Initialize the SPI driver before first use
    SPI_Init(SPI_SPEED_FCPU_DIV_8 | SPI_ORDER_MSB_FIRST | SPI_SCK_LEAD_FALLING |
            SPI_SAMPLE_TRAILING | SPI_MODE_MASTER);

    tlc59711_enable_interrupt();
}

void tlc59711_enable_interrupt() {
    TCCR1B |= (1 << CS10);
    TCNT1 = 0;
    TIMSK1 |= (1 << TOIE1);
    sei();
}



bool shouldRefresh = false;
void tlc59711_write(uint8_t* data) {

    // Send several bytes, ignoring the returned data
    uint32_t command;

    // Magic word for write
    command = 0x25;

    command <<= 5;
    //OUTTMG = 1, EXTGCK = 0, TMGRST = 1, DSPRPT = 1, BLANK = 0 -> 0x16
    command |= 0x16;

    command <<= 7;
    command |= 0x7F;

    command <<= 7;
    command |= 0x7F;

    command <<= 7;
    command |= 0x7F;

    //cli();
    digitalWrite(B7, PinLevelHigh);
    for (uint8_t n=0; n<3; n++) {
        SPI_SendByte(command >> 24);
        SPI_SendByte(command >> 16);
        SPI_SendByte(command >> 8);
        SPI_SendByte(command);

        // 12 channels per TLC59711
        for (int8_t c=11; c >= 0 ; c--) {
            // 16 bits per channel, send MSB first
            SPI_SendByte(data[n*12+c]);
            SPI_SendByte(0);
        }
    }
    digitalWrite(B7, PinLevelLow);
    //sei();
}
uint8_t colour = 0;
void updateLEDMatrix(matrix_row_t* matrix) {
    memcpy(ledStateOld, ledState, TLC59711_NUM_COLUMNS*TLC59711_NUM_ROWS);
    for(int x=0; x<TLC59711_NUM_COLUMNS; x++) for(int y=0; y<TLC59711_NUM_ROWS; y++) {
        int xSum = ledStateOld[y][x]*3;
        int xCount = 3;

        if(x>0) {xSum += ledStateOld[y][x-1]; xCount++;}
        if(x<TLC59711_NUM_COLUMNS-1) {xSum += ledStateOld[y][x+1]; xCount++;}
        if(y>0) {xSum += ledStateOld[y-1][x]; xCount++;}
        if(y<TLC59711_NUM_ROWS-1) {xSum += ledStateOld[y+1][x]; xCount++;}

        xSum -= 2;
        ledStateRaw[ledAddress[y][x]] = matrix_is_on(y, x) ? 100 : max(0, xSum) / xCount;
        ledState[y][x] = max(0, xSum) / xCount;
    }

}
void tlc59711_task(matrix_row_t* matrix) {
    if(!shouldRefresh) return;
    shouldRefresh = false;
    updateLEDMatrix(matrix);
    tlc59711_write(ledStateRaw);

}


/* Assuming a 16MHz CPU clock and a timer that resets at 64k (ICR1), the following interrupt handler will run
 * about 244 times per second.
 */
ISR(TIMER1_OVF_vect) {
    static uint8_t frame = 0;
    if (frame++==4) {
        frame = 0;
        shouldRefresh =  true;
    }
}
bool tlc59711_process_matrix(uint16_t keycode, keyrecord_t *record) {
    if ( record->event.pressed ) {
        /* ledState[record->event.key.row][record->event.key.col] = 20; */
    } else {
        ledState[record->event.key.row][record->event.key.col] = 100;
    }
	return true;
}
