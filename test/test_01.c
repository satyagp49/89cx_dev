#include <stdio.h>

#define ARR_SIZE 3
#define SHIFT_SIZE 2
#define NUM_SHIFT 1
#define WIDTH_SIZE  5

typedef struct {
    unsigned int width: WIDTH_SIZE;
}WIDTH;

void fun_test () {
    WIDTH arr[ARR_SIZE] = {0x08, 0x08, 0x08};
    int count = 0x00;
    char backup, shift;
    
    printf ("\nBefore shift:: ");
    for (count = 0x00; count <ARR_SIZE; count ++) {
        printf (" %02x", arr[count].width);
    }
    for (shift = 0x00; shift<NUM_SHIFT;shift++) {
        for (count = 0; count < ARR_SIZE;count ++) {
            if (count == 0x00) {
                arr [count].width >>= SHIFT_SIZE;
            }
            else {
                backup = arr [count].width & 0x01;
                arr [count].width >>= SHIFT_SIZE;
                arr [count - 1].width = arr [count - 1].width | (backup << 7);            
            }
        }
    }
    printf ("\nAfter Shift::  ");
    for (count = 0x00; count < ARR_SIZE; count ++) {
        printf (" %02x", arr[count].width);
    }
    
    printf ("\n");
}    

void array() {
    char arr[3][4] = {{0x01,0x2,0x3,0x4},
                      {0x11,0x12,0x13,0x14},  
                      {0x21,0x22,0x23,0x24},
    };
    int colomn, row;
    printf ("\nArray::  \n");
    for (row = 0x00; row < 3; row++) {
        for (colomn = 0x00; colomn < 4; colomn ++) {
            printf (" %02x", arr[row][colomn]);
        }
        printf ("\n");
    }
}


int main (void) {
    
    //fun_test ();
    
    array();
    
    printf ("\n");
    return 0;
}

