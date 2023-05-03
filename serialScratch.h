#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_ID uart0
#define BAUD_RATE 115200

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define GREEN_LED 16
#define RED_LED 17
#define BLUE_LED 25

#define COMMAND_LENGTH 9 // length of command including null character

// typedef void *(*command_handler)(const char *);
// typedef struct  {
//     char *command_string;
//     command_handler handler;
// }cli_command;

// struct cli_command cmds[] = {
//     {"toggleRd", toggle_red_led},
//     {"toggleGr", toggle_green_led},
//     {"toggleBl", toggle_blue_led},
// };

// void toggle_red_led(const char* command);
// void toggle_green_led(const char* comamnd);
// void toggle_blue_led(const char* command); 