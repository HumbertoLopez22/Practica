/*
  ESP32 PS3 Controller - LED Control Test
  esp32-ps3-led.ino
  Control three LEDs with PS3 Controller
  LED Hookup - LED1=4  LED2=16  LED3=15
  Requires ESP32-PS3 Library - https://github.com/jvpernis/esp32-ps3
  
  DroneBot Workshop 2023
  https://dronebotworkshop.com
*/

// Include PS3 Controller library
#include <Ps3Controller.h>

// Define LED Pins
#define LED3_PIN 15

// Variables to hold LED states
bool led2State = false;
bool led3State = false;

// Callback Function
void notify() {

  // Cross button - LED1 momentary control

  // Triangle Button - LED2 toggle control
  if (Ps3.event.button_down.triangle) {
    Serial.println("Triangle presssed");
    led2State = !led2State;
    digitalWrite(LED2_PIN, led2State);
  }

  // Square Button - LED3 on
  if (Ps3.event.button_down.square) {
    Serial.println("Square pressed");
    led3State = true;
    digitalWrite(LED3_PIN, led3State);
  }

  // Circle Button - LED3 off
  if (Ps3.event.button_down.circle) {
    Serial.println("Circle pressed");
    led3State = false;
    digitalWrite(LED3_PIN, led3State);
  }
}

// On Connection function
void onConnect() {
  // Print to Serial Monitor
  Serial.println("Connected.");
}

void setup() {

  // Setup Serial Monitor for testing
  Serial.begin(115200);

  // Define Callback Function
  Ps3.attach(notify);
  // Define On Connection Function
  Ps3.attachOnConnect(onConnect);
  // Emulate console as specific MAC address (change as required)
  Ps3.begin("00:00:00:00:00:00");

  // Set LED pins as outputs
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  // Print to Serial Monitor
  Serial.println("Ready.");
}

void loop() {
  if (!Ps3.isConnected())
    return;
  delay(2000);
}