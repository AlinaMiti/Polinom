#pragma once
#include "Monom.h"

class Node {
private:
    Monom _monom;
public:
    Node* Next = nullptr;
    Node(Monom monom): _monom(monom) {
    }

    void SetMonom(Monom monom) {
        _monom = monom;
    }

    const Monom& GetMonom() const {
        return _monom;
    }
};