//
// Created by richard on 28/11/18.
//

#include <kernel/mem.h>
#include <kernel/atag.h>
#include <common/stdlib.h>
#include <stdint.h>
#include <stddef.h>


extern uint8_t __end;

static uint32_t num_pages;


DEFINE_LIST(page);
IMPLEMENT_LIST(page);

static page_t * all_pages_array;
page_list_t free_pages;


/*
 * Implement kmalloc as a linked list of allocated segments.
 * Segments should be 4 byte aligned.
 * Use best fit algorithm to find an allocation.
 */

void mem_init( atag_t * atags ){
    uint32_t mem_size, page_array_len, kernel_pages, i;

    // get the total number of pages
    mem_size = get_mem_size( atags );
    num_pages = mem_size / PAGE_SIZE;

    // allocate memory for all of those pages' metadata, start this block just after the ernel image is finished
    page_array_len = sizeof( page_t ) * num_pages;
    all_pages_array = ( page_t *)&__end;
    bzero( all_pages_array, page_array_len );
    INITIALISE_LIST( free_pages );

    // iterate over all the pages, and mark them as appropriate
    kernel_pages = ((uint32_t)&__end) /PAGE_SIZE;
    for( i=0; i<kernel_pages, i++){
        all_pages_array[i].vaddr_mapped = i * PAGE_SIZE;
        all_pages_array[i].flags.allocated = 1;
        all_pages_array[i].flags.kernel_page = 1;
    }

    // map the rest of the ages as free
    for(; i<num_pages; i++){
        all_pages_array[i].flags.allocated = 0;
        append_page_list( &free_pages, &all_pages_array[i] );
    }

}

void * alloc_page( void ){
    page_t * page;
    void * page_mem;

    if( size_page_list(&free_pages) == 0 ){
        return 0; // we don't have any free pages to allocate
    }

    // get a free page
    page = pop_page_list( &free_pages );
    page->flags.kernel_page = 1;
    page->flags.allocated = 1;

    // get the address the physical page metadata refers to
    page_mem = ( void * )(( page - all_pages_array ) * PAGE_SIZE );

    // zero out the page memory
    bzero( page_mem, PAGE_SIZE );

    return page_mem;
}


void free_page( void * ptr ){
    page_t * page;

    // get the page metadata from the physical address
    page = all_pages_array + ((uint32_t) ptr / PAGE_SIZE );

    // mark the pge as free
    page->flags.allocated = 0;
    append_page_list( &free_pages, page );
}


