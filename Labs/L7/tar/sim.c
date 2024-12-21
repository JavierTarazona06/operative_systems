/*
Identification:

Author: Jarrod Pas
Modified by students:  Javier Tarazona
		elr490
		11411898
 */

/* Note: code intentionally not commented */


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <unistd.h>

struct frame {
    int number; /* number == -1 means unused */
    bool reference;
    bool dirty;
};

int npages;
int next_slot;
int nslots;
struct frame *slots;
struct frame *memory_iterator;


/* Handles a page fault via the second-chance algorithm.
 * Returns the pointer to the slot the victim is in. */
struct frame *find_victim_slot() {
    /* TODO: implement second chance page replacement algorithm */
    struct frame *current_p;
    bool flag = true;

    current_p = memory_iterator;

    if (next_slot < nslots){
        return current_p;
    }

    while (flag){
        current_p = memory_iterator;
        if ((current_p -> reference) == true){
            current_p -> reference = false;
        } else {
            if ((current_p -> dirty) == true){
                current_p -> dirty = false;
            } else {
                /*The dirty bit is 0  or 0* */
                /*The change must be perform, so break the cycle*/
                flag = false;
            }
        }

        if ((memory_iterator) == (slots + (nslots-1))){
            memory_iterator = slots;
        } else {
            memory_iterator++;
        }
    }

    return current_p;
}

int main(int argc, char **argv) {
    int times;
    int page;
    bool fault;
    bool write;
    struct frame *p;

    if (argc != 3 && argc != 4) {
        printf("usage: %s npages nslots <times>\n", argv[0]);
        exit(1);
    }

    npages = atoi(argv[1]);
    if (npages <= 0) {
        printf("npages must be greater than 0\n");
        exit(1);
    }

    nslots = atoi(argv[2]);
    if (nslots <= 0) {
        printf("nslots must be greater than 0\n");
        exit(1);
    }
    next_slot = 0;
    slots = malloc(sizeof(struct frame) * nslots);
    memory_iterator = slots;

    if (argc == 4) {
        times = atoi(argv[3]);
        if (times <= 0) {
            printf("times must be greater than 0.\n");
            exit(1);
        }
    } else {
        times = -1;
    }

    for (p = slots; p < &slots[nslots]; p++) {
        p->number = -1;
        p->reference = false;
        p->dirty = false;
    }

    while (times < 0 || times-- > 0) {
        page = npages * sqrt((double) rand() / RAND_MAX);
        write = rand() % 2;

        if (write) {
            printf("RW on page %d.\n", page);
        } else {
            printf("R  on page %d.\n", page);
        }

        fault = true;
        for (p = slots; p < &slots[nslots]; p++) {
            if (p->number != page) continue;
            p->reference = true;
            p->dirty |= write;
            fault = false;
            break;
        }

        if (fault) {
            printf(" This triggered a page fault.");
            p = find_victim_slot();
            if (next_slot < nslots) {
                printf(" There was a free slot!");
                p = slots + next_slot++;
            } else {
                printf(" The chosen victim was page %d.", p->number);
            }
            p->number = page;
            p->reference = true;
            p->dirty = write;
        }

        if (times < 0) usleep(100 * 1000);

        putchar('\n');
    }

    return 0;
}

