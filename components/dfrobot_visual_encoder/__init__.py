import esphome.codegen as cg
import esphome.config_validation as cv

from esphome.components import i2c
from esphome.const import CONF_ID

DEPENDENCIES = ["i2c"]

CONF_ON_CLOCKWISE = "on_clockwise"
CONF_ON_COUNTER_CLOCKWISE = "on_counter_clockwise"
CONF_ON_PRESS = "on_press"
CONF_ON_LONG_PRESS = "on_long_press"

dfrobot_visual_encoder_ns = cg.esphome_ns.namespace("dfrobot_visual_encoder")

DFRobotVisualEncoder = dfrobot_visual_encoder_ns.class_(
    "DFRobotVisualEncoder", cg.Component, i2c.I2CDevice
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(DFRobotVisualEncoder),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x36))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
