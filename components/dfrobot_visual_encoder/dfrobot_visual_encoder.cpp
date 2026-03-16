#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace dfrobot_visual_encoder {

class DFRobotVisualEncoder : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void loop() override;

  void set_led_level(float level);

 protected:
  int16_t last_value_{0};
  uint32_t last_button_{0};
};

}  // namespace dfrobot_visual_encoder
}  // namespace esphome
