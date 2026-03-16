#pragma once

#include "esphome.h"
#include "DFRobot_VisualRotaryEncoder.h"

namespace esphome {
namespace dfrobot_visual_encoder {

class DFRobotVisualEncoder : public PollingComponent, public i2c::I2CDevice {
 public:
  explicit DFRobotVisualEncoder(i2c::I2CComponent *parent)
      : PollingComponent(50), i2c::I2CDevice(parent) {}

  void setup() override {
    encoder.begin();
    this->encoder.setGainCoefficient(1);
    last_value = encoder.getEncoderValue();
  }

  void update() override {
    uint16_t new_val = encoder.getEncoderValue();
    if (new_val > last_value) {
      for (auto &cb : on_clockwise_callbacks_) cb();
    } else if (new_val < last_value) {
      for (auto &cb : on_counter_clockwise_callbacks_) cb();
    }
    last_value = new_val;
  }

  void add_on_clockwise_callback(std::function<void()> cb) {
    on_clockwise_callbacks_.push_back(cb);
  }
  void add_on_counter_clockwise_callback(std::function<void()> cb) {
    on_counter_clockwise_callbacks_.push_back(cb);
  }
  void add_on_press_callback(std::function<void()> cb) {
    on_press_callbacks_.push_back(cb);
  }
  void add_on_long_press_callback(std::function<void()> cb) {
    on_long_press_callbacks_.push_back(cb);
  }

  void set_led_level(float level) {
    encoder.setEncoderValue((uint16_t) (level * 1023.0f));
  }

 protected:
  DFRobot_VisualRotaryEncoder encoder;
  uint16_t last_value{0};
  std::vector<std::function<void()>> on_clockwise_callbacks_;
  std::vector<std::function<void()>> on_counter_clockwise_callbacks_;
  std::vector<std::function<void()>> on_press_callbacks_;
  std::vector<std::function<void()>> on_long_press_callbacks_;
};

}  // namespace dfrobot_visual_encoder
}  // namespace esphome