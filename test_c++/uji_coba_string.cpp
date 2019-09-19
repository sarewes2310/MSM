#include <stdio.h>
#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

String rewrite_file(String nama, int nama_file, int total)
{
    String data = "";
    int panjang = 0;
    String parse_data[12];
    int z = 0;
    while (myFile.available())
    {
        //String list = myFile.readStringUntil('\n'); //MODE Debugging (test_s.txt)
        String list = myFile.readStringUntil(';'); //MODE Debugging (test_1.txt)
        for (int i = 0; i < list.length(); ++i)
        {
            if(isAlphaNumeric(list[i]))
            {
                parse_data[z] += list[i];
            }else
            {
                int x = list[i];
                //Serial.print(x);
                //Serial.println(list[i]);
                //Serial.print("TEST\nCOK");
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

    //Serial.println(parse_data);

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
    return data;
}

uint8_t testing_output_while()
{
	cout << "test gan" << endl;
	return 1;
}

int main(int argc, char const *argv[])
{
	String data_test = "
	4991461381872128:0,1;
	4991461381872129:1,3;
	4991461381872170:2,4;
	";
	int total,nama_file; //inisialisasi
	bool z = true;
	cout << z << endl;
	string test = "UJI COBA GAN";
	for (int i = 0; i < test.length(); ++i)
	{
		if(test[i] != '\t')cout << test[i] << endl;
		else cout << "SPASI" << endl;
	}
	while(!testing_output_while());
	String hasil = rewrite_file(data_test, nama_file, total);
	return 0;
}