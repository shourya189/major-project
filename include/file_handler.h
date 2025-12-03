#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "employee.h"

void saveEmployee(Employee e);
void loadAllEmployees();
void rewriteEmployeeFile(Employee employees[], int count);

#endif
