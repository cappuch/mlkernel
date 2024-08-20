#include "system.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

static char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static char keyboard_map_shift[128] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0,
    '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static int shift_pressed = 0;
static int caps_lock = 0;

void init_keyboard(void) {
    outb(0x21, inb(0x21) & 0xFD);
}

char keyboard_read(void) {
    char c = 0;
    if (inb(KEYBOARD_STATUS_PORT) & 0x01) {
        unsigned char scancode = inb(KEYBOARD_DATA_PORT);
        if (scancode == 0x2A || scancode == 0x36) {
            shift_pressed = 1;
        } else if (scancode == 0xAA || scancode == 0xB6) {
            shift_pressed = 0;
        } else if (scancode == 0x3A) {
            caps_lock = !caps_lock;
        } else if (scancode == 0x4B) {
            return 'L'; // testing arrow keys
        } else if (scancode == 0x4D) {
            return 'R'; // testing arrow keys
        } else if (!(scancode & 0x80)) {
            if (shift_pressed || caps_lock) {
                c = keyboard_map_shift[scancode];
            } else {
                c = keyboard_map[scancode];
            }
            
            if (caps_lock && c >= 'a' && c <= 'z') {
                c -= 32; // handling uppercase
            }
        }
    }
    return c;
}

void outb(uint16_t port, uint8_t val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}