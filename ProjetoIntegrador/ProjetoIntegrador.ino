#include <DHT.h>

//definir o tipo de sensor como DHT11
#define DHT_TYPE DHT11

//definir o pino conectado ao DHT11
#define DHT_PIN 27

// definir o pino do cooler
// este cooler tem lógica invertida, então fica ativo no estado "LOW"
#define coolerPIN 26

DHT dht(DHT_PIN, DHT_TYPE);

int movimentSensor = 12;
int ledMovimentDetected = 13;
int ledSystem = 14;
int systemState = LOW;
int sensorState = 0;

 


void setup() {
  pinMode(ledMovimentDetected, OUTPUT);
  pinMode(ledSystem, OUTPUT);
  pinMode(movimentSensor, INPUT);
  pinMode(coolerPIN, OUTPUT);
  digitalWrite(coolerPIN, HIGH);

  Serial.begin(9600);
  dht.begin();

  
}

void loop() {

  // INICIO SENSOR DE TEMPERATURA
  float temperature = dht.readTemperature();

  if(isnan(temperature)) { 
    Serial.println("Erro na leitura do sensor de temperatura e umidade");
  } else {
    Serial.print("Temperatura: "); 
    Serial.print(temperature); 
    Serial.println(" °C");
  };
  // FIM SENSOR DE TEMPERATURA


  sensorState = digitalRead(movimentSensor);
  Serial.println(sensorState);

 
  if(sensorState == HIGH) {
    digitalWrite(ledMovimentDetected, HIGH); // acende a luz que demonstra que o sensor foi ativado

    if (systemState == LOW) {
      Serial.println("Sistema ativado!");  
      digitalWrite(coolerPIN, LOW);
      digitalWrite(ledSystem, HIGH); // ativa o led que demonstra que se sistema de controle térmico está operante
      delay(1500);
      systemState = HIGH;                     // registra o sistema como ativo
    } else { // se o sensor for ativado novamente enquanto o sistema já está em funcionamento, significa que o animal saiu do espaço, portanto o sistema deve ser desligado!
      Serial.println("Sistema desativado!"); 
      digitalWrite(coolerPIN, HIGH);
      digitalWrite(ledSystem, LOW); // desativa o led que demonstra que se sistema de controle térmico está operante
      delay(1500);
      systemState = LOW; // registra o sistema como desativado
    }
  }
    else {
        digitalWrite(ledMovimentDetected, LOW); // apaga a luz que demonstra que o sensor foi ativado
    }
}
  
