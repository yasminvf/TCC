/*******************************************************************************
*
*    TCC Mecatrônica - Yasmin Vitorino Freitas
*
*******************************************************************************/

#include <Wire.h> //INCLUSÃO DA BIBLIOTECA
#include "RTClib.h" //INCLUSÃO DA BIBLIOTECA
#include "DHT.h"

#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

RTC_DS3231 rtc; //OBJETO DO TIPO RTC_DS3231

//****************************************************************************

const int LM35 = 0; // entrada sensor no Arduino: A0 - Analógica
float temperatura = 0; // variável tipo float - inícia no 0
int ADClido = 0;
const int Buzzer = 12; // entrada buzzer: 12 - digital
const int Led10 = 10; // entrada led: 10 - digital
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado"}; //DECLARAÇÃO DOS DIAS DA SEMANA
DHT dht(DHTPIN, DHTTYPE);
const int analogInPin = A0;             // Pino analógico que o sensor está conectado
const int digitalPin = 2;
int sensorValue = 0;                     // valor que será lido do sensor
int setpoint = 200;
int ldrValor = 0; //Valor lido do LDR
int ldrPin = 0; //LDR no pino analígico 8

//****************************************************************************

void setup(){

//Parte do RTC
{
  Serial.begin(9600); //INICIALIZA A SERIAL
  if(! rtc.begin()) { // SE O RTC NÃO FOR INICIALIZADO, FAZ
    Serial.println("DS3231 não encontrado"); //IMPRIME O TEXTO NO MONITOR SERIAL
    while(1); //SEMPRE ENTRE NO LOOP
  }
  if(rtc.lostPower()){ //SE RTC FOI LIGADO PELA PRIMEIRA VEZ / FICOU SEM ENERGIA / ESGOTOU A BATERIA, FAZ
    Serial.println("DS3231 OK!"); //IMPRIME O TEXTO NO MONITOR SERIAL
    //REMOVA O COMENTÁRIO DE UMA DAS LINHAS ABAIXO PARA INSERIR AS INFORMAÇÕES ATUALIZADAS EM SEU RTC
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO
    //rtc.adjust(DateTime(2021, 06, 01, 21, 38, 20)); //(ANO), (MÊS), (DIA), (HORA), (MINUTOS), (SEGUNDOS)
  }
  delay(100); //INTERVALO DE 100 MILISSEGUNDOS
}

//Parte do DHT11

{
  Serial.begin(9600);
  dht.begin();

  delay(100); //INTERVALO DE 100 MILISSEGUNDOS
}

//Parte do LDR
{
  Serial.begin(9600);                    // inicializa a comunicação serial com a taxa de 9600 bps
  pinMode(digitalPin, OUTPUT);
  
}

}

//****************************************************************************
 
void loop(){

//Parte RTC
{
    DateTime now = rtc.now(); //CHAMADA DE FUNÇÃO
    Serial.print("Data: "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(now.day(), DEC); //IMPRIME NO MONITOR SERIAL O DIA
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.month(), DEC); //IMPRIME NO MONITOR SERIAL O MÊS
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.year(), DEC); //IMPRIME NO MONITOR SERIAL O ANO
    //Serial.print(" / Dia: "); //IMPRIME O TEXTO NA SERIAL
    //Serial.print(daysOfTheWeek[now.dayOfTheWeek()]); //IMPRIME NO MONITOR SERIAL O DIA
    Serial.print(" / Horas: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(now.hour(), DEC); //IMPRIME NO MONITOR SERIAL A HORA
    Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.minute(), DEC); //IMPRIME NO MONITOR SERIAL OS MINUTOS
    Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.second(), DEC); //IMPRIME NO MONITOR SERIAL OS SEGUNDOS
    Serial.print(' '); //IMPRIME O CARACTERE NO MONITOR SERIAL
    //Serial.println(); //QUEBRA DE LINHA NA SERIAL
    
    delay(1000); //INTERVALO DE 1 SEGUNDO
  }

  //Parte DHT11
  {
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("Failed to read from DHT");
  } 
  else
  {
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(" Umidade: ");
    Serial.print(h);
    Serial.print(' '); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(" Temperatura: ");
    Serial.print(t);
    Serial.print(" *C");
    delay(1000); //INTERVALO DE 1 SEGUNDO
  }

}

//Parte LDR
{
  
  ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
  
  Serial.print(' '); //IMPRIME O CARACTERE NO MONITOR SERIAL
  Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
  Serial.print(" sensor = " );            // Imprime o resultado no monitor serial
  Serial.print(ldrValor);      
  
  if(sensorValue < setpoint){
  
     digitalWrite(digitalPin, HIGH);
  
  } else {
   
   digitalWrite(digitalPin, LOW);
  
  }

  delay(1000); //INTERVALO DE 1 SEGUNDO                             // Aguarda 2 milisegundos para estabilizar o conversor ADC                  

  Serial.println(); //QUEBRA DE LINHA NA SERIAL
}
}
