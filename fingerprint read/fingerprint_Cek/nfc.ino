// Global variables use 1,383 bytes (67.5%) of dynamic memory, leaving 665 bytes for local variables. Maximum is 2,048 bytes.
void cek_inisialisasi_nfc()
{
    nfc.begin();
    uint32_t versiondata = nfc.getFirmwareVersion();
    if (! versiondata) {
        Serial.println(F("Didn't find PN53x board"));
        while (1); // halt
    }else{
        Serial.println(F("Found PN53x board"));
    }

    // configure board to read RFID tags
    nfc.SAMConfig();  
    Serial.println(F("Waiting"));
}

String check_nfc_1()
{
    uint8_t success;
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
    uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
    //success = 1; // Mode Debugging
    //uidLength = 7; // Mode Debugging
    if (success) {
        if (uidLength == 7)
        {
            //Serial.println(F("RUNN"));
            uint8_t data[32];
            success = nfc.mifareultralight_ReadPage (4, data); //mode debugging mati
            if (success)
            {
                String nameku = "";
                for(int i=0;i<uidLength;i++){
                    nameku += String(uid[i]);
                }
                return nameku;
            }
            else
            {
                Serial.println(F("Ooops ... unable to read the requested page!?"));
                return "Gagal";
            }
        }
    }
}   
