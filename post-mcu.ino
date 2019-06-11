#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//Modificar as constantes abaixo conforme necessário.
const char* nomeWifi = "";
const char* senhaWifi = "";

const String organizacao = "";
const String tipo = "";
const String id = "";
const char* senha = "";

//Nao modificar os valores das constantes abaixo
const String evento = "data";
const char* usuario = "use-token-auth"; 
const String endereco = "http://"+organizacao+".messaging.internetofthings.ibmcloud.com:1883/api/v0002/device/types/"+tipo+"/devices/"+id+"/events/"+evento;

int pinoLDR = A0;

void setup () {
  Serial.begin(115200);
  
  WiFi.begin(nomeWifi, senhaWifi);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}
 
void loop() {
  int valor = analogRead(pinoLDR);

  if(!isnan(valor)) {
    enviar("luminosidade", valor);
  }

  delay(2000);
}


void enviar(String descricao, double valor) {
  if (WiFi.status() == WL_CONNECTED) {  
    HTTPClient http;
    http.begin(endereco);

    http.setAuthorization(usuario, senha);
    http.addHeader("Content-Type", "application/json");

    String json = String("{\"d\":{\""+descricao+"\" : "+valor+"}}");

    int httpCode = http.POST(json);

    http.end(); 
  }  
}
