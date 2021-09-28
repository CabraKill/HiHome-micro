#define RELAY 0 // relay connected to  GPIO0

void setup() 
{
  pinMode(RELAY,OUTPUT);
  digitalWrite(RELAY, LOW); 
}
 
void loop() 
{
  digitalWrite(RELAY, HIGH);
  delay(1000);
  digitalWrite(RELAY, LOW);
  delay(1000);
}
