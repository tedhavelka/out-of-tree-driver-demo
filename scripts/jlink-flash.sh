#!/bin/bash

# /opt/SEGGER/JLink/JLinkExe -nogui 1 -if swd -speed auto -device LPC55S69_M33_0 -CommanderScript /usr/local/bin/runner-cpu0.jlink
/opt/SEGGER/JLink/JLinkExe -nogui 1 -if swd -speed auto -device LPC55S69_M33_0 -CommanderScript ./runner-cpu0.jlink

# ExitOnError 1
# r
# loadfile "/home/ted/projects/container-based/v2-driver/build/zephyr/zephyr.bin" 0x10000000
# g
# writeDP 1 0 
# readDP 1
# q

exit $?
