#include <Arduino.h>

void setup() {
    Serial.begin(115200);


}

void loop() {
    Serial.write("hello,world");
    delay(1000);
}
