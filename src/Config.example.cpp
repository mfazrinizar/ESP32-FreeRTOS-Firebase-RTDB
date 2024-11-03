// #include "Config.h"
// #include <Arduino.h>
// // #include <FS.h>          // Include the SPIFFS library for file handling
// // #include <SPIFFS.h>     // Include SPIFFS for filesystem access

// // Default values
// const char *API_KEY = nullptr;
// const char *DATABASE_URL = nullptr;
// const char *WIFI_SSID = nullptr;
// const char *WIFI_PASSWORD = nullptr;

// void loadConfig()
// {
//     // // Initialize the SPIFFS filesystem
//     // if (!SPIFFS.begin(true)) {
//     //     Serial.println("SPIFFS Mount Failed");
//     //     return;
//     // }

//     // // Open the .env file
//     // File envFile = SPIFFS.open(".env", "r");
//     // if (!envFile) {
//     //     Serial.println("Failed to open .env file");
//     //     return;
//     // }

//     // // Read the file line by line
//     // while (envFile.available()) {
//     //     String line = envFile.readStringUntil('\n');
//     //     line.trim(); // Remove whitespace

//     //     // Skip empty lines and comments
//     //     if (line.length() == 0 || line.startsWith("#")) {
//     //         continue;
//     //     }

//     //     // Split the line into key and value
//     //     int separatorIndex = line.indexOf('=');
//     //     if (separatorIndex != -1) {
//     //         String key = line.substring(0, separatorIndex);
//     //         String value = line.substring(separatorIndex + 1);

//     //         // Store the values in the respective variables
//     //         if (key == "API_KEY") {
//     //             API_KEY = strdup(value.c_str()); // Duplicate the string
//     //         } else if (key == "DATABASE_URL") {
//     //             DATABASE_URL = strdup(value.c_str());
//     //         } else if (key == "WIFI_SSID") {
//     //             WIFI_SSID = strdup(value.c_str());
//     //         } else if (key == "WIFI_PASSWORD") {
//     //             WIFI_PASSWORD = strdup(value.c_str());
//     //         }
//     //     }
//     // }

//     // // Close the file
//     // envFile.close();

//     API_KEY = "YOUR_API_KEY";
//     DATABASE_URL = "YOUR_DATABASE_URL";
//     WIFI_SSID = "YOUR_WIFI_SSID";
//     WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
// }
