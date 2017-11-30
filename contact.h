#define NAME_LEN 1024
#define ADDRESS_LEN 1024
#define EMAIL_LEN 1024

struct Person
{
    int id;
    char name[NAME_LEN];
    int age;
    int number;
    char email[EMAIL_LEN];
    char address[ADDRESS_LEN];
};
