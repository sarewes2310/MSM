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

void check_nfc()
{
    uint8_t success;
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
    uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
    if (success) {
        if (uidLength == 7)
        {
            Serial.println(F("RUNN"));
            uint8_t data[32];
            success = nfc.mifareultralight_ReadPage (4, data);
            String name = "4991461381872128";
            if (success)
            {
                //Debugging
                /*for(int i=0;i<uidLength;i++){
                    name += String(uid[i]);
                }*/
                Serial.println(name); //Value: 4991461381872128 nilai dari EKTP
                delay(1000);
                open_files("test_s.txt", 1); //Buka file tempat meyimpan data index file dengan permission READ
                int total,nama_file; //inisialisasi
                boolean cek_k;
                check_file(name,nama_file,total,cek_k);
                if(cek_k){
                    //Serial.println(cek_k);
                    boolean cek_fp = enroll_finger();
                    String hasil = rewrite_file(name, nama_file, total);
                    if(cek_fp){
                        close_connection();
                        open_files(nama_file, 0); //Buka file tempat meyimpan data index file dengan permission WRITE
                        write_files(id,1); //add data id from fingersensor
                        if(write_files(id, 1) == 1){
                            Serial.println(F("Berhasil"));
                        }else{
                            Serial.println(F("Gagal"));
                        }
                        close_connection();
                        remove_files("test_s.txt");
                        open_files("test_s.txt", 0); //Buka file tempat meyimpan data index file dengan permission WRITE
                        //write_files(hasil,0);
                        if(write_files(hasil, 0) == 1){
                            Serial.println(F("Berhasil"));
                        }else{
                            Serial.println(F("Gagal"));
                        }
                    }
                }else
                {
                    Serial.println(F("DATA tidak ditemukan"));
                }
                close_connection();

            }
            else
            {
                Serial.println(F("Ooops ... unable to read the requested page!?"));
            }
        }
    }
}

    