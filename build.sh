!#/bin/bash

cmake -B build/
make -C build/
python gui.py