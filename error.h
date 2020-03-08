#pragma once

#include <stdbool.h>


typedef enum dll_Error {

    dll_Error_ok = 0,
    dll_Error_allocation,
    dll_Error_computation,
    dll_Error_num_codes   // guard value

} dll_Error;


bool dll_Error_is_valid(dll_Error err);
const char* dll_Error_description(dll_Error err);
