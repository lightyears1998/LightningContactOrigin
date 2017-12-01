#include "core.h"
#include "interface.h"
#include "contact.h"
#include <stdbool.h>

void call_module(int);

int main(void)
{
    init();
    while (true)
    {
        display_main_menu();
        call_module(limited_input('0', '7') - '0');
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
        case 5: modify_record(); break;
        case 6: save_record(); break;
        case 7: sort_record(); break;
    }
}
