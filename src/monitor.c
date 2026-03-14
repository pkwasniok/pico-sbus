#include <stdio.h>
#include "pico/stdio_usb.h"
#include "pico/time.h"
#include "sbus.h"

#define SBUS_GPIO 17
#define SBUS_UART uart0

int main(void) {
    stdio_usb_init();

    sbus_inst_t sbus;
    sbus_init(&sbus, SBUS_UART, SBUS_GPIO);

    while (1) {
        printf("%c[0;0H", 0x1b);

        for (int i = 0; i < 16; i++) {
            printf("%2d: [", i);

            uint16_t value = sbus_get_channel(&sbus, i);

            for (int i = 0; i < value/23; i++)
                printf("=");
            for (int i = 0; i < 89 - (value/23); i++)
                printf(" ");

            printf("] (%4d/2047)\n", value);
        }
        printf("\n");

        sleep_ms(200);
    }
}

