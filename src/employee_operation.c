#include <stdio.h>
#include <string.h>
#include "../include/employee_operations.h"
#include "../include/file_handler.h"

Employee employees[100];
int empCount = 0;

void addEmployee() {
    Employee e;

    printf("Enter Employee ID: ");
    scanf("%d", &e.id);
    printf("Enter Name: ");
    scanf("%s", e.name);
    printf("Enter Age: ");
    scanf("%d", &e.age);
    printf("Enter Position: ");
    scanf("%s", e.position);
    printf("Enter Salary: ");
    scanf("%f", &e.salary);

    employees[empCount] = e;
    empCount++;

    saveEmployee(e);

    printf("Employee Added Successfully!\n");
}

void viewEmployees() {
    loadAllEmployees();
    printf("\n--- Employee List ---\n");
    for (int i = 0; i < empCount; i++) {
        printf("%d\t%s\t%d\t%s\t%.2f\n",
               employees[i].id,
               employees[i].name,
               employees[i].age,
               employees[i].position,
               employees[i].salary);
    }
}

void searchEmployee() {
    int id, found = 0;
    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    loadAllEmployees();

    for (int i = 0; i < empCount; i++) {
        if (employees[i].id == id) {
            printf("Record Found!\n");
            printf("%d %s %d %s %.2f\n",
                   employees[i].id,
                   employees[i].name,
                   employees[i].age,
                   employees[i].position,
                   employees[i].salary);
            found = 1;
            break;
        }
    }

    if (!found) printf("Employee not found!\n");
}

void updateEmployee() {
    int id, found = 0;
    printf("Enter Employee ID to update: ");
    scanf("%d", &id);

    loadAllEmployees();

    for (int i = 0; i < empCount; i++) {
        if (employees[i].id == id) {
            printf("Enter New Name: ");
            scanf("%s", employees[i].name);
            printf("Enter New Age: ");
            scanf("%d", &employees[i].age);
            printf("Enter New Position: ");
            scanf("%s", employees[i].position);
            printf("Enter New Salary: ");
            scanf("%f", &employees[i].salary);
            found = 1;
        }
    }

    rewriteEmployeeFile(employees, empCount);

    if (found)
        printf("Record Updated!\n");
    else
        printf("Employee not found!\n");
}

void deleteEmployee() {
    int id, found = 0;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    loadAllEmployees();

    int j = 0;
    Employee temp[100];

    for (int i = 0; i < empCount; i++) {
        if (employees[i].id != id) {
            temp[j++] = employees[i];
        } else {
            found = 1;
        }
    }

    empCount = j;
    rewriteEmployeeFile(temp, empCount);

    if (found)
        printf("Record Deleted!\n");
    else
        printf("Employee not found!\n");
}
