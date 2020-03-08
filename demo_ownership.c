#include "logger.h"


void borrower(dll_Logger* logger)
{
    // Using a borrowed object
    dll_Logger_msg(logger, "borrower using log");
    // Don't own, so should not retain a reference
    dll_Logger_msg(logger, "borrower NULLing reference");
    logger = NULL;
}


void new_new_owner(dll_Logger* o_logger)
{
    // Granting a sublease
    dll_Logger_msg(o_logger, "new_new_owner loaning to sub_borrower");
    borrower(o_logger);

    // We own this logger so we must destroy before going out of scope
    dll_Logger_msg(o_logger, "new_new_owner destroying");
    dll_Logger_destroy(&o_logger);
}


void new_owner(dll_Logger* o_logger)
{

    // Granting a sublease
    dll_Logger_msg(o_logger, "new_owner loaning to sub_borrower");
    borrower(o_logger);

    // Transferring ownership
    dll_Logger_msg(o_logger, "new_owner transferring to new_new_owner");
    new_new_owner(o_logger);

    // Don't own the logger anymore, so must not destroy
    // Don't have a lease, so must not use the logger
    printf("new_owner NULLing reference (but has no loan for the logger)\n");
    o_logger = NULL;
}


int main()
{
    // Init same as before
    dll_Logger_init();
    dll_Logger_set_file(stdout);
    printf("\n");

    // Demo borrowing
    dll_Logger* o_borrowed_log = dll_Logger_create("demo1");
    printf("demo borrowing\n\n");
    // Granting a sublease
    dll_Logger_msg(o_borrowed_log, "main loaning to borrower");
    borrower(o_borrowed_log);
    // deallocating
    dll_Logger_msg(o_borrowed_log, "main destroying\n");
    dll_Logger_destroy(&o_borrowed_log);

    // Demo ownership transfer
    dll_Logger* o_transferred_log = dll_Logger_create("demo2");
    printf("demo ownership transfer\n\n");
    dll_Logger_msg(o_transferred_log, "main transferring to new_owner");
    new_owner(o_transferred_log);
    // Don't own, so should not retain a reference
    // Don't have a lease, so must not use the logger
    printf("main NULLing reference (but has no loan for the logger)\n");
    o_transferred_log = NULL;

    // Finalize module same as before
    dll_Logger_finalize();

    printf("\n");

    return 0;
}
