const int LDR_PIN=A0;
const int LED_PIN=8;

int lightLevel=0;
int threshold=500;

void setup() {
 pinMode(LED_PIN,OUTPUT);
 Serial.begin(9600);
 
}

void loop() {
 lightLevel=analogRead(LDR_PIN);
 Serial.print("LightLevel:");
 Serial.print("lightLevel");
 if(lightLevel<threshold){
  digitalWrite(LED_PIN,HIGH);
 }else{
  digitalWrite(LED_PIN,LOW);
 } 
 delay(500);
}
