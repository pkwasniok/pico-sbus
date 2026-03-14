#pragma once
#include "hardware/gpio.h"
#include "hardware/uart.h"

typedef struct {
    uart_inst_t *uart;
    uint gpio;
} sbus_inst_t;

void sbus_init(sbus_inst_t *sbus, uart_inst_t *uart, uint gpio);

void sbus_get_channel(uint channel);

