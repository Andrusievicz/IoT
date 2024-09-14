#include <SoftwareSerial.h>

#include <SPI.h>      //Biblioteca para utilização do protocolo SPI;
#include <MFRC522.h>  //Biblioteca para utilização do circuito RFID MFRC522;

#define C_SELECT 53  //Pino SDA do módulo;
#define RESET 9      //Pino RESET do módulo MFRC522;
#define LED_RED 8
#define LED_GREEN 7

SoftwareSerial BT(13, 12); //13 = RX; 12 = TX; - TX DO MÓDULO VAI NA 13, RX DO MÓDULO VAI NA 12;

MFRC522 rfid(C_SELECT, RESET);  //Declaração do módulo com o nome "rfid" no sistema com os pinos do define;

char info;
String dados = "";  //String vazia para armazenar o endereço da tag/cartão RFID;

unsigned long tempo_anterior = 0;
unsigned long intervalo = 2000;

void setup() {
  Serial.begin(9600);
  BT.begin(38400);
  SPI.begin();  //Inicialização do protocolo SPI;
  rfid.PCD_Init();  //Inicialização do módulo RFID;
  Serial.println("RFID: Operacional");
  pinMode (LED_RED, OUTPUT);
  pinMode (LED_GREEN, OUTPUT);
}

void loop() {

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);

  if (BT.available()) {
    info = BT.read();
    Serial.print(info);
  }

  if (Serial.available()) {
    BT.write(Serial.read()); //Escreve o que vem do Console Serial
  }

  unsigned long tempo_atual = millis(); //Variável para armazenar o valor da função millis();

  if (tempo_atual - tempo_anterior >= intervalo) { //Temporização que faz com que o RFID realize uma leitura a cada 2 seg;
    tempo_anterior = tempo_atual; //Variável tempo_anterior sendo "zerada";

    if (!rfid.PICC_IsNewCardPresent()) {  //If para testar caso o módulo NÃO tenha lido nenhum cartão/tag;
      return;
    }

    if (!rfid.PICC_ReadCardSerial()) {  //If para testar caso o módulo NÃO tenha conseguido ler o endereço do cartão/tag;
      return;
    }
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
    BT.print(dados);
    Serial.println();     //Printa os valores de endereço no Console Serial;

    delay(200);
    dados = "";
    
    if (dados.substring(1) == "B6 63 7B AC") {  //Testa se o endereço lido é igual ao contido entre " ";
      Serial.println("Acesso Permitido!");
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, HIGH);
      delay(1000);
      dados = "";  //Zera o valor da string para a próxima leitura;
    }
    else {
      digitalWrite(LED_RED, HIGH);
      delay(1000);
      dados = "";  //Zera o valor da string para a próxima leitura;
    }
  }
}
