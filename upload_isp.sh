#!/usr/local/bin/bash
avrdude -C/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -patmega32u4 -cusbasp -D -Uflash:w:.build/merp_rev1_hs.hex:i
