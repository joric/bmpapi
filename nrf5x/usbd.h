#ifndef TMK_CORE_PROTOCOL_NRF_NRF52_USBD_H_
#define TMK_CORE_PROTOCOL_NRF_NRF52_USBD_H_

#include "apidef.h"

#define report_keyboard_t bmp_api_key_report_t
#define report_mouse_t bmp_api_mouse_report_t

int usbd_init(void);
int usbd_enable(void);
void usbd_process(void);
int usbd_send_keyboard(report_keyboard_t *report);
int usbd_send_mouse(report_mouse_t *report);
int usbd_send_system(uint16_t data);
int usbd_send_consumer(uint16_t data);
int usbd_send_abs_mouse(int8_t x, int8_t y);
void usbd_send_cdc_acm(uint8_t *dat, uint8_t cnt);

// Functions for CLI
int cdc_acm_byte_to_read();
void cdc_acm_putc(char c);
char cdc_acm_getc();

#endif /* TMK_CORE_PROTOCOL_NRF_NRF52_USBD_H_ */
