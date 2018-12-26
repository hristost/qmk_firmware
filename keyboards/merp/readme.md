Merp
=======

Split 12x5 ortholinear bluetooth keyboard. See [hristost.github.io/projects/merp](hristost.github.io/projects/merp).

To flash firmware to the master half, run

    make merp/rev1:hs:avrdude

 from the root folder of the repository

To flash firmware to the slave half, run

    make merp/rev1:hs

 from the root folder of the repository. Then, upload the resulting `.hex` file using an ISP programmer:
    avrdude -C/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -patmega32u4 -cusbasp -D -Uflash:w:.build/merp_rev1_hs.hex:i

-- Hristo

