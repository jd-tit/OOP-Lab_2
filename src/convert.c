//
// Created by jdt on 3/11/2022.
//

#include <stdlib.h>
#include <stdbool.h>

#include "convert.h"

bool str_to_s_long(char* buff, long int* result_p){
    /**
     * Convert a C-string to a signed long
     * @pre: none extra
     * @post: result of conversion is assigned to the value pointed to by result_p
     *          result is 0 if conversion failed;
     * @return: true if successful, false otherwise
     */
    char* end_ptr = NULL;
    *result_p = strtol(buff, &end_ptr, 10);
    if(buff == end_ptr)
        return false;
    return true;
}
