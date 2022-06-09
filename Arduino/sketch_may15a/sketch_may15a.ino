//Librerías
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include <DHT.h>
#include <SevSeg.h>
#include <TimerOne.h>

//Definiendo el pin donde se conecta el sensor
#define DHTPIN A0
//Tipo de sensor
#define DHTTYPE DHT11
//Inicializar el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

//Variables
SevSeg sevseg;
int ten, unity, decimal;
float humidity, temp, HeatIndex;
unsigned long start;

void setup(){
  //Inicializar comunicación serie
  Serial.begin(9600);
  //Comenzar el sensor DHT
  dht.begin();
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
  bool resistorsOnSegments = true;
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_CATHODE;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
  //Dispara la funcion CalcTemp cada 5 segundo
  Timer1.initialize(5000000);
  Timer1.attachInterrupt(CalcTemp);
}

void loop(){
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

  if (millis() - start > 5000){
    Serial.print(temp, 1);  // un solo decimal
    Serial.println(" C");
    sevseg.setNumber(temp,1);
    start = millis();
  }
  sevseg.refreshDisplay();
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
