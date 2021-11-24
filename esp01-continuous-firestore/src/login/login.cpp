#include <Arduino.h>
#include <WiFiClientSecure.h>
#include "login.h"
#include "../requestHandler/requestHandler.h"
#include "getToken.h"

String loginFirestoreWithEmail(String email, String password)
{
    WiFiClientSecure client;
    client.setFingerprint(fingerprint);
    client.setTimeout(500);
    
    Serial.println("Login Firestore");
    if (!client.connect(loginHost, 443))
    {
        Serial.println("Login connection failed.");
        return "";
    }

    Serial.println("Connection started...");
    Request response = postRequest(loginHost, path, "{\"email\":\"" + email + "\",\"password\":\"" + password + "\",\"returnSecureToken\":true}");
    if (response.statusCode != 200)
    {
        Serial.println("Connection failed.");
        return "";
    }

    Serial.println("Login success.");
    Serial.println("Body: " + response.body);
    String token = getToken(response.body);
    Serial.println("Token: " + token);
    return token;
}