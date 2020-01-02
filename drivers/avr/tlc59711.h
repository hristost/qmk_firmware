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

#ifndef LIGHT_TLC59711_H_
#define LIGHT_TLC59711_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "matrix.h"
#include "quantum.h"
#include <stdbool.h>


/// Initialize the SPI interface needed for the LED driver
void tlc59711_init(void);
/// Enable the refresh interrupt
void tlc59711_enable_interrupt(void);
/// Disable the refresh interrupt
void tlc59711_disable_interrupt(void);
/// Whether backlight is enabled
bool tlc59711_is_enabled(void);

bool tlc59711_toggle_enabled(void);
void tlc59711_set_enabled(bool enabled);
/// Tell the LED driver to transmit data if needed
void tlc59711_task(matrix_row_t* matrix);
void tlc59711_write(uint8_t* data);

bool tlc59711_process_matrix(uint16_t keycode, keyrecord_t *record);

#endif /* LIGHT_TLC59711_H_ */
