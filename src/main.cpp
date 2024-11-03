#include <Arduino.h>
#include "Config.h"
#include "FirebaseHandler.h"
#include "Tasks.h"

void setup()
{
  Serial.begin(115200);
  loadConfig();
  wifiConnection();
  initFirebase();

  // Initialize the command path
  initializeCommands();

  // Create tasks with reasonable stack sizes
  xTaskCreate(ProducerTask, "Producer Task", 50000, NULL, 1, NULL); // Higher priority
  xTaskCreate(ConsumerTask, "Consumer Task", 50000, NULL, 1, NULL); // Lower priority
}

void loop()
{
  // FreeRTOS handles the task scheduling
}
