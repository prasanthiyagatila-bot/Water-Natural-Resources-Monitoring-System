#define TRIG 9
#define ECHO 10

#define PH_SENSOR A0
#define TURBIDITY_SENSOR A1
#define TEMP_SENSOR A2

float distance;
float waterLevel;
float phValue;
float temperature;
float turbidityVoltage;

// Set this according to the actual water container depth
const float tankDepth = 30.0;

// These are example calibration values.
// Calibrate your pH sensor using standard buffer solutions.
const float phSlope = -5.7;
const float phOffset = 21.34;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  Serial.println("Natural Water Resources Monitoring");
  Serial.println("-----------------------------------");
}

void loop() {

  // 1. Measure water level
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);

  if (duration > 0) {
    distance = duration * 0.0343 / 2;

    waterLevel = tankDepth - distance;

    if (waterLevel < 0)
      waterLevel = 0;

    if (waterLevel > tankDepth)
      waterLevel = tankDepth;

    Serial.print("Water Level: ");
    Serial.print(waterLevel);
    Serial.println(" cm");
  } else {
    Serial.println("Water level: Sensor error");
  }

  // 2. Measure pH
  int phRaw = analogRead(PH_SENSOR);
  float phVoltage = phRaw * (5.0 / 1023.0);

  phValue = phSlope * phVoltage + phOffset;

  Serial.print("pH Value: ");
  Serial.println(phValue, 2);

  // 3. Measure turbidity
  int turbidityRaw = analogRead(TURBIDITY_SENSOR);

  turbidityVoltage = turbidityRaw * (5.0 / 1023.0);

  Serial.print("Turbidity Sensor Voltage: ");
  Serial.print(turbidityVoltage);
  Serial.println(" V");

  // 4. Measure temperature using LM35
  int tempRaw = analogRead(TEMP_SENSOR);

  float tempVoltage = tempRaw * (5.0 / 1023.0);

  temperature = tempVoltage * 100.0;

  Serial.print("Water Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.println("-----------------------------------");

  delay(2000);
}
