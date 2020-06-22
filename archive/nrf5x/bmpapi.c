/*
  open source bmpapi implementation by joric
  readme https://github.com/joric/qmk_bmpapi
*/

#include "apidef.h"

#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_power.h"
#include "nrfx_power.h"
#include "nrfx_pwm.h"
#include "nrf.h"
#include "app_ble_func.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#include "custom_board.h"

#include "ws2812.h"

#include "usbd.h"
#include "ble_common.h"
#include "i2c.h"
#include "oled_driver.h"

bmp_error_t bmp_err;

// logger
//void logger_init(void) {}
void logger_init(void); // defined in ble_common.c
void logger_info(const char* str) { NRF_LOG_INFO(str); }


// adafruit bootloader, 500 ms double reset
#define DFU_MAGIC_UF2_RESET             0x57
#define DFU_DBL_RESET_MEM               0x20007F7C
#define DFU_DBL_RESET_MAGIC             0x5A1AD5      // SALADS
void bmp_bootloader_jump(void) {
  sd_power_gpregret_set(0, DFU_MAGIC_UF2_RESET);
  uint32_t* dbl_reset_mem = ((uint32_t*)  DFU_DBL_RESET_MEM );
  *dbl_reset_mem = DFU_DBL_RESET_MAGIC;

  NVIC_SystemReset();
}

const char* get_bootloader_info(void) { return "bmpapi"; }

// app
int32_t app_init(bmp_api_config_t const* const conf) { return 0; }
void app_reset(uint32_t param) {};
void enter_sleep_mode(void){};
void main_task_start(void (*main_task)(void*), uint8_t interval_ms) {};


/*
static void render_logo(void) {
    static const char qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
                                            0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
                                            0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};

    oled_write_P(qmk_logo, false);
}
void oled_task_user(void) { render_logo(); }
*/

int counter=0;
void process_task(void) {
  usbd_process(); 

  //NRF_LOG_INFO("I");
  //NRF_LOG_DEBUG("D");

/*
  if (counter==100000) {
    logger_info("all ok");
    counter = 0;

render_logo();

  }
  counter++;
*/

};


bmp_error_t push_keystate_change(bmp_api_key_event_t const* const key) { return 0; }
uint32_t pop_keystate_change(bmp_api_key_event_t* key, uint32_t len, uint8_t burst_threshold) { return 0; };
uint16_t bmp_keymap_key_to_keycode(uint8_t layer, bmp_api_keypos_t const* const key) { return 0; }
bmp_error_t set_keycode_to_keymap(uint8_t layer, bmp_api_keypos_t const* const key, uint16_t keycode) { return 0; }
bmp_error_t set_keymap(const uint16_t* keymap, uint16_t len, const char* layout_name)  { return bmp_err; }
void set_layout_code(const uint8_t* layout_code){};
bmp_error_t set_config(bmp_api_config_t const* const conf) { return bmp_err; }
bmp_error_t get_keymap_info(bmp_api_keymap_info_t* const keymap_info) { return bmp_err; }
const bmp_api_config_t* get_config(void) { return 0; }
bmp_error_t save_file(uint8_t file_id) { return bmp_err; }
bmp_error_t delete_file(uint8_t file_id) { return bmp_err; }
bmp_error_t get_file(uint8_t file_id, uint8_t** buf, uint32_t* const len) { return bmp_err; }
uint16_t get_vcc_mv(void) { return 4200; };
uint16_t get_vcc_percent(void) { return 100; };
bmp_error_t set_state_change_cb(bmp_api_state_change_cb_t state) { return bmp_err; };

// usb
void usb_init(bmp_api_config_t const* const config, uint32_t disable_msc) { usbd_init();};
void usb_enable(void) { usbd_enable(); };
void usb_process(void) {};
void usb_send_key(bmp_api_key_report_t* rep) {};
void usb_send_mouse(bmp_api_mouse_report_t* rep) {};
void usb_send_system(uint16_t param) {};
void usb_send_consumer(uint16_t param) {};


