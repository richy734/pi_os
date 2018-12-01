//
// Created by richard on 28/11/18.
//

#include <stdint.h>
#include <kernel/atag.h>
#include <kernel/list.h>
#ifndef OS_MEM_H
#define OS_MEM_H

#define PAGE_SIZE 4096
#define KERNEL_HEAP_SIZE (1024 * 1024)

typedef struct{
    uint8_t allocated: 1;   // this page is allocated to something
    uint8_t kernel_page: 1; // this page is part of the kernel
    uint32_t reserved: 30;
} page_flags_t;


typedef struct page{
    uint32_t vaddr_mapped;  // the virtual address that maps to this space
    page_flags_t flags;
    DEFINE_LINK( page );
} page_t;


void mem_init( atag_t * atags );

void * alloc_page( void );
void free_page( void * ptr );

void * kmalloc( uint32_t bytes );
void kfree( void *ptr );


#endif //OS_MEM_H
