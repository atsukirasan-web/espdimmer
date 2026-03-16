import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.cpp_types import Component
from esphome.components import i2c
from esphome.cpp_generator import Pvariable, add

# Automation keys
CONF_ON_PRESS = "on_press"
CONF_ON_LONG_PRESS = "on_long_press"
CONF_ON_CLOCKWISE = "on_clockwise"
CONF_ON_COUNTER_CLOCKWISE = "on_counter_clockwise"

DEPENDENCIES = ["i2c"]

dfrobot_visual_encoder_ns = esphome.codegen.namespace('dfrobot_visual_encoder')
DFRobotVisualEncoder = dfrobot_visual_encoder_ns.class_(
    'DFRobotVisualEncoder', Component, i2c.I2CDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(DFRobotVisualEncoder),
    cv.Optional(CONF_ON_CLOCKWISE): cv.single_automation(),
    cv.Optional(CONF_ON_COUNTER_CLOCKWISE): cv.single_automation(),
    cv.Optional(CONF_ON_PRESS): cv.single_automation(),
    cv.Optional(CONF_ON_LONG_PRESS): cv.single_automation(),
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = Pvariable(config[CONF_ID], 0x36)  # default I2C address
    add(var)

    if CONF_ON_CLOCKWISE in config:
        for call in config[CONF_ON_CLOCKWISE]:
            var.add_on_clockwise_callback(call)
    if CONF_ON_COUNTER_CLOCKWISE in config:
        for call in config[CONF_ON_COUNTER_CLOCKWISE]:
            var.add_on_counter_clockwise_callback(call)
    if CONF_ON_PRESS in config:
        for call in config[CONF_ON_PRESS]:
            var.add_on_press_callback(call)
    if CONF_ON_LONG_PRESS in config:
        for call in config[CONF_ON_LONG_PRESS]:
            var.add_on_long_press_callback(call)