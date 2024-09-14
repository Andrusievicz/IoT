#include <Wire.h> //Biblioteca para uso do protocolo I2C;
#include <Adafruit_GFX.h> //Biblioteca para manipulação gráfica no display;
#include <Adafruit_SH1106.h> //Biblioteca para operação do driver de controle do display;

#include <Fonts/FreeMono9pt7b.h> //Fonte para alteração do texto;
#include <Fonts/FreeSansBoldOblique9pt7b.h> //Fonte para alteração do texto;
#include <Fonts/FreeMonoOblique9pt7b.h> //Fonte para alteração do texto;

#define OLED_RESET -1 //Em displays que não possuem pino RESET, é dado o valor -1;
#define tensao A0


Adafruit_SH1106 display(OLED_RESET); //Declaração da tela com o nome "display";

float medicao_tensao(){

 float medida_v = analogRead(tensao);
 medida_v = ((float)medida_v / 1023)*4.830;
  
  return medida_v;
}

void setup() {
  Serial.begin(9600);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C); //Inicialização do display com a biblioteca e endereço de hardware do display;
}

void loop() {

  display.clearDisplay(); //Comando para limpar a tela;
  display.setTextColor(WHITE); //Comando para definir a cor do texto;
  display.drawRect(0, 0, 128, 64, WHITE); //Desenhar retângulo não-preenchido (pos x, pos y, largura, altura, cor);

  display.setCursor(50,27);
  display.print("Tensao(V): ");
  display.setCursor(61,38);
  display.print(medicao_tensao());
  //delay(1000);
  
  
 if(medicao_tensao () > 3 && medicao_tensao() < 4.0){
    display.clearDisplay();
    display.drawRect(0, 0, 128, 64, WHITE);
    display.setCursor(50,27);
    display.print("SURTO DE (V)!:");
    display.setCursor(64,41);
    display.print(medicao_tensao());
   // delay(1000);
   }
   
   else if (medicao_tensao() > 4){    
    display.clearDisplay();
    display.drawRect(0, 0, 128, 64, WHITE);
    display.setCursor(50,27);
    display.print("SOBREC.(V)!:");
    display.setCursor(62,39);
    display.print(medicao_tensao());
    //delay(1000);
   }
  display.display(); //Mostrar informações na tela;
}
