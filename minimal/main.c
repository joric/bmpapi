#include "apidef.h"
#include "bmpapi.h"

#define GPIO(port, pin) ((port << 6) | pin)
#define LED_PIN GPIO(1,10)

void bootloader_jump(void) {
  // 2 long flashes
  nrf_gpio_cfg_output(LED_PIN);
  for (int i=0; i<4; i++) { nrf_gpio_pin_write(LED_PIN, i%2==0); nrf_delay_ms(250); }
}

void logger_init(void) {
  // 4 short flashes
  nrf_gpio_cfg_output(LED_PIN);
  for (int i=0; i<8; i++) { nrf_gpio_pin_write(LED_PIN, i%2==0); nrf_delay_ms(100); }
}

int main(void) {
  BMPAPI->bootloader_jump();
  BMPAPI->logger.init();
}

