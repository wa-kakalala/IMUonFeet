#include <Arduino.h>
#include <WiFi.h>

#define AP_SSID "wakaka"
#define AP_PSK  "swc20001030"

const char* ssid     = AP_SSID;
const char* password = AP_PSK;

WiFiUDP udp;

unsigned int localUdpPort  = 33333;  // 自定义本地监听端口
unsigned int remoteUdpPort;

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
                break;
            } else{
                Serial.printf("handshake failed, recv: %s\r\n",incomingPacket);
            }
        }
    }
}

void setup() {
    Serial.begin(115200);
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

void loop() {

    Serial.write("hello,world\r\n");
    delay(1000);
}
