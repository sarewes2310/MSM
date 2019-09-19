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

boolean getFingerprintID() {
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
    id = finger.fingerID;
    delay(50);
    //return finger.fingerID;
    return true;
}

int getFingerprintIDez() {
    uint8_t p = finger.getImage();
    if (p != FINGERPRINT_OK)  return 0;
  
    p = finger.image2Tz();
    if (p != FINGERPRINT_OK)  return 0;
  
    p = finger.fingerFastSearch();
    if (p != FINGERPRINT_OK)  return 0 ;
    else {
        // found a match!
        Serial.print("Found ID #"); Serial.print(finger.fingerID); 
        Serial.print(" with confidence of "); Serial.println(finger.confidence);
        id = finger.fingerID;
        delay(50);
        return 1;  
    } 
}


