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
int IN_PIN = 8;
boolean keadaan = false;
//String a[10];

#if defined(ARDUINO_ARCH_SAMD)
   #define Serial SerialUSB
#endif

void setup(void) 
{
    led_inisialisasi(7);
    led_inisialisasi(9);
    led_inisialisasi(10);
    cek_led(7,1);     
    cek_led(9,1);
    cek_led(10,1);
    delay(1);
    cek_led(9,0);
    cek_led(10,0);
    Serial.begin(115200);
    //Serial.begin(9600);
    //checking semua sensor
    cek_inisialisasi_sdcard();
    cek_inisialisasi_fingerprint();
    relay_inisialisasi();
    cek_inisialisasi_nfc();
}

void loop(void) 
{
    //check_nfc();
    //Serial.println(getFingerprintIDez());
    String nfc = check_nfc_1();
    //nfc = "4991461381872134";
    Serial.println(nfc);
    if(nfc.equals("Gagal") == false)
    {
        //delay(1000);
        open_files("test_1.txt", 1); //Buka file tempat meyimpan data index file dengan permission READ
        int total,nama_file; //inisialisasi
        boolean cek_k;
        check_file(nfc,nama_file,total,cek_k); //Check File masih gagal
        //Serial.println(F("RUNN cek_k")); //Mode debugging
        if(cek_k){
            cek_led(9,1);
            Serial.println(F("Masukan jari:"));
            int cek_fp = getFingerprintIDez();
            while(!cek_fp){
                cek_fp = getFingerprintIDez();  
                //Serial.println(cek_fp);
            }
            //boolean cek_fp = true; // Mode Debugging
            close_connection();
            //Serial.println(F("RUNN cek_fp"));
            //Serial.println(total);
            Serial.println(cek_fp);
            if(cek_fp == 1){ 
                //Serial.println(hasil);
                String nama_file_str = String(nama_file) + ".txt";
                Serial.println(nama_file_str);
                open_files(nama_file_str, 1); //Buka file tempat meyimpan data index file dengan permission READ (kurang .txt)
                //id = 3;
                int fpku = 0;
                fpku = read_filesku(String(id));
                //delay(1000);
                if(fpku == 1){ // Add data id from fingersensor
                    if(keadaan == false){
                        cek_relay(0);
                        Serial.println(F("Relay aktif"));
                        keadaan = true;
                        cek_led(10,1);
                    }else{
                        cek_relay(1);
                        Serial.println(F("Relay tidak aktif"));
                        keadaan = false;
                        cek_led(10,0);
                    }
                    //id = -1
                }else{
                    Serial.println(F("Tidak ditemukan data jari"));
                }
            }
        }else
        {
            Serial.println(F("DATA tidak ditemukan"));
        }
        close_connection();
    }else
    {
        Serial.println(F("EKTP tidak ditemukan"));      
    }
    //cek_led(9,0);
    Serial.println(F("Waiting"));
}

