#include "apidef.h"
#include "bmpapi.h"

#define GPIO(port, pin) ((port << 6) | pin)
#define LED_PIN GPIO(1,10)

void bootloader_jump(void) {
  nrf_gpio_cfg_output(LED_PIN);
  for (int i=0; i<4; i++) { nrf_gpio_pin_write(LED_PIN, i%2==0); nrf_delay_ms(250); }
}

void logger_init(void) {
  nrf_gpio_cfg_output(LED_PIN);
  for (int i=0; i<8; i++) { nrf_gpio_pin_write(LED_PIN, i%2==0); nrf_delay_ms(250); }
}

int main(void) {

  // set LDO to 3.3V (nRFMicro 1.2)
  if (NRF_UICR->REGOUT0 != UICR_REGOUT0_VOUT_3V3) {
    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
    NRF_UICR->REGOUT0 = UICR_REGOUT0_VOUT_3V3;
    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
  }

  BMPAPI->bootloader_jump();
}

