#ifndef CUSTOM_BOARD_H
#define CUSTOM_BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#define GPIO(port, pin) ((port << 6) | pin)

//#define USE_NRFMICRO_1_1
#define USE_NRFMICRO_1_2
//#define USE_NRFMICRO_1_3

#ifdef USE_NRFMICRO_1_1
#define FLIPPED_NRFMICRO
#define USE_SWITCH_PIN
#define USE_BATTERY_PIN
#define BATTERY_R1 10
#define BATTERY_R2 13
#endif

#ifdef USE_NRFMICRO_1_2
#define USE_INTERNAL_LDO
#define USE_MCP73811_CTRL
//#define USE_MCP73831_CTRL
#define USE_BATTERY_PIN
#define BATTERY_R1 820
#define BATTERY_R2 2000
#endif

#ifdef USE_NRFMICRO_1_3
#define USE_TP4054_CTRL
#define USE_BATTERY_PIN
#define BATTERY_R1 820
#define BATTERY_R2 2000
#endif

#define PIN1 GPIO(0,6)
#define PIN2 GPIO(0,8)

#ifdef FLIPPED_NRFMICRO //flipped nRFMicro 0.03 (jumpers on the on/off switch side)

#define PIN20 GPIO(0,15)
#define PIN19 GPIO(0,17)
#define PIN18 GPIO(0,20)
#define PIN17 GPIO(0,13)
#define PIN16 GPIO(0,24)
#define PIN15 GPIO(0,9)
#define PIN14 GPIO(0,10)
#define PIN13 GPIO(1,6)

#define PIN12 GPIO(1,11)
#define PIN11 GPIO(0,28)
#define PIN10 GPIO(0,3)
#define PIN9 GPIO(1,13)
#define PIN8 GPIO(0,2)
#define PIN7 GPIO(0,29)
#define PIN6 GPIO(0,31)
#define PIN5 GPIO(0,30)

#else // regular nRFMicro 0.03 (jumpers on the USB connector side)

#define PIN5 GPIO(0,15)
#define PIN6 GPIO(0,17)
#define PIN7 GPIO(0,20)
#define PIN8 GPIO(0,13)
#define PIN9 GPIO(0,24)
#define PIN10 GPIO(0,9)
#define PIN11 GPIO(0,10)
#define PIN12 GPIO(1,6)

#define PIN13 GPIO(1,11)
#define PIN14 GPIO(0,28)
#define PIN15 GPIO(0,3)
#define PIN16 GPIO(1,13)
#define PIN17 GPIO(0,2)
#define PIN18 GPIO(0,29)
#define PIN19 GPIO(0,31)
#define PIN20 GPIO(0,30)

#endif

#define LED_PIN GPIO(1,10)
#define SWITCH_PIN GPIO(0,26)
#define POWER_PIN GPIO(1,9)

#define STAT_PIN GPIO(0,7)
#define PROG_PIN GPIO(0,5)

// i2c pins
#define CONFIG_PIN_SDA PIN5
#define CONFIG_PIN_SCL PIN6

#ifndef RGB_DI_PIN
#define RGB_DI_PIN PIN1
#endif

//#define NRF_LOG_ENABLED 0
//#define NRF_LOG_BACKEND_SERIAL_USES_UART 0
//#define NRF_LOG_BACKEND_SERIAL_UART_TX_PIN 5
//#define NRF_LOG_BACKEND_UART_TX_PIN 8
//#define DEBUG
// Low frequency clock source to be used by the SoftDevice
#ifdef S210
// #define NRF_CLOCK_LFCLKSRC      NRF_CLOCK_LFCLKSRC_XTAL_20_PPM
#else

// NRF_CLOCK_LF_SRC_RC - internal oscillator
// NRF_CLOCK_LF_SRC_XTAL - external crystal
// using E73 internal oscillator (assume there's no external crystal soldered)
#define NRF_CLOCK_LFCLKSRC      {.source        = NRF_CLOCK_LF_SRC_RC,            \
                                 .rc_ctiv       = 16,                                \
                                 .rc_temp_ctiv  = 2,                                \
                                 .xtal_accuracy = 0}

#endif


#ifdef __cplusplus
}
#endif

#endif // CUSTOM_BOARD_H
