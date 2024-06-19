#include "utils.h"

void prettyPrintChars(uint8_t *theData, int theLength)
{
    const int charPerLine = 32;
    Serial.println();

    for (int i = 0; i < theLength; i += charPerLine)
    {
        if (i < 10000)
            Serial.print(F("0"));
        if (i < 1000)
            Serial.print(F("0"));
        if (i < 100)
            Serial.print(F("0"));
        if (i < 10)
            Serial.print(F("0"));
        Serial.print(i);

        Serial.print(F(" 0x"));

        if (i < 0x1000)
            Serial.print(F("0"));
        if (i < 0x100)
            Serial.print(F("0"));
        if (i < 0x10)
            Serial.print(F("0"));
        Serial.print(i, HEX);

        Serial.print(F(" "));

        int j;
        for (j = 0; ((i + j) < theLength) && (j < charPerLine); j++)
        {
            if (theData[i + j] < 0x10)
                Serial.print(F("0"));
            Serial.print(theData[i + j], HEX);
            Serial.print(F(" "));
        }

        if (((i + j) == theLength) && (j < 16))
        {
            for (int k = 0; k < (charPerLine - (theLength % charPerLine)); k++)
            {
                Serial.print(F("   "));
            }
        }

        for (j = 0; ((i + j) < theLength) && (j < charPerLine); j++)
        {
            if ((theData[i + j] >= 0x20) && (theData[i + j] <= 0x7E))
                Serial.write(theData[i + j]);
            else
                Serial.print(F("."));
        }

        Serial.println();
    }

    Serial.println();
}
