#define NAME_LEN 1024
#define ADDRESS_LEN 1024
#define EMAIL_LEN 1024

struct Person
{
    int id;
    int number;
    int age;
    char name[NAME_LEN];
    char address[ADDRESS_LEN];
    char email[EMAIL_LEN];
};
