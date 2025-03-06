#ifndef _I2C_WRAPPER_H_
#define _I2C_WRAPPER_H_

typedef struct sf_i2c_bus_config{
    unsigned int     sda_io_num;
    unsigned int     scl_io_num;
    unsigned int     clk_source;
    unsigned int     i2c_port;
    unsigned int     glitch_ignore_cnt;
} sf_i2c_bus_config_t;

typedef struct sf_i2c_device_config{
    unsigned int     dev_addr_length;
    unsigned int     device_address;
    unsigned int     scl_speed_hz;
} sf_i2c_device_config;

typedef struct sf_i2c_config{
    sf_i2c_bus_config_t     bus_config;
    sf_i2c_device_config    device_config;
} sf_i2c_config_t;


#endif