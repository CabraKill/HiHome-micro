#include <Arduino.h>
#include <ArduinoJson.h>
#include "read_data.h"
#include "../requestHandler/requestHandler.h"
#include "../jsonConverter/getStringValueFromKey.h"

String readFromFirestore(const String url, const String path, String token, const char *fingerprint)
{
    Request requestValue = getRequest(url, path, ";Authorization: Bearer " + token, fingerprint);
    if (requestValue.statusCode != 200)
    {
        const String empty = "";
        return empty;
    }
    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, requestValue.body);
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return "";
    }
    String value = doc["fields"]["value"]["stringValue"];
    return value;
}