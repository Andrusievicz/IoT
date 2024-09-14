void setup() {
  // put your setup code here, to run once:
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int contador=0;

  //CICLO DIURNO
  do{
    //SINAL VERDE PARA OS VEICULOS E VERMELHO PARA OS PEDESTRES
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    delay(3000);
    //SINAL AMARELO PARA OS VEICULOS E VERMELHO PARA OS PEDESTRES
    digitalWrite(10,LOW);
    digitalWrite(9,HIGH);
    delay(3000);
    //SINAL VERMELHO PARA OS VEICULOS E VERDE PARA OS PEDESTRES
    digitalWrite(9,LOW);
    digitalWrite(11,LOW);
    digitalWrite(8,HIGH);
    digitalWrite(12,HIGH);
    delay(3000);
    //DESLIGAMENTO DOS LEDS
    digitalWrite(12,LOW);
    digitalWrite(8,LOW);
    //INCREMENTO DA VARIÁVEL
    contador++;
   }
  while(contador<10);
  contador=0;
  

  //CICLO NOTURNO
  do{
    //SINAL VERDE PARA OS VEICULOS E VERMELHO PARA OS PEDESTRES
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    delay(10000);
    //SINAL AMARELO PARA OS VEICULOS E VERMELHO PARA OS PEDESTRES
    digitalWrite(10,LOW);
    digitalWrite(9,HIGH);
    delay(10000);
    //SINAL VERMELHO PARA OS VEICULOS E VERDE PARA OS PEDESTRES
    digitalWrite(9,LOW);
    digitalWrite(11,LOW);
    digitalWrite(8,HIGH);
    digitalWrite(12,HIGH);
    delay(10000);
    //DESLIGAMENTO DOS LEDS
    digitalWrite(12,LOW);
    digitalWrite(8,LOW);
    //INCREMENTO DA VARIÁVEL
    contador++;
   }
  while(contador<10);
  contador=0;
}
