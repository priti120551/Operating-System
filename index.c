#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct dir {
    char fname[20];
    int ino, flag;
    struct dir* next;
} DIR;

DIR* first, * last;
int d, fat[200], free_blocks;

void print_dir() {
    DIR* p;
    int i;
    printf("------------------------------\n");
    printf("File\tInode\tBlocks List\n");
    printf("------------------------------\n");
    p = first;
    while (p != NULL) {
        if (p->flag == 0) {
            printf("%s\t%d\t", p->fname, p->ino);
            for (i = 0; i < d; i++) {
                if (fat[i] == p->ino) {
                    printf("%d ", i);
                }
            }
            printf("\n");
        }
        p = p->next;
    }
    printf("-----------------------------\n");
}

void print_free_list() {
    int i;
    printf("Free blocks list: ");
    for (i = 0; i < d; i++) {
        if (fat[i] == -999) {
            printf("%d -> ", i);
        }
    }
    printf("NULL\n");
}

void main() {
    DIR* p;
    int i, j, bno, ch;
    char fname[20];

    printf("Enter no of disk blocks: ");
    scanf("%d", &d);
    for (i = 0; i < d; i++)
        fat[i] = -999;
    free_blocks = d;

    while (1) {
        printf("1. Create\n2. Delete\n3. Print Dir/Free list\n4. Exit\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", fname);  // Use %s to read string
                printf("Enter no of blocks: ");
                scanf("%d", &bno);

                if (free_blocks >= bno) {  // Check if there are enough blocks
                    free_blocks -= bno;  // Decrease the free block count
                    p = (DIR*)malloc(sizeof(DIR));
                    strcpy(p->fname, fname);
                    p->flag = 0;  // File is created, so flag is 0
                    p->next = NULL;

                    // Find an inode for the file
                    for (i = 0; i < d; i++) {
                        if (fat[i] == -999) {
                            p->ino = i;
                            fat[i] = p->ino;
                            break;
                        }
                    }

                    // Allocate blocks for the file
                    int blocks_assigned = 0;
                    i++;
                    while (blocks_assigned < bno && i < d) {
                        if (fat[i] == -999) {
                            fat[i] = p->ino;
                            blocks_assigned++;
                        }
                        i++;
                    }

                    // If the file is the first one, set first pointer
                    if (first == NULL) first = p;
                    else last->next = p;

                    last = p;  // Update the last pointer to the new file
                    printf("File %s created successfully\n", fname);
                } else {
                    printf("Unable to create file %s, not enough space.\n", fname);
                }
                break;

            case 2:
                printf("Enter file to be deleted: ");
                scanf("%s", fname);

                p = first;
                while (p != NULL) {
                    if (strcmp(p->fname, fname) == 0 && p->flag == 0)
                        break;
                    p = p->next;
                }

                if (p == NULL) {
                    printf("File %s not found\n", fname);
                } else {
                    p->flag = 1;  // Mark file as deleted
                    bno = 0;
                    for (i = 0; i < d; i++) {
                        if (fat[i] == p->ino) {
                            fat[i] = -999;
                            bno++;
                        }
                    }
                    free_blocks += bno;  // Reclaim free blocks
                    printf("File %s deleted successfully\n", fname);
                }
                break;

            case 3:
                print_dir();
                print_free_list();
                break;

            case 4:
                exit(0);
        }
    }
}
