#include <Arduino.h>

//SHA-1 Fingerprint
const char fingerprint[] PROGMEM = "68 DB 23 67 82 7A 3D 3A 3D 68 E1 7B DD 8E 49 36 FB 46 8B B8";
const String loginHost = "identitytoolkit.googleapis.com";
const String path = "/v1/accounts:signInWithPassword?key=AIzaSyAIdWnqjoG0uo3Z2CYYpB0IHig1CqtLpKA";

String loginFirestoreWithEmail(String email, String password);