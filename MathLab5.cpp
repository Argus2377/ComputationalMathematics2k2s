#include <iostream>
#include <iomanip>
#include "NewtonSolution.h"
#include "LagrangianSolution.h"


int main() {
    const std::vector<std::vector<double>> coord = {
            {0.45, 20.1946},
            {0.46, 19.6133},
            {0.47, 18.9425},
            {0.48, 18.1746},
            {0.49, 17.3010},
            {0.50, 16.3123},
            {0.51, 15.1984},
            {0.52, 13.9484},
            {0.53, 12.5508},
            {0.54, 10.9937},
            {0.55, 9.2647},
            {0.56, 7.3510},
    };

    std::cout << "\t\tNewton" << std::endl << std::endl;

    auto first = newton::atFirstDerivative(coord);
    std::cout << "First derivative" << std::endl;
    for (auto &i : first) {
        std::cout << left
                  << setprecision(4) << std::setw(7) << i[0]
                  << "\t"
                  << setprecision(5) << setw(5) << i[1]
                  << std::endl;
    }

    std::cout << std::endl;

    auto second = newton::atSecondDerivative(coord);
    std::cout << "Second derivative" << std::endl;
    for (auto &i : second) {
        std::cout << left
                  << setprecision(4) << std::setw(7) << i[0]
                  << "\t"
                  << setprecision(5) << setw(5) << i[1]
                  << std::endl;
    }

    std::cout << std::endl;

    std::cout << "\t\tLagrangian" << std::endl << std::endl;

    first = lagrangian::atFirstDerivative(coord);
    std::cout << "First derivative" << std::endl;
    for (auto &i : first) {
        std::cout << left
                  << setprecision(4) << std::setw(7) << i[0]
                  << "\t"
                  << setprecision(5) << setw(5) << i[1]
                  << std::endl;
    }

    std::cout << std::endl;

    second = lagrangian::atSecondDerivative(coord);
    std::cout << "Second derivative" << std::endl;
    for (auto &i : second) {
        std::cout << left
                  << setprecision(4) << std::setw(7) << i[0]
                  << "\t"
                  << setprecision(5) << setw(5) << i[1];
        std::cout << endl;
    }

    return 0;
}
