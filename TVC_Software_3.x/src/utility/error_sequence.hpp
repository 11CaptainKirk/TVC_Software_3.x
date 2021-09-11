#include <Arduino.h>

void errorSequence (int mult, int num){
        for (int i = 0; i < 3; i++){            // Sequence start beeps/flashes
            digitalWrite(35, HIGH);             // Because delay is used here, failover deployment is included multiple times to ensure it can run.
            digitalWrite(23, HIGH);             // TODO (Switch for millis implementation)
            delay(50);
            digitalWrite(35, LOW);
            digitalWrite(23, LOW);
            delay(50); 
        }
        delay(1000);
        for (int i = 0; i < mult; i++){            // Multiplier beeps/flashes
            digitalWrite(35, HIGH);
            digitalWrite(23, HIGH);
            delay(200);
            digitalWrite(35, LOW);
            digitalWrite(23, LOW);
            delay(200); 
        }
        delay(500 + 400*(4-mult));
        for (int i = 0; i < num; i++){            // Number beeps/flashes
            digitalWrite(35, HIGH);
            digitalWrite(23, HIGH);
            delay(400);
            digitalWrite(35, LOW);
            digitalWrite(23, LOW);
            delay(400); 
        }
        delay(500 + 800*(4-num));
        }