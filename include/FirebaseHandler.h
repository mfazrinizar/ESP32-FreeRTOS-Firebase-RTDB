#ifndef FIREBASE_HANDLER_H
#define FIREBASE_HANDLER_H

#include <Firebase_ESP_Client.h>

void initFirebase();
void wifiConnection();
void checkFirebaseConnection();
void initializeCommands();
extern FirebaseData fbdo;

#endif
