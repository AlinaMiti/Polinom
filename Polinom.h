#include "Monom.h"

class Polinom{
private:
    Monom* _head;
public:
    Polinom(){
        _head = nullptr;
    }

    void AppendMonom(Monom* monom){  //добавление монома в полином
        if (_head == nullptr){
            _head = monom;
        }
        else{
            Monom* tmp = _head;
            while(tmp != nullptr){
                tmp = tmp->GetNext();
            }
            tmp->_next = monom;
        }
    }

    void Print(){
        Monom* tmp = _head;
        while(tmp != nullptr){
            tmp->print();
            tmp = tmp->GetNext();
            if (tmp != nullptr)
                std::cout << " + ";
        }
    }
};