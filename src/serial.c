#include <stdio.h>
#include <stdint.h>
#include "rprintf.h"

// Memory-mapped I/O macros
#define SERIAL_PORT_ADDR 0x7D001000
#define MMIO_WRITE(reg, data) (*(volatile uint32_t *)(uintptr_t)(reg) = (data))
#define MMIO_READ(reg) (*(volatile uint32_t *)(uintptr_t)(reg))

// Function to write a character to the serial port
int my_putc(int data) {
    printf("Testing\n");

    // Wait until the serial port is ready to transmit (checking the status register)
    while (!(MMIO_READ(SERIAL_PORT_ADDR + 0x18) & 0x20)) { 
        // Busy wait
    }

    // Write the character to the serial data register
    MMIO_WRITE(SERIAL_PORT_ADDR, data);
    return 0;
}

// Function to get the current execution level
unsigned int getEL() {
    unsigned int el;
    // Inline assembly to read the CurrentEL register
    asm volatile ("mrs %0, CurrentEL" : "=r" (el));
    
    // The EL is stored in bits [3:2] of the CurrentEL register, so we shift right
    return (el >> 2) & 0x3;
}

// Test function to demonstrate printing the current execution level using esp_printf
void print_execution_level() {
    esp_printf(my_putc, "Current Execution Level is %d\r\n", getEL());
}

// Main function
int main() {
    my_putc('A');
    print_execution_level();
    return 0;
}
