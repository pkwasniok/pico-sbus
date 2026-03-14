#include "sbus.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"

uint8_t buffer_uart0[32];
uint8_t buffer_uart1[32];
uint8_t buffer_frame0[25];
uint8_t buffer_frame1[25];
uint8_t counter0 = 0;
uint8_t counter1 = 0;

static void irq_handler(uart_inst_t *uart, uint8_t *counter, uint8_t *buffer_uart, uint8_t *buffer_frame) {
    buffer_uart[(*counter)++] = uart_getc(uart);

    if ((*counter) >= 2 && buffer_uart[(*counter) - 2] == 0x00 && buffer_uart[(*counter) - 1] == 0x0F) {
        for (int i = 0; i < 25; i++)
            buffer_frame[i] = buffer_uart[i];

        (*counter) = 0;
        buffer_uart[(*counter)++] = 0x0F;
    }
}

void irq_uart0(void) {
    irq_handler(uart0, &counter0, buffer_uart0, buffer_frame0);
}

void irq_uart1(void) {
    irq_handler(uart1, &counter1, buffer_uart1, buffer_frame1);
}

void sbus_init(sbus_inst_t *sbus, uart_inst_t *uart, uint gpio) {
    sbus->uart = uart;
    sbus->gpio = gpio;

    // Initialize GPIO
    gpio_set_function(gpio, UART_FUNCSEL_NUM(uart, gpio));
    gpio_set_inover(gpio, GPIO_OVERRIDE_INVERT);

    // Initialize IRQ
    irq_set_exclusive_handler(UART_IRQ_NUM(uart), uart == uart0 ? irq_uart0 : irq_uart1);
    irq_set_enabled(UART_IRQ_NUM(uart), true);

    // Initialize UART
    uart_init(uart, 100000);
    uart_set_format(uart, 8, 2, UART_PARITY_EVEN);
    uart_set_fifo_enabled(uart, false);
    uart_set_irqs_enabled(uart, true, false);
}

uint16_t sbus_get_channel(sbus_inst_t *sbus, uint channel) {
    uint8_t *buffer_frame = sbus->uart == uart0 ? buffer_frame0 : buffer_frame1;

    uint8_t byte_start = ((channel * 11) / 8) + 1;
    uint8_t bit_offset = (channel * 11) % 8;

    return ((buffer_frame[byte_start] | (buffer_frame[byte_start + 1] << 8) | (buffer_frame[byte_start + 2] << 16)) >> bit_offset) & 0b11111111111;
}

