#!/usr/local/bin/bash
avrdude -C/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -patmega32u4 -cusbasp -D -Uflash:w:.build/preonic_split_rev1_default.hex:i
