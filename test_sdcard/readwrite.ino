/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
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

void check_file(String nama, int &nama_file, int &total, boolean &cek)
{
  String data[2];
  int panjang = 0;
  if(myFile)
  {
    int z = 0;
    String parse_data[12];
    while (myFile.available())
    {
        String list = myFile.readStringUntil('\n');
        for (int i = 0; i < list.length(); ++i)
        {
          if(isAlphaNumeric(list[i]))
          {
            parse_data[z] += list[i];
          }else
          {
            //int z = list[i];
            //Serial.println(z);
            if(list[i] == 13 || list[i] == 10 || list[i] == 59 || list[i] == 244)
            {
              z++;
              //Serial.println("RUNN");
            }else parse_data[z] += list[i];
          }
        }
        panjang = z;
    }
    for(int i = 0; i < panjang; ++i)
    {
      boolean b = false;
      int a = 0; //inisialisasi awal dari index data
      Serial.println(parse_data[i].indexOf(nama));
      if(parse_data[i].indexOf(nama) != -1)
      {
        String list = parse_data[i];
        for (int j = 0; j < parse_data[i].length(); ++j)
        {
          if(b)
          {
            if(isAlphaNumeric(list[j]))
            {
              data[a] += (list[j]);
              cek = true;
            }
          }
          if(!isAlphaNumeric(list[j]))
          {
            b = true;
            a++;
          }
        }
        break;
      }
      else
      {
        //Serial.println(parse_data[i].indexOf(nama));
        //data += (nama + ":" + String(nama_file) + "," + String(total));
        Serial.println("RUNNNN");
        cek = false;
      }
    }
  }else{
    Serial.println("Error opening " + nama + ".txt");
  }
  total = data[1].toInt(); //Output menampilkan jumlah total data fingerprint
  nama_file = data[0].toInt(); //Output menampilkan nama file data tempat menyimpan fingerprint
}

String rewrite_file(String nama, int nama_file, int total)
{
  String data = "";
  int panjang = 0;
  if(myFile)
  {
    String parse_data[12];
    int z = 0;
    while (myFile.available())
    {
      String list = myFile.readStringUntil('\n');
      for (int i = 0; i < list.length(); ++i)
      {
        if(isAlphaNumeric(list[i]))
        {
          parse_data[z] += list[i];
        }else
        {
          int x = list[i];
          //Serial.print(x);
          //Serial.println(list[i]);
          //Serial.print("TEST\nCOK");
          if(list[i] == 13 || list[i] == 10 || list[i] == 59 || list[i] == 244){
            z++;
            //Serial.println("RUNN");
          }
          else parse_data[z] += list[i];
        }
        //Serial.println(parse_data[z]);
      }
      panjang = z;
    } 

    //Serial.println(parse_data);
    
    for(int i = 0; i < panjang; ++i)
    {
      if(parse_data[i].indexOf(nama))
      {
        data += parse_data[i];
        data += ";"; //hanya digunakan untuk debugging
      }else
      {
        //Serial.println(parse_data[i].indexOf(nama));
        data += nama;
        data += ":";
        data += String(nama_file);
        data += ",";
        data += String(total);
        data += ";";
      }
    }
  }else
  {
    Serial.println("Error opening " + nama + ".txt");
  }
  return data;
}

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

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  /*myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }*/

  // re-open the file for reading:
  
  // #########################################################################################################################################################
  //
  //                                                                   TESTING REWRITE FILE
  //
  // #########################################################################################################################################################
  /*
  String namafile = "test_1.txt";
  String namafiletest = "test_s.txt";

  myFile = SD.open(namafile, FILE_READ);
  String hasil = rewrite_file("4991461381872129",1,2);
  myFile.close();
  Serial.print(hasil);
  //String coba = "TESTING FILE BUK";
  //Serial.println(coba.indexOf("TEST"));
  
  SD.remove(namafile);
  myFile = SD.open(namafile, FILE_WRITE);
  if (myFile) {
    Serial.println("Writing to test.txt...");
    Serial.print(hasil);
    myFile.print(hasil);
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
  myFile = SD.open(namafile, FILE_READ);
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  */
  // #########################################################################################################################################################
  //
  //                                                                   TESTING CHECKING FILE
  //
  // #########################################################################################################################################################
  String namafile = "test_1.txt";
  String namafiletest = "test_s.txt";
  String nama_id = "4991461381872132";
  int n,m;
  boolean cek_k;

  myFile = SD.open(namafile, FILE_READ);
  //String hasil = rewrite_file("4991461381872129",1,2);
  check_file(nama_id, n, m, cek_k);
  myFile.close();
  if(cek_k == 1){
    Serial.print(nama_id);
    Serial.print(":");
    Serial.print(n);
    Serial.print(",");
    Serial.println(m);  
  }else Serial.println("Data tidak ditemukan");
  //String coba = "TESTING FILE BUK";
  //Serial.println(coba.indexOf("TEST"));
  
  myFile = SD.open(namafile, FILE_READ);
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {
  // nothing happens after setup
}

