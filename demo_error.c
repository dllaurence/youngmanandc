#include <stdio.h>
#include <stdint.h>

#include "error.h"


// Dummy resource allocation functions

dll_Error dll_get_resourceN(uint32_t n, uint32_t limit)
{
    if (limit >= n) {
        printf("Acquired resource %u\n", n);
        return dll_Error_ok;
    }

    printf("Failed to aquire resource %u\n", n);
    return dll_Error_allocation;
}


dll_Error dll_get_resource1(uint32_t limit)
{
    return dll_get_resourceN(1, limit);
}


dll_Error dll_get_resource2(uint32_t limit)
{
    return dll_get_resourceN(2, limit);
}


dll_Error dll_get_resource3(uint32_t limit)
{
    return dll_get_resourceN(3, limit);
}


dll_Error dll_get_resource4(uint32_t limit)
{
    return dll_get_resourceN(4, limit);
}


// Pedantic do_stuff function
dll_Error dll_do_stuff_Dijkstra(uint32_t fail_point)
{
    dll_Error err = dll_Error_ok;

    err = dll_get_resource1(fail_point);
    if (!err) {

        err = dll_get_resource2(fail_point);
        if (!err) {

            err = dll_get_resource3(fail_point);
            if (!err) {

                err = dll_get_resource4(fail_point);
                if (!err) {

                    // Main body of function
                    if (fail_point <= 5) {
                        printf("Failed to compute results, rolling back\n");
                        err = dll_Error_computation;
                    }

                    if (!err) {
                        printf("Computed results\n");

                        // Commit results
                        printf("Committed results to output variables\n");
                    }

                    printf("Released resource 4\n");
                }

                printf("Released resource 3\n");
            }

            printf("Released resource 2\n");
        }

        printf("Released resource 1\n");
    }

    return err;
}


// Idiomatic do_stuff function
dll_Error dll_do_stuff_idiomatic(uint32_t fail_point)
{
    dll_Error err = dll_Error_ok;

    // Weirdly, GCC uses extra parens to indicate intentional assignment.
    // VC++ may not have a way to indicate this at all.
    if (( err = dll_get_resource1(fail_point) )) {
        goto RELEASE_0;
    }

    if (( err = dll_get_resource2(fail_point) )) {
        goto RELEASE_1;
    }

    if (( err = dll_get_resource3(fail_point) )) {
        goto RELEASE_2;
    }

    if (( err = dll_get_resource4(fail_point) )) {
        goto RELEASE_3;
    }

    // Main body of function
    if (fail_point <= 5) {
        printf("Failed to compute results, rolling back\n");
        err = dll_Error_computation;
        goto RELEASE_4;
    }

    printf("Computed results\n");

    // Commit results
    printf("Committed results to output variables\n");

RELEASE_4:
    printf("Released resource 4\n");

RELEASE_3:
    printf("Released resource 3\n");

RELEASE_2:
    printf("Released resource 2\n");

RELEASE_1:
    printf("Released resource 1\n");

RELEASE_0:

    return err;
}


void do_tests(const char* name, dll_Error (*fn)(uint32_t))
{
    printf("Testing function: %s\n\n", name);

    printf("Test failure during allocation\n\n");
    fn(2);
    printf("\n");

    printf("Test failure during computation\n\n");
    fn(5);
    printf("\n");

    printf("Test success\n\n");
    fn(6);
    printf("\n");
}


int main() {

    printf("\n");

    // Show demonstrate why there is a dll_Error_num_codes symbol, etc.
    printf("Error code list:\n\n");
    for (dll_Error err=dll_Error_ok; err < dll_Error_num_codes; err++) {
        printf("    %d: %s\n", err, dll_Error_description(err));
    }

    printf("\n");

    do_tests("pedantic", dll_do_stuff_Dijkstra);
    do_tests("idiomatic", dll_do_stuff_idiomatic);

    return 0;
}
