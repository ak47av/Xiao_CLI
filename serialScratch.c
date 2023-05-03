
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

void recv_and_reply(uart_inst_t* uart)
{
    volatile char* command=(char *)calloc(sizeof(char),6); // Make space for command on the heap
    if(uart_is_readable(uart)) // check if the UART FIFO has data in it
    {
        for(int i=0; i<COMMAND_LENGTH; i++){ // get up to COMMAND_LENGTH characters. Default 8
            command[i] = uart_getc(uart);
        }
    }
        
    if(uart_is_writable(uart0) && *command!='\0'){  // check if the UART write buffer is empty
        uart_puts(uart, command); // put the string on the uart
        free(command); // free the space allocated for the command
    }
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

    while(1)
    {
        recv_and_reply(uart0);
    }


}

/// \end::hello_uart[]
