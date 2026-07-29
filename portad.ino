#include <Ultrasonic.h>
// Definindo os pinos onde os sensores estão conectados
const int sensorInicioPin = 8; // Pino para o sensor de início
const int sensorParadaPin = 12;  // Pino para o sensor de parada
#define trigPin 4
#define echoPin 6
// Variável para controlar o estado da nossa "ação"
bool acaoEmAndamento = false;

// Variável para o LED interno do Arduino (pin 13) - opcional para visualização
const int ledPin = 13;
Ultrasonic ultrasonic(trigPin, echoPin);
int sensor1;
int sensor2;
unsigned long t;  
unsigned long t_0;  
float tempo;
float x;
float x_0;

void setup() {
  // Configura os pinos dos sensores como entrada
  pinMode(sensorInicioPin, INPUT);
  pinMode(sensorParadaPin, INPUT);

  // Configura o pino do LED como saída
  pinMode(ledPin, OUTPUT);

  // Inicia a comunicação serial para depuração (opcional)
  Serial.begin(9600);
  Serial.println("Sistema iniciado. Aguardando sensor de inicio...");
t_0 = 0;
x_0 = 0;
}
void loop() {
  long microsec = ultrasonic.timing();
  
  // put your main code here, to run repeatedly:
  x = ultrasonic.convert(microsec, Ultrasonic::CM);
  t = millis();  // in seconds
  
  // Lê o estado dos sensores
  int estadoSensorInicio = digitalRead(sensorInicioPin);
  int estadoSensorParada = digitalRead(sensorParadaPin);

  // Lógica para iniciar a ação
  // Só inicia se o sensor de início for ativado E a ação não estiver em andamento E
  // o sensor de parada NÃO estiver ativado.
  if (estadoSensorInicio == LOW && !acaoEmAndamento && estadoSensorParada == HIGH) {
    acaoEmAndamento = true; // Define que a ação está em andamento
    Serial.println("Sensor de INICIO detectado! Acao iniciada.");
    digitalWrite(ledPin, HIGH); // Liga o LED
    t_0 = t;
    x_0 = x;
    // Coloque aqui o código da sua ação que deve iniciar
  }

  // Lógica para parar a ação
  // Se o sensor de parada detectar algo (LOW) e a ação estiver em andamento
  if (estadoSensorParada == LOW && acaoEmAndamento) {
    acaoEmAndamento = false; // Define que a ação parou
    Serial.println("Sensor de PARADA detectado! Acao interrompida.");
    digitalWrite(ledPin, LOW); // Desliga o LED
    // Coloque aqui o código para parar sua ação
  }
  // Se a ação estiver em andamento, você pode manter um comportamento contínuo aqui
  if (acaoEmAndamento) {digitalWrite(ledPin, HIGH);
 //Exibe informacoes no serial monitor
    tempo = (t - t_0)/1000.0;
    Serial.print(tempo);  //in seconds
    Serial.print(",");
    Serial.println(x - x_0); 
    // Código que deve ser executado continuamente enquanto a ação está ativa
  }

  delay(50);}