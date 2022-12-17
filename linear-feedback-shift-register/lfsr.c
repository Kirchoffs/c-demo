#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "bit_ops.h"
#include "lfsr.h"

void lfsr_calculate(uint16_t* reg) {
    unsigned new_bit = get_bit((unsigned) *reg, 0) ^ get_bit((unsigned) *reg, 2) ^ 
                       get_bit((unsigned) *reg, 3) ^ get_bit((unsigned) *reg, 5);
    
    *reg >>= 1;
    set_bit((unsigned *) reg, 15, new_bit);
}

