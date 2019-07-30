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
  Serial.println("RUNNN OPENFILES "+nama);
  if (SD.exists(nama)) {
    Serial.println(nama + " ada.");
    myFile = cek == 0 ? SD.open(nama, FILE_WRITE) : SD.open(nama, FILE_READ);
  }else {
    Serial.println(nama + " membuat file.");
  }
}

int write_files(String data, int cek)
{
  if (myFile)
  {
    if(cek == 0)myFile.print(data);
    else myFile.println(data);
    myFile.close();
    return 1;
  }else
  {
    //Serial.println("Error opening");
    return 0;
  }
}

void read_files(String nama){
  //myFile = SD.open(nama, FILE_WRITE);
  if(myFile){
    
    //myFile.close();
  }else{
    Serial.println("Error opening " + nama + ".txt");
  }
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
        String list = myFile.readStringUntil(';');
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
                //int x = list[i];
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

void close_connection()
{
  myFile.close();
}

// Global variables use 1,383 bytes (67.5%) of dynamic memory, leaving 665 bytes for local variables. Maximum is 2,048 bytes.