void usb_serial_putc(char c) { return cdc_acm_putc(c); };
char usb_serial_getc(void) { return cdc_acm_getc(); };
void usb_serial_puts(uint8_t const* s, uint8_t len) {  while (*s) cdc_acm_putc(*s++); };
int  usb_serial_byte_to_read(void) { return cdc_acm_byte_to_read(); };


void usb_set_raw_receive_cb(void (*raw_receive_cb)(const uint8_t *data, uint8_t length)) {};
int  usb_raw_send(const uint8_t *data, uint8_t length) { return 0; };
bmp_error_t usb_create_file(const char* sfn, const uint8_t* dat, uint32_t size) { return bmp_err; };
bmp_error_t usb_set_msc_write_cb(bmp_api_msc_write_cb_t cb) { return bmp_err; };

// ble
void ble_init(bmp_api_config_t const* const conf) {};
void ble_advertise(uint8_t param) {};
void ble_scan(void) {};
bmp_error_t ble_get_bonding_info(bmp_api_bonding_info_t* info, uint32_t* len) { return bmp_err; };
void ble_delete_bond(uint8_t param) {}
void ble_send_key(bmp_api_key_report_t* rep) {}
void ble_send_mouse(bmp_api_mouse_report_t* rep) {}
void ble_send_system(uint16_t param) {}
void ble_send_consumer(uint16_t param) {}
bmp_error_t bmpapi_ble_nus_send_bytes(uint8_t* buf, uint16_t len) { return bmp_err; };
bmp_error_t ble_set_nus_rcv_cb(bmp_error_t (*callback)(const uint8_t* dat, uint32_t len)) { return bmp_err; };
bmp_error_t ble_set_nus_disconnect_cb(bmp_error_t (*callback)(void)) { return bmp_err; };

/*
int bmp_pins = { 0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7, PIN8, PIN9, PIN10, PIN11,
  PIN12, PIN13, PIN14, PIN15, PIN16, PIN17, PIN18, PIN19, PIN20, PIN21
};
*/

// gpio
bmp_error_t gpio_set_mode(uint8_t pin_num, bmp_api_gpio_mode_t const* const mode) { return bmp_err; }
uint32_t    gpio_read_pin(uint8_t pin_num) { return 0; }
bmp_error_t gpio_set_pin(uint8_t pin_num) { return bmp_err; }
bmp_error_t gpio_clear_pin(uint8_t pin_num) { return bmp_err; }

// encoder
bmp_error_t encoder_init(uint32_t encoder_scan_ms, const uint8_t* pin_a, const uint8_t* pin_b, uint8_t num_of_enc) { return bmp_err; }
int32_t encoder_get_count(uint8_t idx) { return 0; }

// i2c_master
// conflicts with serial port for some reason
#if 0
int i2cm_init(bmp_api_i2cm_config_t const* const conf) { return i2c_init(); };
void i2cm_uninit(void) { i2c_uninit(); }
uint8_t i2cm_transmit(uint8_t address, uint8_t* data, uint16_t length) { return i2c_transmit(address, data, length); }
uint8_t i2cm_receive(uint8_t address, uint8_t* data, uint16_t length) { return i2c_receive(address, data, length); }
uint8_t i2cm_write_reg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout) { return i2c_writeReg(devaddr, regaddr, data, length, timeout); }
uint8_t i2cm_read_reg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout) { return i2c_readReg(devaddr, regaddr, data, length, timeout); }
#else
int i2cm_init(bmp_api_i2cm_config_t const* const conf) { return 0; };
void i2cm_uninit(void) { }
uint8_t i2cm_transmit(uint8_t address, uint8_t* data, uint16_t length) { return 0; }
uint8_t i2cm_receive(uint8_t address, uint8_t* data, uint16_t length) { return 0; }
uint8_t i2cm_write_reg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout) { return 0; }
uint8_t i2cm_read_reg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout) { return 0; }
#endif

