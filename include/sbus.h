#pragma once
#include "hardware/uart.h"

typedef struct {
    uint8_t *buffer_uart;
    uint8_t *buffer_frame;
    uart_inst_t *uart;
    uint gpio;
} sbus_inst_t;

void sbus_init(sbus_inst_t *sbus, uart_inst_t *uart, uint gpio);

uint16_t sbus_get_channel(sbus_inst_t *sbus, uint channel);

