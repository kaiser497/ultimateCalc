#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <map>

using namespace std;

// Constants
const double PI = 3.14159265358979323846;
const double E = 2.71828182845904523536;

// Scientific Calculator Class
class ScientificCalculator {
private:
    map<string, double> variables;
    vector<string> history;

    void addToHistory(const string& operation, double result) {
        stringstream ss;
        ss << fixed << setprecision(6) << operation << " = " << result;
        history.push_back(ss.str());
        if (history.size() > 10) history.erase(history.begin());
    }

    double parseExpression(const string& expr) {
        try {
            size_t pos;
            double value = stod(expr, &pos);
            if (pos < expr.length()) {
                string remaining = expr.substr(pos);
                if (remaining == "pi") return value * PI;
                if (remaining == "e") return value * E;
                if (variables.find(remaining) != variables.end()) return value * variables[remaining];
            }
            return value;
        }
        catch (...) {
            return 0;
        }
    }

public:
    ScientificCalculator() {
        variables["pi"] = PI;
        variables["e"] = E;
    }

    double calculate(double num1, double num2, char op) {
        double result = 0;
        string operation;

        switch (op) {
        case '+':
            result = num1 + num2;
            operation = to_string(num1) + " + " + to_string(num2);
            break;

        case '-':
            result = num1 - num2;
            operation = to_string(num1) + " - " + to_string(num2);
            break;

        case '*':
            result = num1 * num2;
            operation = to_string(num1) + " * " + to_string(num2);
            break;

        case '/':
            if (fabs(num2) < 1e-15) {
                throw runtime_error("Division by zero error!");
            }
            result = num1 / num2;
            operation = to_string(num1) + " / " + to_string(num2);
            break;

        case '^':
            if (num1 < 0 && fmod(num2, 1) != 0) {
                throw runtime_error("Cannot raise negative number to fractional power!");
            }
            result = pow(num1, num2);
            operation = to_string(num1) + "^" + to_string(num2);
            break;

        case 'r': // Root (nth root)
            if (num1 < 0 && fmod(num2, 2) == 0) {
                throw runtime_error("Even root of negative number!");
            }
            result = pow(num1, 1.0 / num2);
            operation = to_string(num2) + "?" + to_string(num1);
            break;

        case 'l': // Logarithm
            if (num1 <= 0) throw runtime_error("Logarithm of non-positive number!");
            result = log(num1) / log(num2);
            operation = "log_" + to_string(num2) + "(" + to_string(num1) + ")";
            break;

        case '%':
            result = fmod(num1, num2);
            operation = to_string(num1) + " % " + to_string(num2);
            break;

        case 'C': // Combination
            if (num1 < num2 || num1 < 0 || num2 < 0)
                throw runtime_error("Invalid combination values!");
            result = tgamma(num1 + 1) / (tgamma(num2 + 1) * tgamma(num1 - num2 + 1));
            operation = "C(" + to_string((int)num1) + "," + to_string((int)num2) + ")";
            break;

        default:
            throw runtime_error("Unknown operator!");
        }

        addToHistory(operation, result);
        return result;
    }

