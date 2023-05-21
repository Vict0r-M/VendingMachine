#pragma once
// Repository.h
#include <vector>
#include <string> // Add this to use std::string
#include "Product.h"
#include "Currency.h"

class Repository {
public:
    Repository();
    ~Repository();

    virtual void addProduct(Product product);
    virtual void removeProduct(const std::string& code);
    virtual std::vector<Product> getAllProducts() const;

    virtual void updateCurrency(const Currency& updatedCurrency);
    virtual void addCurrency(Currency currency);
    virtual void removeCurrency(int value);
    virtual std::vector<Currency> getAllCurrencies() const;

    virtual Product* findProductByCode(const std::string& code);
    virtual Currency* findCurrencyByValue(int value);

private:
    std::vector<Product> products;
    std::vector<Currency> currencies;
};
