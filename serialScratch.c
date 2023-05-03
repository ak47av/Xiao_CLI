
/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "serialScratch.h"

// void toggle_red_led(const char * command){
    
// }

// void listen_for_command(uart_inst_t* uart)
// {
//     volatile 
//     volatile cli_command* command =(char *)calloc(sizeof(cli_command)); // Make space for command on the heap
//     if(uart_is_readable(uart)) // check if the UART FIFO has data in it
//     {
//         for(int i=0; i<COMMAND_LENGTH; i++){ // get up to COMMAND_LENGTH characters. Default 8
//             command->command_string[i] = uart_getc(uart);
//         }
//     }
//     command->handler(command_string);
//     free(command);
// }

int compare(const char *X, const char *Y)
{
    while (*X)
    {
        // if characters differ, or end of the second string is reached
        if (*X != *Y) {
            break;
        }
 
        // move to the next pair of characters
        X++;
        Y++;
    }
 
    // return the ASCII difference after converting `char*` to `unsigned char*`
    return *(const unsigned char*)X - *(const unsigned char*)Y;
}

void toggle_green_led() {
    uint32_t mask = 0x10000;
    gpio_xor_mask(mask);

}
void toggle_red_led() {
    uint32_t mask = 0x20000;
    gpio_xor_mask(mask);
}

void toggle_blue_led(){
    uint32_t mask = 0x2000000;
    gpio_xor_mask(mask);
}

void recv_and_reply(uart_inst_t* uart)
{
    volatile int str_cmp_res;
    volatile char* command=(char *)calloc(COMMAND_LENGTH,sizeof(char)); // Make space for command on the heap
    if(uart_is_readable(uart)) // check if the UART FIFO has data in it
    {
        int i=0;
        char res;
        for(i=0; i<COMMAND_LENGTH; i++){ // get up to COMMAND_LENGTH characters. Default 8
            command[i] = uart_getc(uart);
        }
        for(i=0; i<TOTAL_NO_COMMANDS; i++)
        {
            str_cmp_res = strcmp(command, cmds[i].command_string);
            if(uart_is_writable(uart0) && str_cmp_res==0)
            {
                cmds[i].handler();
                uart_puts(uart, command);
                break;
            }
        }
        if(uart_is_writable(uart) && str_cmp_res!=0) uart_puts(uart, command); 
    }   
    free(command);
}

int main() {
    // Set up our UART with the required speed.
    uart_init(UART_ID, BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    gpio_set_function(GREEN_LED, GPIO_FUNC_SIO);
    gpio_set_function(RED_LED, GPIO_FUNC_SIO);
    gpio_set_function(BLUE_LED, GPIO_FUNC_SIO);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
    gpio_set_dir(RED_LED, GPIO_OUT);
    gpio_set_dir(BLUE_LED, GPIO_OUT);

    char dummy = uart_getc(uart0);
    while(1)
    {
        recv_and_reply(uart0);
    }
}

/// \end::hello_uart[]
