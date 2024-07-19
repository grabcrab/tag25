#include "tag.h"

#include <SparkFun_ST25DV64KC_Arduino_Library.h>

#include "utils.h"

SFE_ST25DV64KC_NDEF tag;

extern const unsigned char tag_txt_start[] asm("_binary_tags_file_tag_txt_start");
extern const unsigned char tag_txt_end[] asm("_binary_tags_file_tag_txt_end");

#define TXT_MAX_SIZE 3000
char theText[TXT_MAX_SIZE];

void setText(String txt)
{
    uint16_t txtSize = txt.length();
    memset(theText, 0, TXT_MAX_SIZE);
    Serial.printf("setText: %d bytes \r\n", txtSize);
    if (txtSize > TXT_MAX_SIZE)
    {
        Serial.printf("Warning! The text is too long (%d bytes), reduced to %d bytes\r\n", txtSize, TXT_MAX_SIZE);
        txtSize = TXT_MAX_SIZE;
    }
    memcpy(theText, txt.c_str(), txtSize);
}

void setTextFromFile(void)
{
    uint16_t txtSize = tag_txt_end - tag_txt_start;
    memset(theText, 0, TXT_MAX_SIZE);
    Serial.printf("setTextFromFile: %d bytes from src/tag.txt file\r\n", txtSize);
    if (txtSize > TXT_MAX_SIZE)
    {
        Serial.printf("Warning! The text is too long (%d bytes), reduced to %d bytes\r\n", txtSize, TXT_MAX_SIZE);
        txtSize = TXT_MAX_SIZE;
    }
    memcpy(theText, tag_txt_start, txtSize);
}

bool initTag(void)
{
    Wire.begin(SDA_PIN, SCL_PIN, I2C_FREQ);
    return tag.begin(Wire);
}

void printTag(void)
{
    uint16_t textLen = TXT_MAX_SIZE;
    Serial.println("NDEF field content:");
    if (tag.readNDEFText((uint8_t *)theText, &textLen))
        prettyPrintChars((uint8_t *)theText, textLen);
    else
        Serial.println("ERROR reading record!!!");
}

void writeTag(void)
{
    Serial.println(F("Writing CC_File"));
    if (!tag.writeCCFile8Byte())
        Serial.println("ERROR[1]");

    uint16_t memLoc = tag.getCCFileLen();

    Serial.print(F("Writing the NDEF Text record..."));
    unsigned long ms = millis();
    bool res = tag.writeNDEFText(theText, &memLoc);
    unsigned long deltaMs = millis() - ms;
    if (res)
    {
        Serial.printf(" done in %lu ms\r\n", deltaMs);
    }
    else
    {
        Serial.println("ERROR writing record!!!");
    }
}