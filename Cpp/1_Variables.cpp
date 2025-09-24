#include <iostream>   // Needed for input/output
#include <string>     // Needed for using std::string

int main() {

    // ===============================
    // 1) Integer (whole numbers)
    // ===============================
    int age = 21;        // Example: someone's age
    int year = 2023;     // Example: current year
    int days = 7;        // Example: number of days in a week

    // ===============================
    // 2) Double (decimal numbers)
    // ===============================
    double price = 10.99;     // Example: price of an item
    double gpa = 2.5;         // Example: Grade Point Average
    double temperature = 25.1; // Example: room temperature

    // ===============================
    // 3) Char (single character)
    // ===============================
    char grade = 'A';     // Example: letter grade
    char initial = 'C';   // Example: first letter of a name
    char currency = '$';  // Example: currency symbol

    // ===============================
    // 4) Boolean (true or false)
    // ===============================
    bool student = false;   // Example: is the person a student?
    bool power = true;      // Example: is the power ON?
    bool forSale = true;    // Example: is the item for sale?

    // ===============================
    // 5) String (text / sequence of characters)
    // ===============================
    std::string name = "Bro";         // Example: person's name
    std::string day = "Friday";       // Example: day of the week
    std::string food = "pizza";       // Example: favorite food
    std::string address = "123 Fake St."; // Example: address

    // ===============================
    // OUTPUT (printing variables)
    // ===============================
    std::cout << "Hello " << name << '\n';
    std::cout << "You are " << age << " years old\n";

    return 0;   // End of program
}
