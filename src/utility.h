#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum boolean {
    FALSE = 0,
    TRUE
} Boolean;

typedef enum {
    ALLOCATE,
    DEALLOCATE
} Step;

#define NEW_LINE_SPACE 1
#define NULL_SPACE 1
#define NAME_LENGTH 256

/**
 * This is used to compensate for the extra character spaces taken up by
 * the '\n' and '\0' when input is read through fgets().
 **/
#define EXTRA_SPACES (NEW_LINE_SPACE + NULL_SPACE)

#define EMPTY_STRING ""

#endif