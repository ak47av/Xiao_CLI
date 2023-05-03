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

#define COMMAND_LENGTH 8 // length of command including null character

#define TOTAL_NO_COMMANDS 3

typedef struct  {
    char *command_string;
    void (*handler)();
}cli_command;

void toggle_red_led();
void toggle_green_led();
void toggle_blue_led(); 

cli_command cmds[] = {
    {"toggleRd", toggle_red_led},
    {"toggleGr", toggle_green_led},
    {"toggleBl", toggle_blue_led},
};

void recv_and_reply(uart_inst_t* uart);