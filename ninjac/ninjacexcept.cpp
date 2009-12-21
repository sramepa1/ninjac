#include <cstring>

#include "ninjacexcept.h"

NinjacException::NinjacException (bool runtime, const char* msg, int line, int column) {
    runt = runtime;
    l = line;
    c = column;
    strncpy(message, msg, sizeof(message));
    message[sizeof(message) - 1] = '\0';
}
