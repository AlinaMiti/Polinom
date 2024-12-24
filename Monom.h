#include <iostream>
#include <stdint.h>

class Monom{
private:
    double _coef;
    size_t _size;
    int16_t* _array;
public:
    Monom(double coef, size_t size, int16_t* array);
    size_t GetSize()const;
    double GetCoef()const;
    void SetCoef(double coef);
    void print() const;
    Monom(const Monom& mon);
    Monom& operator=(const Monom& mon);
    Monom operator+(const Monom& mon)const;
    bool CanOperate(const Monom& mon) const;
    Monom operator-(const Monom& mon)const;
    Monom operator*(const Monom& mon) const;
    Monom operator/(const Monom& mon) const;
    ~Monom();
    const int16_t* GetArray() const {
            return _array;
        }
    bool bolsche(const Monom& a) const;
};