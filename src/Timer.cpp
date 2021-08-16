#include "Timer.h"

Timer::Timer(uint32_t id, int64_t trigger_time, int64_t interval_time, const TaskCallback& handler)
    : interval_time_(interval_time)
    , repeated_(interval_time_ > 0)   // 根据是否设置间隔时间 判断是否需要重复
    , trigger_time_(trigger_time)
    , id_(id)
    , task_(handler) {
}

void Timer::execute() {
  if (task_) {
    task_();
  }
}
