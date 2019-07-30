void cek_inisialisasi_fingerprint()
{
    finger.begin(57600);
    if (finger.verifyPassword()) 
    {
      Serial.println(F("Found fingerprint"));
    }
    else 
    {
      Serial.println(F("Fingerprints not found"));
      while (1) { delay(1); }
    }
}

uint8_t getFingerprintID() {
    uint8_t p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println(F("Image taken"));
        break;
      case FINGERPRINT_NOFINGER:
        Serial.println(F("No finger detected"));
        return p;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println(F("Communication error"));
        return p;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println(F("Imaging error"));
        return p;
      default:
        Serial.println(F("Unknown error"));
        return p;
    }
  
    // OK success!
  
    p = finger.image2Tz();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println(F("Image converted"));
        break;
      case FINGERPRINT_IMAGEMESS:
        Serial.println(F("Image too messy"));
        return p;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println(F("Communication error"));
        return p;
      case FINGERPRINT_FEATUREFAIL:
        Serial.println(F("Could not find fingerprint features"));
        return p;
      case FINGERPRINT_INVALIDIMAGE:
        Serial.println(F("Could not find fingerprint features"));
        return p;
      default:
        Serial.println(F("Unknown error"));
        return p;
    }
    
    // OK converted!
    p = finger.fingerFastSearch();
    if (p == FINGERPRINT_OK) {
      Serial.println(F("Found a print match!"));
    } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
      Serial.println(F("Communication error"));
      return p;
    } else if (p == FINGERPRINT_NOTFOUND) {
      Serial.println(F("Did not find a match"));
      return p;
    } else {
      Serial.println(F("Unknown error"));
      return p;
    }   
    
    // found a match!
    Serial.print(F("Found ID #")); Serial.print(finger.fingerID); 
    Serial.print(F(" with confidence of ")); Serial.println(finger.confidence); 
  
    return finger.fingerID;
}

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
            //Serial.println("RUNNNN");
            cek = false;
        }
      }
    }else{
      Serial.println("Error opening " + nama + ".txt");
    }
    total = data[1].toInt(); //Output menampilkan jumlah total data fingerprint
    nama_file = data[0].toInt(); //Output menampilkan nama file data tempat menyimpan fingerprint
}

