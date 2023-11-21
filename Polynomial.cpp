//
//  Polynomial.cpp
//  Polynomial Calculator
//
//  Created by Riccardo Belletta on 11/21/23.
//

#include "Polynomial.h"
#include <iostream>
using namespace std;

Polynomial::Polynomial(int terms, double coeff[], char variable)
: numberOfTerms(terms), variable(variable) {
    
    coefficients = new double[numberOfTerms];
    for (int i = 0; i < numberOfTerms; i++)
    {
        coefficients[i] = coeff[i];
    }
};

Polynomial::Polynomial(int terms, double coeff[], char variable, string name)
: numberOfTerms(terms), variable(variable), name(name) {
    
    coefficients = new double[numberOfTerms];
    for (int i = 0; i < numberOfTerms; i++)
    {
        coefficients[i] = coeff[i];
    }
};

// Console output
ostream& operator<<(ostream& stream, Polynomial& p) {
    
    // format: f: -------
//    stream << p.name << ": " << showpos;
    
    // format: f(x) = -----
    stream << showpos;
    
    for (int exp = p.numberOfTerms - 1; exp >= 0; exp--)
    {
        double coeff = p.coefficients[exp];
        char x = p.variable;
        // if a constant term
        if (exp == 0)
        {
            if (coeff == 0)
            {
                stream << 0;
                continue;
            }
            stream << coeff << " ";
        }
        // if degree of the term is 1
        else if (exp == 1)
        {
            if (coeff == 0)
            {
                continue;
            }
            // if coefficient is 1
            else if (coeff == 1)
            {
                stream << "+ " << x << " ";
            }
            else if (coeff == -1)
            {
                stream << "- " << x << " ";
            }
            // if degree of the term is 1 and coefficient is a number
            else
            {
                stream << coeff << x << " ";
            }
        }
        // if degree of the term is > 1 and not last term
        else if (exp > 1 && exp != p.numberOfTerms - 1)
        {
            if (coeff == 0)
            {
                continue;
            }
            else if (coeff == 1)
            {
                stream << "+ " << x << "^" << noshowpos << exp << showpos << " ";
            }
            else if (coeff == -1)
            {
                stream << "- " << x << "^" << noshowpos << exp << showpos << " ";
            }
            else
            {
                stream << coeff << x << "^" << noshowpos << exp << showpos << " ";
            }
            
        }
        // last term
        else
        {
            if (coeff == 0)
            {
                // stream << "      ";
                continue;
            }
            else if (coeff == 1)
            {
                stream << noshowpos <<  x << "^" << exp << showpos << " ";
            }
            else if (coeff == -1)
            {
                stream << "-" << noshowpos << x << "^" << exp << " " << showpos;
            }
            else
            {
                if (coeff > 0)
                {
                    stream << noshowpos << coeff << x << "^" << noshowpos << exp << " " << showpos;
                }
                else
                {
                    stream << coeff << x << "^" << noshowpos << exp << " " << showpos;
                }
                
            }
        }
     }

    stream << noshowpos;
    return stream;
}

void Polynomial::display()
{
    cout << getName() << "(" << getVariable() << ") = " << *this;
}

// f(x) + k
const Polynomial operator+ (Polynomial& p1, const double& k) {
    
    Polynomial sum = p1;
    sum.coefficients[0] += k;
    return sum;
}

// k + f(x)
const Polynomial operator+ (const double& k, Polynomial& p1) {
    
    Polynomial sum = p1;
    sum.coefficients[0] += k;
    sum.setName(p1.name + " + " + to_string(k));
    return sum;
}

// f(x) + g(x)
Polynomial Polynomial::operator+ (Polynomial& p1) {
    
    // if adding two polynomials with the same variables names
    if (variable == p1.variable)
    {
        // if adding two polynomials with the same variables and same number of terms
        if (numberOfTerms == p1.numberOfTerms)
        {
            Polynomial sum(numberOfTerms, variable);
            for (int i = 0; i < numberOfTerms; i++)
            {
                sum.coefficients[i] = coefficients[i] + p1.coefficients[i];
            }
            sum.setName("[" + name + " + " + p1.name + "]");
            return sum;
        }
        // if adding two polynomials with the same variables and different number of terms
        else
        {
            if (numberOfTerms > p1.numberOfTerms)
            {
                Polynomial sum(numberOfTerms, variable);
                for (int i = 0; i < p1.numberOfTerms; i++)
                {
                    sum.coefficients[i] = coefficients[i] + p1.coefficients[i];
                }
                for (int i = p1.numberOfTerms; i < numberOfTerms; i++)
                {
                    sum.coefficients[i] = coefficients[i];
                }
                sum.setName("[" + name + " + " + p1.name + "]");
                return sum;
            }
            
            else if (numberOfTerms < p1.numberOfTerms)
            {
                Polynomial sum(p1.numberOfTerms, variable);
                for (int i = 0; i < numberOfTerms; i++)
                {
                    sum.coefficients[i] = coefficients[i] + p1.coefficients[i];
                }
                for (int i = numberOfTerms; i < p1.numberOfTerms; i++)
                {
                    sum.coefficients[i] = p1.coefficients[i];
                }
                sum.setName("[" + name + " + " + p1.name + "]");
                return sum;
            }
            
        }

        
    }
    // if adding two polynomials with different variables
    else
    {
        cout << "This program can't add polynomials with different variable names.\n";
        exit(2);
    }
    return Polynomial();
}

