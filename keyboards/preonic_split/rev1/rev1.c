#include "viterbi.h"

void matrix_init_kb(void) {
    // JTAG disable for PORT F. write JTD bit twice within four cycles.
    // We need this to use pin PF4
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);

    // // green led on
    // DDRD |= (1<<5);
    // PORTD &= ~(1<<5);

    // // orange led on
    // DDRB |= (1<<0);
    // PORTB &= ~(1<<0);

	matrix_init_user();
};
