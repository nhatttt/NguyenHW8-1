#!/bin/bash
echo "configuring and building GPIO Pins to be used"
config-pin -a p8.16 in+
config-pin -a p9.12 out
g++ control_GPIO.cpp -o control_GPIO
echo "configuration complete"
