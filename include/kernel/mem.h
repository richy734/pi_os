//
// Created by richard on 28/11/18.
//

#include <stdint.h>
#include <kernel/atags.h>
#include <kernel/list.h>
#ifndef OS_MEM_H
#define OS_MEM_H

#define PAGE_SIZE 4096;

typedef struct{
    uint8_t allocated: 1;   // this page is allocated to something
    uint8_t kernel_page: 1; // this page is part of the kernel
    uint32_t reserved: 30;
} page_flags_t;


typedef struct{
    uint32_t vaddr_mapped;  // the virtual address that maps to this space
    page_flags_t page_flags;
    DEFINE_LINK( page );
} page_t;


void mem_init( atag_t * atags );

void * alloc_page( void );

void free_page( void * ptr );


#endif //OS_MEM_H
