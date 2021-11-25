#include <Arduino.h>
#include <ArduinoJson.h>
#include "../jsonConverter/getStringValueFromKey.h"

String getToken(const char* json)
{
    String token = getStringValueFromKey("idToken", json) ;
    return token;
}