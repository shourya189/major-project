#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMPLOYEES 200
#define FILENAME "employees.txt"

// Employee structure
typedef struct {
    int id;
    char name[50];
    int age;
    char position[50];
    char description[200];
} Employee;

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

/* ------------------------------------------
    UTILITY FUNCTIONS
-------------------------------------------*/

// Remove newline after fgets
void trimNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

/* ------------------------------------------
    FILE HANDLING
-------------------------------------------*/

void loadFromFile() {
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) {
        printf("No existing data found. Starting fresh.\n");
        return;
    }

    employeeCount = 0;

    while (fscanf(fp, "%d|%49[^|]|%d|%49[^|]|%199[^\n]\n",
                  &employees[employeeCount].id,
                  employees[employeeCount].name,
                  &employees[employeeCount].age,
                  employees[employeeCount].position,
                  employees[employeeCount].description) == 5) 
    {
        employeeCount++;
    }

    fclose(fp);
}

void saveToFile() {
    FILE *fp = fopen(FILENAME, "w");
    if (!fp) {
        printf("Error saving file!\n");
        return;
    }

    for (int i = 0; i < employeeCount; i++) {
        fprintf(fp, "%d|%s|%d|%s|%s\n",
                employees[i].id,
                employees[i].name,
                employees[i].age,
                employees[i].position,
                employees[i].description);
    }

    fclose(fp);
}

/* ------------------------------------------
    ADD EMPLOYEE
-------------------------------------------*/

void addEmployee() {
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Cannot add more employees.\n");
        return;
    }

    Employee e;

    printf("Enter Employee ID: ");
    scanf("%d", &e.id);
    getchar();  // clear newline

    printf("Enter Name: ");
    fgets(e.name, sizeof(e.name), stdin);
    trimNewline(e.name);

    printf("Enter Age: ");
    scanf("%d", &e.age);
    getchar();

    printf("Enter Position: ");
    fgets(e.position, sizeof(e.position), stdin);
    trimNewline(e.position);

    printf("Enter Description: ");
    fgets(e.description, sizeof(e.description), stdin);
    trimNewline(e.description);

    employees[employeeCount++] = e;
    saveToFile();

    printf("\nEmployee added successfully!\n");
}

/* ------------------------------------------
    DISPLAY ALL EMPLOYEES
-------------------------------------------*/

void displayEmployees() {
    if (employeeCount == 0) {
        printf("\nNo employees found.\n");
        return;
    }

    printf("\n---- EMPLOYEE LIST ----\n");
    for (int i = 0; i < employeeCount; i++) {
        printf("\nEmployee %d:\n", i + 1);
        printf("ID: %d\n", employees[i].id);
        printf("Name: %s\n", employees[i].name);
        printf("Age: %d\n", employees[i].age);
        printf("Position: %s\n", employees[i].position);
        printf("Description: %s\n", employees[i].description);
    }
}

/* ------------------------------------------
    SEARCH EMPLOYEE BY ID OR NAME
-------------------------------------------*/

void searchEmployee() {
    if (employeeCount == 0) {
        printf("No employees to search.\n");
        return;
    }

    char search[50];
    int id;

    printf("\nSearch by:\n1. ID\n2. Name\nChoose: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        printf("Enter Employee ID: ");
        scanf("%d", &id);

        for (int i = 0; i < employeeCount; i++) {
            if (employees[i].id == id) {
                printf("\nEmployee Found:\n");
                printf("ID: %d\nName: %s\nAge: %d\nPosition: %s\nDescription: %s\n",
                       employees[i].id, employees[i].name, employees[i].age,
                       employees[i].position, employees[i].description);
                return;
            }
        }
        printf("Employee not found.\n");

    } else if (choice == 2) {

        printf("Enter Name: ");
        fgets(search, sizeof(search), stdin);
        trimNewline(search);

        for (int i = 0; i < employeeCount; i++) {
            if (strcasecmp(employees[i].name, search) == 0) {
                printf("\nEmployee Found:\n");
                printf("ID: %d\nName: %s\nAge: %d\nPosition: %s\nDescription: %s\n",
                       employees[i].id, employees[i].name, employees[i].age,
                       employees[i].position, employees[i].description);
                return;
            }
        }
        printf("Employee not found.\n");

    } else {
        printf("Invalid choice.\n");
    }
}

/* ------------------------------------------
    DELETE EMPLOYEE BY ID
-------------------------------------------*/

void deleteEmployee() {
    if (employeeCount == 0) {
        printf("No employees to delete.\n");
        return;
    }

    int id;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {

            for (int j = i; j < employeeCount - 1; j++) {
                employees[j] = employees[j + 1];
            }

            employeeCount--;
            saveToFile();

            printf("Employee deleted successfully.\n");
            return;
        }
    }

    printf("Employee not found.\n");
}

/* ------------------------------------------
    UPDATE EMPLOYEE DETAILS
-------------------------------------------*/

void updateEmployee() {
    if (employeeCount == 0) {
        printf("No employees available.\n");
        return;
    }

    int id;
    printf("Enter Employee ID to update: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            
            printf("Enter New Name: ");
            fgets(employees[i].name, sizeof(employees[i].name), stdin);
            trimNewline(employees[i].name);

            printf("Enter New Age: ");
            scanf("%d", &employees[i].age);
            getchar();

            printf("Enter New Position: ");
            fgets(employees[i].position, sizeof(employees[i].position), stdin);
            trimNewline(employees[i].position);

            printf("Enter New Description: ");
            fgets(employees[i].description, sizeof(employees[i].description), stdin);
            trimNewline(employees[i].description);

            saveToFile();
            printf("Employee updated successfully.\n");
            return;
        }
    }

    printf("Employee not found.\n");
}

/* ------------------------------------------
    MAIN MENU
-------------------------------------------*/

int main() {
    int choice;

    loadFromFile();

    do {
        printf("\n\n------ EMPLOYEE MANAGEMENT SYSTEM ------\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Update Employee\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: deleteEmployee(); break;
            case 5: updateEmployee(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}
