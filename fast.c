#include "./common.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s FILE\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_CREAT | O_RDWR, 0600);

    if (!fd) {
        perror("open");
        return 1;
    }

    struct stat s;
    size_t size = stat(argv[1], &s) ? 0 : s.st_size;

    if (!size) {
        if (errno) {
            perror("stat");
        } else {
            fprintf(stderr, "Error: empty file: %s\n", argv[1]);
        }
        return 1;
    }

    char* buffer = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);

    if (!buffer || (buffer == MAP_FAILED)) {
        perror("mmap");
        return 1;
    }

    size_t hval = hash(0, buffer, size);

    munmap(buffer, size);

    printf("Hash: %lx\n", (unsigned long)hval);

    close(fd);
    return 0;
}