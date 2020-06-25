#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf.h"

bmp_error_t bmp_err;
bmp_api_config_t bmp_conf;

void bootloader_jump(void);
const char* get_bootloader_info(void) { return "bmpapi"; }

// logger
void my_logger_init(void); // implement in main.c
void my_logger_info(const char* str); // implement in main.c

void logger_init(void); // called in ble_common.c !
void logger_info(const char* str) {};

// app
int32_t app_init(bmp_api_config_t const* const conf) { bmp_conf = *conf; return 0;  } //1 - force safe mode
void app_reset(uint32_t param) {};
void enter_sleep_mode(void){};
void main_task_start(void (*main_task)(void*), uint8_t interval_ms) {};

//void process_task(void) {};
void process_task(void) { }

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
//void usb_init(bmp_api_config_t const* const config, uint32_t disable_msc) {};
//void usb_enable(void) {};
void usb_init(bmp_api_config_t const* const config, uint32_t disable_msc) { usbd_init();};
void usb_enable(void) { usbd_enable(); };
void usb_process(void) { usbd_process(); };

void usb_send_key(bmp_api_key_report_t* rep) {};
void usb_send_mouse(bmp_api_mouse_report_t* rep) {};
void usb_send_system(uint16_t param) {};
void usb_send_consumer(uint16_t param) {};

#if 0
void usb_serial_putc(char c) { };
char usb_serial_getc(void) { return 0; };
void usb_serial_puts(uint8_t const* s, uint8_t len) { };
int  usb_serial_byte_to_read(void) { return 0; };
#else
void usb_serial_putc(char c) { return cdc_acm_putc(c); };
char usb_serial_getc(void) { return cdc_acm_getc(); };
void usb_serial_puts(uint8_t const* s, uint8_t len) {  while (*s) cdc_acm_putc(*s++); };
int  usb_serial_byte_to_read(void) { return cdc_acm_byte_to_read(); };
#endif


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

__attribute__((section(".api_table")))
bmp_api_t API_TABLE = {
  9,
  bootloader_jump,
  get_bootloader_info,
  {
    app_init,
    app_reset,
    enter_sleep_mode,
    main_task_start,
    process_task,
    push_keystate_change,
    pop_keystate_change,
    bmp_keymap_key_to_keycode,
    set_keycode_to_keymap,
    set_keymap,
    set_layout_code,
    set_config,
    get_keymap_info,
    get_config,
    save_file,
    delete_file,
    get_file,
    get_vcc_mv,
    get_vcc_percent,
    set_state_change_cb
  },
  {
    usb_init,
    usb_enable,
    usb_process,
    usb_send_key,
    usb_send_mouse,
    usb_send_system,
    usb_send_consumer,
    usb_serial_putc,
    usb_serial_getc,
    usb_serial_puts,
    usb_serial_byte_to_read,
    usb_set_raw_receive_cb,
    usb_raw_send,
    usb_create_file,
    usb_set_msc_write_cb
  },
  {
    ble_init,
    ble_advertise,
    ble_scan,
    ble_get_bonding_info,
    ble_delete_bond,
    ble_send_key,
    ble_send_mouse,
    ble_send_system,
    ble_send_consumer,
    bmpapi_ble_nus_send_bytes,
    ble_set_nus_rcv_cb,
    ble_set_nus_disconnect_cb
  },
  {
    gpio_set_mode,
    gpio_read_pin,
    gpio_set_pin,
    gpio_clear_pin
  },
  {
    i2cm_init,
    i2cm_uninit,
    i2cm_transmit,
    i2cm_receive,
    i2cm_write_reg,
    i2cm_read_reg
  },
  {
    bmp_i2cs_init,
    i2cs_uninit,
    i2cs_prepare,
    i2cs_receive
  },
  {
    spim_init,
    spim_cs_init,
    spim_start
  },
  {
    setleds_pin
  },
  {
    my_logger_init,
    my_logger_info
  },
  {
    webc_enter,
    webc_set_rcv_callback,
    webc_set_send_buffer,
    webc_set_disconnect_callback
  },
  {
    encoder_init,
    encoder_get_count
  },
  {
    adc_config_vcc_channel,
    adc_config_channel,
    adc_sample_and_convert
  }
};
