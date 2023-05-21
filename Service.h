// Service.h
#pragma once
#include "VendingMachine.h"
#include <functional>
#include <stack>

class Service {
private:
    VendingMachine& vendingMachine;
    std::stack<std::function<void()>> history;

public:
    Service(VendingMachine& vm);

    Product getProduct(const std::string& code);
    Currency getCurrency(int value);

    void addProduct(const Product& product);
    void removeProduct(const std::string& code);
    int convertToBani(const std::string& valueStr);
    void addCurrency(const std::string& valueStr, int quantity);
    void removeCurrency(const std::string& valueStr, int quantity);
    Product* findProduct(const std::string& code);
    Currency* findCurrency(int value);
    bool canMakeChange(int amount) const;
    void purchase(const std::string& productCode, int paidAmount);
    std::vector<Product> getProducts() const;
    std::vector<Currency> getCurrencies() const;
    void undo();
};
