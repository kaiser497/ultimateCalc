#include <iostream>
#include <cmath>


char operand;
double num1;
double num2;

double checkOperandandCalculate() {
    switch (operand) {
        case '+': 
            return num1 + num2;
        
        case '-': 
            return num1 - num2;
        
        case '*':
            return num1 * num2;
       
        case '/': 
            if (num2 != 0) {
                return (double)num1 / num2;
            }
            else {
                std::cout << "Error Division By Zero!\n";
            }
        
        case '^':
            return  pow(num1, num2);

        case '@':
            return pow(num1, 1/num2);

        case '#':
            return sqrt(num1);

        default:
        std::cout << "Invalid operator\n";
        return 0;
    }
}

int main() {
    std::cout << "Enter number 1: ";
    std::cin >> num1;

    std::cout << "Enter operator (+(add) -(multiply) *-multiply /-division ^-power @-root #-root2 of num1):\n ";
    std::cin >> operand;

    std::cout << "Enter number 2: ";
    std::cin >> num2;

    std::cout << "Result: " << checkOperandandCalculate();

    return 0;
}
