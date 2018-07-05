#!/usr/local/bin/bash
avrdude -C/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -patmega32u4 -cavr109 -P/dev/cu.usbmodem1411 -b57600 -D -Uflash:w:.build/merp_rev1_hs.hex:i
avrdude -C/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -patmega32u4 -cavr109 -P/dev/cu.usbmodem143111 -b57600 -D -Uflash:w:.build/merp_rev1_hs.hex:i
