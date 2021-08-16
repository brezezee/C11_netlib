#pragma once

#include <chrono>
#include <string>
#include <memory>
#include <vector>
#include <list>

#include "Timer.h"

using spTimer = std::shared_ptr<Timer>;

class TimeWheel {
public:
  TimeWheel(uint32_t slot, uint32_t ms_pre_slot, const std::string& name = "");

  uint32_t ms_pre_slot() const {
    return ms_pre_slot_;
  }

  uint32_t num_slot() const {
    return num_slot_;
  }

  uint32_t current_index() const {
    return current_index_;
  }


  // 设置相对自己的下级时间轮
  void set_less_level_tw(TimeWheel* less_level_tw) {
    less_level_tw_ = less_level_tw;
  }

  void set_greater_level_tw(TimeWheel* greater_level_tw) {
    greater_level_tw_ = greater_level_tw;
  }

  int64_t GetWheelTime() const;

  void AddTimer(spTimer timer);

  void Increase();

  std::list<spTimer> TakeoutSlot();

  friend bool operator< (const TimeWheel& lhs, const TimeWheel& rhs) {
    return lhs.ms_pre_slot_ < rhs.ms_pre_slot_;
  }

  friend bool operator> (const TimeWheel& lhs, const TimeWheel& rhs) {
    return lhs.ms_pre_slot_ > rhs.ms_pre_slot_;
  }

private:
  std::string name_;
  uint32_t current_index_;

  // A time wheel can be devided into multiple slot. A scals has N ms.
  uint32_t num_slot_;
  uint32_t ms_pre_slot_;

  // Every slot corresponds to a scale. Every slot contains the timers.
  std::vector<std::list<spTimer>> slots_;

  TimeWheel* less_level_tw_;  // Less scale unit.
  TimeWheel* greater_level_tw_;  // Greater scale unit.
};

using TimeWheelPtr = std::shared_ptr<TimeWheel>;

// 获取当前时间戳
inline int64_t GetNowTimestamp() {
  using namespace std::chrono;
  auto now = system_clock::now().time_since_epoch();
  // 以毫秒为粒度
  return duration_cast<milliseconds>(now).count();
}

