#pragma once
#include <iostream>
#include "FixedPoint.h"

void displayInputMessage();
void mainLoop(short*, int&, const int&);
void mainLoop(short*, int&, const unsigned int&);
void mainLoop(short*, int&, const FixedPoint&);
void mainLoop(short*, unsigned int&, const int&);
void mainLoop(short*, unsigned int&, const unsigned int&);
void mainLoop(short*, unsigned int&, const FixedPoint&);
void mainLoop(short*, FixedPoint&, const int&);
void mainLoop(short*, FixedPoint&, const unsigned int&);
void mainLoop(short*, FixedPoint&, const FixedPoint&);