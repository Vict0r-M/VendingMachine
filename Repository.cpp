// Repository.cpp
#include "Repository.h"
#include <algorithm>
#include <iostream>

Repository::Repository() {}

Repository::~Repository() {}

void Repository::addProduct(Product product) {
    products.push_back(product);
}

void Repository::removeProduct(const std::string& code) {
    products.erase(std::remove_if(products.begin(), products.end(), [&code](Product& product) {
        return product.getCode() == code;
        }), products.end());
}

std::vector<Product> Repository::getAllProducts() const {
    return products;
}

void Repository::addCurrency(Currency currency) {
    currencies.push_back(currency);
}

void Repository::removeCurrency(int value) {
    currencies.erase(std::remove_if(currencies.begin(), currencies.end(), [value](Currency& currency) {
        return currency.getValue() == value;
        }), currencies.end());
}

void Repository::updateProduct(const Product& updatedProduct) {

    auto it = std::find_if(products.begin(), products.end(), [&](const Product& p) {
        return p.getCode() == updatedProduct.getCode();
        });
    if (it == products.end()) {
        throw std::runtime_error("Product not found.");
    }
    *it = updatedProduct;
}

void Repository::updateCurrency(const Currency& updatedCurrency) {
    
    auto it = std::find_if(currencies.begin(), currencies.end(), [&](const Currency& c) {
        return c.getValue() == updatedCurrency.getValue();
        });
    if (it == currencies.end()) {
        throw std::runtime_error("Currency not found");
    }
    *it = updatedCurrency;
}

std::vector<Currency> Repository::getAllCurrencies() const {
    return currencies;
}

Product* Repository::findProductByCode(const std::string& code) {
    for (Product& product : products) {
        if (product.getCode() == code) {
            return &product;
        }
    }
    return nullptr;
}

Currency* Repository::findCurrencyByValue(int value) {
    for (Currency& currency : currencies) {
        if (currency.getValue() == value) {
            return &currency;
        }
    }
    return nullptr;
}
