//
// Created by richard on 01/12/18.
//

#ifndef OS_LIST_H
#define OS_LIST_H

#define DEFINE_LIST( nodeType ) \
typedef struct nodeType##list { \
    struct nodeType * head; \
    struct nodeType * tail; \
    unit_32 size; \
} nodeType##list;


#define DEFINE_LINK( nodeType ) \
struct nodeType * next##nodeType;
struct nodeType * prev##nodeType;


#define INITIALISE_LIST( list ) \
list.head = list.tail = (void *) 0; \
list.size = 0;


#define IMPLEMENT_LIST( nodeType ) \
void append_##nodeType##_list( nodeType##_list_t * list, struct nodeType * node ){ \
    list->tail->next##nodeType = node; \
    list->prev##nodeType = list->tail; \
    list->tail = node; \
    node->next##nodeType = NULL; \
    list->size += 1; \
} \
\
\
void push_##nodeType##_list( nodeType##_list_t * list, struct nodeType * node){ \
    node->next##nodeType## = list->head; \
    node->prev##nodeType## = NULL; \
    list->head = node; \
    list->size +=1; \
} \
\
\
struct nodeType * peek_##nodeType##_list( nodeType##_list_t * list ){ \
    return list->head; \
}\
\
\
struct nodeType * pop_##nodeType##_list( nodeType##_list_t * list ){ \
    struct nodeType * res = list->head; \
    list->head = list->head->next##nodeType; \
    list->head->prev##nodeType = NULL; \
    list->size -= 1; \
    return res; \
}\
\
\
uint32_t size_##nodeType##_list( nodeType##_list_t * list ){ \
    return list->size;\
}\
\
\
struct nodeType * next_##nodeType##_list( struct nodeType * node ){ \
    return node->next; \
}


#endif //OS_LIST_H