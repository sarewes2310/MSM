/*
  SD card basic file example

 This example shows how to create and destroy an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */
#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  if (SD.exists("test_s.txt")) {
    Serial.println("test_s.txt exists.");
  } else {
    Serial.println("test_s.txt doesn't exist.");
  }

  // open a new file and immediately close it:
  Serial.println("Creating test_s.txt...");
  myFile = SD.open("test_s.txt", FILE_WRITE);
  myFile.close();

  // Check to see if the file exists:
  if (SD.exists("test_s.txt")) {
    Serial.println("test_s.txt exists.");
  } else {
    Serial.println("test_s.txt doesn't exist.");
  }

  // delete the file:
  Serial.println("Removing test_s.txt...");
  SD.remove("test_s.txt");

  if (SD.exists("test_s.txt")) {
    Serial.println("test_s.txt exists.");
  } else {
    Serial.println("test_s.txt doesn't exist.");
  }
}

void loop() {
  // nothing happens after setup finishes.
}