// i2c_slave
int bmp_i2cs_init(bmp_api_i2cs_config_t const* const param) { return 0; }
void i2cs_uninit(void) {}
void i2cs_prepare(uint8_t* const dat, uint8_t len) {}
void i2cs_receive(uint8_t* const dat, uint8_t len) {}

// spi_master
int spim_init(bmp_api_spim_config_t const* const param) { return 0; }
int spim_cs_init(uint8_t cs_pin) { return 0; }
int spim_start(uint8_t* p_tx_buffer, size_t tx_length, uint8_t* p_rx_buffer, size_t rx_length, uint8_t cs_pin) { return 0; }

// ws2812
bool ws2812_enabled = true;
void setleds_pin(bmp_api_led_t* ledarray, uint16_t number_of_leds, uint8_t pinmask) {
  if (ws2812_enabled)
    ws2812_setleds_pin(ledarray, number_of_leds, RGB_DI_PIN);
};

// adc
int adc_config_vcc_channel(uint8_t ain, uint16_t vmax_mv, uint16_t vmin_mv) { return 0; }
int adc_config_channel(uint8_t channel, uint8_t pin) { return 0; }
int adc_sample_and_convert(uint8_t channel, int16_t* const result) { return 0; }

// webconfig
void webc_enter(void){}
bmp_error_t webc_set_rcv_callback(bmp_error_t (*callback)(const uint8_t* dat, uint32_t len)){ return bmp_err; }
bmp_error_t webc_set_send_buffer(uint8_t* buf, uint16_t len) { return bmp_err; }
bmp_error_t webc_set_disconnect_callback(bmp_error_t (*callback)(void)) { return bmp_err; }