// f(x) - k
const Polynomial operator- (Polynomial& p1, const double& k) {
    
    Polynomial sum = p1;
    sum.coefficients[0] -= k;
    return sum;
}

// k - f(x)
const Polynomial operator- (const double& k, Polynomial& p1) {
    
    Polynomial sum = p1;
    for (int i = 0; i < p1.numberOfTerms; i++)
    {
        sum.coefficients[i] = -sum.coefficients[i];
    }
    sum.coefficients[0] += k;
    return sum;
}

// f(x) - g(x): performed as f(x) + (-g(x))
Polynomial Polynomial::operator- (Polynomial& p) {
    
    Polynomial p1 = p;
    // flipping sign in g(x), then adds f(x) + g(x)
    for (int i = 0; i < p1.getNumOfTerms(); i++)
    {
        p1.coefficients[i] = -p1.coefficients[i];
    }
    // if adding two polynomials with the same variables names
    if (variable == p1.variable)
    {
        // if adding two polynomials with the same variables and same number of terms
        if (numberOfTerms == p1.numberOfTerms)
        {
            Polynomial sum(numberOfTerms, variable);
            for (int i = 0; i < numberOfTerms; i++)
            {
                sum.coefficients[i] = coefficients[i] + p1.coefficients[i];
            }
            sum.setName("[" + name + " - " + p1.name + "]");
            return sum;
        }
        // if adding two polynomials with the same variables and different number of terms
        else
        {
            if (numberOfTerms > p1.numberOfTerms)
            {
                Polynomial sum(numberOfTerms, variable);
                for (int i = 0; i < p1.numberOfTerms; i++)
                {
                    sum.coefficients[i] = coefficients[i] + p1.coefficients[i];
                }
                for (int i = p1.numberOfTerms; i < numberOfTerms; i++)
                {
                    sum.coefficients[i] = coefficients[i];
                }
                sum.setName("[" + name + " - " + p1.name + "]");
                return sum;
            }
            
            else if (numberOfTerms < p1.numberOfTerms)
            {
                Polynomial sum(p1.numberOfTerms, variable);
                for (int i = 0; i < numberOfTerms; i++)
                {
                    sum.coefficients[i] = coefficients[i] + p1.coefficients[i];
                }
                for (int i = numberOfTerms; i < p1.numberOfTerms; i++)
                {
                    sum.coefficients[i] = p1.coefficients[i];
                }
                sum.setName("[" + name + " - " + p1.name + "]");
                return sum;
            }
            
        }
    }
    // if adding two polynomials with different variables
    else
    {
        cout << "This program can't add polynomials with different variable names.\n";
        exit(2);
    }
    return Polynomial();
}

// f(x) * k
const Polynomial operator* (Polynomial& p, const double& k) {
    int terms = p.getNumOfTerms();
    Polynomial result(terms, p.getVariable());
    for (int i = 0; i < terms; i++)
    {
        result.coefficients[i] = k * p.coefficients[i];
    }
    return result;
}

// k * f(x)
const Polynomial operator* (const double& k, Polynomial& p) {
    int terms = p.getNumOfTerms();
    Polynomial result(terms, p.getVariable());
    for (int i = 0; i < terms; i++)
    {
        result.coefficients[i] = k * p.coefficients[i];
    }
    return result;
}

// f(x) * g(x)
const Polynomial operator* (Polynomial& p1, Polynomial& p2) {
    if (p1.variable == p2.variable)
    {
        int newTerms = p1.numberOfTerms * p2.numberOfTerms;
        Polynomial result(newTerms, p1.variable);
        for (int i = 0; i < p1.numberOfTerms; i++)
        {
            for (int j = 0; j < p2.getNumOfTerms(); j++)
            {
                result.coefficients[i+j] += p1.coefficients[i] * p2.coefficients[j];
            }
        }
        return result;
    }
    
    else
    {
        cout << "This program can't multiply polynomials with different variable names.\n";
        exit(2);
    }
    
    return Polynomial();
}

// returns f(input)
double Polynomial::evaluate(double input) {
    double result = coefficients[0];
    for (int i = 1; i < numberOfTerms; i++)
    {
        result += (coefficients[i] * pow(input, i));
    }
    
    return result;
}
 
double Polynomial::ARC(double x1, double x2) {
    
    double fx1 = evaluate(x1);
    double fx2 = evaluate(x2);
    return (fx1 - fx2) / (x1 - x2);
}

Polynomial Polynomial::derivative()
{
    if (getNumOfTerms() == 1)
    {
        string newName = getName() + "'";
        double newCoeff[1] = {0};
        return Polynomial(1, newCoeff, variable, newName);
    }
    double newCoeff[numberOfTerms - 1];
    for (int i = 0; i < numberOfTerms - 1; i++)
    {
        newCoeff[i] = coefficients[i + 1] * (i + 1);
    }
    string newName = getName() + "'";

    return Polynomial(numberOfTerms - 1, newCoeff, variable, newName);
}
