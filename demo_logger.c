#include "logger.h"


int main()
{
    dll_Logger_init();
    if (!dll_Logger_get_file()) {
        dll_Logger_set_file(stderr);
    }

    dll_Logger* log = dll_Logger_create("main");
    dll_Logger_msg(log, "main successfully logged");
    dll_Logger_destroy(&log);
    assert(!log);

    dll_Logger_finalize();

    return 0;
}
