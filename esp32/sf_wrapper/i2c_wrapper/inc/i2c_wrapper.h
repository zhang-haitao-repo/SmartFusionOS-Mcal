#ifndef _I2C_WRAPPER_H_
#define _I2C_WRAPPER_H_

#include "driver/i2c.h"
#include "esp_log.h"
#include "esp_intr_alloc.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_TAG "I2C_DRIVER"
#define MAX_DEVICES 128

/**
 * @brief I2C寄存器地址宽度类型
 */
typedef enum {
    I2C_REG_ADDR_8BIT = 1,   ///< 8位寄存器地址
    I2C_REG_ADDR_16BIT = 2    ///< 16位寄存器地址
} i2c_reg_addr_width_t;

/**
 * @brief 异步传输上下文结构体
 */
typedef struct {
    i2c_cmd_handle_t cmd;     ///< I2C命令句柄
    SemaphoreHandle_t sem;    ///< FreeRTOS信号量
    bool is_success;          ///< 传输状态标志
} i2c_async_context_t;

// DMA内存对齐配置
#if CONFIG_IDF_TARGET_ESP32
#define I2C_DMA_ALIGNMENT 4
#else
#define I2C_DMA_ALIGNMENT 8
#endif

/**
 * @brief 增强版I2C初始化（支持DMA和中断）
 * @param i2c_port I2C端口号 (I2C_NUM_0/I2C_NUM_1)
 * @param sda_pin SDA GPIO编号
 * @param scl_pin SCL GPIO编号
 * @param clk_speed 时钟频率 (Hz)
 * @param dma_buf_size DMA缓冲区大小 (0表示禁用DMA)
 * @param intr_flags 中断标志位
 * @return true 初始化成功, false 初始化失败
 */
bool i2c_init_enhanced(i2c_port_t i2c_port,
                       gpio_num_t sda_pin,
                       gpio_num_t scl_pin,
                       uint32_t clk_speed,
                       size_t dma_buf_size,
                       int intr_flags);

/**
 * @brief 增强寄存器写操作
 * @param i2c_port I2C端口号
 * @param dev_addr 设备地址 (7-bit)
 * @param reg_addr 寄存器地址
 * @param reg_width 寄存器地址宽度
 * @param data 待写入数据缓冲区
 * @param len 数据长度
 * @param timeout_ms 超时时间 (ms)
 * @param flags 控制标志 (I2C_ACK_CHECK_EN等)
 */
bool i2c_write_reg_ex(i2c_port_t i2c_port,
                     uint8_t dev_addr,
                     uint16_t reg_addr,
                     i2c_reg_addr_width_t reg_width,
                     const uint8_t *data,
                     size_t len,
                     uint32_t timeout_ms,
                     int flags);

/**
 * @brief 增强寄存器读操作
 * @param i2c_port I2C端口号
 * @param dev_addr 设备地址 (7-bit)
 * @param reg_addr 寄存器地址
 * @param reg_width 寄存器地址宽度
 * @param data 数据接收缓冲区
 * @param len 要读取的数据长度
 * @param timeout_ms 超时时间 (ms)
 * @param flags 控制标志 (I2C_ACK_CHECK_EN等)
 */
bool i2c_read_reg_ex(i2c_port_t i2c_port,
                    uint8_t dev_addr,
                    uint16_t reg_addr,
                    i2c_reg_addr_width_t reg_width,
                    uint8_t *data,
                    size_t len,
                    uint32_t timeout_ms,
                    int flags);

/**
 * @brief 连续分页写操作
 * @param i2c_port I2C端口号
 * @param dev_addr 设备地址
 * @param data 待写入数据缓冲区
 * @param total_len 总数据长度
 * @param page_size 设备页大小 (0表示禁用分页)
 * @param timeout_ms 超时时间 (ms)
 */
bool i2c_sequential_write(i2c_port_t i2c_port,
                         uint8_t dev_addr,
                         const uint8_t *data,
                         size_t total_len,
                         size_t page_size,
                         uint32_t timeout_ms);

/**
 * @brief I2C总线扫描
 * @param i2c_port I2C端口号
 * @param found_addrs 发现设备地址的输出缓冲区
 * @param max_devices 最大可存储设备数量
 * @return 实际发现的设备数量
 */
uint8_t i2c_scan_bus(i2c_port_t i2c_port,
                    uint8_t *found_addrs,
                    uint8_t max_devices);

/**
 * @brief 异步DMA传输
 * @param i2c_port I2C端口号
 * @param cmd 预构建的I2C命令句柄
 * @param timeout_ms 超时时间 (ms)
 */
bool i2c_async_dma_transfer(i2c_port_t i2c_port,
                           i2c_cmd_handle_t cmd,
                           uint32_t timeout_ms);

#ifdef __cplusplus
}
#endif

#endif