#define USE_WIFI_NINA         false
#define USE_WIFI101           true
#include <WiFiWebServer.h>

const char ssid[] = "EEERover";
const char pass[] = "exhibition";

//Webpage to return when root is requested
const char webpage[] = \
"<html><head>\
<title>MOONROVER CONTROLS</title>\
<link href=\"style.css\" rel=\"stylesheet\">\
</head><body>\
<header>MOONROVER CONTROLS</header>\
<div id=\"all\"><div class=\"center\">\
<button id=\"f\" class=\"vert btn\">&#x21E7;</button>\
</div><br><div class=\"center\">\
<button class=\"btn\" id=\"l\">&#x21E6;</button>\
<button class=\"btn\" id=\"s\">Scan</button>\
<button class=\"btn\" id=\"r\">&#x21E8;</button>\
</div><br>\
<div class=\"center\">\
<button id=\"b\" class=\"vert btn\">&#x21E9;</button>\
</div><br></div></body>\
<script type=\"text/javascript\" src=\"java.js\"></script>\
<script type=\"text/javascript\" src=\"java1.js\"></script>\
<footer>\
<h2>mineral:<div id=\"mineral\">none</div></h2><h2>direction:<div class=\"inline\" id=\"state\">stationary</div></h2>\
</footer></html>";

const char style[] = \
"*{margin: 0;padding: 0;}\
body {background-color: rgb(78, 78, 78);}\
.btn{background-color: rgb(54, 54, 54);color: #eee;padding: 10px 25px;font-size: 80px;font-family: 'Courier New', Courier, monospace;margin: 7.5px 15px;border-radius: 10px;}\
.vert{padding: 10px 33px;}\
#all{padding: 100px;margin: 0;position: absolute;top: 50%; left: 50%;-ms-transform: translateY(-50%);transform: translateY(-50%);-ms-transform: translate(-50%, -50%);transform: translate(-50%, -50%);}\
.btn:hover {background: rgb(93, 93, 93);}\
h2{color: black;text-transform: uppercase;font-size: 50px;font-family: 'Courier New', Courier, monospace;display: inline-block;width: 50%; text-align: center;}\
header{color: black;font-size: 60px;font-weight: 550;font-family: 'Courier New', Courier, monospace;text-align: center;text-decoration: underline;}\
.center{width: max-content;margin: 0 auto;}\
footer{position: fixed;bottom: 0;width: 100%;}";

const char java[] = \
"var last_key = 0;\
function changecolor(i){document.getElementById(i).style.backgroundColor = \"rgb(93, 93, 93)\";};\
document.onkeydown = function down(event){var key_press = event.keyCode;\
if(key_press == last_key){}else if(key_press == 87){Fforwards();changecolor(\"f\");}else if(key_press == 83){Fbackwards();changecolor(\"b\");}else if(key_press == 65){Fleft();changecolor(\"l\");}else if(key_press == 68){Fright();changecolor(\"r\");}else if(key_press == 81){scan();changecolor(\"s\");}else if(key_press == 38){Sforwards();changecolor(\"f\");}else if(key_press == 40){Sbackwards();changecolor(\"b\");}else if(key_press == 37){Sleft();changecolor(\"l\");}else if(key_press == 39){Sright();changecolor(\"r\");}else if(key_press == 69){reset();}\
last_key = key_press;};\
document.onkeyup = function up(event){neutral();\
for (let i = 0; i < 5; i++){document.getElementsByClassName(\"btn\")[i].style.backgroundColor = \"rgb(54, 54, 54)\";}\
last_key = 0;};";

const char java1[] = \
"var xhttp = new XMLHttpRequest();\
var miner = new XMLHttpRequest();\
xhttp.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {document.getElementById(\"state\").innerHTML = this.responseText;}};\
miner.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {document.getElementById(\"mineral\").innerHTML = this.responseText;}};\
function Fright() {xhttp.open(\"GET\", \"/fr\"); xhttp.send();}\
function Fleft() {xhttp.open(\"GET\", \"/fl\"); xhttp.send();}\
function Fforwards(){xhttp.open(\"GET\", \"/ff\"); xhttp.send();}\
function Fbackwards(){xhttp.open(\"GET\", \"/fb\"); xhttp.send();}\
function Sright() {xhttp.open(\"GET\", \"/sr\"); xhttp.send();}\
function Sleft() {xhttp.open(\"GET\", \"/sl\"); xhttp.send();}\
function Sforwards(){xhttp.open(\"GET\", \"/sf\"); xhttp.send();}\
function Sbackwards(){xhttp.open(\"GET\", \"/sb\"); xhttp.send();}\
function neutral(){xhttp.open(\"GET\", \"/nu\"); xhttp.send();}\
function reset(){xhttp.open(\"GET\", \"/r\"); xhttp.send();}\
function scan(){miner.open(\"GET\", \"/s\");miner.send();}";

WiFiWebServer server(80);
int  LDirection  = 4;
int RDirection = 3;
int avgacu;
int avgmag;

