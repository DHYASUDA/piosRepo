struct ppage physical_page_array[128];

void init_pfa_list(void) {
    for (int i = 0; i < 128; i++) {
        physical_page_array[i].physical_addr = (void *)(i * 0x200000);  

        
        if (i > 0) {
            physical_page_array[i].prev = &physical_page_array[i - 1];
            physical_page_array[i - 1].next = &physical_page_array[i];
        }
    }
    physical_page_array[0].prev = NULL;
    physical_page_array[127].next = NULL;
}

struct ppage *allocate_physical_pages(unsigned int npages) {
    struct ppage *allocd_list = NULL;
    struct ppage *last_allocd_page = NULL;

    for (unsigned int i = 0; i < npages && free_physical_pages != NULL; i++) {
        struct ppage *current_page = free_physical_pages;
  //links
        free_physical_pages = current_page->next;
        if (free_physical_pages) {
            free_physical_pages->prev = NULL;
        }

       //allocates
        if (allocd_list == NULL) {
            allocd_list = current_page;
            last_allocd_page = current_page;
        } else {
            last_allocd_page->next = current_page;
            current_page->prev = last_allocd_page;
            last_allocd_page = current_page;
        }
    }

    // Ensure the last page in the allocated list has a NULL next pointer
    if (last_allocd_page != NULL) {
        last_allocd_page->next = NULL;
    }

    return allocd_list;
}
void free_physical_pages(struct ppage *ppage_list) {
    while (ppage_list != NULL) {
        struct ppage *current_page = ppage_list;
        ppage_list = current_page->next;

        // Link back into the free list
        current_page->next = free_physical_pages;
        if (free_physical_pages != NULL) {
            free_physical_pages->prev = current_page;
        }
        free_physical_pages = current_page;
        current_page->prev = NULL;
    }
}
