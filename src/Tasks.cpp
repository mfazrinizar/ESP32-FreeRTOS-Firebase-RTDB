#include "Tasks.h"
#include <DHT.h>
#include <Arduino.h>
#include "FirebaseHandler.h"

#define DHTPIN 13
#define DHTTYPE DHT22
#define LED_PIN 12

DHT dht(DHTPIN, DHTTYPE);

void ProducerTask(void *pvParameters)
{
    float temperature;
    float lastTemperature = 0;   // Variable to store the last temperature reading
    const float threshold = 0.5; // Define a threshold for temperature change

    dht.begin(); // Initialize DHT sensor

    for (;;)
    {
        temperature = dht.readTemperature();

        // Only proceed if the temperature changes significantly
        if (abs(temperature - lastTemperature) >= threshold)
        {
            // Send temperature data to Firebase
            if (Firebase.RTDB.setFloat(&fbdo, "/ESP32/sensorTemperature", temperature))
            {
                Serial.println("Producer: Temperature data sent to Firebase.");
            }
            else
            {
                Serial.print("Producer: Failed to send data. Error: ");
                Serial.println(fbdo.errorReason());
            }

            // Set command based on temperature
            int commandValue = (temperature > 40) ? 1 : 0;
            if (Firebase.RTDB.setInt(&fbdo, "/ESP32/commands", commandValue))
            {
                Serial.printf("Producer: Command set to %d.\n", commandValue);
            }
            else
            {
                Serial.print("Producer: Failed to set command. Error: ");
                Serial.println(fbdo.errorReason());
            }

            lastTemperature = temperature; // Update lastTemperature to current temperature
        }

        vTaskDelay(5000 / portTICK_PERIOD_MS); // Delay 5 seconds
    }
}

void ConsumerTask(void *pvParameters)
{
    int command;
    int lastCommand = -1; // Variable to store the last command value

    pinMode(LED_PIN, OUTPUT); // Set LED pin as output

    for (;;)
    {
        // Poll Firebase for the latest command
        if (Firebase.RTDB.getInt(&fbdo, "/ESP32/commands"))
        {
            command = fbdo.intData();

            // Only proceed if the command has changed
            if (command != lastCommand)
            {
                Serial.print("Consumer: Command received from Firebase: ");
                Serial.println(command);

                // Control LED
                if (command == 1)
                {
                    Serial.println("Turning LED ON");
                    digitalWrite(LED_PIN, HIGH);
                }
                else
                {
                    Serial.println("Turning LED OFF");
                    digitalWrite(LED_PIN, LOW);
                }

                lastCommand = command; // Update lastCommand to current command
            }
        }
        else
        {
            Serial.print("Consumer: Failed to get data. Error: ");
            Serial.println(fbdo.errorReason());
        }

        vTaskDelay(3000 / portTICK_PERIOD_MS); // Delay 3 seconds
    }
}
