#include <Arduino.h>

typedef struct
{
    int statusCode;
    const String body;
} Request;

Request postRequest(String url, String path, String body, const String headers, const char *fingerprint);
Request getRequest(String url, String path, const String headers, const char *fingerprint);
bool makeRequest(String url, String path, String body, const String headers, String requesType, int port, const char *fingerprint);
String readBody();