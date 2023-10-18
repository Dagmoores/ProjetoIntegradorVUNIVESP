int movimentSensor = 12;
int ledMovimentDetected = 13;
int ledSystem = 14;
int systemState = LOW;
int sensorState = 0;


void setup() {
  pinMode(ledMovimentDetected, OUTPUT);
  pinMode(ledSystem, OUTPUT);
  pinMode(movimentSensor, INPUT);

  Serial.begin(9600);
}

void loop() {
  sensorState = digitalRead(movimentSensor);
  Serial.println(sensorState);

 
  if(sensorState == HIGH) {
    digitalWrite(ledMovimentDetected, HIGH); // acende a luz que demonstra que o sensor foi ativado
    delay(1000);

    if (systemState == LOW) {
      Serial.println("Sistema ativado!");  
      digitalWrite(ledSystem, HIGH); // ativa o led que demonstra que se sistema de controle térmico está operante
      delay(1500);
      systemState = HIGH;                     // registra o sistema como ativo
    } else { // se o sensor for ativado novamente enquanto o sistema já está em funcionamento, significa que o animal saiu do espaço, portanto o sistema deve ser desligado!
      Serial.println("Sistema desativado!"); 
      digitalWrite(ledSystem, LOW); // desativa o led que demonstra que se sistema de controle térmico está operante
      delay(1500);
      systemState = LOW; // registra o sistema como desativado
    }
  }
    else {
        digitalWrite(ledMovimentDetected, LOW); // apaga a luz que demonstra que o sensor foi ativado
    }
  }
  
