#include "audio.h"

#include "Arduino.h"

void amorfos::playSound(unsigned int frequency, unsigned long duration) {
    tone(BUZZER, frequency, duration);
}