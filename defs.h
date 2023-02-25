#ifndef LISTA_DWUKIERUNKOWA_DEFS_H
#define LISTA_DWUKIERUNKOWA_DEFS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

struct info_t
{
    char *name;
    uint8_t games;
    uint8_t points;	//1 - home team wins, 0 - draw, 2 - away team wins
    uint8_t hash_value;
};

struct node_t
{
    struct info_t *info;
    struct node_t *next;
    struct node_t *prev;
};

struct double_linked_list_t
{
    struct node_t *head;
    struct node_t *tail;
};

#define CREATE_FUNCTION_COUNT01(typ)\
typ count01_##typ (typ a){            \
    int count = 0;                  \
    unsigned long i = 1UL<<(sizeof(a)*CHAR_BIT-1);\
    while(i) {\
        if(a & i){\
        }                           \
        else{                       \
            i>>=1;\
            if(a & i){\
                count++;\
            }                       \
            else{                   \
            i<<=1;                        \
            }\
        }                            \
        i>>=1;\
    }                               \
    return count;\
}                                   \


int read_table(struct double_linked_list_t** lists, const char* filename, uint8_t (*wsk)(uint8_t));
void display_table_forward(const struct double_linked_list_t* lists);
void free_list(struct double_linked_list_t* lists);
#endif
