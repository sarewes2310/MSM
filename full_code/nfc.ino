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
    //success = 1; // Mode Debugging
    //uidLength = 7; // Mode Debugging
    if (success) {
        if (uidLength == 7)
        {
            Serial.println(F("RUNN"));
            uint8_t data[32];
            success = nfc.mifareultralight_ReadPage (4, data); //mode debugging mati
            //String nameku = "4991461381872134";
            String nameku = "";
            if (success)
            {
                for(int i=0;i<uidLength;i++){
                    nameku += String(uid[i]);
                }
                //Serial.println(nameku); //Value: 4991461381872128 nilai dari EKTP
                delay(1000);
                
                /* Inisialisasi variabel */
                open_files("test_1.txt", 1); //Buka file tempat meyimpan data index file dengan permission READ
                int total,nama_file; //inisialisasi
                boolean cek_k;
                
                /* Cek data EKTP */
                check_file(nameku,nama_file,total,cek_k); //Check File masih gagal
                //Serial.println(F("RUNN cek_k")); //Mode debugging
                //Serial.println(cek_k);
                close_connection();
                
                /* Hasil cek data EKTP */
                if(cek_k == 1)
                {
                    if(total < 10)
                    {
                        //Serial.println(cek_k);
                        boolean cek_fp = enroll_finger();
                        //boolean cek_fp = true; //MODE:DEBUGGING
                        delay(1000);
                        //Serial.println(F("RUNN cek_fp")); //MODE:DEBUGGING
                        //Serial.println(total); //MODE:DEBUGGING
                        if(cek_fp == true){ 
                            //Serial.println(hasil);
                            
                            /* Menulis ulang data index EKTP */
                            total = total + 1;  
                            open_files("test_1.txt", 1); //Buka file tempat meyimpan data index file dengan permission READ
                            String hasil = rewrite_file(nameku, nama_file, total);
                            close_connection();
                            Serial.println(hasil);
                            
                            /* Menambah data sidik jari pada ektp */
                            String nama_file_str = String(nama_file) + ".txt";
                            //Serial.println(nama_file_str);
                            open_files(nama_file_str, 0); //Buka file tempat meyimpan data index file dengan permission WRITE (kurang .txt)
                            //id = 2; //MODE:DEBUGGING
                            int fp = write_files(String(id)+";", 0);
                            if(fp == 1){ // Add data id from fingersensor
                                Serial.println(F("Berhasil menambahkan data jari"));
                            }else{
                                Serial.println(F("Gagal menambahkan data jari"));
                            }
                            //Serial.println(total);
                            close_connection();
                            
                            /* Menambah data hasil dari tulis ulang data index */
                            remove_files("test_1.txt");
                            open_files("test_1.txt", 0); //Buka file tempat meyimpan data index file dengan permission WRITE
                            //write_files(hasil,0);
                            if(write_files(hasil, 0) == 1){
                                Serial.println(F("Berhasil merubah data index"));
                            }else{
                                Serial.println(F("Gagal merubah data index"));
                            }
                        }else
                        {
                            Serial.println(F("Berhasil menambahkan data pada fingerprint sensor"));
                        }
                    }else
                    {
                        Serial.println(F("Data jari telah penuh pada EKTP ini"));       
                    }
                }
                close_connection();
            }
            else
            {
                Serial.println(F("Data EKTP tidak ditemukan"));
            }
        }else
        {
            Serial.println(F("Anda bukan memasukkan kartu EKTP"));
        }
    }
}
