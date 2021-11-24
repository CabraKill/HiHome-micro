#include <Arduino.h>
#include <ArduinoJson.h>

String getToken(String body){
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, body);
    String token = doc["idToken"];
    return token;
}