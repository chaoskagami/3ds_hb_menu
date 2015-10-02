#!/bin/bash

# If you run some system where py3 is the default, slap a 2 on the end.
PYTHON=python

$PYTHON font.py font.fnt font1 > source/font1.c
$PYTHON font.py fontSmall.fnt font2 > source/font2.c
