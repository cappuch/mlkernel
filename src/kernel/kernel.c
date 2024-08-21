#include "system.h"


void kernel_main(void) 
{
    terminal_initialize();
    init_keyboard();
    terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
    char vendor[13];
    get_cpu_vendor(vendor);
    
    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK));
    terminal_writestring("CPU Info:\n");
    
    terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
    terminal_writestring("Vendor: ");
    terminal_writestring(vendor);
    terminal_writestring("\n");

    char buffer[32];

    int cores = get_cpu_cores();
    itoa(cores, buffer, 10);
    terminal_writestring("Cores: ");
    terminal_writestring(buffer);
    terminal_writestring("\n");
	terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
	terminal_writestring("====================================\n");
    terminal_writestring("testing input section: \n");

    while (1) {
        char c = keyboard_read();
        if (c != 0) {
            terminal_putchar(c);
        }
    }
}