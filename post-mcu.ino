#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//Modificar as constantes abaixo conforme necessário.
const char* ssid = "iPhone de Diego";
const char* password = "12345678";

const String orgId = "8xa6fn";
const String deviceType = "l-sensor";
const String deviceId = "ls-01";
const char* deviceToken = "EnQKw4gdRbz1iBnb?9";
const String eventId = "data";


//Nao modificar os valores das constantes abaixo
const char* user = "use-token-auth"; 
const String url = "http://"+orgId+".messaging.internetofthings.ibmcloud.com:1883/api/v0002/device/types/"+deviceType+"/devices/"+deviceId+"/events/"+eventId;


//Modificar as variáveis abaixo conforme necessário. 
String json = "";
String dataType = "luminosity";
int data = 20;


void setup () {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}
 
void loop() {
  sendData(); //Envia os dados 
  delay(5000); //Delay de 5 segundos
  data++; //Adiciona 1 ao valor de 'data'
}

//Método que envia os dados para a plataforma
void sendData() {
  if (WiFi.status() == WL_CONNECTED) {  
    HTTPClient http;
    http.begin(url);

    http.setAuthorization(user, deviceToken);
    http.addHeader("Content-Type", "application/json");

    json = String("{\"d\":{\""+dataType+"\" : "+data+"}}");

    int httpCode = http.POST(json);

    http.end(); 
  }  
}
