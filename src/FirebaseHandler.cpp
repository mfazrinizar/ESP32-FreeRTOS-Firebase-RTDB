#include "FirebaseHandler.h"
#include "Config.h"
#include <WiFi.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void wifiConnection()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println("\nConnected to Wi-Fi");
}

void initFirebase()
{
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;

    // Anonymous sign-up (required)
    if (Firebase.signUp(&config, &auth, "", ""))
    {
        Serial.println("Firebase sign-up successful.");
    }
    else
    {
        Serial.printf("Sign-up error: %s\n", config.signer.signupError.message.c_str());
    }

    // Set callback function for token status
    config.token_status_callback = tokenStatusCallback;

    // Initialize Firebase
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    vTaskDelay(10000 / portTICK_PERIOD_MS);
}

void initializeCommands()
{
    // Variable to hold the current command value
    int currentCommand = 0;

    // Retrieve the current command value
    if (Firebase.RTDB.getInt(&fbdo, "/ESP32/commands"))
    {
        currentCommand = fbdo.intData();
        Serial.printf("Command path exists with value: %d\n", currentCommand);
    }
    else
    {
        Serial.println("Initializing command path.");
        if (Firebase.RTDB.setInt(&fbdo, "/ESP32/commands", 0))
        {
            Serial.println("Command path initialized with default value 0.");
        }
        else
        {
            Serial.print("Failed to initialize command path. Error: ");
            Serial.println(fbdo.errorReason());
        }
    }

    // Set command path to its current value
    if (Firebase.RTDB.setInt(&fbdo, "/ESP32/commands", currentCommand))
    {
        Serial.printf("Command path reset to its current value: %d\n", currentCommand);
    }
    else
    {
        Serial.print("Failed to reset command path. Error: ");
        Serial.println(fbdo.errorReason());
    }

    // Variable to hold the current sensor temperature value
    float currentTemperature = 0.0;

    // Retrieve the current sensor temperature value
    if (Firebase.RTDB.getFloat(&fbdo, "/ESP32/sensorTemperature"))
    {
        currentTemperature = fbdo.floatData();
        Serial.printf("sensorTemperature path exists with value: %.2f\n", currentTemperature);
    }
    else
    {
        Serial.println("Initializing sensorTemperature path.");
        if (Firebase.RTDB.setFloat(&fbdo, "/ESP32/sensorTemperature", 0.0))
        {
            Serial.println("sensorTemperature path initialized with default value 0.0.");
        }
        else
        {
            Serial.print("Failed to initialize sensorTemperature path. Error: ");
            Serial.println(fbdo.errorReason());
        }
    }

    // Set sensor temperature path to its current value
    if (Firebase.RTDB.setFloat(&fbdo, "/ESP32/sensorTemperature", currentTemperature))
    {
        Serial.printf("sensorTemperature path reset to its current value: %.2f\n", currentTemperature);
    }
    else
    {
        Serial.print("Failed to reset sensorTemperature path. Error: ");
        Serial.println(fbdo.errorReason());
    }

    Serial.println("End of initializeCommands.");
    vTaskDelay(3000 / portTICK_PERIOD_MS);
}

void checkFirebaseConnection()
{
    if (Firebase.ready())
    {
        Serial.println("Firebase connected.");
    }
    else
    {
        Serial.println("Firebase not connected.");
    }
}
