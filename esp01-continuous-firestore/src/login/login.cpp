#include <Arduino.h>
#include <WiFiClientSecure.h>
#include "login.h"
#include "../requestHandler/requestHandler.h"
#include "getToken.h"

WiFiClientSecure client;

String loginFirestoreWithEmail(String email, String password, String host, String path,const char *key)
{
    Serial.println("Login Firestore");
    Request response = postRequest(host, path, "{\"email\":\"" + email + "\",\"password\":\"" + password + "\",\"returnSecureToken\":true}", key);
    if (response.statusCode != 200)
    {
        Serial.println("Connection failed.");
        return "";
    }

    Serial.println("Login success.");
    Serial.println("Body: " + response.body);
    const String token = getToken(response.body.c_str());
    Serial.println("Token: " + token);
    return token;
}