#!/bin/bash
#This script will build the executable and copy it to usr/bin/

cd build/
gmake ..
make
sudo cp lkctrl /usr/bin
