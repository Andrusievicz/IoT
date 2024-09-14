#include <SoftwareSerial.h>

SoftwareSerial BT(13,12); //13 = RX; 12 = TX; - TX DO MÓDULO VAI NA 13, RX DO MÓDULO VAI NA 12;
char info;

void setup() {
  Serial.begin(9600);
  BT.begin(38400);
}

void loop() {

  if(BT.available()){
      info = BT.read();
      Serial.print(info);
  }

  if(Serial.available()){
    BT.write(Serial.read()); //Escreve o que vem do Console Serial
  }
}
