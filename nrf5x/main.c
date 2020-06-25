#include "apidef.h"

//#include "custom_board.h"
#include "ws2812.h"
#include "usbd.h"
#include "ble_common.h"
#include "i2c.h"

#include "bmpapi.h"

#define GPIO(port, pin) ((port << 6) | pin)
#define LED_PIN GPIO(1,10)

// adafruit bootloader, 500 ms double reset
#define DFU_MAGIC_UF2_RESET             0x57
#define DFU_DBL_RESET_MEM               0x20007F7C
#define DFU_DBL_RESET_MAGIC             0x5A1AD5      // SALADS
void bootloader_jump(void) {
  sd_power_gpregret_set(0, DFU_MAGIC_UF2_RESET);
  uint32_t* dbl_reset_mem = ((uint32_t*)  DFU_DBL_RESET_MEM );
  *dbl_reset_mem = DFU_DBL_RESET_MAGIC;
  NVIC_SystemReset();
}

void blink(int times, int delay) {
  nrf_gpio_cfg_output(LED_PIN);
  for (int i=0; i<times*2; i++) { nrf_gpio_pin_write(LED_PIN, i%2==0); nrf_delay_ms(delay); }
}

void my_logger_info(const char* str) {
  blink(1,50); // short logger blink
  //while (*str++) blink(1,25); // blink as much as many characters
}

void my_logger_init(void) {
  blink(2,200); // two blinks at start
  // call real logger init
  logger_init();
}


bmp_api_config_t bmp_conf;

int main(void) {

  // set LDO to 3.3V (nRFMicro 1.2)
  if (NRF_UICR->REGOUT0 != UICR_REGOUT0_VOUT_3V3) {
    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
    NRF_UICR->REGOUT0 = UICR_REGOUT0_VOUT_3V3;
    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
  }

  BMPAPI->logger.init();
  BMPAPI->logger.info("logger init");
  BMPAPI->usb.init(&bmp_conf, 0);
  BMPAPI->usb.enable();

  for (;;) {
    BMPAPI->app.process_task();
    BMPAPI->usb.process();
  }
}


