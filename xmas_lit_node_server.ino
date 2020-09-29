/*------------------------------------------------------------------------------
  07/01/2018
  Author: Makerbro
  Platforms: ESP8266
  Language: C++/Arduino
  File: webserver_html.ino
  ------------------------------------------------------------------------------
  Description: 
  Code for YouTube video demonstrating how to use HTML weppages in a web 
  server's response.
  https://youtu.be/VNgFbQAVboA

  Do you like my videos? You can support the channel:
  https://patreon.com/acrobotic
  https://paypal.me/acrobotic
  ------------------------------------------------------------------------------
  Please consider buying products from ACROBOTIC to help fund future
  Open-Source projects like this! We'll always put our best effort in every
  project, and release all our design files and code for you to use. 

  https://acrobotic.com/
  https://amazon.com/acrobotic
  ------------------------------------------------------------------------------
  License:
  Please see attached LICENSE.txt file for details.
------------------------------------------------------------------------------*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>




ESP8266WebServer server;
uint8_t pin_led = 16;
//char* ssid = "FD-75";
//char* password = "4brother";
char* ssid = "WLANGUEST-CTO";
char* password = "GU3$TC0NN3CTKEY";
//int a =0;
int flex=0;





char webpage[] PROGMEM = R"=====(
<html>
<head>
<script src =" https://cdnjs.cloudflare.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
<script src="https://cdn.socket.io/socket.io-1.4.5.js"></script>

</head>
<body>
<form action="/toggle">

<button> TOGGLE </button>
<p id="val1"></p>
</form>
<script>
var socket=io("http://10.201.92.195:5010");
 $("#val1").html(0);
 var flagP=0,flagC=0;
 console.log(socket);
    socket.on("fSentiment",function(data)
      {
        console.log(data);
        if(data=="happy"||data=="surprise"||data == "neutral"){
                  flagC++; 
                  if(flagC<=1)   
              { $.get("/yellow"); flagP=0;}         
          }
        else if(data == "fear"||data == "sad"||data == "angry"){
           flagP++; 
                  if(flagP<=1)   
              { $.get("/pink"); flagC=0;}         
          }
//        else
//        {
//          $.get("/off");
//        }
        
      $("#val1").html(data);
        });
//setInterval(function(){
//   // console.log("ehllo");
////  $.ajax({
////    url:"/toggle",
////    success: function(data){
////     // socket.emit("value",data1);
////   
////    }
//  });
//},500);
</script>
</body>
</html>
)=====";


//void toggleLED()
//{
//  //digitalWrite(pin_led,!digitalRead(pin_led));
//  flex = analogRead(A0);
//  int a = flex;
//  Serial.println(a);
//  char b[4];
//  String str;
//  str = String(a);
//  str.toCharArray(b,4);
//   server.send_P(200,"text/plain",b);
//  //server.send_P(200,"text/html", webpage);
//  //server.on("/toggle",toggleLED);
//     
//  //digitalWrite(pin_led,!digitalRead(pin_led));
//  //server.send_P( 200,"text/html","<h1>Hello World!</h1>"+a);
//}

void yellowLed()
{

  digitalWrite(D0,LOW);
  digitalWrite(D1,HIGH);
  Serial.print("Yellow");
  server.send(200,"text/plain","abc");
  
  }
  void pinkLed(){
  digitalWrite(D1,LOW);
  digitalWrite(D0,HIGH);
  Serial.print("Pink");
   server.send(200,"text/plain","abc");
  }
void off()
{

  digitalWrite(D0,HIGH);
  digitalWrite(D1,HIGH);
  Serial.print("off");
  
  
  }
  void setup()
{
  // put your setup code here, to run once:
  pinMode(D0,OUTPUT);
  pinMode(D1, OUTPUT);
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

 // server.on("/toggle",toggleLED);
  server.on("/yellow",yellowLed);
  server.on("/pink",pinkLed);
  server.on("/off",off);

  
  server.on("/",[](){server.send(200,"text/html",webpage);});
 
  server.begin();
}

void loop()
{
  server.handleClient();
}
