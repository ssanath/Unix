#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#define FILE_NAME "shared_file.txt"
#define SHARED_MEM_SIZE sizeof(int)
int main() {
int fd;
int *offset_ptr;
char *write_buffer = "This is written from the parent process.\n";
char read_buffer[100];
// Create/open the file with read/write permissions
fd = open(FILE_NAME, O_RDWR | O_CREAT, 0666);
if (fd == -1) {
perror("open");
exit(1);
}
// Create a shared memory segment
int shm_fd = shm_open("offset_shm", O_RDWR | O_CREAT, 0666);
if (shm_fd == -1) {
perror("shm_open");
exit(1);
}
// Set the size of the shared memory segment
ftruncate(shm_fd, SHARED_MEM_SIZE);
// Map the shared memory segment to the address space of this process
offset_ptr = mmap(NULL, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE,
MAP_SHARED, shm_fd, 0);
if (offset_ptr == MAP_FAILED) {
perror("mmap");
exit(1);
}
pid_t pid = fork();
if (pid < 0) {
perror("fork");
exit(1);
} else if (pid == 0) { // Child process
printf("Child process started.\n");
lseek(fd, *offset_ptr, SEEK_SET);
// Read from the file
int bytes_read = read(fd, read_buffer, sizeof(read_buffer));
if (bytes_read > 0) {
read_buffer[bytes_read] = '\0'; // Null-terminate the string
printf("Child process: Read %d bytes: %s\n", bytes_read, read_buffer);
} else {
perror("read");
}
// Update the offset with the current position in the file
*offset_ptr = lseek(fd, 0, SEEK_CUR);
printf("Child process finished.\n");
} else { // Parent process
printf("Parent process started.\n");
// Write to the file
write(fd, write_buffer, strlen(write_buffer));
// Update the offset with the current position in the file
*offset_ptr = lseek(fd, 0, SEEK_CUR);
printf("Parent process finished.\n");
}
// Unmap the shared memory segment
munmap(offset_ptr, SHARED_MEM_SIZE);
close(shm_fd);
// Close the file descriptor
close(fd);
return 0;
}
