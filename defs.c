#include <string.h>
#include "defs.h"

int read_table(struct double_linked_list_t** lists, const char* filename, uint8_t (*wsk)(uint8_t)){
    if(lists==NULL || filename==NULL){
        return -1;
    }

    FILE *f = fopen(filename,"r");
    if(f==NULL){
        return -2;
    }

    int result;
    int count = 0;
    char home_name[41], away_name[41];

    while (!feof(f)) {
        int res = fscanf(f, "%40[^|]|%40[^|]|%d\n", home_name, away_name, &result);
        if(res==EOF){
            break;
        }
        if (res != 3) {
            free_list(*lists);
            fclose(f);
            return -3;
        }

        if (*lists == NULL) {
            *lists = calloc(1, sizeof(struct double_linked_list_t));
            if (*lists == NULL) {
                fclose(f);
                return -4;
            }
        }


        struct node_t *vec = ((*lists))->head;
        while ((vec) != NULL) {
            if (strcmp(vec->info->name, home_name) == 0) {
                break;
            }
            vec = vec->next;
        }

        if (vec) {
            vec->info->games++;
            if (result == 1) {
                vec->info->points += 3;
            } else if (result == 0) {
                vec->info->points += 1;
            }
            vec->info->hash_value = wsk(vec->info->points);
        }
        else {
            vec = calloc(1, sizeof(struct node_t));
            if (vec == NULL) {
                free_list(*lists);
                fclose(f);
                return -4;
            }

            vec->info = calloc(1,sizeof(struct info_t));
            if (vec->info == NULL) {
                free(vec);
                free_list(*lists);
                fclose(f);
                return -4;
            }

            int len = (int) strlen(home_name);
            vec->info->name = calloc(len + 1, sizeof(char));
            if (vec->info->name == NULL) {
                free(vec->info);
                free(vec);
                free_list(*lists);
                fclose(f);
                return -4;
            }
            strcpy(vec->info->name, home_name);
            vec->info->games = 1;
            if (result == 1) {
                vec->info->points = 3;
            } else if (result == 0) {
                vec->info->points = 1;
            } else if (result == 2) {
                vec->info->points = 0;
            }
            else {
                free(vec->info->name);
                free(vec->info);
                free(vec);
                free_list(*lists);
                fclose(f);
                return -3;
            }

            vec->info->hash_value = wsk(vec->info->points);

            if (((*lists))->head == NULL) {
                ((*lists))->head = vec;
                ((*lists))->tail = vec;
            } else {
                struct node_t *p = ((*lists))->tail;
                ((*lists))->tail->next = vec;
                ((*lists))->tail = vec;
                ((*lists))->tail->prev = p;

            }
            count++;
        }

        vec = ((*lists))->head;
        while ((vec) != NULL) {
            if (strcmp(vec->info->name, away_name) == 0) {
                break;
            }
            vec = vec->next;
        }

        if (vec) {
            vec->info->games++;
            if (result == 2) {
                vec->info->points += 3;
            } else if (result == 0) {
                vec->info->points += 1;
            }
            vec->info->hash_value = wsk(vec->info->points);
        }
        else {
            vec = calloc(1, sizeof(struct node_t));
            if (vec == NULL) {
                free_list(*lists);
                fclose(f);
                return -4;
            }

            vec->info = calloc(1,sizeof(struct info_t));
            if (vec->info == NULL) {
                free(vec);
                free_list(*lists);
                fclose(f);
                return -4;
            }

            int len = (int) strlen(away_name);
            vec->info->name = calloc(len + 1, sizeof(char));
            if (vec->info->name == NULL) {
                free(vec->info);
                free(vec);
                free_list(*lists);
                fclose(f);
                return -4;
            }

            strcpy(vec->info->name, away_name);
            vec->info->games = 1;
            if (result == 1) {
                vec->info->points = 0;
            } else if (result == 0) {
                vec->info->points = 1;
            } else if (result == 2) {
                vec->info->points = 3;
            } else {
                free(vec->info->name);
                free(vec->info);
                free(vec);
                free_list(*lists);
                fclose(f);
                return -3;
            }
            vec->info->hash_value = wsk(vec->info->points);

            struct node_t *p = ((*lists))->tail;
            ((*lists))->tail->next = vec;
            ((*lists))->tail = vec;
            ((*lists))->tail->prev = p;
            count++;
        }
    }

    fclose(f);
    return 0;
}
void display_table_forward(const struct double_linked_list_t* lists){
    if(lists!=NULL){
        struct node_t *vec = lists->head;
        while (vec!=NULL){
            printf("%s: %d %d %d\n",vec->info->name,vec->info->games,vec->info->points,vec->info->hash_value);
            vec =  vec->next;
        }
    }
}
void free_list(struct double_linked_list_t* lists){
    if(lists!=NULL){
        struct node_t *vec = lists->head;
        while(vec!=NULL){
            free(vec->info->name);
            free(vec->info);
            struct node_t *p = vec;
            vec = vec->next;
            free(p);
        }
        free(lists);
    }
}
