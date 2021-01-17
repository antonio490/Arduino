#include <Arduino_HTS221.h>
#include <Arduino_LSM9DS1.h>

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  if (!initSensor()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
  }

  if (!initIMU()) {
    Serial.println("Failed to initialize IMU!");
  }
}

void loop() {
  // read all the sensor values
  float temperature;
  float humidity;
  getSensorValues(&temperature, &humidity);

  // print each of the sensor values
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity    = ");
  Serial.print(humidity);
  Serial.println(" %");

  // wait 1 second to print again
  delay(1000);

  float x, y, z;

  if (getIMUValues(&x, &y, &z)) {
    IMU.readAcceleration(x, y, z);

    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);
  }

  // print an empty line
  Serial.println();
}

// Sensor
bool initSensor() {
  return HTS.begin();
}

void getSensorValues(float *temperatureVal, float *humidityVal) {
  *temperatureVal = HTS.readTemperature();
  *humidityVal    = HTS.readHumidity();
}

// IMU
bool initIMU() {
  return IMU.begin();
}

bool getIMUValues(float *xVal, float *yVal, float *zVal) {
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(*xVal, *yVal, *zVal);
    return true;
  }
  return false;
}
