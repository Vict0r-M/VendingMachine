#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <fstream>

class Product {
private:
    std::string code;
    std::string name;
    double price;
    int quantity; // add this

public:
    Product();
    Product(const std::string& code, const std::string& name, double price, int quantity); // add quantity here
    ~Product();

    std::string getCode() const;
    std::string getName() const;
    double getPrice() const;
    int getQuantity() const; // add this

    void setCode(const std::string& code);
    void setName(const std::string& name);
    void setPrice(double price);
    void setQuantity(int quantity); // add this

    friend std::istream& operator>>(std::istream& in, Product& product);
    friend std::ostream& operator<<(std::ostream& out, const Product& product);
};

#endif // PRODUCT_H
