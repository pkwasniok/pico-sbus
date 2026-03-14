#include <hardware/structs/io_bank0.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/uart.h"
#include "sbus.h"

#define SBUS_GPIO 17

// uint8_t counter = 0;
// uint8_t buffer[128];
// uint8_t frame[22];

uint8_t frame[22];
uint8_t buffer[32];
uint8_t counter = 0;
void handler(void) {
    buffer[counter++] = uart_getc(uart0);

    if (counter >= 1 && buffer[counter-2] == 0x00 && buffer[counter-1] == 0x0F) {
        for (int i = 0; i < 22; i++) {
            frame[i] = buffer[i];
        }

        counter = 0;
        buffer[counter++] = 0x0F;
    }
}

uint16_t get_channel(uint8_t channel) {
    uint8_t byte_start = ((channel * 11) / 8) + 1;
    uint8_t bit_offset = (channel * 11) % 8;

    return ((frame[byte_start] | (frame[byte_start + 1] << 8) | (frame[byte_start + 2] << 16)) >> bit_offset) & 0b11111111111;
}

int main(void) {
    stdio_usb_init();

    sbus_inst_t sbus;

    sbus_init(&sbus, uart0, SBUS_GPIO);

    // // Initialize GPIO
    // gpio_set_function(SBUS_GPIO, UART_FUNCSEL_NUM(uart0, SBUS_GPIO));
    // gpio_set_inover(SBUS_GPIO, GPIO_OVERRIDE_INVERT);
    //
    // gpio_set_function(25, GPIO_FUNC_PWM);
    //
    //
    //
    // // Initialize IRQs
    // irq_set_exclusive_handler(UART0_IRQ, handler);
    // irq_set_enabled(UART0_IRQ, true);
    //
    // // Initialize UART
    // uart_init(uart0, 100000);
    // uart_set_format(uart0, 8, 2, UART_PARITY_EVEN);
    // uart_set_fifo_enabled(uart0, false);
    // uart_set_irqs_enabled(uart0, true, false);


    while (1) {
        for (int i = 0; i < 16; i++) {
            printf("channel %d: %d\n", i, get_channel(i));
        }
        printf("\n");

        sleep_ms(1000);
    }
}

