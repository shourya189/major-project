#include <stdio.h>
#include "../include/file_handler.h"

void saveEmployee(Employee e) {
    FILE *fp = fopen("employees.txt", "a");
    fprintf(fp, "%d %s %d %s %.2f\n",
            e.id, e.name, e.age, e.position, e.salary);
    fclose(fp);
}

void loadAllEmployees() {
    FILE *fp = fopen("employees.txt", "r");
    empCount = 0;

    if (fp == NULL) return;

    while (fscanf(fp, "%d %s %d %s %f",
                  &employees[empCount].id,
                  employees[empCount].name,
                  &employees[empCount].age,
                  employees[empCount].position,
                  &employees[empCount].salary) != EOF)
    {
        empCount++;
    }

    fclose(fp);
}

void rewriteEmployeeFile(Employee employees[], int count) {
    FILE *fp = fopen("employees.txt", "w");

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %d %s %.2f\n",
                employees[i].id,
                employees[i].name,
                employees[i].age,
                employees[i].position,
                employees[i].salary);
    }

    fclose(fp);
}
