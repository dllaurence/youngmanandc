#include <stdio.h>
#include <stdint.h>

#include "error.h"
#include "logger.h"


// Can't be a const because the buffer is static
#define BUF_SIZE 100


// Dummy resource allocation functions

dll_Error dll_get_resource(dll_Logger** o_logger, uint32_t n, uint32_t limit)
{

    static char buf[BUF_SIZE+1];
    snprintf(buf, BUF_SIZE, "resource %u", n);

    if (limit >= n) {

        dll_Logger* o_new_logger = dll_Logger_create(buf);
        if (o_new_logger) {

            *o_logger = o_new_logger;
            printf("Acquired %s\n", buf);

            return dll_Error_ok;
        }

        printf("***Real*** failed to aquire %s\n", buf);
        return dll_Error_allocation_real;
    }

    printf("Simulated failure to aquire %s\n", buf);
    return dll_Error_allocation_simulated;
}


void dll_release_resource(dll_Logger** o_logger)
{
    // FIXME: make accessor method
    printf("Released %s\n", dll_Logger_get_category(*o_logger));

    dll_Logger_destroy(o_logger);
}


// Pedantic do_stuff function
dll_Error dll_do_stuff_Dijkstra(uint32_t fail_point)
{
    dll_Error err = dll_Error_ok;

    dll_Logger* o_resource1;
    err = dll_get_resource(&o_resource1, 1, fail_point);
    if (!err) {

        dll_Logger* o_resource2;
        err = dll_get_resource(&o_resource2, 2, fail_point);
        if (!err) {

            dll_Logger* o_resource3;
            err = dll_get_resource(&o_resource3, 3, fail_point);
            if (!err) {

                dll_Logger* o_resource4;
                err = dll_get_resource(&o_resource4, 4, fail_point);
                if (!err) {

                    // Main body of function
                    if (fail_point <= 5) {
                        printf("Simulated failure to compute results, rolling back\n");
                        err = dll_Error_computation_simulated;
                    }

                    if (!err) {
                        printf("Computed results\n");

                        // Commit results
                        printf("Committed results to output variables\n");
                    }

                    dll_release_resource(&o_resource4);
                }

                dll_release_resource(&o_resource3);
            }

            dll_release_resource(&o_resource2);
        }

        dll_release_resource(&o_resource1);
    }

    return err;
}


// Idiomatic do_stuff function
dll_Error dll_do_stuff_idiomatic(uint32_t fail_point)
{
    dll_Error err = dll_Error_ok;

    // Weirdly, GCC uses extra parens to indicate intentional assignment.
    // VC++ may not have a way to indicate this at all.
    dll_Logger* o_resource1;
    if (( err = dll_get_resource(&o_resource1, 1, fail_point) )) {
        goto RELEASE_0;
    }

    dll_Logger* o_resource2;
    if (( err = dll_get_resource(&o_resource2, 2, fail_point) )) {
        goto RELEASE_1;
    }

    dll_Logger* o_resource3;
    if (( err = dll_get_resource(&o_resource3, 3, fail_point) )) {
        goto RELEASE_2;
    }

    dll_Logger* o_resource4;
    if (( err = dll_get_resource(&o_resource4, 4, fail_point) )) {
        goto RELEASE_3;
    }

    // Main body of function
    if (fail_point <= 5) {
        printf("Simulated failure to compute results, rolling back\n");
        err = dll_Error_computation_simulated;
        goto RELEASE_4;
    }

    printf("Computed results\n");

    // Commit results
    printf("Committed results to output variables\n");

RELEASE_4:
    dll_release_resource(&o_resource4);

RELEASE_3:
    dll_release_resource(&o_resource3);

RELEASE_2:
    dll_release_resource(&o_resource2);

RELEASE_1:
    dll_release_resource(&o_resource1);

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
