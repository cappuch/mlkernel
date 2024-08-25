#include "system.h"

#define MAX_COMMAND_LENGTH 256

void execute_command(const char* command) { // i will make it so each command is it's own thing
    if (strcmp(command, "help") == 0) {
        terminal_writestring("commands:\n");
        terminal_writestring("  help - help lol\n");
        terminal_writestring("  clear - cls or clear\n");
        terminal_writestring("  cpuinfo - display primitive CPU info\n");
        terminal_writestring("  meminfo - display memory information\n");
    } else if (strcmp(command, "clear") == 0) {
        terminal_initialize();
    } else if (strcmp(command, "cpuinfo") == 0) {
        char vendor[13];
        get_cpu_vendor(vendor);
        terminal_writestring("CPU Vendor: ");
        terminal_writestring(vendor);
        terminal_writestring("\n");

        char buffer[32];
        int cores = get_cpu_cores();
        itoa(cores, buffer, 10);
        terminal_writestring("CPU Cores: ");
        terminal_writestring(buffer);
        terminal_writestring("\n");
    } else if (strcmp(command, "meminfo") == 0) {
        uint64_t total_ram = get_ram_amount();
        uint64_t used_ram = get_used_memory();
        
        char buffer[32];
        
        terminal_writestring("Total RAM: ");
        itoa(total_ram / 1024 / 1024, buffer, 10);
        terminal_writestring(buffer);
        terminal_writestring(" MB\n");
        
        terminal_writestring("Used RAM: ");
        itoa(used_ram / 1024, buffer, 10);
        terminal_writestring(buffer);
        terminal_writestring(" KB\n");
        
        uint64_t free_ram = total_ram - used_ram;
        terminal_writestring("Free RAM: ");
        itoa(free_ram / 1024 / 1024, buffer, 10);
        terminal_writestring(buffer);
        terminal_writestring(" MB\n");
    } else {
        terminal_writestring("unk: ");
        terminal_writestring(command);
        terminal_writestring("\n");
    }
}

void kernel_main(void) 
{
    terminal_initialize();
    init_keyboard();
    terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));

    terminal_writestring("help for commands lol\n");

    char command[MAX_COMMAND_LENGTH] = {0};
    int command_index = 0;

    while (1) {
        terminal_writestring("> ");
        command_index = 0;

        while (1) {
            char c = keyboard_read();
            if (c != 0) {
                if (c == '\n') {
                    terminal_putchar(c);
                    command[command_index] = '\0';
                    execute_command(command);
                    break;
                } else if (c == '\b' && command_index > 0) {
                    command_index--;
                    terminal_putchar(c);
                    terminal_putchar(' ');
                    terminal_putchar(c);
                } else if (command_index < MAX_COMMAND_LENGTH - 1) {
                    command[command_index++] = c;
                    terminal_putchar(c);
                }
            }
        }
    }
}