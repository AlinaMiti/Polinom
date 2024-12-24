#include "Polynom.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

Polynom::Polynom() {
    _head = nullptr;
}

Polynom::Polynom(const Polynom& tmp) {
    if(tmp._head!=nullptr){
        _head=new Node(tmp._head->GetMonom());
        Node* tmp_next=tmp._head->Next;
        Node* current = _head;
        while(tmp_next!=0){
            current->Next=new Node(tmp_next->GetMonom());
            current=current->Next;
            tmp_next=tmp_next->Next;

        }
    }
}

Polynom::~Polynom() {
  Node* current = _head;
  while (current != nullptr) {
    Node* next = current->Next;
    delete current;
    current = next;
  }
  _head = nullptr;
}

void Polynom::AppendMonom(Monom monom) {
    if (_head == nullptr) {
        _head = new Node(monom);
        return;
    } 
        Node* tmp = _head;
        while (tmp->Next != nullptr) {
            if (tmp->GetMonom().CanOperate(monom)) {
                Monom result = tmp->GetMonom() + monom;
                tmp->SetMonom(result);
                return ;
            }
            tmp = tmp->Next;
        }
        if (tmp->GetMonom().CanOperate(monom)) {
                Monom result = tmp->GetMonom() + monom;
                tmp->SetMonom(result);
                return ;
            }
        else
            tmp->Next = new Node(monom);
}

void Polynom::Print() {
    Node* tmp = _head;
    int pr_flag=0;
    while (tmp != nullptr) {
        if (tmp == _head ){
            if(tmp->GetMonom().GetCoef()!=0){
                tmp->GetMonom().print();
                pr_flag++;
            }
        }
        else {
            if (tmp->GetMonom().GetCoef() > 0){
                if (pr_flag!=0)
                    std::cout << " +";
            }
            if (tmp->GetMonom().GetCoef() !=0){
                std::cout<<" ";
                tmp->GetMonom().print();
            }
        }
        tmp = tmp->Next;
    }
    std::cout<<std::endl;
}

Polynom Polynom::operator+(const Polynom& polynom) const {
    Polynom res(*this);
    Node* rightPolynom = polynom._head;

    while (rightPolynom != nullptr)
    {
        res.AppendMonom(rightPolynom->GetMonom());
        rightPolynom = rightPolynom->Next;
    }
    return res;
}

// Polynom Polynom::operator-(const Polynom& polynom) const {
//     Polynom res(*this);
//     Node* rightPolynom = polynom._head;

//     while (rightPolynom != nullptr)
//     {
//         Monom m_min=rightPolynom->GetMonom()*(-1);
//         res.AppendMonom(m_min);
//         rightPolynom = rightPolynom->Next;
//     }
//     return res;
// }

Polynom Polynom::operator-(const Polynom& polynom) const {
    Polynom res(*this);
    Node* rightPolynom = polynom._head;

    while (rightPolynom != nullptr) {
        Monom negatedMonom = rightPolynom->GetMonom();
        negatedMonom.SetCoef(negatedMonom.GetCoef()*-1); 
        res.AppendMonom(negatedMonom);
        rightPolynom = rightPolynom->Next;
    }
    return res;
}

Polynom Polynom::operator*(const Polynom& polynom) const {
    Node* rightPolynom = polynom._head;
    Polynom res=Polynom();
    while ((rightPolynom!=nullptr)){
        Node* left_polynom=_head;
        Monom right_mon=rightPolynom->GetMonom();
        while (left_polynom!=nullptr){
            Monom mon=(left_polynom->GetMonom())*right_mon;
            //std::cout<<"mon:"<<mon<<" = "<<left_polynom->GetMonom()<<" * "<<right_mon<<std::endl;
            res.AppendMonom(mon);
            //res.Print();
            left_polynom=left_polynom->Next;
        }
        rightPolynom=rightPolynom->Next;
        
    }
    

    return res;
}

// Polynom Polynom::operator*(const Polynom& polynom) const {
//         Polynom res;
//         Node* leftPolynom = _head;
//         while (leftPolynom != nullptr)
//         {
//                 Node* rightPolynom = polynom._head;
//             while(rightPolynom != nullptr)
//             {
//                 res.AppendMonom(leftPolynom->GetMonom() * rightPolynom->GetMonom());
//                 rightPolynom = rightPolynom->Next;
//             }
//              leftPolynom = leftPolynom->Next;
//         }
//         return res;
// }

Polynom Polynom::operator*(const Monom& mon) const{
    Polynom res=Polynom();
    Node* tmp=_head;
    while(tmp!=nullptr){
        res.AppendMonom(tmp->GetMonom()*mon);
        tmp=tmp->Next;
    }
    return res;
}




//Функция для сравнения мономов по "степени" 
bool Polynom::compareMonoms(const Monom& a, const Monom& b) {
    int aSum = 0;
    int bSum = 0;
    if(b.GetCoef() == 0 && a.GetCoef() != 0)
        return true;
    if(b.GetCoef() != 0 && a.GetCoef() == 0)
        return false;
    if(b.GetCoef() == 0 && a.GetCoef() == 0)
        return false;
    for (size_t i = 0; i < a.GetSize(); i++) {
        aSum += a.GetArray()[i];
        bSum += b.GetArray()[i];
    }
    if (aSum > bSum )
        return true;
    if(aSum == bSum){
        for (size_t i = 0; i < a.GetSize(); ++i) {
            if (a.GetArray()[i] > b.GetArray()[i]) {
                return true;
            } 
            else {
                if (a.GetArray()[i] < b.GetArray()[i]) 
                    return false;
            }
        }
    }
        
    return false;

}

// Monom Polynom::getLeadingMonom() const { //главный моном
    
//     Node* current = _head;
//     Monom leadingMonom = _head->GetMonom();
    
//     while (current->Next != nullptr) {
//         //if (Polynom::compareMonoms(current->Next->GetMonom(), leadingMonom)) {
//         if (current->Next->GetMonom().bolsche(leadingMonom)) {
//             leadingMonom = current->Next->GetMonom();
//         }
//         current = current->Next;
//     }
//     //leadingMonom.print();
//     //std::cout << std::endl;
//     return leadingMonom;
//}

Monom Polynom::getLeadingMonom() const {
        if (_head == nullptr) {
            return Monom(0,0,nullptr);
        }
        Node* current = _head;
        Monom leadingMonom = _head->GetMonom();
        while (current != nullptr) {
            if (Polynom::compareMonoms(current->GetMonom(), leadingMonom)) {
              leadingMonom = current->GetMonom();
            }
            current = current->Next;
        }
        return leadingMonom;
    }


Polynom Polynom::operator/(const Polynom& delitel) const {
    if(delitel._head == nullptr){
        throw "11";
    }
    Polynom delimoe(*this);
    Polynom res;
    if(!(delimoe.getLeadingMonom().bolsche(delitel.getLeadingMonom())))
        throw "222";
    while(delimoe.getLeadingMonom().bolsche(delitel.getLeadingMonom())){
        Monom a1 = delimoe.getLeadingMonom();
        Monom a2 = delitel.getLeadingMonom();
        Monom s = a1/a2;
        if(s.GetCoef() != 0){
            res.AppendMonom(s);
            Polynom NewDelimoe = delimoe - (delitel*s);

            delimoe = NewDelimoe;
        }
    }

    Polynom result = res;
    std::cout << "Ostatok: ";
    delimoe.Print();
    std::cout << std::endl;
    //res.Print();
    return result;

}
