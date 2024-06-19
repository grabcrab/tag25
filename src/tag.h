#pragma once
#include <Arduino.h>

bool initTag(void);
void setTextFromFile(void);
void setText(String txt);
void writeTag(void);
void printTag(void);