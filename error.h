#pragma once

#include <stdbool.h>


typedef enum dll_Error {

    dll_Error_ok = 0,

    // Simulated errors
    dll_Error_allocation_simulated,
    dll_Error_computation_simulated,

    // Real errors
    dll_Error_allocation_real,

    // Guard value
    dll_Error_num_codes   // guard value

} dll_Error;


bool dll_Error_is_valid(dll_Error err);
const char* dll_Error_description(dll_Error err);
