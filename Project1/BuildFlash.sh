# This program builds and flashes the current ESP32-project
# To make executable: chmod u+x BuildFlash.sh

#!/bin/zsh
whoami
date

echo ">>> Executing get_idf"
. $HOME/esp/esp-idf/export.sh

echo ">>> Building project"
idf.py build

# find available serial ports with
# $ ls /dev/cu.*
echo ">>> Flashing project"
# idf.py -p /dev/cu.usbserial-5 flash
idf.py -p /dev/cu.usbserial-4 flash
