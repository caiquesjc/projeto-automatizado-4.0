#include <ESP32Servo.h>

#include <WiFi.h>

#include "BluetoothSerial.h" //Header File for Serial Bluetooth, will be added by default into Arduino

BluetoothSerial ESP_BT; //Object for Bluetooth

int incoming;


String  ClientRequest;
WiFiServer server(80);

WiFiClient client;

String myresultat;

String ReadIncomingRequest(){
while(client.available()) {
ClientRequest = (client.readStringUntil('\r'));
 if ((ClientRequest.indexOf("HTTP/1.1")>0)&&(ClientRequest.indexOf("/favicon.ico")<0)){
myresultat = ClientRequest;
}
}
return myresultat;
}

Servo servo_13;

void setup()
{
  Serial.begin(9600);
  ESP_BT.begin("Solucães"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");
ClientRequest = "";


pinMode(26, OUTPUT); //este é um pino para que você possa testar um led, acender um led, caso queira acender
servo_13.attach(13); 

  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("Miguel","25038791");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
  server.begin();

}


void loop(){ //dentro deste loop, 1, 2, 3 representam a qunantidade de ração que será liberada. 
			 //Ou seja, o tempo em que a pá do motor irá de mecher
  

  if (ESP_BT.available()) //Check if we receive anything from Bluetooth
  {
    incoming = ESP_BT.read(); //Read what we recevive 
    Serial.print("Received:"); Serial.println(incoming);

    if (incoming == 1) {
      servo_13.write(60);
      delay(100);
      servo_13.write(0);
    }

    if (incoming == 2) {
      servo_13.write(60);
      delay(100);
      servo_13.write(0);
    }

    if (incoming == 2) {
      servo_13.write(60);
      delay(250);
      servo_13.write(0);
    }

    if (incoming == 3) {
      servo_13.write(60);
      delay(250);
      servo_13.write(0);
    }

    if (incoming == 01) {
      digitalWrite(26, HIGH);
    }
    if (incoming == 011) {
      digitalWrite(26, LOW);
    }

    
    

    

    client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    ClientRequest = (ReadIncomingRequest());
    ClientRequest.remove(0, 5);
    ClientRequest.remove(ClientRequest.length()-9,9);
    if (ClientRequest == "on") {
      digitalWrite(26,HIGH);
      servo_13.write(180);
      delay(2000);
      servo_13.write(0);

    }
    if (ClientRequest == "off") {
      digitalWrite(26,LOW);

    }
    if (ClientRequest == "1") {
      servo_13.write(60);
      delay(0);
      delay(100);
      servo_13.write(0);
      delay(0);

    }
    if (ClientRequest == "2") {
      servo_13.write(60);
      delay(250);
      servo_13.write(0);

    }
    if (ClientRequest == "3") {
      servo_13.write(60);
      delay(500);
      servo_13.write(0);

    }
    if (ClientRequest == "00") {
      servo_13.write(360);
      delay(500);
      servo_13.write(0);

    }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("OK");
    client.println("</html>");
    client.stop();
    delay(1);
    client.flush();
  }
}
