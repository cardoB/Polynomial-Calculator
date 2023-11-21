//
//  Polynomial.h
//  Polynomial Calculator
//
//  Created by Riccardo Belletta on 11/21/23.
//


#ifndef Polynomial_h
#define Polynomial_h

#include <iostream>

// ==================================================================================== Polynomial   vvv
class Polynomial {
private:
    int numberOfTerms;
    char variable; // x, y, z
    std::string name; // f, or g, or f(x)
    // coefficients, starting from constant term. The index of the array is the degree of the term.
    double* coefficients;
    
public:
    // Polynomial with zero terms, variable name set at '#'
    Polynomial(): numberOfTerms(0), variable('#') { coefficients = new double[numberOfTerms];};
    
    Polynomial(int n) : numberOfTerms(n), variable('#'), name("no-name") {coefficients = new double[numberOfTerms];};
    Polynomial(int terms, char variable) : numberOfTerms(terms), variable(variable), name("no-name") {coefficients = new double[numberOfTerms];};
    Polynomial(int terms, double coeff[], char variable);
    Polynomial(int terms, double coeff[], char variable, std::string name);
    
    int getNumOfTerms() { return numberOfTerms; }
    char getVariable() { return variable; }
    std::string getName() { return name; }
    double getCoeff(int i) { return coefficients[i - 1];} // term 1 is the constant term
    
    void setName(std::string newName) { name = newName; }
    void setVariable(char newVar) { variable = newVar; }
    void setCoeff(int i, double newCoeff) { coefficients[i - 1] = newCoeff; }
    
    friend std::ostream& operator<<(std::ostream& stream, Polynomial& p);
    
    Polynomial operator+ (Polynomial& p1);
    friend const Polynomial operator+ (Polynomial& p, const double& k);
    friend const Polynomial operator+ (const double& k, Polynomial& p);
    
    Polynomial operator- (Polynomial& p1);
    friend const Polynomial operator- (const double& k, Polynomial& p1);
    friend const Polynomial operator- (Polynomial& p1, const double& k);
    
    friend const Polynomial operator* (Polynomial& p1, Polynomial& p2);
    friend const Polynomial operator* (Polynomial& p, const double& k);
    friend const Polynomial operator* (const double& k, Polynomial& p);
    
    // average rate of change of the polynomial at 2 argument inputs.
    double ARC(double x1, double x2);
    double evaluate(double input);
    
    Polynomial derivative();
    void display();
    
    // copy constructor
    Polynomial(const Polynomial& p) {
        numberOfTerms = p.numberOfTerms;
        coefficients = new double[numberOfTerms];
        variable = p.variable;
        name = p.name;
        for (int i = 0; i < numberOfTerms; i++)
        {
            coefficients[i] = p.coefficients[i];
        }
    }
    
    ~Polynomial() {
        delete [] coefficients;
        // cout << "Polynomial deleted.\n";
    }
};


#endif /* Polynomial_h */
