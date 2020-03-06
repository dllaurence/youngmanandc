// New school
#pragma once
//
// Old school
//#ifndef LOGGER_H
//#define LOGGER_H


#include <stdio.h>
#include <assert.h>


// forward declare object struct
typedef struct dll_Logger dll_Logger;


// Class functions
void dll_Logger_init(void);
void dll_Logger_finalize(void);
void dll_Logger_set_file(FILE* log_file);
FILE* dll_Logger_get_file(void);

// factory
dll_Logger* dll_Logger_create(const char* module);

// Methods
void dll_Logger_destroy(dll_Logger** self);
void dll_Logger_msg(dll_Logger* self, const char* msg);


// Old school
//#endif // ifndef LOGGER_H
