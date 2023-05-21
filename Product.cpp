#include "Product.h"
#include <stdexcept>

Product::Product() : code(""), name(""), price(0.0), quantity(0) {
    // default constructor implementation
}

Product::Product(const std::string& code, const std::string& name, double price, int quantity)
    : code(code), name(name), price(price), quantity(quantity) {
    // parameterized constructor implementation
}

Product::~Product() {
    // destructor implementation
}

std::string Product::getCode() const {
    return this->code;
}

std::string Product::getName() const {
    return this->name;
}

double Product::getPrice() const {
    return this->price;
}

int Product::getQuantity() const { // add this
    return this->quantity;
}

void Product::setCode(const std::string& code) {
    this->code = code;
}

void Product::setName(const std::string& name) {
    this->name = name;
}

void Product::setPrice(double price) {
    if (price >= 0) {
        this->price = price;
    }
    else {
        throw std::invalid_argument("Price cannot be negative");
    }
}

void Product::setQuantity(int quantity) { // add this
    if (quantity >= 0) {
        this->quantity = quantity;
    }
    else {
        throw std::invalid_argument("Quantity cannot be negative");
    }
}

std::istream& operator>>(std::istream& in, Product& product) {
    // read the product details from the input stream
    in >> product.code >> product.name >> product.price >> product.quantity; // add quantity here
    return in;
}

std::ostream& operator<<(std::ostream& out, const Product& product) {
    // write the product details to the output stream
    out << product.code << " " << product.name << " " << product.price << " " << product.quantity; // add quantity here
    return out;
}
