#include <Arduino.h>
#include <ArduinoJson.h>
#include "../jsonConverter/getStringValueFromKey.h"

String getToken(const String json)
{
    String token = getStringValueFromKey("idToken", json);
    return token;
}