#include <Arduino.h>
#include "writeFlightTimeOnFirestore.h"
#include "../requestHandler/requestHandler.h"

void writeFlightTimeOnFirestore(const String url, const String path, const String time, String token, const char *fingerprint)
{
    String body = "{\"fields\":{\"time\":{\"doubleValue\": " + time + "}}}";
    postRequest(url, path, body, ";Authorization: Bearer " + token, fingerprint);
}