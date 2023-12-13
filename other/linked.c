#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

struct node {
    struct node *next;
    bool alloc;
};

struct file {
    char name[20];
    struct node start;
} files[20];

int fileCount = 0;
struct node blocks[100];

int main() {
    int choice;

    for (int i = 0; i < 100; ++i) {
        blocks[i].next = NULL;
        blocks[i].alloc = false;
    }

    printf("Memory has 100 blocks in total\n");

    do {
        printf("\tMENU\n");
        printf("1. Create file\n2. Display files\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (fileCount < 20) {
                    // Input file name and size
                    printf("Enter file name : ");
                    scanf("%s", files[fileCount].name);

                    int blockSize;
                    printf("Enter number of blocks : ");
                    scanf("%d", &blockSize);

                    // Allocate blocks for the file
                    struct node *nextNode = &files[fileCount].start;

                    for (int i = 0; i < blockSize; i++) {
                        int randomNumber;
                        struct node *newNode = (struct node *)malloc(sizeof(struct node));
                        newNode->next = NULL;

                        do {
                            randomNumber = rand() % 100;
                        } while (blocks[randomNumber].alloc);

                        blocks[randomNumber].alloc = true;
                        nextNode->next = &blocks[randomNumber];
                        nextNode->alloc = true;
                        nextNode = nextNode->next;
                    }

                    printf("File %s created!\n\n", files[fileCount].name);
                    fileCount++;
                } else {
                    printf("Cannot create more files. Limit reached.\n");
                }
                break;

            case 2:
                for (int i = 0; i < fileCount; i++) {
                    printf("File %s blocks: ", files[i].name);
                    struct node *currentNode = files[i].start.next;
                    while (currentNode != NULL) {
                        printf("%ld --->", currentNode - blocks);
                        currentNode = currentNode->next;
                    }
                    printf("NULL\n");
                }
                break;
        }
    } while (choice >= 1 && choice <= 2);

    return 0;
}
