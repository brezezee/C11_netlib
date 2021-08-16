#pragma once

#include <mutex>
#include <vector>
#include <thread>
#include <unordered_set>

#include "TimeWheel.h"

template<int BaseScale = 50>
class TimeWheelManager {
public:
  static TimeWheelManager* GetTimerWheelManager();

  uint32_t CreateTimerAt(int64_t trigger_time, const TaskCallback& task);
  uint32_t CreateTimerAfter(int64_t delay_time, const TaskCallback& task);
  uint32_t CreateTimerEvery(int64_t interval_time, const TaskCallback& task);

  void CancelTimer(uint32_t timer_id);

  uint32_t RefreshTimer(uint32_t timer_id, int64_t delay_time, const TaskCallback& task);

  bool Start();
  void Stop();

  void AppendTimeWheel(uint32_t numslot, uint32_t ms_pre_slot, const std::string& name = "");

private:
  void Run();

  TimeWheelPtr GetGreatestTimeWheel();
  TimeWheelPtr GetLeastTimeWheel();

// 单例相关
private:
  TimeWheelManager(uint32_t basescale = BaseScale);
  ~TimeWheelManager();

  static TimeWheelManager* ptimemanager_;

  struct GC {
    GC() { }

    ~GC() {
      if (ptimemanager_) { 
        ptimemanager_->Stop();
        delete ptimemanager_;
      }
    }
  };

  static GC gc;

private:
  std::mutex mtx_;
  std::thread thread_;

  bool stop_;

  std::unordered_set<uint32_t> cancel_timer_ids_;

  uint32_t base_scale_ms_;
  std::vector<TimeWheelPtr> time_wheels_;
};
