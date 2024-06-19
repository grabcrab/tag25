# tag25
SparkFun Qwiic Dynamic NFC/RFID Tag with dynamic update over Wi-Fi

1. Running in the file-only mode (the NDEF text is loaded from the file):
    - Open the platformio.ini file and change the TAG source parameters in the following way:
        -D USE_FILE=1
        -D USE_WIFI=0
    - Open the src/tag.txt file and edit the TAG's text.
    - Upload the firmware.
    - Scan the ТАG, check if the text from the TAG matches the text from the file.

2. Running in the Wi-Fi-only mode (the NDEF text is loaded from the online resource):
    - Open the platformio.ini file and change the parameters in the following way:
        - Open the platformio.ini file and change the TAG source parameters in the following way:
            -D USE_FILE=0
            -D USE_WIFI=1
        


