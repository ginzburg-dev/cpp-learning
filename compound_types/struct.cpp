#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

struct Computer
{
    int processor;    // 0 by default
    int ram { 32 };   // 32 by default
    double price {};  // 0 by default
};

std::ostream& operator<<(std::ostream& out, const Computer& computer)
{
    out << "processor: " << computer.processor << " RAM: " << computer.ram << " price: " << computer.price;
    return out;
}

std::ostream& operator<<(std::ostream& out, const Employee& employee)
{
    out << "id: " << employee.id << " age: " << employee.age << " wage: " << employee.wage;
    return out;
}

int main()
{
    Employee joe { 14, 32, 60000.0 }; // list initialization using braced list (preferred)

    Computer computer {};
    std::cout << computer << '\n';

    const Employee constEmployee {18, 21, 35000.0};

    Employee e1 { .age{ 30 }, .id{ 19 }, .wage{ 60000.0 } }; // C++20
    Employee e2 { .age = 30, .id = 19, .wage = 60000.0 }; // C++20

    e1 = { 31, 19, 61000.0 };
    e2 = {.age = 30, .id = 20, .wage = e2.wage };
    std::cout << e2 << '\n'; 

    Employee a1 = e2; // copy-initialization
    Employee a2(e2);  // direct-initialization
    Employee a3 {e2}; // direct-list-initialization

    Employee frank {};
    frank.id = 15;
    frank.age = 28;
    frank.wage = 45000.0;

    int totalAge { joe.age + frank.age };
    std::cout << "Joe and Frank have lived " << totalAge << " total years\n";

    if (joe.wage > frank.wage)
        std::cout << "Joe makes more than Frank\n";
    else if (joe.wage > frank.wage)
        std::cout << "Frank makes more than Joe\n";
    else
        std::cout << "Joe and Frank make the same amount\n";

    // Frank got a promotion
    frank.wage += 5000.0;

    // Today is Joe's birthday
    ++joe.age;

    return 0;
}
