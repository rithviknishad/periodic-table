/*
==========================================================
NAME:			CDEF.H
AUTHOR:			RITHVIK NISHAD
ABOUT:			SmartCraft Creative - C Standard Definitions
Last Updated:	October 13, 2018
==========================================================
*/

#if !defined(__CDEF_H)
#define __CDEF_H

typedef signed char byte;
typedef signed char sbyte;
typedef unsigned char ubyte;

const double PI = 3.14159;

enum BOOL
{
    false = 0,
    true
};

typedef byte bool;

char *SapcedString(char *input)
{
    static char x = 0;
    static int outLen = 0;

    outLen = strlen(input) * 2;

    char *buffer = new char[outLen + 1];
    strcpy(buffer, "");

    for (x = 0; x < outLen && *(input + x) != '\0'; ++x)
    {
        *(buffer + (2 * x)) = *(input + x);
        *(buffer + (2 * x) + 1) = ' ';
    }
    *(buffer + (2 * x)) = '\0';

    return buffer;
}

#endif