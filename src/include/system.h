#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// might be some nice ways of doing such
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
	VGA_COLOR_YELLOW = 14,
};

void get_cpu_vendor(char *vendor);
int get_cpu_cores(void);
int get_cpu_threads(void);
uint64_t get_cpu_frequency(void);
uint64_t get_ram_amount(void);
void cpuid(int code, uint32_t *a, uint32_t *d);

void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_writestring(const char* data);
void terminal_putchar(char c);
uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);

void set_graphics_mode();
void set_text_mode();
void draw_pixel(int x, int y, uint8_t color);
void draw_line(int x1, int y1, int x2, int y2, uint8_t color);
void clear_screen(uint8_t color);

void init_keyboard(void);
char keyboard_read(void);
void update_cursor(int x, int y);


size_t strlen(const char* str);
char* itoa(int num, char* str, int base);

#endif