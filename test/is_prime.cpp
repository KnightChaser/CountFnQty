#include <iostream>

bool is_prime(int n) {
    if (n <= 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int num;
    std::cout << "Enter a number: ";
    if (!(std::cin >> num)) {
        std::cout << "Invalid input." << std::endl;
        return 1;
    }
    if (is_prime(num)) {
        std::cout << num << " is a prime number." << std::endl;
    } else {
        std::cout << num << " is not a prime number." << std::endl;
    }
    return 0;
}
