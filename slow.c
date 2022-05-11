#include "./common.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s FILE\n", argv[0]);
        return 1;
    }

    FILE* fp = fopen(argv[1], "r");

    if (!fp) {
        perror("fopen");
        return 1;
    }

    char buffer[4096] = { 0 };

    int read_size = 0;

    size_t hval = 0;

    do {
        read_size = fread(buffer, sizeof(*buffer), sizeof(buffer), fp);
        hval = hash(hval, buffer, read_size);
    } while (read_size);

    printf("Hash: %lx\n", (unsigned long)hval);

    fclose(fp);
    return 0;
}