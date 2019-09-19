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
                //Debugging
                for(int i=0;i<uidLength;i++){
                    nameku += String(uid[i]);
                }
                //Serial.println(nameku); //Value: 4991461381872128 nilai dari EKTP
                delay(1000);
                open_files("test_1.txt", 1); //Buka file tempat meyimpan data index file dengan permission READ
                int total,nama_file; //inisialisasi
                boolean cek_k;
                check_file(nameku,nama_file,total,cek_k); //Check File masih gagal
                //Serial.println(F("RUNN cek_k")); //Mode debugging
                //Serial.println(cek_k);
                close_connection();
                if(cek_k == 0)
                {
                    Serial.println(F("Data EKTP tidak ditemukan"));
                    delay(1000);
                    Serial.println(F("Memebuat data EKTP baru........."));
                    int jumlah_ektp;
                    open_files("test_2.txt", 1);
                    check_jumlah_ektp(jumlah_ektp);
                    close_connection();
                    if(jumlah_ektp < 12)
                    {
                        boolean cek_fp = enroll_finger();
                        //boolean cek_fp = true; // Mode Debugging
                        if(cek_fp == true){ 
                        
                            /* Menulis ulang data index ektp */
                            String add_new_data = nameku + ":" + String(jumlah_ektp) + ",1;";
                            //Serial.println(add_new_data);
                            String nama_file_str = String(jumlah_ektp) + ".txt";
                            //Serial.println(nama_file_str);
                            
                            /* Menambad data jari */
                            open_files(nama_file_str, 0); //Buka file tempat meyimpan data index file dengan permission WRITE (kurang .txt)
                            //write_files(id,1); //add data id from fingersensor
                            //id = 2; //Mode Debugging
                            Serial.println(id);
                            delay(5);
                            int fp = write_files(String(id)+";", 0);
                            if(fp == 1){ // Add data id from fingersensor
                                Serial.println(F("Berhasil menambahkan data jari"));
                            }else{
                                Serial.println(F("Gagal menambahkan data jari"));
                            }
                            //Serial.println(total);
                            close_connection();
                            
                            /* Menambahkan data jumlah ektp */
                            jumlah_ektp += 1;
                            //add_nfc_sdcard(nameku, (jumlah_ektp + 1), 0);
                            String hasil_jumlah_ektp = String(jumlah_ektp) + ";";
                            //Serial.println(hasil_jumlah_ektp);
                            remove_files("test_2.txt");
                            open_files("test_2.txt", 0); // Permission READ
                            if(write_files(hasil_jumlah_ektp, 0))
                            {   
                                Serial.println(F("Jumlah Data EKTP baru berhasil ditambahkan"));
                            }else
                            {
                                Serial.println(F("Jumlah Data EKTP baru Gagal ditambahkan"));
                            }
                            close_connection();
                            
                            /* Menambahkan data index ektp */
                            open_files("test_1.txt", 0); // Permission READ
                            delay(5);
                            if(write_files(add_new_data, 0))
                            {   
                                Serial.println(F("Data EKTP baru berhasil ditambahkan"));
                            }else
                            {
                                Serial.println(F("Data EKTP baru Gagal ditambahkan"));
                            }
                        }
                    }else
                    {
                        Serial.println(F("Data EKTP pada sistem penuh"));
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

