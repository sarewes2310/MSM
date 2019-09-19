void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  String data_list = "4991461381872128:3310,900;";
  boolean b = false;
  String data[3];
  data[1] = "";
  data[2] = "";
  int a = 0; //inisialisasi awal dari index data
  for(int j = 0;j < data_list.length();j++){
    if(b)
    {
      if(isAlphaNumeric(data_list[j]))
      {
          data[a] += data_list[j];
          Serial.print("[");
          Serial.print(a);
          Serial.print("]");
          Serial.print(data_list[j]);
          Serial.println();
          //if(a == 1) nama_file = list[j].toInt();
          //else total = list[j].toInt();
      }
    }
    if(!isAlphaNumeric(data_list[j]))
    {
      b = true;
      a++;
    }
  }
  Serial.println(data[1]);
  Serial.println(data[2]);
  int c = 1;
  if(c)Serial.println("coeg");
}

void loop() {
  // put your main code here, to run repeatedly:

}
