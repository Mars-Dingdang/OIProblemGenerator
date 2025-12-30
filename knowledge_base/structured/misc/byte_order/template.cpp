// Check little endian or big endian
bool is_little_endian() {
    int x = 1;
    return *(char*)&x == 1;
}

// Example: print bytes of an integer in memory order
void print_bytes(int value) {
    unsigned char* bytes = (unsigned char*)&value;
    int size = sizeof(value);
    for (int i = 0; i < size; ++i) {
        printf("%02x ", bytes[i]);
    }
    printf("\n");
}