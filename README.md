# tag25
SparkFun Qwiic Dynamic NFC/RFID Tag with dynamic update over Wi-Fi

1. Running in the file-only mode (the NDEF text is loaded from the file):
    - Open the platformio.ini file and change the TAG source parameters in the following way:
        -D USE_FILE=1
        -D USE_WIFI=0
    - Open the tags/file_tag.txt file and edit the TAG's text.
    - Upload the firmware.
    - Scan the ТАG, check if the text from the TAG matches the text from the file.

2. Running in the Wi-Fi-only mode (the NDEF text is loaded from the online resource):
    - Open the platformio.ini file and change the parameters in the following way:
        - Open the platformio.ini file and change the TAG source parameters in the following way:
            -D USE_FILE=0
            -D USE_WIFI=1
        - Change the Wi-Fi credentials for the Wi-Fi network that is used for connection:
            -D WIFI_SSID=\"tcutestnet\"
            -D WIFI_PASS=\"tcutestpass\"	
        - Set the text update interval (in seconds):
            -D WIFI_GET_INTERVAL_S=30
        - Set the hyperlink to the TAG's text (any raw text file can be used):
            -D WIFI_TAG_TEXT_LINK=\"https://raw.githubusercontent.com/grabcrab/tag25/main/tags/test_tag2.txt\"
        - Upload the firmware.
        - Scan the ТАG, check if the text from the TAG matches the text from the online resource.
        


