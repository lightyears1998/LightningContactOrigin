#include "core.h"
#include "interface.h"
#include "contact.h"
#include <stdbool.h>

void call_module(int);

int main(void)
{
    int input;
    while (true)
    {
        display_main_menu();
        input = limited_input('0', '7');
        call_module(input - '0');
    }
    return 0;
}

void call_module(int idx)
{
    clear_display();
    switch (idx)
    {
        case 0: goodbye(); break;
        case 1: add_record(); break;
        case 2: show_record(); break;
        case 3: delete_record(); break;
        case 4: query_record(); break;
        case 5: save_record(); break;
        case 6: sort_record(); break;
    }
}
