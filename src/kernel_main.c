

  extern int __bss_start, __bss_end;
  
  void clearBss(void){
  
  char *bss = &__bss_start;
  
  while(bss < &__bss_end){
  *bss++ == 0;
}

}
void kernel_main() {

    clearBss();
    while(1){
    }
}
