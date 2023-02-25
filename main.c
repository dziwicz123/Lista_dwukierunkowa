#include <stdio.h>
#include "defs.h"
#include <stdint.h>

CREATE_FUNCTION_COUNT01(uint8_t)

int main(int argc, char** argv) {
    if(argc<1 || argv==NULL || *argv==NULL){
        printf("Not enough arguments");
        return 9;
    }

    struct double_linked_list_t* lists = NULL;

    for (int i = 0; i < argc; ++i) {
        int res = read_table(&lists,*(argv+i+1),count01_uint8_t);
        if(res==-2){
            free_list(lists);
            printf("Couldn't open file");
            return 4;
        }
        else if(res==-4){
            printf("Failed to allocate memory");
            return 8;
        }
        else if(res==-3){
            printf("File corrupted");
            return 6;
        }
    }

    if(lists==NULL){
        printf("Not enough arguments");
        return 9;
    }
    display_table_forward(lists);
    free_list(lists);
    return 0;
}
