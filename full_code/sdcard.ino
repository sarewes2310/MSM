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
		//myFile = cek == 0 ? SD.open(nama, FILE_WRITE) : SD.open(nama, FILE_READ);
		if(cek == 1) myFile = SD.open(nama, FILE_READ);
		else myFile = SD.open(nama, FILE_WRITE);
	}else {
		if(cek == 1) myFile = SD.open(nama, FILE_READ);
		else myFile = SD.open(nama, FILE_WRITE);
		Serial.println(nama + " membuat file.");
	}
	Serial.println(myFile);
}

int write_files(String data, int cek)
{
	if (myFile)
	{
		//Serial.println(F("Write FILES RUNN"));
		if(cek == 0) myFile.print(data);
		else myFile.println(data);
		return 1;
	}else
	{
		Serial.println("Error opening");
		return 0;
	}
}

void read_files(String nama)
{
  	//myFile = SD.open(nama, FILE_WRITE);
	if(myFile){
		while (myFile.available()) {
			Serial.write(myFile.read());
		}
		//myFile.close();
	}else{
		Serial.println("Error opening " + nama + ".txt");
	}
}

void check_file(String namaku, int &nama_file, int &total, boolean &cek)
{
	String data[3];
  	int panjang = 0;
  	data[1] = "";
  	data[2] = "";
  	cek = false;
  	if(myFile)
  	{
  		int z = 0;
    	String parse_data[12];
    	while (myFile.available())
    	{
    		//String list = myFile.readStringUntil('\n'); //MODE Debugging (test_s.txt)
            String list = myFile.readStringUntil(';'); //MODE Debugging (test_1.txt)
            //Serial.println(t);
            Serial.print(F("LIST_VALUE:"));
		    Serial.println(list);

        	boolean b = false;
		    int a = 0; //inisialisasi awal dari index data
		    //Serial.println(parse_data[i].indexOf(namaku));
		    //Serial.println("RUNN check_file");
		    if(list.indexOf(namaku) == 0)
		    {
		    	//String data_list = list; //Mode Debugging
		        for (int j = 0; j < list.length(); j++)
		        {
		        	if(b)
		          	{
		            	if(isAlphaNumeric(list[j]))
		            	{
		              		data[a] += (list[j]); 
		              		//Serial.print(a);
		              		//Serial.print(" ");
		              		//Serial.print(list[j]);
		              		//Serial.println();
		              		//if(a == 1) nama_file = list[j].toInt();
		              		//else total = list[j].toInt();
		            	}
		          	}
		          	if(!isAlphaNumeric(list[j]))
		          	{
		            	b = true;
		            	a++;
		          	}
		        }
		        cek = true;
		        //Serial.println(cek);
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
		    Serial.println(parse_data[i].indexOf(namaku));
		    //Serial.println("RUNN check_file");
		    if(parse_data[i].indexOf(namaku) == 0)
		    {
		    	String list = parse_data[i];
		        for (int j = 0; j < parse_data[i].length(); ++j)
		        {
		        	if(b)
		          	{
		            	if(isAlphaNumeric(list[j]))
		            	{
		              		data[a] += (list[j]);
		              		//Serial.print(a);
		              		//Serial.print(" ");
		              		//Serial.print(list[j]);
		              		//Serial.println();
		              		//if(a == 1) nama_file = list[j].toInt();
		              		//else total = list[j].toInt();
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
    	Serial.println("Error opening " + namaku + ".txt");
  	}
  	total = data[2].toInt(); //Output menampilkan jumlah total data fingerprint
  	nama_file = data[1].toInt(); //Output menampilkan nama file data tempat menyimpan fingerprint
  	//Serial.println(total);
  	//Serial.println(nama_file);
  	//Serial.println(cek);
}

String rewrite_file(String name_ektp, int nama_file, int total)
{
	//Serial.println("RUNN rewrite_file");
	//Serial.println(nama);
    String dataku = "";
    int panjang = 0;
    String nama_file_parse = String(nama_file);
    String total_parse = String(total);
    if(myFile)
    {
        //int z = 0;
        while (myFile.available())
    	{
    		//String list = myFile.readStringUntil('\n'); //MODE Debugging (test_s.txt)
            String list = myFile.readStringUntil(';'); //MODE Debugging (test_1.txt)
            //Serial.println(list);
            int ceking_index = list.indexOf(name_ektp);
            if(ceking_index == -1)
            {
            	//dataku += "2"; // Mode debugging
            	dataku += list; 
            	dataku += ";";
            	Serial.println(list);
            }else
            {
            	//Serial.println("COEG");
            	dataku += name_ektp;
                dataku += ":";
                dataku += nama_file_parse;
                dataku += ",";
                dataku += total_parse;
                dataku += ";";
                //dataku += "3"; // Mode Debugging
                //dataku += ";"; // Mode Debugging
            }
            delay(1000);
    	}
    }else
    {
        Serial.println("Error opening test_1.txt");
    }
    //Serial.print(F("dataku = ")); //Mode Debugging
    //Serial.println(dataku); //Mode Debugging
    //Serial.println(dataku.length()); //Mode Debugging
    return dataku;
}

void check_jumlah_ektp(int &total)
{
	String jumlah_all = "";
	if(myFile)
	{
		while (myFile.available())
		{
			jumlah_all = myFile.readStringUntil(';'); 
		}
		total = jumlah_all.toInt();
	}else
    {
        Serial.println("Error opening file");
    }
}

void close_connection()
{	
	myFile.close();
}

void remove_files(String nama)
{
	SD.remove(nama);
}

// Global variables use 1,383 bytes (67.5%) of dynamic memory, leaving 665 bytes for local variables. Maximum is 2,048 bytes.