//Return the web page
void handleRoot()
{
  server.send(200, F("text/html"), webpage);
}
//sends the rest of the webpage
void styler()
{
  server.send(200, F("text/css"), style);
}

void code()
{
  server.send(200, F("text/javascript"), java);
}

void code1()
{
  server.send(200, F("text/javascript"), java1);
}
//the code for all the movement
void Fleft()
{
  digitalWrite(LDirection,HIGH);
  digitalWrite(RDirection,LOW);
  analogWrite(13,250);
  analogWrite(12,250);
  server.send(200, F("text/plain"), F("left"));
}

void Fright()
{
  digitalWrite(LDirection,LOW);
  digitalWrite(RDirection,HIGH);
  analogWrite(13,250);
  analogWrite(12,250);
  server.send(200, F("text/plain"), F("right"));
}

void Fbackwards()
{
  digitalWrite(LDirection,LOW);
  digitalWrite(RDirection,LOW);
  analogWrite(13,250);
  analogWrite(12,250);
  server.send(200, F("text/plain"), F("backwards"));
}

void Fforwards()
{
  digitalWrite(LDirection,HIGH);
  digitalWrite(RDirection,HIGH);
  analogWrite(13,250);
  analogWrite(12,250);
  server.send(200, F("text/plain"), F("forwards"));
}

void Sleft()
{
  digitalWrite(LDirection,HIGH);
  digitalWrite(RDirection,LOW);
  analogWrite(13,90);
  analogWrite(12,90);
  server.send(200, F("text/plain"), F("Slow left"));
}

void Sright()
{
  digitalWrite(LDirection,LOW);
  digitalWrite(RDirection,HIGH);
  analogWrite(13,90);
  analogWrite(12,90);
  server.send(200, F("text/plain"), F("Slow right"));
}

void Sbackwards()
{
  digitalWrite(LDirection,LOW);
  digitalWrite(RDirection,LOW);
  analogWrite(13,90);
  analogWrite(12,90);
  server.send(200, F("text/plain"), F("Slow backwards"));
}

void Sforwards()
{
  digitalWrite(LDirection,HIGH);
  digitalWrite(RDirection,HIGH);
  analogWrite(13,90);
  analogWrite(12,90);
  server.send(200, F("text/plain"), F("Slow forwards"));
}

void neutral()
{
  digitalWrite(LDirection,LOW);
  digitalWrite(RDirection,HIGH);
  analogWrite(13,0);
  analogWrite(12,0);
  server.send(200, F("text/plain"), F("stationary"));
}

//infrared pin a1
//radio pin a0
double MAX(int pinnum){
  double Max = 0;
  double v[600];
  for(int i = 0; i < 600; i++){    
    v[i] = analogRead(pinnum); 
    if(v[i] > Max){
        Max = v[i];
    }
  }
  return Max;
}

double findavg(int pinnum){
  double v[1000];
  double Max,Min,avg;
  Max = 0;
  Min = 1024;
  for(int i = 0; i < 1000; i++){ 
    v[i] = analogRead(pinnum); 
    if(v[i] > Max){
        Max = v[i];
    }
    if(v[i] < Min){
        Min = v[i];
    }
  }
  avg = (Max + Min)/2;
  return avg;
}

double average(int pinnum){
  double avg=0;
  for(int i = 0; i < 1000; i++){ 
    avg = avg + analogRead(pinnum); 
  }
  avg = avg/1000;
  return avg;
}

void reset(){
  avgacu = average(2);
  avgmag = average(5);
  server.send(200, F("text/plain"), F("reset"));
}

int findf(int pinnum, double avg){
  double v3[1200];
  int pass2 = 0,f;
  long int t3=0,t4=0,t5=0;
  for(int i=0;i<1200;i++){      
      v3[i]=analogRead(pinnum); 
      if(i > 0){       
        if((v3[i-1] < avg) && (v3[i]> avg)){
          pass2++;
        }        
        else if((v3[i-1] > avg) && (v3[i]< avg)){
          pass2++;
        }
      }     
      if(pass2 == 1){       
        t3 = micros();
      }    
      if(pass2 == 3){
        t4 = micros();
        t5 = t4 - t3;
      }
    }
    f = 1000000/t5;
    return f; 
}
// radio is pin 0 IF is pin 1
// for IF max is less than 300 for radio is less tha  
int IF() {
  int pass1 = 0,pass2 = 0,IFfrequency = 0;
  double IFavg = MAX(1)/2; 
  IFfrequency = findf(1, IFavg);
  if((IFfrequency<363)&&(IFfrequency>343)){
     IFfrequency = 353;
     pass1++;
  } else if((IFfrequency<591)&&(IFfrequency>551)){
    IFfrequency = 571;
    pass2++;
  } else{
    IFfrequency = 0;
  }
  return IFfrequency;
}
  //RADIO
