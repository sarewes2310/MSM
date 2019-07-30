#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Fingerprint.h>



#define PN532_IRQ   (5)
#define PN532_RESET (6)  // Not connected by default on the NFC Shield

//inisialisasi variabel dari sensor
File myFile;
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;
//int IN_PIN = 8;
//String a[10];

#if defined(ARDUINO_ARCH_SAMD)
   #define Serial SerialUSB
#endif

void setup(void) 
{
    Serial.begin(115200);
    //checking semua sensor
    cek_inisialisasi_sdcard();
    cek_inisialisasi_fingerprint();
    //cek_inisialisasi_nfc();
}

void loop(void) 
{
    check_nfc();
}
