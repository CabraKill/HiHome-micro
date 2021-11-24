#include <Arduino.h>

typedef struct{
    int statusCode;
    String body;
} Request;

Request postRequest(String url, String path, String body);
Request getRequest(String url, String path, String body);
bool makeRequest(String url, String path, String body, String requesType, int port);
String readBody();