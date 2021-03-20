#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

// place overrides here

/* We only use CTL_T style mod-tap keys, so we want the built-in
 * mod-tap-interrupt behavior to allow quickly typing CTRL-W arrow
 * sequences with a CTL_T(ESC) key */
//#undef IGNORE_MOD_TAP_INTERRUPT

/* We want our layer toggle tap to be a double tap */
#define TAPPING_TOGGLE 2

#define TAPPING_TERM 100
/* #define RETRO_TAPPING */

//#define DEBOUNCING_DELAY 10
#define MOUSEKEY_DELAY             0
#define MOUSEKEY_INTERVAL          16
#define MOUSEKEY_MAX_SPEED         8
#define MOUSEKEY_TIME_TO_MAX       60
#define MOUSEKEY_WHEEL_MAX_SPEED   1
#define MOUSEKEY_WHEEL_TIME_TO_MAX 120


#endif
