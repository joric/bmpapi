#include "apidef.h"
#include "bmpapi.h"

void bootloader_jump(void) {
  nrf_gpio_cfg_output(LED_PIN);
  for (int i=0; i<4; i++) { nrf_gpio_pin_write(LED_PIN, i%2==0); nrf_delay_ms(250); }
}

void reset(uint32_t _) { }

__attribute__((section(".api_table")))
bmp_api_t API_TABLE = {
    .api_version = 0x01020304,
    .bootloader_jump = bootloader_jump,
    //.app = { reset, enter_sleep_mode, /* ... */ },
    // ...
};

int main(void) {
  bootloader_jump();
  BMPAPI->bootloader_jump(); // crash
}

