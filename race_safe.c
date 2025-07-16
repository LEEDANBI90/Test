#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int safe_open(const char *pathname, int flags) {
    struct stat st1, st2;
    int fd;
    
    if (lstat(pathname, &st1) == -1) {
        return -1;
    }
    
    if (S_ISLNK(st1.st_mode)) {
        errno = ELOOP;
        return -1;
    }
    
    fd = open(pathname, flags | O_CREAT, 0600);
    if (fd == -1) {
        return -1;
    }
    
    if (fstat(fd, &st2) == -1) {
        close(fd);
        return -1;
    }
    
    if (st1.st_ino != st2.st_ino || st1.st_dev != st2.st_dev) {
        close(fd);
        errno = EAGAIN;
        return -1;
    }
    
    if (!S_ISREG(st2.st_mode)) {
        close(fd);
        errno = EISDIR;
        return -1;
    }
    
    return fd;
}

int main() {
    char *filename = "/tmp/racefile_safe";
    
    printf("Safe file creation...\n");
    
    int fd = safe_open(filename, O_WRONLY | O_CREAT);
    if (fd == -1) {
        perror("Safe open failed");
        return 1;
    }
    
    write(fd, "Safe data: password123\n", 23);
    close(fd);
    
    printf("Safe file created successfully!\n");
    return 0;
}
