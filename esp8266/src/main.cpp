#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define AP_SSID "wakaka"
#define AP_PSK  "swc20001030"

const char* ssid     = AP_SSID;
const char* password = AP_PSK;

WiFiUDP udp;

unsigned int localUdpPort  = 33333;  // 自定义本地监听端口
unsigned int remoteUdpPort;
IPAddress remoteUdpIP;

void handshake(WiFiUDP * udp){
    char incomingPacket[32]; 
    int packetSize;
   
    while( true ){
        packetSize = (*udp).parsePacket();
        if((*udp).available()){
            int len = (*udp).read(incomingPacket, 255);
            incomingPacket[len]='\0';
            if( strcmp(incomingPacket, "hello,imuonfeet!") == 0 ){
                (*udp).beginPacket((*udp).remoteIP(), (*udp).remotePort());
                (*udp).print( "hi,imuonfeet!" );
                (*udp).endPacket();
                Serial.printf("handshake success!\r\n");
                remoteUdpIP = (*udp).remoteIP();
                remoteUdpPort = (*udp).remotePort();
                break;
            } else{
                Serial.printf("handshake failed, recv: %s\r\n",incomingPacket);
            }
        }
    }
    digitalWrite(4,HIGH);
}

void setup() {
    pinMode(4,OUTPUT);
    Serial.begin(115200 * 2);
    Serial.printf("begin to connect to %s...\r\n",ssid);
    WiFi.begin(ssid,password);
    
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\r\nconnected success!");
    Serial.printf("local ip: %s\r\n",WiFi.localIP().toString().c_str());

    if(  udp.begin(localUdpPort) ) {
        Serial.println("udp begin success!");
    }else{
        Serial.println("udp begin failed!");
    }

    handshake(&udp);
}

char fifodata [1024];
int cnt = 0;
void loop() {
    
    if( Serial.available() ){
        fifodata[cnt++] = Serial.read();
        if( cnt == 1024 ) {
            cnt = 0;
            udp.beginPacket(remoteUdpIP, remoteUdpPort);
            udp.write((const uint8_t*)fifodata,1024);
            udp.endPacket();
        } 
        
    }
}
