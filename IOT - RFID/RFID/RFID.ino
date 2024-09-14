#include <SPI.h>      //Biblioteca para utilização do protocolo SPI;
#include <MFRC522.h>  //Biblioteca para utilização do circuito RFID MFRC522;

#define C_SELECT 53  //Pino SDA do módulo;
#define RESET 9      //Pino RESET do módulo MFRC522;
#define LED_RED 8
#define LED_GREEN 7

MFRC522 rfid(C_SELECT, RESET);  //Declaração do módulo com o nome "rfid" no sistema com os pinos do define;

String dados = "";  //String vazia para armazenar o endereço da tag/cartão RFID;

void setup() {
  Serial.begin(9600);
  SPI.begin();  //Inicialização do protocolo SPI;
  pinMode (LED_RED,OUTPUT);
  pinMode (LED_GREEN,OUTPUT);

  rfid.PCD_Init();  //Inicialização do módulo RFID;
  Serial.println("RFID: Operacional");
}

void loop() {

  digitalWrite(LED_GREEN,LOW);
  digitalWrite(LED_RED,LOW);
  

  /*if (!rfid.PICC_IsNewCardPresent()) {  //If para testar caso o módulo NÃO tenha lido nenhum cartão/tag;
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {  //If para testar caso o módulo NÃO tenha conseguido ler o endereço do cartão/tag;
    return;
  }*/

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
      digitalWrite(LED_RED,LOW);
      digitalWrite(LED_GREEN,HIGH);
      delay(1000);
      dados = "";  //Zera o valor da string para a próxima leitura;
    }
      else{
        digitalWrite(LED_RED,HIGH);
        delay(1000);
        dados = "";  //Zera o valor da string para a próxima leitura;
      }
     
    
  }
}
