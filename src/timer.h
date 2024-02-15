#ifndef TIMER_H
#define TIMER_H

#include "raylib.h"
#include <iostream>

typedef struct Timer {
  float timeLimit;
} Timer;

void TimerStart(Timer *timer, float timeLimit);
void TimerStop(Timer *timer);
void TimerUpdate(Timer *timer);
bool TimerIsDone(Timer *timer);

#endif // TIMER_H