int Radio(){
  int RAfrequency = 0;
  double RAMaxi = MAX(0),RAcomp;
  RAcomp = MAX(0) - 10;
  if(RAMaxi > 400){  
    RAfrequency = findf(0, RAcomp);
    if((RAfrequency<161)&&(RAfrequency>141)){
       RAfrequency = 151;
    }  
    else if((RAfrequency<249)&&(RAfrequency>229)){
       RAfrequency = 239;
    }
    else{
      RAfrequency = 0;
    }
  }
  return RAfrequency;
}
 //ACCOUSTIC pin a2
int acoustics(){
  int pass = 0,acoustic = 0;
  for(int i = 0; i < 10; i++){
    double ACmax = MAX(2);
    if(ACmax > avgacu+10){
      pass++;
    }
  }
  if(pass > 5){
    acoustic = 1;
  }
  return acoustic;
}

int magnetic(){
  int magnetic = 0;
  double MAavg = findavg(5);
  if((MAavg > avgmag+50)||(MAavg < avgmag-50)){
    magnetic = 1;
  }
  return magnetic;
}
//Runs all of the scanning functions and works out what rock it is based off that
void scan()
{
  int rad,acu,IR,mag;
  rad = Radio();
  acu = acoustics();
  IR = IF();
  mag = magnetic();
  Serial.print("acu:");
  Serial.println(acu);
  Serial.print("IR:");
  Serial.println(IR);
  Serial.print("rad:");
  Serial.println(rad);
  Serial.print("mag:");
  Serial.println(mag);
  if ((rad == 151)&&(acu == 1)&&(IR == 0)&&(mag == 0)){
    server.send(200, F("text/plain"), F("Gaborium"));
  }else if ((rad == 239)&&(acu == 0)&&(IR == 0)&&(mag == 0)){
    server.send(200, F("text/plain"), F("Lathwaite"));
  }else if ((rad == 0)&&(acu == 0)&&(IR == 353)&&(mag == 0)){
    server.send(200, F("text/plain"), F("Thiotimoline"));
  }else if ((rad == 0)&&(acu == 1)&&(IR == 571)&&(mag == 0)){
    server.send(200, F("text/plain"), F("Netherite"));
  }else if ((rad == 151)&&(acu == 0)&&(IR == 0)&&(mag == 1)){
    server.send(200, F("text/plain"), F("Adamantine"));
  }else if ((rad == 239)&&(acu == 0)&&(IR == 0)&&(mag == 1)){
    server.send(200, F("text/plain"), F("Xirang"));
  }else if ((rad == 0)&&(acu == 0)&&(IR == 0)&&(mag == 1)){
    server.send(200, F("text/plain"), F("Xirang or Adamantine"));
  }else if ((rad == 0)&&(acu == 1)&&(IR == 0)&&(mag == 0)){
    server.send(200, F("text/plain"), F("Netherite or Gaborium"));
  }else{
    server.send(200, F("text/plain"), F("none"));
  }
}

//Generate a 404 response with details of the failed request
void handleNotFound()
{
  String message = F("File Not Found\n\n"); 
  message += F("URI: ");
  message += server.uri();
  message += F("\nMethod: ");
  message += (server.method() == HTTP_GET) ? F("GET") : F("POST");
  message += F("\nArguments: ");
  message += server.args();
  message += F("\n");
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, F("text/plain"), message);
}

void setup()
{

  Serial.begin(9600);

  Serial.println(F("\nStarting Web Server"));

  //Check WiFi shield is present
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println(F("WiFi shield not present"));
    while (true);
  }

  //Configure the static IP address if group number is set
  WiFi.config(IPAddress(192,168,0,20));

  // attempt to connect to WiFi network
  Serial.print(F("Connecting to WPA SSID: "));
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    delay(500);
    Serial.print('.');
  }

  //Register the callbacks to respond to HTTP requests
  server.on(F("/"), handleRoot);
  server.on(F("/style.css"), styler);
  server.on(F("/java.js"), code);
  server.on(F("/java1.js"), code1);
  server.on(F("/fr"), Fright);
  server.on(F("/fl"), Fleft);
  server.on(F("/ff"), Fforwards);
  server.on(F("/fb"), Fbackwards);
  server.on(F("/sr"), Sright);
  server.on(F("/sl"), Sleft);
  server.on(F("/sf"), Sforwards);
  server.on(F("/sb"), Sbackwards);
  server.on(F("/nu"), neutral);
  server.on(F("/s"), scan);
  server.on(F("/r"), reset);

  server.onNotFound(handleNotFound);
  
  server.begin();
  
  Serial.print(F("HTTP server started @ "));
  Serial.println(static_cast<IPAddress>(WiFi.localIP()));

  pinMode( LDirection , OUTPUT);  // is the mag down input high ?
  pinMode( RDirection, OUTPUT);  // IF low forwards
  avgacu = average(2);
  avgmag = average(5);
}

//Call the server polling function in the main loop
void loop()
{
  server.handleClient();
}