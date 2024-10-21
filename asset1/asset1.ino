#include <ArduinoBLE.h>

const char* uuid = "5D4F979E-7E44-43C4-A0C7-E1011D7EF50D"; // Replace with your desired UUID
const int majorValue = 100; // Replace with your desired major value

BLEPeripheral blePeripheral;

BLEService customService(uuid);
BLEUnsignedCharCharacteristic buttonStateChar("ButtonState", BLERead | BLENotify);

const int buttonPin = 2; // Replace with the pin connected to the push button
bool buttonState = false;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  while (!Serial); // Wait for serial monitor to open

  if (!BLE.begin()) {
    Serial.println("BLE initialization failed!");
    while (1);
  }

  blePeripheral.setLocalName("ESP32_BLE");
  blePeripheral.setAdvertisedService(customService);

  customService.addCharacteristic(buttonStateChar);
  BLE.addService(customService);

  BLE.advertise();

  Serial.println("Peripheral (Advertising) is now active!");
}

void loop() {
  int newButtonState = digitalRead(buttonPin);
  if (newButtonState != buttonState) {
    buttonState = newButtonState;
    Serial.println(buttonState ? "true" : "false");
    buttonStateChar.writeValue(buttonState ? 1 : 0);
    delay(50); // Debounce delay
  }

  BLE.poll();
}
