#pragma once
#include "Node.h"

class Polynom {
private:
    Node* _head;

public:
    Polynom();
    Polynom(const Polynom& tmp);
    void AppendMonom(Monom monom);
    void Print();
    Polynom operator+(const Polynom& polynom) const;
    Polynom operator-(const Polynom& polynom) const;
    Polynom operator*(const Polynom& polynom) const;
    Polynom operator/(const Polynom& polynom) const;
    Polynom operator*(const Monom& mon) const;
    ~Polynom();
    void sortPolynom();
    Monom getLeadingMonom() const ;
    static bool compareMonoms(const Monom& a, const Monom& b);
};