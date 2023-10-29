#include <DHT.h>

//definir o pino conectado ao DHT11
#define DHT_PIN 27

//definir o tipo de sensor como DHT11
#define DHT_TYPE DHT11

// este cooler tem lógica invertida, então fica ativo no estado "LOW"
#define coolerPIN 26

//sensor de movimento
#define movimentSensor 12

//led de detecção de movimento
#define ledMovimentDetected 13

//led de sistema ativo
#define ledSystem 14

DHT dht(DHT_PIN, DHT_TYPE);

//estados iniciais
int systemState = LOW;
int sensorState = 0;


//função que ligará o sistema
  void ligar() {
      Serial.println("Sistema ativado!");  
      digitalWrite(coolerPIN, LOW);
      digitalWrite(ledSystem, HIGH); 
      // delay(1000);
      systemState = HIGH; // registra o sistema como ativo
  }


//função que desligará o sistema
  void desligar() {
      Serial.println("Sistema desativado!"); 
      digitalWrite(coolerPIN, HIGH);
      digitalWrite(ledSystem, LOW);
      // delay(1000);
      systemState = LOW; // registra o sistema como desativado
  }

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
    digitalWrite(ledMovimentDetected, HIGH); 

    if (systemState == LOW && temperature > 30) {
      ligar();
    } else { 
      desligar();
    }
  }
    else {
        digitalWrite(ledMovimentDetected, LOW);
    }

  // condição de segurança do sistema para impedir que ele chegue a temperatura muito baixa enquanto ligado.
  if(temperature < 21) {
    desligar();
  }

  delay(1000);
}
  
