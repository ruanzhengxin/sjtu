#include"employee.h"


int main()
{   salaried_employee salariedEmployee("John", "111111111", 800 );
    hourly_employee hourlyEmployee("Tom", "222222222", 16, 50 );
    commission_employee commissionEmployee("Sue", "333333333", 10000, 0.06 );
    base_salary_plus_commission_employee  basePlusCommissionEmployee("Bob", "444444444", 5000, .04, 300 );
    cout<<"姓名"<<"     "<<"身份证号"<<"    "<<"应发工资"<<endl;
    salariedEmployee.display();

    hourlyEmployee.display();

    commissionEmployee.display();

    basePlusCommissionEmployee.display();

    return 0;
}
