#include "apidef.h"
#include "bmpapi.h"

#define GPIO(port, pin) ((port << 6) | pin)
#define LED_PIN GPIO(1,10)

void blink(int times, int delay) {
  nrf_gpio_cfg_output(LED_PIN);
  for (int i=0; i<times*2; i++) { nrf_gpio_pin_write(LED_PIN, i%2==0); nrf_delay_ms(delay); }
}

void bootloader_jump(void) {
  blink(2,200);
}

void logger_init(void) {
  blink(2,100);
}

int main(void) {
  BMPAPI->bootloader_jump();
  BMPAPI->logger.init();
}

