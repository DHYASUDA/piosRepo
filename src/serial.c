#include <stdint.h>
#include "rprintf.h"
#include "rprintf.c"
#define SERIAL_PORT_ADDR 0x7D001000

static inline uint32_t MMIO_READ(uint32_t addr) {
            return *(volatile uint32_t *)(uintptr_t)addr;
}

static inline void MMIO_WRITE(uint32_t addr, uint32_t data) {
            *(volatile uint32_t *)(uintptr_t)addr = data;
}

int s_putc(int data) {
            if (MMIO_READ(SERIAL_PORT_ADDR + 0x18) & 0x20) {
                            MMIO_WRITE(SERIAL_PORT_ADDR, data);
                            return data;
            }
               return -1;
}


int getEL() {
            unsigned int el;
           asm volatile ("mrs %0, CurrentEL" : "=r" (el));
          return (el >> 2) & 0x3;
}
void print_execution_level(){
   esp_printf(s_putc,"level : %d\r\n", getEL());

}

int  main() {
            int current_level = getEL();
                print_execution_level(current_level);
                return 0;
	    return *(volatile uint32_t *)(uintptr_t)addr;
}

static inline void MMIO_WRITE(uint32_t addr, uint32_t data) {
	    *(volatile uint32_t *)(uintptr_t)addr = data;
}

int s_putc(int data) {
	    if (MMIO_READ(SERIAL_PORT_ADDR + 0x18) & 0x20) {
		            MMIO_WRITE(SERIAL_PORT_ADDR, data);
			    return data;
	    }
               return -1; 
}



int getEL() {
	    unsigned int el;
	   asm volatile ("mrs %0, CurrentEL" : "=r" (el));
	  return (el >> 2) & 0x3; 
}
void print_execution_level(){
   esp_printf(s_putc,"level : %d\r\n", getEL()); 
		  
}

int  main() {
	    int current_level = getEL();
	        print_execution_level(current_level);
		return 0;
		
}

