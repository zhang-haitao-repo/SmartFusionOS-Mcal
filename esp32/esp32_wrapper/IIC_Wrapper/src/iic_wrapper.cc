#include "driver/i2c_master.h"
#include "esp_log.h"

static i2c_master_bus_handle_t bus_handle;
static i2c_master_dev_handle_t dev_handle;

void smart_os_iic_init(sf_i2c_config_t* config)
{
    // 1. 配置I2C总线参数
    i2c_master_bus_config_t i2c_config = {
        .clk_source = config.bus_config.clk_source,
        .i2c_port = config.bus_config.i2c_port, // 使用I2C_NUM_0
        .sda_io_num = config.bus_config.sda_io_num,
        .scl_io_num = config.bus_config.scl_io_num,
        .glitch_ignore_cnt = config.bus_config.glitch_ignore_cnt,
        .flags.enable_internal_pullup = config.bus_config.enable_internal_pullup // 启用内部上拉
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_config, &bus_handle));

    // 2. 创建设备句柄
    i2c_device_config_t dev_config = {
        .dev_addr_length = config.device_config.dev_addr_length,
        .device_address = config.device_config.dev_addr_length,
        .scl_speed_hz = config.device_config.dev_addr_length // 时钟频率100kHz
    };
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_config, &dev_handle));
}

void smart_os_iic_write(unsigned int *write_buf, unsigned int buf_size)
{
    ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, write_buf, sizeof(write_buf), -1));
}

void smart_os_iic_read(unsigned int *read_buf, unsigned int buf_size)
{
    ESP_ERROR_CHECK(i2c_master_receive(dev_handle, read_buf, sizeof(read_buf), -1));
}
