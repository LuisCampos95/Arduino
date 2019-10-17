#include <ESP8266WiFi.h>

#define ldr 0
#define led1 14
#define led2 12
#define led3 13

const char* ssid = "Seu Wifi aqui";
const char* password = "Sua senha aqui";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(ldr, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Conectando com ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  
  // Start the server
  server.begin();
  Serial.print("Servidor iniciado em: ");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("Cliente Encontrado");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if(request.indexOf("led1") != -1){
    digitalWrite(led1, !digitalRead(led1));
  }
  if(request.indexOf("led2") != -1){
    digitalWrite(led2, !digitalRead(led2));
  }
  if(request.indexOf("led3") != -1){
    digitalWrite(led3, !digitalRead(led3));
  }

  if(request.indexOf("Desligar") != -1){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }

  if(request.indexOf("Ligar") != -1){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }

  int luminosidade = analogRead(ldr);
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  
  if(digitalRead(led1)){
    client.println("Led1 on");
  }else{
    client.println("Led1 off");
  }
    
  if(digitalRead(led2)){
    client.println("Led2 on");
  }else{
    client.println("Led2 off");
  }
   
  if(digitalRead(led3)){
    client.println("Led3 on");
  }else{
    client.println("Led3 off");
  }
    
  client.print(luminosidade);
  delay(1);
}

