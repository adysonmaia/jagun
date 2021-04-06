#!/bin/bash

qmake-qt4 -project
echo "QT += opengl" >> Jagun.pro
echo "QT += xml" >> Jagun.pro
qmake Jagun.pro
make
make clean

