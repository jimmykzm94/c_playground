/*
Custom printf implementation using custom format specifiers:
- %uint8 : unsigned 8-bit integer
- %int8  : signed 8-bit integer
- %uint16: unsigned 16-bit integer
- %int16 : signed 16-bit integer
- %uint32: unsigned 32-bit integer
- %int32 : signed 32-bit integer
- %f     : float with 6 decimal places

double, uint64, int64 are not supported in this implementation to keep my code simple.
*/

// Header files
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

// Helper function to convert integer to string
void itoa(int64_t value, char *buffer, int *length)
{
    int i = 0;
    if (value == 0) {
        buffer[i++] = '0';
    } else {
        int is_negative = 0;
        if (value < 0) {
            is_negative = 1;
            value = -value;
        }
        while (value > 0) {
            buffer[i++] = (value % 10) + '0';
            value /= 10;
        }
        if (is_negative) {
            buffer[i++] = '-';
        }
        // reverse the string
        for (int j = 0; j < i / 2; j++) {
            char temp = buffer[j];
            buffer[j] = buffer[i - j - 1];
            buffer[i - j - 1] = temp;
        }
    }
    *length = i;
}

// Function to print float with 6 decimal places
void print_float(float x)
{
    int sign = (x > 0) ? 1 : -1;
    int round = (int)x;
    int frac = (int)(sign * x * 1000) - sign * round * 1000;
    //printf("%d.%03d000\n", round, frac); // mimic 6 decimal places from printf
    char buffer[32];
    int len = 0;
    itoa(round, buffer, &len);
    write(STDOUT_FILENO, buffer, len);
    write(STDOUT_FILENO, ".", 1);
    itoa(frac, buffer, &len);
    // pad leading zeros if necessary, 
    if (frac < 100) {
        write(STDOUT_FILENO, "0", 1);
        if (frac < 10) {
            write(STDOUT_FILENO, "0", 1);
        }
    }
    write(STDOUT_FILENO, buffer, len);
    write(STDOUT_FILENO, "000", 3);
}

// Function to print integer based on size and sign
void print_integer(void *ptr, size_t size, int is_signed)
{
    char buffer[32];
    int len = 0;
    if (is_signed) {
        if (size == 1) {
            int8_t val = *(int8_t *)ptr;
            itoa(val, buffer, &len);
        } else if (size == 2) {
            int16_t val = *(int16_t *)ptr;
            itoa(val, buffer, &len);
        } else if (size == 4) {
            int32_t val = *(int32_t *)ptr;
            itoa(val, buffer, &len);
        }
    } else {
        if (size == 1) {
            uint8_t val = *(uint8_t *)ptr;
            itoa(val, buffer, &len);
        } else if (size == 2) {
            uint16_t val = *(uint16_t *)ptr;
            itoa(val, buffer, &len);
        } else if (size == 4) {
            uint32_t val = *(uint32_t *)ptr;
            itoa(val, buffer, &len);
        }
    }
    write(STDOUT_FILENO, buffer, len);
}

// Custom printf function
void custom_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    const char *p = format;

    while (*p) {
        if (*p == '%') {
            p++;
            if (strncmp(p, "uint8", 5) == 0) {
                uint8_t val = (uint8_t)va_arg(args, int);
                print_integer(&val, sizeof(uint8_t), 0);
                p += 5;
            } else if (strncmp(p, "int8", 4) == 0) {
                int8_t val = (int8_t)va_arg(args, int);
                print_integer(&val, sizeof(int8_t), 1);
                p += 4;
            } else if (strncmp(p, "uint16", 6) == 0) {
                uint16_t val = (uint16_t)va_arg(args, unsigned int);
                print_integer(&val, sizeof(uint16_t), 0);
                p += 6;
            } else if (strncmp(p, "int16", 5) == 0) {
                int16_t val = (int16_t)va_arg(args, int);
                print_integer(&val, sizeof(int16_t), 1);
                p += 5;
            } else if (strncmp(p, "uint32", 6) == 0) {
                uint32_t val = va_arg(args, uint32_t);
                print_integer(&val, sizeof(uint32_t), 0);
                p += 6;
            } else if (strncmp(p, "int32", 5) == 0) {
                int32_t val = va_arg(args, int32_t);
                print_integer(&val, sizeof(int32_t), 1);
                p += 5;
            } else if (*p == 'f') {
                float val = (float)va_arg(args, double);
                print_float(val);
                p++;
            } else {
                write(STDOUT_FILENO, "%", 1);
                continue;
            }
        } else {
            write(STDOUT_FILENO, p, 1);
            p++;
        }
    }
    va_end(args);
}

int main() {
    uint8_t u8 = 255;
    int16_t i16 = -32768;
    uint32_t u32 = 4294967295;
    float f = 3;
    custom_printf("uint8: %uint8\n", u8);
    custom_printf("int16: %int16\n", i16);
    custom_printf("uint32: %uint32\n", u32);
    custom_printf("float: %f\n", f);
    custom_printf("unknown specifier will be treated as text: %hello\n");
    return 0;
}