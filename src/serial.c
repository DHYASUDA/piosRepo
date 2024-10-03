#include "rprintf.h"

#define SERIAL_PORT_ADDR 0xFE215040

// Memory-mapped I/O write
static inline void MMIO_WRITE(unsigned int reg, unsigned int data) {
    *(volatile unsigned int *)reg = data;
}

// Memory-mapped I/O read
static inline unsigned int MMIO_READ(unsigned int reg) {
    return *(volatile unsigned int *)reg;
}

// Function to write a character to the serial port
void putc(int data) {
    // Wait until the serial port is ready to transmit (checking the status register)
    while (!(MMIO_READ(SERIAL_PORT_ADDR + 0x18) & 0x20)) {
        // Busy-wait until the transmit FIFO has space
    }

    // Write the character to the serial data register
    MMIO_WRITE(SERIAL_PORT_ADDR, data);
}

// Function to get the current execution level
unsigned int getEL() {
    unsigned int el;
    // Inline assembly to read the CurrentEL register
    asm volatile ("mrs %0, CurrentEL" : "=r" (el));
    
    // The EL is stored in bits [3:2] of the CurrentEL register, so we shift right by 2 to get the actual value
    return (el >> 2) & 0x3;
}

// Test function to demonstrate printing the current execution level using esp_printf
void print_execution_level() {
    esp_printf(putc, "Current Execution Level is %d\r\n", getEL());
}
