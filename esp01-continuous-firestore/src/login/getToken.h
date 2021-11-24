#include <Arduino.h>
#include <ArduinoJson.h>
#include "../getValueFromKey/getValueFromKey.h"

String getToken(const char* json)
{
    String token = getStringValueFromKey("idToken", json);
    return token;
}