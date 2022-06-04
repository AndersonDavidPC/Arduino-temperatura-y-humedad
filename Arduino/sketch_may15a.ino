//Librerías
#include <DHT_U.h>
#include <DHT.h>
#include <TimerOne.h>

//Definiendo el pin donde se conecta el sensor
#define DHTPIN A0
//Tipo de sensor
#define DHTTYPE DHT11
//Inicializar el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

//Los pines de la pantalla se unen a 2-13 respectivamente
const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int pinP = 9;
const int D1 = 10;
const int D2 = 11;
const int D3 = 12;
const int D4 = 13;

//Variables
int ten, unity, decimal;
float humidity, temp, HeatIndex;

void setup() {
  //Inicializar comunicación serie
  Serial.begin(9600);
  //Comenzar el sensor DHT
  dht.begin();

  //Inicializar los pins como OUTPUT
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinP, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  //Dispara la funcion CalcTemp cada 5 segundo
  Timer1.initialize(5000000);
  Timer1.attachInterrupt(CalcTemp);
}

void loop() {
  //Leer la humedad relativa
  humidity = dht.readHumidity();
  //Leer la temperatura en grados centígrados
  temp = dht.readTemperature();

  //Comprobar si ha habido algún error en la lectura
  if (isnan(humidity) || isnan(temp)) {
    Serial.println("Error obtenido los datos del sensor DHT11");
    return;
  }

  //Calcular la sensación térmica
  HeatIndex = dht.computeHeatIndex(temp, humidity, false);

  //Descomponer la temperatura en unidades
  ten = temp/10;
  unity = temp-(ten*10);
  decimal = (temp-ten*10-unity)*10;
  
  //Dibujar temperatura en pantalla
  clearLEDs();
  pickDigit(1);
  pickNumber(ten);
  delay(5);

  clearLEDs();
  pickDigit(2);
  pickNumber(unity);
  digitalWrite(pinP, LOW);
  delay(5);

  clearLEDs();
  pickDigit(3);
  pickNumber(decimal);
  delay(5);

  clearLEDs();
  pickDigit(4);
  celsius();
  delay(5);
}

//Mostrar los valores en la consola
void CalcTemp() {
  Serial.print("Humedad: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print(" *C\t");
  Serial.print("Índice de calor: ");
  Serial.print(HeatIndex);
  Serial.println(" *C");
}
//Iluminar la linea correspondiente
void pickDigit(int DigitNumber) {
  switch(DigitNumber) {
    case 1:
      digitalWrite(D1, HIGH);
      break;
    case 2:
      digitalWrite(D2, HIGH);
      break;
    case 3:
      digitalWrite(D3, HIGH);
      break;
    default:
      digitalWrite(D4, HIGH);
      break;
  }
}
//Indicar que numero mostrar en la pantalla
void pickNumber(int Number) {
  //Number es un numero entero de 0 a 9.
  switch(Number) {
    default:
      zero();
      break;
    case 1:
      one();
      break;
    case 2:
      two();
      break;
    case 3:
      three();
      break;
    case 4:
      four();
      break;
    case 5:
      five();
      break;
    case 6:
      six();
      break;
    case 7:
      seven();
      break;
    case 8:
      eight();
      break;
    case 9:
      nine();
      break;
  }
}

//Limpiar la pantalla
void clearLEDs() {
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinP, HIGH);
}

//Dibujando 0 en la pantalla
void zero() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
}
//Dibujando 1 en la pantalla
void one() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}
//Dibujando 2 en la pantalla
void two() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
}
//Dibujando 3 en la pantalla
void three() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
}
//Dibujando 4 en la pantalla
void four() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}
//Dibujando 5 en la pantalla
void five() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}
//Dibujando 6 en la pantalla
void six() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}
//Dibujando 7 en la pantalla
void seven() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}
//Dibujando 8 en la pantalla
void eight() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}
//Dibujando 9 en la pantalla
void nine() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}
//Dibujamos C en la pantalla
void celsius() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
}
