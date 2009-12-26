#include <cstring>

#include "ninjacexcept.h"

NinjacException::NinjacException (bool runtime, const char* msg, int line) {
    runt = runtime;
    l = line;
    strncpy(message, msg, sizeof(message));
    message[sizeof(message) - 1] = '\0';
}
