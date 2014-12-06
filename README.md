arduino-rgb-pwm-decade-counter
==============================

Licensed under Apache 2.0

Some funky arduino PWMing with a decade counter in the way.

This includes an Arduino sketch and related schematic.  The schematic has a PNG snapshot, the source is in EagleCAD.

Late one night, in a drunken stupor, I thought it might be cool to run a bunch of LEDs with an arduino using a cheap decade counter to save pins.  Decade counters are really cheap.

The schematic is a mess.  It's for a 74xxx series decade counter but I don't think EagleCAD had the part I was using...I was really drunk when I designed this.

It's been a while since I've used the circuit.  This is just a funky way to multiplex the PWM outputs of an Arduino.  By coordinating the decade counter clock and PWM cycles, one can roughly control the colors on all three LEDs simultaneously.

The firmware attempts to coordinate this.  It doesn't do a great job.  From what I recall the colors are not clean and I wrestled with the firmware to correct it, with limited success.  IF such a thing was worth attempting any further, it would probably be more suitable in assembler or with an RTOS.
