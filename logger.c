#include <stdlib.h>

#include "logger.h"



/**********************************************************************
 * class and instance variables
 *
 **********************************************************************/


static FILE* m_log_file;


struct dll_Logger {

    const char* module;
};


/**********************************************************************
 * private interface
 *
 **********************************************************************/


// class methods
static void my_flush(void);


// instance methods
static void dll_Logger_msg_impl(dll_Logger* self, const char* msg);


/**********************************************************************
 * class methods
 *
 **********************************************************************/


// public
void dll_Logger_init(void)
{
    m_log_file = NULL;
}


void dll_Logger_finalize(void)
{
    my_flush();
}


void dll_Logger_set_file(FILE* log_file)
{
    m_log_file = log_file;
}


FILE* dll_Logger_get_file(void)
{
    return m_log_file;
}


// private
static void my_flush(void)
{
    fflush(m_log_file);
}


/**********************************************************************
 * instance methods
 *
 **********************************************************************/


// public
dll_Logger* dll_Logger_create(const char* module)
{
    dll_Logger* new_logger = malloc(sizeof(dll_Logger));
    if (new_logger) {
        new_logger->module = module;
    }

    return new_logger;
}


void dll_Logger_destroy(dll_Logger** self)
{
    (*self)->module = NULL;
    free(*self);
    *self = NULL;
}


void dll_Logger_msg(dll_Logger* self, const char* msg)
{
    if (m_log_file) {
        dll_Logger_msg_impl(self, msg);
        my_flush();
    }
}


// private
static void dll_Logger_msg_impl(dll_Logger* self, const char* msg)
{
    fprintf(m_log_file, "%s: %s\n", self->module, msg);
}
