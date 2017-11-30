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
    switch (idx)
    {
        case 0: goodbye();
        case 1: add_record();
        case 2: show_record();
        case 3: delete_record();
        case 4: query_record();
        case 5: save_record();
        case 6: sort_record();
    }
}
