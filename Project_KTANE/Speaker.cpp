//
// Created by ulric on 1/8/2026.
//

#include "Speaker.hpp"

void init_Speaker() {
    Serial1.begin(9600);
}

void Play_Music(String a) {
    Serial1.println("PLAY:" + a);
}
