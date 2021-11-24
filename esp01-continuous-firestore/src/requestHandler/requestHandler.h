#include <Arduino.h>

typedef struct
{
    int statusCode;
    String body;
} Request;

Request postRequest(String url, String path, String body, const char *fingerprint);
Request getRequest(String url, String path, String body, const char *fingerprint);
bool makeRequest(String url, String path, String body, String requesType, int port, const char *fingerprint);
String readBody();