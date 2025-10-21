#include <cstdlib>
#include <iostream>

double Add(double a, double b) { return a + b; }

double Subtract(double a, double b) { return a - b; }

double Multiply(double a, double b) { return a * b; }

double Divide(double a, double b) {
  if (b == 0.0) {
    std::cerr << "Error: Cannot divide by zero. Exiting.\n";
    std::exit(EXIT_FAILURE);
  }
  return a / b;
}

int main() {
  double first_number{};
  double second_number{};
  char operation{};
  double result{};

  std::cout << "Enter First Number: ";
  if (!(std::cin >> first_number)) {
    std::cerr << "Error: Invalid number input.\n";
    return 1;
  }

  std::cout << "Enter Second Number: ";
  if (!(std::cin >> second_number)) {
    std::cerr << "Error: Invalid number input.\n";
    return 1;
  }

  std::cout << "Choose your operator [+, -, *, /]: ";
  if (!(std::cin >> operation)) {
    std::cerr
        << "Error: Invalid character input. Must be one of the operators.\n";
    return 1;
  }

  switch (operation) {
    case '+':
      result = Add(first_number, second_number);
      break;
    case '-':
      result = Subtract(first_number, second_number);
      break;
    case '*':
      result = Multiply(first_number, second_number);
      break;
    case '/':
      result = Divide(first_number, second_number);
      break;
    default:
      std::cerr << "Error: Invalid operator. Exiting.\n";
      return 1;
  }

  std::cout << "Result: " << result << '\n';
  return 0;
}