const int analogInPin = 34;     // Analog input pin
int sensorValue;
float calibration = 0.36; // Check Battery voltage using multimeter & add/subtract the value

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  delay(1500);
}

void loop() {
  sensorValue = analogRead(analogInPin);
  float voltage = (((sensorValue * 3.3) / 1024) * 2 + calibration); // Multiply by two as voltage divider network is 100K & 100K resistor
 
  float bat_percentage = mapfloat(voltage, 2.8, 4.2, 0, 100); // 2.8V as Battery Cut off Voltage & 4.2V as Maximum Voltage
 
  if (bat_percentage >= 100) {
    bat_percentage = 100;
  }
  if (bat_percentage <= 0) {
    bat_percentage = 0;
  }
 
  // Serial.print("Analog Value = ");
  // Serial.print(sensorValue);
  // Serial.print("\t Output Voltage = ");
  // Serial.print(voltage);
  Serial.print("\t Battery Percentage = ");
  Serial.println(bat_percentage);
  
  delay(1000);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
