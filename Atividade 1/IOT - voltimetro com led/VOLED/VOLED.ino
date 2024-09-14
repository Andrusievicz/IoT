#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define buzzer 8

#define tensao A0

#define RS 7
#define E 6
#define DB4 5
#define DB5 4
#define DB6 3
#define DB7 2

LiquidCrystal lcd(RS, E, DB4, DB5, DB6, DB7);

SoftwareSerial BT(13,12); //13 = RX; 12 = TX; - TX DO MÓDULO VAI NA 13, RX DO MÓDULO VAI NA 12;
char info;



float medicao_tensao(){

 float medida_v = analogRead(tensao);
 medida_v = ((float)medida_v / 1023)*4.830;
  
  return medida_v;

}

void setup() {
 analogReference(DEFAULT);
  lcd.begin(16,2);
  BT.begin(38400);
  Serial.begin(9600);
}

void loop() {
  
   if(BT.available()){
      info = BT.read();
      Serial.print(info);
  }

   if(Serial.available()){
    BT.write(Serial.read()); //Escreve o que vem do Console Serial
  }
  
  //Serial.println(medicao_tensao());
  lcd.setCursor(0,0);
  lcd.print("Tensao(V): ");
  lcd.setCursor(12,0);
  lcd.print(medicao_tensao());
  BT.print("Tensao(V): ");
  BT.println(medicao_tensao());
  delay(1000);
  
  
 if(medicao_tensao () > 3 && medicao_tensao() < 4.0){
    lcd.setCursor(0,1);
    lcd.print("SURTO DE (V)!");
    BT.println("SURTO DE (V)!");
    delay(1000);
    /*tone(buzzer,350);
    delay(350);
    noTone(buzzer);
    delay(350);*/
   }
   
   else if (medicao_tensao() > 4){
    lcd.setCursor(0,1);
    lcd.print("SOBREC.(V)!");
    BT.println("SOBREC.(V)!");
    delay(1000);
    /*tone(buzzer,480);
    delay(200);
    noTone(buzzer);
    delay(200);*/
 }
}
