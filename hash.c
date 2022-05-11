#include "./common.h"

size_t hash(size_t init_v, char data[], size_t length)
{
    size_t hash = init_v;
    int c;

    for (size_t i = 0; i < length; ++i) {
        hash = (c = *data++) + (hash << 6) + (hash << 16) - (uint32_t)hash;
    }

    return hash;
}
