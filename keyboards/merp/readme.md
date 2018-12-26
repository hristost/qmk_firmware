Merp
=======

Split 12x5 ortholinear bluetooth keyboard. See [hristost.github.io/projects/merp](hristost.github.io/projects/merp).

-- Hristo

## Programming the master half
1. Connect the keyboard via usb
2. `cd` to the root directory of this repository
3. Run `make merp/rev1:hs:avrdude`
4. Reset the keyboard, either by pressing a shortcut or by pushing the reset button on the master PCB

## Programming the slave half
1. Disconnect the slave half from the master
2. Connect the slave PCB to an ISP programmer
3. `cd` to the root directory of this repository
4. Run `make merp/rev1:hs:usbasp`
