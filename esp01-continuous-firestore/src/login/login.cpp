#include <Arduino.h>
#include <WiFiClientSecure.h>
#include "login.h"
#include "../requestHandler/requestHandler.h"
#include "getToken.h"

WiFiClientSecure client;

String loginFirestoreWithEmail(String email, String password, String host, String path, const char *fingerprint)
{
    Serial.println("Login Firestore");
    const String body = "{\"email\":\"" + email + "\",\"password\":\"" + password + "\",\"returnSecureToken\":true}";
    Request response = postRequest(host, path, body, "", fingerprint);
    if (response.statusCode != 200)
    {
        Serial.println("Connection failed.");
        return "";
    }

    Serial.println("Login success.");
    const String token = getToken(response.body.c_str());
    return token;
}