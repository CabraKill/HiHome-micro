#include <Arduino.h>
#include "read_data.h"
#include "../requestHandler/requestHandler.h"

String readFromFirestore(const String url, const String path, String token, const char* fingerprint)
{
    Request requestValue = getRequest(url, path, ";Authorization: Bearer " + token, fingerprint);
    if (requestValue.statusCode != 200)
    {
        const String empty = "";
        return empty;
    }
    Serial.println(requestValue.body);
    return "on";
}