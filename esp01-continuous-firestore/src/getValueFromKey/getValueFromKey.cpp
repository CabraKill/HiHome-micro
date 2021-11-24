#include <Arduino.h>
#include <ArduinoJson.h>

String getStringValueFromKey(String key, const char* json)
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
    const char* value = doc[key];
    return value;
}