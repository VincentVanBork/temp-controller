/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <cstdio>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/gpio.h"
#include "modules/pico-onewire/api/one_wire.h"

#define TEMP_SENSE_GPIO_PIN 14
#define EXIT_GPIO_PIN 22

int main() {
    stdio_init_all();
    sleep_ms(10000);

    if (cyw43_arch_init()) {
        printf("WiFi init failed\n");
        return -1;
    }
    One_wire one_wire(TEMP_SENSE_GPIO_PIN);
	one_wire.init();
    printf("Initiated one wire \n");

	gpio_init(EXIT_GPIO_PIN);
	gpio_set_dir(EXIT_GPIO_PIN, GPIO_IN);
	gpio_pull_up(EXIT_GPIO_PIN);
    sleep_ms(1);


    while (gpio_get(EXIT_GPIO_PIN)) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

        printf("Loop\n");
		int count = one_wire.find_and_count_devices_on_bus();
        printf("count: %i \n", count);
		rom_address_t null_address{};
		one_wire.convert_temperature(null_address, true, true);
		for (int i = 0; i < count; i++) {
			auto address = One_wire::get_address(i);
			printf("Address: %02x%02x%02x%02x%02x%02x%02x%02x\r\n", address.rom[0], address.rom[1], address.rom[2],
				   address.rom[3], address.rom[4], address.rom[5], address.rom[6], address.rom[7]);
			printf("Temperature: %3.1foC\n", one_wire.temperature(address));
		}

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(2000);
	}
    return 0;
}