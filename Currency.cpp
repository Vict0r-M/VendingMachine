#include "Currency.h"
#include <stdexcept>

Currency::Currency() : value(0), quantity(0) {
    // default constructor implementation
}

Currency::Currency(int value, int quantity)
    : value(value), quantity(quantity) {
    // parameterized constructor implementation
}

Currency::~Currency() {
    // destructor implementation
}

int Currency::getValue() const {
    return this->value;
}

int Currency::getQuantity() const {
    return this->quantity;
}

void Currency::setValue(int value) {
    if (value > 0) {
        this->value = value;
    }
    else {
        throw std::invalid_argument("Value must be positive");
    }
}

void Currency::setQuantity(int quantity) {
    if (quantity >= 0) {
        this->quantity = quantity;
    }
    else {
        throw std::invalid_argument("Quantity cannot be negative");
    }
}

std::istream& operator>>(std::istream& in, Currency& currency) {
    // read the currency details from the input stream
    in >> currency.value >> currency.quantity;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Currency& currency) {
    // write the currency details to the output stream
    out << currency.value << " " << currency.quantity;
    return out;
}
