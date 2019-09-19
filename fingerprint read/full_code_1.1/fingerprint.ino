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

uint8_t readnumber(void) 
{
  uint8_t num = 0; 
  while (num == 0) 
    {
      while (! Serial.available());
      num = Serial.parseInt();
    }
    return num;
}

boolean enroll_finger()
{
  Serial.println(F("Masukan ID"));
  id = readnumber();
  if (id == 0) {// ID #0 not allowed, try again!
    return 255;
    }
    //Serial.print(F("Enrolling ID #"));
    //Serial.println(id);
    while (!  getFingerprintEnroll() );
    //return 0;
    //Serial.println(F("OUT getFingerprintEnroll"));
    return true;
}

void rule_cek_fingerprint(int p)
{
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println(F("Image taken"));
        break;
    case FINGERPRINT_NOFINGER:
        Serial.println(F("."));
        break;
    case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println(F("Communication error"));
        break;
    case FINGERPRINT_IMAGEFAIL:
        Serial.println(F("Imaging error"));
        break;
    default:
        Serial.println(F("Unknown error"));
        break;
  }
}

void cek_fingerprint(int p)
{
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    rule_cek_fingerprint(p);
  }
}

uint8_t getFingerprintEnroll() 
{
  int p = -1;
  Serial.print(F("Waiting for valid finger to enroll as #")); 
  Serial.println(id);
  cek_fingerprint(p); // Proses mengambil data jari awal

  // OK success!
  p = finger.image2Tz(1); // convert data image jari awal
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
  
  Serial.println(F("Remove finger"));
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print(F("ID ")); Serial.println(id);
  p = -1;
  Serial.println(F("Place same finger again"));
  cek_fingerprint(p); // Proses mengambil data jari awal untuk verifikasi

  // OK success!
  p = finger.image2Tz(2); // convert data image jari awal yang sama
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
  Serial.print(F("Creating model for #"));  Serial.println(id);
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println(F("Prints matched!"));
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println(F("Communication error"));
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println(F("Fingerprints did not match"));
    return p;
  } else {
    Serial.println(F("Unknown error"));
    return p;
  }
  
  Serial.print(F("ID ")); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println(F("Stored!"));
    Serial.println(p);
    return 1;
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println(F("Communication error"));
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println(F("Could not store in that location"));
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println(F("Error writing to flash"));
    return p;
  } else {
    Serial.println(F("Unknown error"));
    return p;
  } 
}