    double scientificFunction(double num, const string& func) {
        double result = 0;

        if (func == "sin") result = sin(num * PI / 180.0);
        else if (func == "cos") result = cos(num * PI / 180.0);
        else if (func == "tan") {
            if (fmod(fabs(num), 180.0) == 90.0)
                throw runtime_error("Tangent undefined!");
            result = tan(num * PI / 180.0);
        }
        else if (func == "asin") {
            if (num < -1 || num > 1) throw runtime_error("Invalid domain for asin!");
            result = asin(num) * 180.0 / PI;
        }
        else if (func == "acos") {
            if (num < -1 || num > 1) throw runtime_error("Invalid domain for acos!");
            result = acos(num) * 180.0 / PI;
        }
        else if (func == "atan") result = atan(num) * 180.0 / PI;
        else if (func == "sinh") result = sinh(num);
        else if (func == "cosh") result = cosh(num);
        else if (func == "tanh") result = tanh(num);
        else if (func == "log") {
            if (num <= 0) throw runtime_error("Log of non-positive number!");
            result = log10(num);
        }
        else if (func == "ln") {
            if (num <= 0) throw runtime_error("Ln of non-positive number!");
            result = log(num);
        }
        else if (func == "exp") result = exp(num);
        else if (func == "sqrt") {
            if (num < 0) throw runtime_error("Square root of negative number!");
            result = sqrt(num);
        }
        else if (func == "cbrt") result = cbrt(num);
        else if (func == "abs") result = fabs(num);
        else if (func == "floor") result = floor(num);
        else if (func == "ceil") result = ceil(num);
        else if (func == "round") result = round(num);
        else if (func == "fact") {
            if (num < 0 || fmod(num, 1) != 0)
                throw runtime_error("Invalid factorial input!");
            result = tgamma(num + 1);
        }
        else if (func == "rad") result = num * PI / 180.0;
        else if (func == "deg") result = num * 180.0 / PI;
        else throw runtime_error("Unknown function!");

        addToHistory(func + "(" + to_string(num) + ")", result);
        return result;
    }

    void displayHistory() {
        cout << "\n=== Calculation History ===\n";
        for (size_t i = 0; i < history.size(); ++i) {
            cout << i + 1 << ". " << history[i] << endl;
        }
        cout << "==========================\n";
    }

    void setVariable(const string& name, double value) {
        variables[name] = value;
        cout << "Variable " << name << " set to " << value << endl;
    }

    void showVariables() {
        cout << "\n=== Variables ===\n";
        for (const auto& [name, value] : variables) {
            cout << name << " = " << value << endl;
        }
        cout << "================\n";
    }

    void clearHistory() {
        history.clear();
        cout << "History cleared!\n";
    }
};

void displayMenu() {
    cout << "\n=== ADVANCED SCIENTIFIC CALCULATOR ===\n";
    cout << "Basic Operations: +  -  *  /  ^  r(root)  %  C(combination)\n";
    cout << "Scientific Functions:\n";
    cout << "  Trigonometric: sin, cos, tan, asin, acos, atan\n";
    cout << "  Hyperbolic: sinh, cosh, tanh\n";
    cout << "  Logarithmic: log, ln\n";
    cout << "  Exponential: exp\n";
    cout << "  Roots: sqrt, cbrt\n";
    cout << "  Rounding: floor, ceil, round, abs\n";
    cout << "  Other: fact(factorial), rad(to radians), deg(to degrees)\n";
    cout << "Calculator Commands: history, clear, vars, set, quit\n";
    cout << "=======================================\n";
}

int main() {
    ScientificCalculator calc;
    string input;
    double num1, num2, result;
    char op;

    cout << fixed << setprecision(10);

    while (true) {
        displayMenu();
        cout << "\nSelect mode (basic/scientific/command): ";
        cin >> input;

        if (input == "quit") break;

        if (input == "basic") {
            try {
                cout << "Enter expression (num1 op num2): ";
                if (!(cin >> num1 >> op >> num2)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input!\n";
                    continue;
                }

                result = calc.calculate(num1, num2, op);
                cout << "Result: " << result << endl;

            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }

        }
        else if (input == "scientific") {
            try {
                string func;
                cout << "Enter function and value: ";
                cin >> func >> num1;

                transform(func.begin(), func.end(), func.begin(), ::tolower);
                result = calc.scientificFunction(num1, func);
                cout << "Result: " << result << endl;

            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }

        }
        else if (input == "history") {
            calc.displayHistory();

        }
        else if (input == "clear") {
            calc.clearHistory();

        }
        else if (input == "vars") {
            calc.showVariables();

        }
        else if (input == "set") {
            string varName;
            double value;
            cout << "Enter variable name and value: ";
            cin >> varName >> value;
            calc.setVariable(varName, value);

        }
        else {
            cout << "Unknown command!\n";
        }

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "\nThank you for using Advanced Scientific Calculator!\n";
    return 0;
}