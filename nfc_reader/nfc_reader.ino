//#include <SoftwareSerial.h>

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
 
PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);

//SoftwareSerial Serial(10, 11); // RX, TX
byte data1,data2,data3,data4;

void setup(void) {
    Serial.begin(115200);
    //Serial.begin(9600);
    Serial.println("Hello!");
    test();
    pinMode(13,OUTPUT);
    digitalWrite(13,LOW);
    nfc.begin();
    uint32_t versiondata = nfc.getFirmwareVersion();
    if (! versiondata) {
        Serial.print("Didn't find PN53x board");
        while (1); // halt
    }
    // Got ok data, print it out!
    Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
    Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
    Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
    // Set the max number of retry attempts to read from a card
    // This prevents us from waiting forever for a card, which is
    // the default behaviour of the PN532.
    nfc.setPassiveActivationRetries(0xFF);
    // configure board to read RFID tags
    nfc.SAMConfig();
    Serial.println("Waiting for an ISO14443A card");
}

void loop(void) {
    boolean success;
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 }; // Buffer to store the returned UID
    uint8_t uidLength; // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    
    // Wait for an ISO14443A type cards (Mifare, etc.). When one is found
    // 'uid' will be populated with the UID, and uidLength will indicate
    // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
    
    if (success) {
        Serial.println("Found a card!");
        Serial.print("UID Length: ");
        Serial.print(uidLength, DEC);
        Serial.println(" bytes");
        Serial.println("UID Value: ");
        //char x[20];
        //String s;
        for (uint8_t i=0; i < uidLength; i++) 
        {
            Serial.print(" Data ke ");
            Serial.print(i);
            Serial.print(" 0x");
            Serial.println(uid[i]); 
            if (i==0) data1=uid[i];
            if (i==1) data2=uid[i];
            if (i==2) data3=uid[i];
            if (i==3) data4=uid[i];
        }
        Serial.println("");
        // Wait 1 second before continuing
        if ((data1==42)&&(data2==157)==(data3==227)&&(data4==117)) digitalWrite(13,HIGH);
        delay(1000);
        //Serial.println(data1);
        //Serial.println(data2);
        //Serial.println(data3);
        //Serial.println(data4);
    }
    else
    {
        // PN532 probably timed out waiting for a card
        Serial.println("Timed out waiting for a card");
        digitalWrite(13,LOW);
    }
}
