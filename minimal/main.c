#include "apidef.h"
#include "bmpapi.h"

#define LOCATE_FUNC  __attribute__((__section__(".mysection")))

void LOCATE_FUNC bootloader_jump(void) {
  nrf_gpio_cfg_output(LED_PIN);
  for (int i=0; i<4; i++) { nrf_gpio_pin_write(LED_PIN, i%2==0); nrf_delay_ms(250); }
}

/*
bmp_api_t bmpapi_static = {
  .api_version = 0,
  .bootloader_jump = bootloader_jump
};
*/

int main(void) {
  bootloader_jump();
  ((void(*)(void))0xFDE00)();
}

