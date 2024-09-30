#include <stdint.h>
#include "rprintf.h"  
#include "serial.h"  

#define MU_IO_ADDRESS 0xFE215004


void putc(int data) {
    volatile uint32_t *mu_io = (uint32_t *)MU_IO_ADDRESS;
    *mu_io = (uint32_t)data;
}


void print_execution_level() {
    esp_printf(putc, "LVEL: %d\r\n", getEL());
}
