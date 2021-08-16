#pragma once

#include <cstdint>
#include <functional>
#include <memory>

using  TaskCallback = std::function<void()>;

class Timer {
public:
  Timer(uint32_t id, int64_t trigger_time, int64_t interval_time, const TaskCallback& task);

  // 执行定时器指定的任务
  void execute();  

  uint32_t id() const {
    return id_;
  }

  int64_t trigger_time() const {
    return trigger_time_;
  }

  bool repeated() const {
    return repeated_;
  }

  void UpdateTriggerTime() {
    trigger_time_ += interval_time_;
  }
 
private:
  // 定时器任务封装， id标识、任务回调、触发时间、间隔时间、是否重复
  uint32_t id_;
  TaskCallback task_;
  int64_t trigger_time_;
  uint32_t interval_time_;
  bool repeated_;
};
