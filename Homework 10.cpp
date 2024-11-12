#include <iostream>
#include <stdexcept> //Defines several standard classes used for reporting exceptions
#include <string>

// Custom exception class
class CustomException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Error in nestedFunction";
    }
};

// Function to divide two integers
double divide(int numerator, int denominator) {
    if (denominator == 0) {
        throw std::runtime_error("Error: Division by zero is not allowed.");
    }
    return static_cast<double>(numerator) / denominator;
}

// Function to access an element in an array with bounds checking
int accessArray(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Error: Index out of bounds.");
    }
    return arr[index];
}

// Function that throws a custom exception
void nestedFunction() {
    throw CustomException();
}

// Function that calls nestedFunction and catches then rethrows the exception
void outerFunction() {
    try {
        nestedFunction();
    } catch (const CustomException& e) {
        std::cerr << "Caught exception in outerFunction: " << e.what() << std::endl;
        throw;  // Rethrow the exception
    }
}

int main() {
    // Testing the divide function
    int numerator, denominator;
    std::cout << "Enter numerator: ";
    std::cin >> numerator;
    std::cout << "Enter denominator: ";
    std::cin >> denominator;

    try {
        double result = divide(numerator, denominator);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    // Testing the accessArray function
    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;
    int* arr = new int[size];  // Dynamic allocation of array

    // Initializing array with sample values
    for (int i = 0; i < size; i++) {
        arr[i] = i * 10;
    }

    int index;
    std::cout << "Enter index to access: ";
    std::cin >> index;

    try {
        int value = accessArray(arr, size, index);
        std::cout << "Element at index " << index << ": " << value << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }

    delete[] arr;  // Clean up dynamically allocated array

    // Testing nestedFunction and outerFunction
    try {
        outerFunction();
    } catch (const CustomException& e) {
        std::cerr << "Caught rethrown exception in main: " << e.what() << std::endl;
    }

    return 0;
}