void bmpapi_init(void) {

  nrf_gpio_cfg_output(LED_PIN);

  // blink twice on start
  for (int i=0; i<4; i++) nrf_gpio_pin_write(LED_PIN, i%2==0), nrf_delay_ms(100);

  BMPAPI = &BMPAPI_static;
  BMPAPI->api_version = API_VERSION;
  BMPAPI->bootloader_jump = bmp_bootloader_jump;

  // app
  BMPAPI->app.init = app_init;
  BMPAPI->app.reset = app_reset;
  BMPAPI->app.enter_sleep_mode = enter_sleep_mode;
  BMPAPI->app.main_task_start = main_task_start;
  BMPAPI->app.process_task = process_task;
  BMPAPI->app.push_keystate_change = push_keystate_change;
  BMPAPI->app.pop_keystate_change = pop_keystate_change;
  BMPAPI->app.keymap_key_to_keycode = bmp_keymap_key_to_keycode;
  BMPAPI->app.set_keycode_to_keymap = set_keycode_to_keymap;
  BMPAPI->app.set_keymap = set_keymap;
  BMPAPI->app.set_layout_code = set_layout_code;
  BMPAPI->app.set_config = set_config;
  BMPAPI->app.get_keymap_info = get_keymap_info;
  BMPAPI->app.get_config = get_config;
  BMPAPI->app.save_file = save_file;
  BMPAPI->app.delete_file = delete_file;
  BMPAPI->app.get_file = get_file;
  BMPAPI->app.get_vcc_mv = get_vcc_mv;
  BMPAPI->app.get_vcc_percent = get_vcc_percent;
  BMPAPI->app.set_state_change_cb = set_state_change_cb;

  // usb
  BMPAPI->usb.init = usb_init;
  BMPAPI->usb.enable = usb_enable;
  BMPAPI->usb.process = usb_process;
  BMPAPI->usb.send_key = usb_send_key;
  BMPAPI->usb.send_mouse = usb_send_mouse;
  BMPAPI->usb.send_system = usb_send_system;
  BMPAPI->usb.send_consumer = usb_send_consumer;
  BMPAPI->usb.serial_putc = usb_serial_putc;
  BMPAPI->usb.serial_getc = usb_serial_getc;
  BMPAPI->usb.serial_puts = usb_serial_puts;
  BMPAPI->usb.serial_byte_to_read = usb_serial_byte_to_read;
  BMPAPI->usb.set_raw_receive_cb = usb_set_raw_receive_cb;
  BMPAPI->usb.raw_send = usb_raw_send;
  BMPAPI->usb.create_file = usb_create_file;
  BMPAPI->usb.set_msc_write_cb = usb_set_msc_write_cb;

  // ble
  BMPAPI->ble.init = ble_init;
  BMPAPI->ble.advertise = ble_advertise;
  BMPAPI->ble.scan = ble_scan;
  BMPAPI->ble.get_bonding_info = ble_get_bonding_info;
  BMPAPI->ble.delete_bond = ble_delete_bond;
  BMPAPI->ble.send_key = ble_send_key;
  BMPAPI->ble.send_mouse = ble_send_mouse;
  BMPAPI->ble.send_system = ble_send_system;
  BMPAPI->ble.send_consumer = ble_send_consumer;
  BMPAPI->ble.nus_send_bytes = bmpapi_ble_nus_send_bytes;
  BMPAPI->ble.set_nus_rcv_cb = ble_set_nus_rcv_cb;
  BMPAPI->ble.set_nus_disconnect_cb = ble_set_nus_disconnect_cb;

  BMPAPI->gpio.set_mode  = gpio_set_mode;
  BMPAPI->gpio.read_pin  = gpio_read_pin;
  BMPAPI->gpio.set_pin   = gpio_set_pin;
  BMPAPI->gpio.clear_pin = gpio_clear_pin;

  BMPAPI->i2cm.init      = i2cm_init;
  BMPAPI->i2cm.uninit    = i2cm_uninit;
  BMPAPI->i2cm.transmit  = i2cm_transmit;
  BMPAPI->i2cm.receive   = i2cm_receive;
  BMPAPI->i2cm.write_reg = i2cm_write_reg;
  BMPAPI->i2cm.read_reg  = i2cm_read_reg;

  BMPAPI->i2cs.init      = bmp_i2cs_init;
  BMPAPI->i2cs.uninit    = i2cs_uninit;
  BMPAPI->i2cs.prepare   = i2cs_prepare;
  BMPAPI->i2cs.receive   = i2cs_receive;

  BMPAPI->spim.init      = spim_init;
  BMPAPI->spim.cs_init   = spim_cs_init;
  BMPAPI->spim.start     = spim_start;

  BMPAPI->ws2812.setleds_pin = setleds_pin;

  BMPAPI->logger.init = logger_init;
  BMPAPI->logger.info = logger_info;

  BMPAPI->web_config.enter                   = webc_enter;
  BMPAPI->web_config.set_rcv_callback        = webc_set_rcv_callback;
  BMPAPI->web_config.set_send_buffer         = webc_set_send_buffer;
  BMPAPI->web_config.set_disconnect_callback = webc_set_disconnect_callback;

  BMPAPI->encoder.init = encoder_init;
  BMPAPI->encoder.get_count = encoder_get_count;

  BMPAPI->adc.config_vcc_channel = adc_config_vcc_channel;
  BMPAPI->adc.config_channel     = adc_config_channel;
  BMPAPI->adc.sample_and_convert = adc_sample_and_convert;

  // blink RGB leds twice
  const int led_num=6;
  bmp_api_led_t leds[led_num];

  for (int k=0; k<4; k++) {

    for (int i=0; i<led_num; i++) { 
      leds[i].b = k%2==0 ? 255 : 0;
      leds[i].r = leds[i].g = 0;
    }

    BMPAPI->ws2812.setleds_pin(leds, led_num, RGB_DI_PIN);
    nrf_delay_ms(150);
  }

  nrf_gpio_pin_write(RGB_DI_PIN, 0);
  ws2812_enabled = false;

  // blink twice on finish
  for (int i=0; i<4; i++) nrf_gpio_pin_write(LED_PIN, i%2==0), nrf_delay_ms(100);
}

