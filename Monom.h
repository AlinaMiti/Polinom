//+ - * / Print
#include <iostream>

class Monom{
private:
    double _coef;
    size_t _size;
    uint16_t* _array;  //массив степеней
    Monom* _next;    //указатель на слдщ элемент
public:
    Monom(double coef, size_t size, uint16_t* array){
        _coef = coef;
        _size = size;
        _array =  array;
        _next = nullptr;
    }

    void print(){
        std::cout << _coef;
        for(int i = 0; i < _size; i++){
            std::cout << "X" << i+1 << "^" << _array[i];
        }
    }

    Monom(const Monom& mon){
        _size = mon._size;
        _coef = mon._coef;
        _next = mon._next;
        _array = new uint16_t[_size];
        for(size_t i = 0; i < _size; i++){
            _array[i] = mon._array[i];
        }
    }

    Monom& operator=(const Monom& mon){
        if (this == &mon)
            return *this;
        delete [] _array;
        _array = new uint16_t[mon._size];
        _size = mon._size;
        _coef = mon._coef;
        _next = mon._next;
        for (size_t i = 0; i < _size; i++){
            _array[i] = mon._array[i];
        }
        return *this;
    }

    Monom& operator+(const Monom& mon){
        
    }

    ~Monom(){
        delete [] _array;
    }

};