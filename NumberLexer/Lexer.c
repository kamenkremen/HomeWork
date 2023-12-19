#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "lexer.h"

enum Types
{
    digit,
    dot,
    e,
    end,
    plusOrMinus,
    undefined,
};

enum States
{
    firstDigits,
    afterDot,
    afterDotAndDigit,
    afterE,
    afterPlusOrMinus,

};

static int symbolType(const char symbol)
{
    if (symbol >= '0' && symbol <= '9')
    {
        return digit;
    }
    if (symbol == '.')
    {
        return dot;
    }
    if (symbol == 'E')
    {
        return e;
    }
    if (symbol == '\0')
    {
        return end;
    }
    if (symbol == '+' || symbol == '-')
    {
        return plusOrMinus;
    }
    return undefined;
}

static void nextSymbol(const char* const string, char* const symbol, size_t* const index)
{
    ++(*index);
    if (*index >= strlen(string))
    {
        *symbol = '\0';
        return;
    }
    *symbol = string[*index];
}

bool isNumber(const char* const string)
{
    if (string == NULL)
    {
        return true;
    }
    size_t index = 0;
    char symbol = string[index];
    int state = firstDigits;
    while (1)
    {
        switch (state)
        {
        case firstDigits:
            switch(symbolType(symbol))
            {
            case digit:
                nextSymbol(string, &symbol, &index);
                break;
            case dot:
                state = afterDot;
                nextSymbol(string, &symbol, &index);
                break;
            case e:
                state = afterE;
                nextSymbol(string, &symbol, &index);
                break;
            case end:
                return true;
            default:
                return false;
            }
            break;
        case afterDot:
            switch (symbolType(symbol))
            {
            case digit:
                nextSymbol(string, &symbol, &index);
                state = afterDotAndDigit;
                break;
            default:
                return false;
            }
            break;
        case afterDotAndDigit:
            switch (symbolType(symbol))
            {
            case digit:
                nextSymbol(string, &symbol, &index);
                break;
            case e:
                state = afterE;
                nextSymbol(string, &symbol, &index);
                break;
            case end:
                return true;
            default:
                return false;
            }
            break;
        case afterE:
            switch (symbolType(symbol))
            {
            case plusOrMinus:
                state = afterPlusOrMinus;
                nextSymbol(string, &symbol, &index);
                break;
            default:
                return false;
            }
            break;
        case afterPlusOrMinus:
            switch (symbolType(symbol))
            {
            case digit:
                nextSymbol(string, &symbol, &index);
                break;
            case end:
                return true;
            default:
                return false;
            }
            break;
        default:
            return false;
        }
    }
}
