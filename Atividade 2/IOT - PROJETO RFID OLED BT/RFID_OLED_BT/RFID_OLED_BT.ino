#include <SPI.h>      //Biblioteca para utilização do protocolo SPI;
#include <MFRC522.h>  //Biblioteca para utilização do circuito RFID MFRC522;

#include <Wire.h> //Biblioteca para uso do protocolo I2C;
#include <Adafruit_GFX.h> //Biblioteca para manipulação gráfica no display;
#include <Adafruit_SH1106.h> //Biblioteca para operação do driver de controle do display;

#include <Fonts/FreeMono9pt7b.h> //Fonte para alteração do texto;
#include <Fonts/FreeSansBoldOblique9pt7b.h> //Fonte para alteração do texto;
#include <Fonts/FreeMonoOblique9pt7b.h> //Fonte para alteração do texto;

#include <SoftwareSerial.h>

#define C_SELECT 53  //Pino SDA do módulo;
#define RESET 9      //Pino RESET do módulo MFRC522;
#define LED_RED 8
#define LED_GREEN 7
#define LED_YELLOW 10

#define OLED_RESET -1 //Em displays que não possuem pino RESET, é dado o valor -1;

MFRC522 rfid(C_SELECT, RESET);  //Declaração do módulo com o nome "rfid" no sistema com os pinos do define;
Adafruit_SH1106 display(OLED_RESET); //Declaração da tela com o nome "display";

SoftwareSerial BT(13,12); //13 = RX; 12 = TX; - TX DO MÓDULO VAI NA 13, RX DO MÓDULO VAI NA 12;
char info;

String dados = "";  //String vazia para armazenar o endereço da tag/cartão RFID;

void setup() {
  Serial.begin(9600);
  SPI.begin();  //Inicialização do protocolo SPI;
  pinMode (LED_RED,OUTPUT);
  pinMode (LED_GREEN,OUTPUT);
  pinMode (LED_YELLOW,OUTPUT);

  rfid.PCD_Init();  //Inicialização do módulo RFID;
  Serial.println("RFID: Operacional");

  BT.begin(38400);
  
  display.begin(SH1106_SWITCHCAPVCC, 0x3C); //Inicialização do display com a biblioteca e endereço de hardware do display;
}

void loop() {

  digitalWrite(LED_GREEN,LOW);
  digitalWrite(LED_RED,LOW);
  digitalWrite(LED_YELLOW,LOW);
  
  display.clearDisplay(); //Comando para limpar a tela;
  display.setTextColor(WHITE); //Comando para definir a cor do texto;
  display.drawRect(0, 0, 128, 64, WHITE); //Desenhar retângulo não-preenchido (pos x, pos y, largura, altura, cor);
  

  /*if (!rfid.PICC_IsNewCardPresent()) {  //If para testar caso o módulo NÃO tenha lido nenhum cartão/tag;
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {  //If para testar caso o módulo NÃO tenha conseguido ler o endereço do cartão/tag;
    return;
  }*/

if(BT.available()){
      info = BT.read();
      Serial.print(info);
  }

    if(Serial.available()){
    BT.write(Serial.read()); //Escreve o que vem do Console Serial
  }

  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    Serial.print("Endereco da TAG (HEX): ");

    for (byte i = 0; i < rfid.uid.size; i++) {  //Loop que percorre o endereço lido no RFID como um vetor;
      if (rfid.uid.uidByte[i] < 0x10) {
        Serial.print(" 0");
      } else {
        Serial.print(" ");
      }

      Serial.print(rfid.uid.uidByte[i], HEX);  //Código para conversão dos dados lidos no módulo, de binário para HEX;

      if (rfid.uid.uidByte[i] < 0x10) {
        dados.concat(String(" 0"));
      } else {
        dados.concat(String(" "));
      }
      dados.concat(String(rfid.uid.uidByte[i], HEX));
    }

    dados.toUpperCase();  //Colocando todos os valores do endereço em caixa alta;
    Serial.println();     //Printa os valores de endereço no Console Serial;
 

    if (dados.substring(1) == "96 26 D0 F7") {  //Testa se o endereço lido é igual ao contido entre " ";
      Serial.println("Acesso Permitido!");
      display.setCursor(5,5);
      display.print("Acesso Permitido!");
      display.print("                     ");
      display.print("    Adress:");
      display.print(dados);
      display.display(); //Mostrar informações na tela;
      digitalWrite(LED_GREEN,HIGH);
      BT.println("Acesso Permitido!");
      BT.print("Adress:");
      BT.println(dados);
      delay(3000);
      dados = "";  //Zera o valor da string para a próxima leitura;
    }
      else if (dados.substring(1) == "66 A0 5E AC") {
        display.setCursor(5,5);
        display.print("Acesso Negado!");
        display.print("                     ");
        display.print("       Adress:");
        display.print(dados);
        display.display(); //Mostrar informações na tela;
        digitalWrite(LED_RED,HIGH);
        BT.println("Acesso Negado!");
        BT.print("Adress:");
        BT.println(dados);
        delay(3000);
        dados = "";  //Zera o valor da string para a próxima leitura;
      }
      else{
        display.setCursor(5,5);
        display.print("Acesso Desconhecido!");
        display.print("                     ");
        display.print(" Adress:");
        display.print(dados);
        display.display(); //Mostrar informações na tela;
        digitalWrite(LED_YELLOW,HIGH);
        BT.println("Acesso Desconhecido!");
        BT.print("Adress:");
        BT.println(dados);
        delay(3000);
        dados = "";  //Zera o valor da string para a próxima leitura;       
      }
       
  }
    display.display(); //Mostrar informações na tela;
}
