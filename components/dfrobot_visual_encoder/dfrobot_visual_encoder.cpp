#include "dfrobot_visual_encoder.h"
#include "esphome/core/log.h"

namespace esphome {
namespace dfrobot_visual_encoder {

static const char *TAG = "dfrobot_visual_encoder";

void DFRobotVisualEncoder::setup() {
  ESP_LOGI(TAG, "DFRobot Visual Encoder initialized");
}

void DFRobotVisualEncoder::loop() {

  uint8_t data[2];

  if (!this->read(data, 2)) {
    return;
  }

  int16_t value = (data[0] << 8) | data[1];

  if (value > last_value_) {
    ESP_LOGD(TAG, "Clockwise");
  }

  if (value < last_value_) {
    ESP_LOGD(TAG, "Counter Clockwise");
  }

  last_value_ = value;
}

void DFRobotVisualEncoder::set_led_level(float level) {

  uint8_t brightness = level * 255;

  uint8_t buf[2];
  buf[0] = 0x10;
  buf[1] = brightness;

  this->write(buf, 2);
}

}  // namespace dfrobot_visual_encoder
}  // namespace esphome
