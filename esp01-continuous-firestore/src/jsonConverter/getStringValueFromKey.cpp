#include <Arduino.h>
#include <ArduinoJson.h>
#include "getStringValueFromKey.h"

String getStringValueFromKey(String key, const char* text)
{
    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, text);
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return "";
    }

    String value = doc[key];
    return value;
}