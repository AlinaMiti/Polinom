#include "Monom.h"
#include <stdint.h>

bool Monom::bolsche(const Monom& a) const{
    if(a._size > _size)
        return false;
    for(size_t i = 0; i < a._size; i++){
        if(_array[i] < a._array[i])
            return false;
    }
    return true;
}

Monom::Monom(double coef, size_t size, int16_t* array){
    _coef = coef;
    _size = size;
    _array = array;
}

double Monom::GetCoef() const {
    return _coef;
}

void Monom::SetCoef(double coef){
        _coef = coef;
    }

size_t Monom::GetSize()const{
    return _size;
}

void Monom::print() const{
    if (_coef == 0) return;

    std::cout<<_coef;

    for (size_t i = 0; i < _size; i++){
        if (_array[i] != 0)
        {
            std::cout<<"X"<<i+1; 
            if (_array[i] != 1)
                std::cout<<"^"<<_array[i];
        }
    }
}

Monom::Monom(const Monom& mon){
    _size = mon._size;
    _coef = mon._coef;
    _array = new int16_t[_size]();
    for (size_t i = 0; i < _size; i++){
        _array[i] = mon._array[i];
    }
}

Monom& Monom::operator=(const Monom& mon){
    if (this == &mon){
        return *this;
    }
    delete [] _array;
    _array = new int16_t[mon._size];
    _size = mon._size;
    _coef = mon._coef;
    for (size_t i = 0; i < _size; i++){
        _array[i] = mon._array[i];
    }
    return *this;
}

Monom Monom::operator+(const Monom& mon)const{
    Monom a(*this);
    if (a._size != mon._size){
        throw "66";
    }
    for (size_t i = 0; i < _size; i ++){
        if (a._array[i] != mon._array[i]){
            throw "55";
        }
    }
    a._coef += mon._coef;
    return a;
};

bool Monom::CanOperate(const Monom& mon) const {
    if (this->_size != mon._size){
        return false;
    }
    for (size_t i = 0; i < _size; i ++){
        if (this->_array[i] != mon._array[i]){
            return false;
        }
    }
    return true;
}

Monom Monom::operator-(const Monom& mon)const{
    Monom a(*this);
    if (a._size != mon._size){
        throw "Mnogo hochesh";
    }
    for (size_t i = 0; i < _size; i ++){
        if (a._array[i] != mon._array[i]){
            throw "Mnogo hochesh";
        }
    }
    a._coef -= mon._coef;
    return a;
};

// Monom Monom::operator*(const Monom& mon) const{
//     size_t mSize = std::max(this->_size, mon._size);
//     int16_t* array = new int16_t[mSize]();
//     int16_t* maxArr = _array;
//     if (mSize == mon._size)
//         maxArr = mon._array;
//     size_t minSize = std::min(this->_size, mon._size);
//     for(size_t i = 0; i < mSize; i++){
//         array[i] = i < minSize ? _array[i] + mon._array[i] : maxArr[i];
//     }
//     return Monom(_coef * mon._coef, mSize, array);
// }

Monom Monom::operator*(const Monom& mon) const{
    size_t mSize = std::max(this->_size, mon._size);
    int16_t* array = new int16_t[mSize];
    size_t minSize = std::min(this->_size, mon._size);
    for(size_t i = 0; i < mSize; i++){
        array[i]=0;
        if (i < _size) {
            array[i] += _array[i]; 
        }
        if (i < mon._size) {
            array[i] += mon._array[i]; 
        }
    }
    return Monom(_coef * mon._coef, mSize, array);
}

Monom Monom::operator/(const Monom& mon) const{
    if (mon._coef == 0) {
        throw "tttt";
    }
    size_t mSize = std::max(this->_size, mon._size);
    int16_t* array = new int16_t[mSize]();
    size_t minSize = std::min(this->_size, mon._size);
    for(size_t i = 0; i < minSize; i++){
        array[i] = _array[i] - mon._array[i];
    }
    if(this->_size > mon._size){
        for(size_t i = minSize; i < this->_size; i++){
            array[i] -= _array[i];
        } 
    }
    else{
        for(size_t i = minSize; i < mon._size; i++){
            array[i] -= mon._array[i];
        } 
    }
    return Monom(_coef / mon._coef, mSize, array);
}

Monom::~Monom(){
    delete [] _array;
}