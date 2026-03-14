#pragma once
#include "hardware/uart.h"

/** Descriptor of SBUS instance.
 */
typedef struct {
    uint8_t *buffer_uart;
    uint8_t *buffer_frame;
    uart_inst_t *uart;
    uint gpio;
} sbus_inst_t;

/** Initialize SBUS on specified UART and GPIO.
 *
 * @param[out] sbus Pointer to SBUS instance descriptor.
 * @param[in] uart UART instance to be used as SBUS.
 * @param[in] gpio GPIO number to be used as SBUS.
 */
void sbus_init(sbus_inst_t *sbus, uart_inst_t *uart, uint gpio);

/** Get value of SBUS channel.
 *
 * @param[in] sbus Pointer to SBUS instance descriptor.
 * @param[in] channel SBUS channel number.
 */
uint16_t sbus_get_channel(sbus_inst_t *sbus, uint channel);

/** Check if SBUS failsafe is active.
 *
 * @param[in] sbus Pointer to SBUS instance descriptor.
 */
bool sbus_is_failsafe(sbus_inst_t *sbus);

