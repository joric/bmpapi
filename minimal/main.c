#include "apidef.h"

#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf.h"

#define GPIO(port, pin) ((port << 6) | pin)
#define LED_PIN GPIO(1,10)

bmp_error_t bmp_err;

// logger
void logger_init(void) {}
void logger_info(const char* str) { }

//#define LOCATE_FUNC  __attribute__((__section__(".mysection")))

void bootloader_jump(void) {
  nrf_gpio_cfg_output(LED_PIN);

  // blink twice on start
  for (int i=0; i<4; i++) { nrf_gpio_pin_write(LED_PIN, i%2==0); nrf_delay_ms(250);}
}


bmp_api_t bmpapi_static = {
	.api_version = 0,
	.bootloader_jump = bootloader_jump
};

const char* get_bootloader_info(void) { return "bmpapi"; }

// app
int32_t app_init(bmp_api_config_t const* const conf) { return 0; }
void app_reset(uint32_t param) {};
void enter_sleep_mode(void){};
void main_task_start(void (*main_task)(void*), uint8_t interval_ms) {};
void process_task(void) {};

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
void usb_init(bmp_api_config_t const* const config, uint32_t disable_msc) {};
void usb_enable(void) {};
void usb_process(void) {};
void usb_send_key(bmp_api_key_report_t* rep) {};
void usb_send_mouse(bmp_api_mouse_report_t* rep) {};
void usb_send_system(uint16_t param) {};
void usb_send_consumer(uint16_t param) {};

void usb_serial_putc(char c) { };
char usb_serial_getc(void) { return 0; };
void usb_serial_puts(uint8_t const* s, uint8_t len) { };
int  usb_serial_byte_to_read(void) { return 0; };


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

// gpio
bmp_error_t gpio_set_mode(uint8_t pin_num, bmp_api_gpio_mode_t const* const mode) { return bmp_err; }
uint32_t    gpio_read_pin(uint8_t pin_num) { return 0; }
bmp_error_t gpio_set_pin(uint8_t pin_num) { return bmp_err; }
bmp_error_t gpio_clear_pin(uint8_t pin_num) { return bmp_err; }

// encoder
bmp_error_t encoder_init(uint32_t encoder_scan_ms, const uint8_t* pin_a, const uint8_t* pin_b, uint8_t num_of_enc) { return bmp_err; }
int32_t encoder_get_count(uint8_t idx) { return 0; }

int i2cm_init(bmp_api_i2cm_config_t const* const conf) { return 0; };
void i2cm_uninit(void) { }
uint8_t i2cm_transmit(uint8_t address, uint8_t* data, uint16_t length) { return 0; }
uint8_t i2cm_receive(uint8_t address, uint8_t* data, uint16_t length) { return 0; }
uint8_t i2cm_write_reg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout) { return 0; }
uint8_t i2cm_read_reg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout) { return 0; }

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
void setleds_pin(bmp_api_led_t* ledarray, uint16_t number_of_leds, uint8_t pinmask) {};

// adc
int adc_config_vcc_channel(uint8_t ain, uint16_t vmax_mv, uint16_t vmin_mv) { return 0; }
int adc_config_channel(uint8_t channel, uint8_t pin) { return 0; }
int adc_sample_and_convert(uint8_t channel, int16_t* const result) { return 0; }

// webconfig
void webc_enter(void){}
bmp_error_t webc_set_rcv_callback(bmp_error_t (*callback)(const uint8_t* dat, uint32_t len)){ return bmp_err; }
bmp_error_t webc_set_send_buffer(uint8_t* buf, uint16_t len) { return bmp_err; }
bmp_error_t webc_set_disconnect_callback(bmp_error_t (*callback)(void)) { return bmp_err; }

int main(void) {

  nrf_gpio_cfg_output(LED_PIN);

  // blink twice on start
  for (int i=0; i<4; i++) { nrf_gpio_pin_write(LED_PIN, i%2==0); nrf_delay_ms(250);}

  bootloader_jump();

/*
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
*/
}

