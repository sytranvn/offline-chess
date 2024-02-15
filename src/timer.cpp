#include "timer.h"

void TimerStart(Timer *timer, float timeLimit) {
  if (timer != nullptr) {
    timer->timeLimit = timeLimit;
  }
}

void TimerStop(Timer *timer) {
  if (timer != nullptr) {
    timer->timeLimit = 0;
  }
}

void TimerUpdate(Timer *timer) {
  if (timer != nullptr) {
    timer->timeLimit -= GetFrameTime();
  }
}

bool TimerIsDone(Timer *timer) {
  if (timer != nullptr) {
    return timer->timeLimit <= 0;
  }
  return false;
}
