#!/usr/bin/env bash

check_devices=`lsusb | grep eZ430`

if [ $# -lt 1 ]
then
    echo "Not enough arguments, usage $0 <file to flash>"
    exit 1
fi

echo "check $check_devices"

if [ -n "$check_devices" ]
then
    echo "Detected ez430 dev kit"
    echo 'mspdebug rf2500 "prog ' $1 '"'
    mspdebug rf2500 "prog $1"
    exit 0
fi

check_devices=`lsusb | grep 2047`

if [ -n "$check_devices" ]
then
    echo "Detected msp430 dev kit"
    echo '/opt/ti/uniflash/dslite.sh --config /opt/ti/uniflash/MSP430G2553.ccxml -f ' $1
    /opt/ti/uniflash/dslite.sh --config /opt/ti/uniflash/MSP430G2553.ccxml -f $1
    exit 0
else
    echo "No valid msp430 devices found! Are you sure the MSP430 is connected to the vm (check lsusb)? "
    exit 1
fi


   
