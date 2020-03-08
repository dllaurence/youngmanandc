#include "error.h"


static const char* name_list[dll_Error_num_codes] = {
    "OK",    // 0
    "Allocation failure",
    "Computation failure",
};


bool dll_Error_is_valid(dll_Error err)
{
    return err >= dll_Error_ok && err < dll_Error_num_codes;
}


const char* dll_Error_description(dll_Error err)
{
    if (dll_Error_is_valid(err)) {
        return name_list[err];
    }

    return "invalid error code";
}
