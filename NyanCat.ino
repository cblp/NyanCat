#include <QuadDisplay2.h>
#include <TroykaDHT11.h>

const int ButtonPin = 8;
const int BuzzerPin = 2;
const int YellowLedPin = 3;
const int HumTempSensorPin = 4;
const int QuadDisplayPin = 10;

const int ModeInterval = 2000;

DHT11 humTemp(HumTempSensorPin);
QuadDisplay qdisplay(QuadDisplayPin);

void setup() {
  // открываем последовательный порт для мониторинга действий в программе
  Serial.begin(9600);

  pinMode(YellowLedPin, OUTPUT);
  digitalWrite(YellowLedPin, LOW);

  qdisplay.begin();

  humTemp.begin();
}

enum Mode {
  Humidity,
  Temperature,
};

void loop() {
  static int mode = Humidity;
  int result = humTemp.read();
  switch (result) {
    case DHT_OK:
      mode = displayHumTemp(mode);
      break;
    case DHT_ERROR_CHECKSUM:
      Serial.println("Checksum error");
      break;
    case DHT_ERROR_TIMEOUT:
      Serial.println("Time out error");
      break;
    default:
      Serial.println("Unknown error");
      break;
  }
  delay(ModeInterval);
}

int displayHumTemp(int mode) {
  switch (mode) {
    case Humidity:
      qdisplay.displayHumidity(humTemp.getHumidity());
      return Temperature;
    case Temperature:
      qdisplay.displayTemperatureC(humTemp.getTemperatureC());
      return Humidity;
  }
}
