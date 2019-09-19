void cek_inisialisasi_sdcard(){
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    //return 1;
  }else{
    Serial.println("Found Sdcard!");
    //return 0;
  }
}

void open_files(String nama, boolean cek){
  //Serial.println("RUNNN OPENFILES "+nama);
  if (SD.exists(nama)) {
    //Serial.println(nama + " ada.");
    //myFile = cek == 0 ? SD.open(nama, FILE_WRITE) : SD.open(nama, FILE_READ);
    if(cek == 1) myFile = SD.open(nama, FILE_READ);
    else myFile = SD.open(nama, FILE_WRITE);
  }else {
    if(cek == 1) myFile = SD.open(nama, FILE_READ);
    else myFile = SD.open(nama, FILE_WRITE);
    //Serial.println(nama + " membuat file.");
  }
}

int read_filesku(String cari)
{
    //Serial.println("RUNN read_files");
    String data = "";
    int panjang = 0;
    if(myFile)
    {
        String parse_data[12];
        int z = 0;
        while (myFile.available())
        {
            //String list = myFile.readStringUntil('\n'); //MODE Debugging (test_s.txt)
            String list = myFile.readStringUntil(';'); //MODE Debugging (test_1.txt)
            //Serial.println(z);
            //Serial.println(list);
            /*parse_data[z] = list;
            z++;
            panjang = z;*/
            int ceking_index = list.indexOf(cari);
            if(ceking_index == 0)
            {
              //dataku += "2"; // Mode debugging
              return 1;
            }
        }
    
        /*for(int i = 0; i < panjang; ++i)
        {
            Serial.println(parse_data[i].indexOf(cari));
            if(parse_data[i].indexOf(cari) == 0)
            {
                return 1;   
            }
        }*/
    }else
    {
        Serial.println("Error opening " + cari + ".txt");
    }
    //Serial.println(data);
    return 0;
}

void check_file(String nama, int &nama_file, int &total, boolean &cek)
{
    String data[3];
    int panjang = 0;
    data[1] = "";
    data[2] = "";
    if(myFile)
    {
      int z = 0;
      String parse_data[12];
      while (myFile.available())
      {
        //String list = myFile.readStringUntil('\n'); //MODE Debugging (test_s.txt)
        String list = myFile.readStringUntil(';'); //MODE Debugging (test_1.txt)
        //Serial.println(t);
        //Serial.println(list);
        boolean b = false;
        int a = 0; //inisialisasi awal dari index data
        //Serial.println(parse_data[i].indexOf(nama));
        //Serial.println("RUNN check_file");
        if(list.indexOf(nama) == 0)
        {
          String data_list = list;
            for (int j = 0; j < list.length(); ++j)
            {
              if(b)
                {
                  if(isAlphaNumeric(list[j]))
                  {
                      data[a] += (data_list[j]);
                  }
                }
                if(!isAlphaNumeric(list[j]))
                {
                  b = true;
                  a++;
                }
            }
            cek = true;
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
      /*
      //Serial.println(parse_data[1]);
      for(int i = 0; i < panjang; ++i)
      {
        boolean b = false;
        int a = 0; //inisialisasi awal dari index data
        //Serial.println(parse_data[i].indexOf(nama));
        //Serial.println("RUNN check_file");
        if(parse_data[i].indexOf(nama) == 0)
        {
          String list = parse_data[i];
            for (int j = 0; j < parse_data[i].length(); ++j)
            {
              if(b)
                {
                  if(isAlphaNumeric(list[j]))
                  {
                      data[a] += (list[j]);
                  }
                }
                if(!isAlphaNumeric(list[j]))
                {
                  b = true;
                  a++;
                }
            }
            cek = true;
            break;
        }
        else
        {
          //Serial.println(parse_data[i].indexOf(nama));
            //data += (nama + ":" + String(nama_file) + "," + String(total));
            //Serial.println("RUNNNN");
            cek = false;
        }
      }*/
    }else{
      Serial.println("Error opening " + nama + ".txt");
    }
    total = data[2].toInt(); //Output menampilkan jumlah total data fingerprint
    nama_file = data[1].toInt(); //Output menampilkan nama file data tempat menyimpan fingerprint
    //Serial.println(total);
    //Serial.println(nama_file);
}

void close_connection()
{
  myFile.close();
}
