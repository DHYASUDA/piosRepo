extern int __bss_start, __bss_end;
  
   unsigned long get_timer_count(){
	unsigned long *timer_count_register = (unsigned long*) 0x3f003004;
	return *timer_count_register;
}
 	
 void clearBss(void){ 
  char *bss = &__bss_start;
  
  while(bss < &__bss_end){
  *bss++ = 0;
	}

	}
void kernel_main() {
    clearBss();
    //timer
    unsigned long start = get_timer_count();
    unsigned long wait = 1000;
    int x = 1234;
    	
    while(get_timer_count() - start < wait ){
	
    }
    while(1){
    }
}
