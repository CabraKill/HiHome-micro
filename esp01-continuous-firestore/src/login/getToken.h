#include <Arduino.h>
#include <ArduinoJson.h>

const char* getToken(const char* json)
{
    DynamicJsonDocument doc(2048);
    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, json);
    // Test if parsing succeeds.
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return "";
    }
    Serial.println("success on json");
    const char* token = doc["idToken"];
    return token;
}