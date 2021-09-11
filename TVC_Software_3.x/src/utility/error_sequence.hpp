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
        delay(2000);
        for (int i = 0; i < mult; i++){            // Multiplier beeps/flashes
            digitalWrite(35, HIGH);
            digitalWrite(23, HIGH);
            delay(350);
            digitalWrite(35, LOW);
            digitalWrite(23, LOW);
            delay(350); 
        }
        delay(1000 + 700*(4-mult));
        for (int i = 0; i < num; i++){            // Number beeps/flashes
            digitalWrite(35, HIGH);
            digitalWrite(23, HIGH);
            delay(500);
            digitalWrite(35, LOW);
            digitalWrite(23, LOW);
            delay(500); 
        }
        delay(1000 + 1000*(4-num));
        }