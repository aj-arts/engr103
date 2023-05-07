#include <stdio.h>


typedef struct {
    char name[20];
    int age;
    float salary;
} Employee;

int main(){
    Employee* e = {"John Smith", 30, 5000.0};
    // printf("Name: %s, Salary: %.2f\n", e.name, e.salary);
    printf("Name: %s, Salary: %.2f\n", e->name, e->salary);
    // printf("Name: %s, Salary: %.2f\n", (*e).name, (*e).salary);
    // printf("Name: %s, Salary: %.2f\n", e[name], e[salary]);
    return 0;
}