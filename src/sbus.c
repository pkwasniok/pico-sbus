#include "sbus.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"

void irq_handler(void) {

}

void sbus_init(sbus_inst_t *sbus, uart_inst_t *uart, uint gpio) {
    sbus->uart = uart;
    sbus->gpio = gpio;

    // Initialize GPIO
    gpio_set_function(gpio, UART_FUNCSEL_NUM(uart, gpio));
    gpio_set_inover(gpio, GPIO_OVERRIDE_INVERT);

    // Initialize IRQ
    irq_set_exclusive_handler(UART_IRQ_NUM(uart), irq_handler);
    irq_set_enabled(UART_IRQ_NUM(uart), true);

    // Initialize UART
    uart_init(uart, 100000);
    uart_set_format(uart, 8, 2, UART_PARITY_EVEN);
    uart_set_fifo_enabled(uart, false);
    uart_set_irqs_enabled(uart, true, false);
}

void sbus_get_channel(uint channel) {

}

