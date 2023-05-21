#pragma once
#ifndef CURRENCY_H
#define CURRENCY_H

#include <fstream>

class Currency {
private:
    int value;
    int quantity;

public:
    Currency();
    Currency(int value, int quantity);
    ~Currency();

    int getValue() const;
    int getQuantity() const;

    void setValue(int value);
    void setQuantity(int quantity);

    friend std::istream& operator>>(std::istream& in, Currency& currency);
    friend std::ostream& operator<<(std::ostream& out, const Currency& currency);
};

#endif // CURRENCY_H
