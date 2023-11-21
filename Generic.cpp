//
//  Generic.cpp
//  Polynomial Calculator
//
//  Created by Riccardo Belletta on 11/21/23.
//

#include "Generic.hpp"
#include "Polynomial.h"

void welcome()
{
    std::cout << "==============================================================\n"
         << "    Welcome to the single variable Polynomial calculator\n"
         << "==============================================================\n";
 }

int menu()
{
    std::cout << "1. Display\n"
         << "2. Evaluate\n"
         << "3. Add\n"
         << "4. Subtract\n"
         << "5. Multiply\n"
         << "6. Derivative\n"
         << "0. Exit\n"
         << "Enter selection: ";
    int selection;
    std::cin >> selection;
    return selection;
}

Polynomial getPolynomial(char variable)
{
    std::cout << "Enter the degree of the Polynomial: ";
    int degree;
    
    std::cin >> degree;
    degree++;
    
    
    std::cout << "Enter the coefficients, starting with the constant and moving up each term. For missing terms, enter zero: ";
    double* coefficients = new double[degree];
    
    for (int i = 0; i < degree; i++)
    {
        std::cin >> coefficients[i];
    }
    
    std::cout << "Enter the name of the function: ";
    std::string name;
    std::cin >> name;
    
    return Polynomial(degree, coefficients, variable, name);
    
}

