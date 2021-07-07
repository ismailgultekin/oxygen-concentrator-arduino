//example(Receive): 16 09 01 00 D2 00 00 00 C8 00 00 46
const byte diziBoyutu = 9;


void setup() {
  Serial.begin(9600);
  delay(3000);
}

void loop() {
  char dizi[diziBoyutu];  // Gelen byte dizisi, 9 boyutlu bir dizi
  
  while (1){
    if(Serial.available()>0)    
    {         
      
      char inByte = (char)Serial.read();
      if (inByte == 0X16)
      {
        
        while (Serial.available() <= 0);    // Bir sonraki byte gelene kadar bekler
        inByte = (char)Serial.read();
        if (inByte == 0x09)
        {
          
          while (Serial.available() <= 0);  // Bir sonraki byte gelene kadar bekler
          inByte = (char)Serial.read();
          if (inByte == 0x01)
          {
            Serial.readBytes(dizi, diziBoyutu);// 9 byte okuma yap ve diziye yaz. Ayrıca gelen verinin kaç byte inin işlendiğini sakla.
            // CheckSum Hesabı
            int toplam = 0;
            for (int i = 0; i < 8; i++)
            {
              toplam += dizi[i];
            }
            int gtoplam = 0 - toplam - 0X20;
            
            if ((char)gtoplam == dizi[8]){

                byte dsifir   = dizi[0];//
                byte dbir     = dizi[1];//

                
                //float oxygen  = (dizi[0] * 256.0 + dizi[1]) / 10;
                float oxygen  = (dsifir * 256 + dbir) / 10;
                float flow    = (dizi[2] * 256.0 + dizi[3]) / 10;
                float temp    = (dizi[4] * 256.0 + dizi[5]) / 10;

                if(flow < 5){
                  oxygen = 21;
                } else if (flow > 100) {
                  oxygen = 21;
                }
                
                Serial.print("OXYGEN / Q2: ");      Serial.print(oxygen, 1);   Serial.println();
                Serial.print("Flow / Debi: ");    Serial.print(flow, 1);     Serial.println();
                Serial.print("Temp / Sıcaklık: ");   Serial.print(temp, 1);     Serial.println();
                Serial.println();
            }//if ((char)gtoplam == dizi[8])
          }//if (inByte == 0x01)
        }//if (inByte == 0x09)
      }//if (inByte == 0X16)
    }//if(Serial.av
  }//while
}//void loop()
