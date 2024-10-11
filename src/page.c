#include <stdio.h>
#include "page.h"

struct ppage physical_page_array[128];
struct ppage  *free_physical_page_list = NULL;

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
    free_physical_page_list = &physical_page_array[0];
}

struct ppage *allocate_physical_pages(unsigned int npages) {
    struct ppage *allocd_list = NULL;
    struct ppage *last_allocd_page = NULL;

    for (unsigned int i = 0; i < npages && free_physical_page_list != NULL; i++) {
        struct ppage *current_page = free_physical_page_list;
  //links
        free_physical_page_list = current_page->next;
        if (free_physical_page_list) {
            free_physical_page_list->prev = NULL;
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
        if (free_physical_page_list != NULL) {
            free_physical_page_list->prev = current_page;
        }
        free_physical_page_list = current_page;
        current_page->prev = NULL;
    }
}


void test_physical_page_allocator() {
    printf("creatingphysical page allocator: \n");
    init_pfa_list();

    printf("Allocating 5 pages...\n");
    struct ppage *allocd_list = allocate_physical_pages(5);

    // Check if we got 5 unique pages and print their physical addresses
    struct ppage *current = allocd_list;
    int count = 0;
    while (current != NULL) {
   printf("allo%d at physical address: %p\n", count++, current->physical_addr);
        current = current->next;
    }

    // Free the allocated pages
    printf("Freeing allocated pages...\n");
    free_physical_page(allocd_list);

    // Allocate more pages and check again
    printf("Allocating 2 more pages...\n");
    allocd_list = allocate_physical_page_list(2);

    count = 0;
    current = allocd_list;
    while (current != NULL) {
        printf("Allocated page %d at physical address: %p\n", count++, current->physical_addr);
        current = current->next;
    }

    // Free the pages again
    printf("Freeing allocated pages...\n");
    free_physical_page(allocd_list);

    // Final check for correct memory management
    printf("Physical page allocator test completed.\n");
}
/*void print_free_list() {
    struct ppage *current = free_physical_pages;
    int count = 0;
    while (current != NULL) {
        printf("Free page %d at physical address: %p\n", count++, current->physical_addr);
        current = current->next;
    }
}*/

int main(){
    test_physical_page_allocator();
    return 0;
}



