#include "utils.h"
#include "tag.h"
#include "wifiUtils.h"

static String wifiStr = "";
static String prev_wifiStr = "";

void processFile(void)
{
    Serial.println("Processing the TAG text from the file:");
    setTextFromFile();
    writeTag();
    if (PRINT_TAG)
        printTag();
}

void processWiFi(void)
{
    const uint16_t noConDelayMs = (WIFI_GET_INTERVAL_S * 1000) / 5;
    wifiInit(WIFI_SSID, WIFI_PASS);
    while(true)
    {
        if (!wifiIsConnected())
        {
            Serial.printf("Wi-Fi is not connected, waiting connection [%s %s]...\r\n", WIFI_SSID, WIFI_PASS);
            delay(noConDelayMs);
            continue;
        }
        wifiPrintStatus();
        Serial.printf("Getting the TAG text by the link: %s \r\n", WIFI_TAG_TEXT_LINK);
        unsigned long ms = millis();
        wifiStr = wifiGetString(WIFI_TAG_TEXT_LINK);
        unsigned long deltaMs = millis() - ms;
        //Serial.println(wifiStr);
        //Serial.println();
        if (wifiStr != "")
        {
            if (wifiStr != prev_wifiStr)
            {
                Serial.printf("New TAG data received by the link in %lu ms\r\n", deltaMs);                
                setText(wifiStr);
                writeTag();
                if (PRINT_TAG)
                    printTag();
                prev_wifiStr = wifiStr;
            }
            else 
            {
                Serial.println("No new TAG data received by the link, SKIPPING");
            }
        }
        else
        {
            Serial.println("\r\nWarning!!! Empty string received from the server, connection or server error!");
        }
        Serial.printf("Delayed for %ds\r\n\n\n", WIFI_GET_INTERVAL_S);
        delay(WIFI_GET_INTERVAL_S * 1000);
    }
}

void setup()
{
    delay(1000);
    Serial.begin(115200);

    Serial.println("ST25DV64KC TAG");
    
    Serial.println("\n FW settings:");
    Serial.print("TAG from file:  ");
    if (USE_FILE)
    {
        Serial.println("ON");
    }
    else 
        Serial.println("OFF");

    Serial.print("TAG from Wi-Fi: ");
    if (USE_WIFI)
    {
        Serial.println("ON");
    }
    else 
        Serial.println("OFF");       

    Serial.print("Print TAG:      ");
    if (PRINT_TAG)
    {
        Serial.println("ON");
    }
    else 
        Serial.println("OFF");       


    if (!initTag())
    {
        Serial.println(F("ST25 not detected. Freezing..."));
        while (1) ;        
    }

    Serial.println(F("ST25 connected."));

    if (USE_FILE)
        processFile();   
    
    if (USE_WIFI)
    {
        processWiFi();
    }
}

void loop()
{

}

