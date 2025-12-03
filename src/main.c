#include <stdio.h>
#include <stdlib.h>
#include "../include/employee_operations.h"

int main() {
    int choice;

    while (1) {
        printf("\n----- Employee Management System -----\n");
        printf("1. Add Employee\n");
        printf("2. View Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee\n");
        printf("5. Delete Employee\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: viewEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: updateEmployee(); break;
            case 5: deleteEmployee(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}
