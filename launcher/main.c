#include "apidef.h"

#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf.h"

#define GPIO(port, pin) ((port << 6) | pin)
#define LED_PIN GPIO(1,10)

int main(void) {

  // set LDO to 3.3V (nRFMicro 1.2)
  if (NRF_UICR->REGOUT0 != UICR_REGOUT0_VOUT_3V3) {
    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
    NRF_UICR->REGOUT0 = UICR_REGOUT0_VOUT_3V3;
    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
  }

  // 1 flash to indicate launcher started
  nrf_gpio_cfg_output(LED_PIN);
  for (int i=0; i<2; i++) { nrf_gpio_pin_write(LED_PIN, i%2==0); nrf_delay_ms(250); }

  BMPAPI->bootloader_jump(); // crash!

  nrf_delay_ms(500);

  // 1 flash to indicate launcher finished
  nrf_gpio_cfg_output(LED_PIN);
  for (int i=0; i<2; i++) { nrf_gpio_pin_write(LED_PIN, i%2==0); nrf_delay_ms(250); }

}

