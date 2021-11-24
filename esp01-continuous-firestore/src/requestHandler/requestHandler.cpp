#include <Arduino.h>
#include <WiFiClientSecure.h>
#include "requestHandler.h"

bool makeRequest(String url, String path, String body, String requesType, int port)
{
  WiFiClientSecure client;
  if (!client.connect(url, port))
  {
    Serial.println("Login connection failed.");
    return false;
  }

  client.print(String(requesType + " ") + path + " HTTP/1.1\r\n" +
               "Host: " + url + "\r\n" +
               "Content-Type: application/json" +
               "Connection: close\n" +
               "Content-Length: " + body.length() +
               "\n\n" +
               body + "\n");
  // "\r\n\r\n"
  Serial.println("request sent");

  return true;
}

Request postRequest(String url, String path, String body)
{
  WiFiClientSecure client;
  bool result = makeRequest(url, path, body, "POST", 443);
  if (!result)
  {
    return {400, "Bad Request"};
  }
  String responseBody = readBody();
  Request request = {0, responseBody};
  return request;
}

Request getRequest(String url, String path, String body)
{
  WiFiClientSecure client;
  bool result = makeRequest(url, path, body, "GET", 443);
  if (!result)
  {
    return {400, "Bad Request"};
  }
  String responseBody = readBody();
  Request request = {0, responseBody};
  return request;
}

String readBody()
{
  WiFiClientSecure client;
  String requestBody = "";
  String line = "";
  while (client.connected())
  {

    line = client.readStringUntil('\n');
    if (line == "\r")
    {
      // Serial.println(line);
      // Serial.println("headers received");
      break;
    }
    else
    {
      // Serial.print(line);
    }
  }

  String last = "";
  bool first = true;

  while (client.available())
  {
    line = client.readStringUntil('\n');
    if (first)
    {
      first = false;
    }
    else
    {
      // Serial.println(last + "|");
      requestBody = requestBody + last;
      last = line;
    }
  }
  return requestBody;
}