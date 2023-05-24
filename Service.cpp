// Service.cpp
#include "Service.h"

Service::Service(VendingMachine& vm) : vendingMachine(vm) {}

void Service::addProduct(const Product& product) {
    vendingMachine.addProduct(product);
    history.push([=]() {vendingMachine.removeProduct(product.getCode()); });
}

void Service::removeProduct(const std::string& code) {
    if (vendingMachine.findProduct(code) == nullptr) {
        throw std::runtime_error("Product not found.");
    }
    Product product = *vendingMachine.findProduct(code);
    
    vendingMachine.removeProduct(code);
    history.push([=]() {vendingMachine.addProduct(product); });
}

int Service::convertToBani(const std::string& valueStr) {
    if ((valueStr == "1 leu") || (valueStr == "5 lei") || (valueStr == "10 lei") || (valueStr == "20 lei") ||
        (valueStr == "50 lei") || (valueStr == "100 lei") || (valueStr == "200 lei") || (valueStr == "500 lei")) {
        return std::stoi(valueStr.substr(0, valueStr.length() - 4)) * 100;
    }
    else if ((valueStr == "1 ban")) {
        return std::stoi(valueStr.substr(0, valueStr.length() - 4));
    } 
    else if((valueStr == "5 bani") || (valueStr == "10 bani") || (valueStr == "50 bani")) {
        return std::stoi(valueStr.substr(0, valueStr.length() - 5));
    }
    else {
        throw std::runtime_error("Invalid currency input.");
    }
}

void Service::addCurrency(const std::string& valueStr, int quantity) {
    // Parsing the value and converting to "bani"
    int valueInBani = convertToBani(valueStr);

    // Adding the currency
    vendingMachine.addCurrency(valueInBani, quantity);

    // Push to history for undo action
    history.push([=]() {vendingMachine.removeCurrency(valueInBani, quantity); });
}

void Service::removeCurrency(const std::string& valueStr, int quantity) {
    // Parsing the value and converting to "bani"
    int valueInBani = convertToBani(valueStr);

    // Removing the currency
    vendingMachine.removeCurrency(valueInBani, quantity);

    // Push to history for undo action
    history.push([=]() {vendingMachine.addCurrency(valueInBani, quantity); });
}

Product* Service::findProduct(const std::string& code) {
    return vendingMachine.findProduct(code);
}

Currency* Service::findCurrency(int value) {
    return vendingMachine.findCurrency(value);
}

bool Service::canMakeChange(int amount) const {
    return vendingMachine.canMakeChange(amount);
}

Product Service::getProduct(const std::string& code) {
    Product* product = vendingMachine.findProduct(code);
    if (product == nullptr) {
        throw std::runtime_error("Product not found");
    }
    return *product;
}

Currency Service::getCurrency(int value) {
    Currency* currency = vendingMachine.findCurrency(value);
    if (currency == nullptr) {
        throw std::runtime_error("Currency not found");
    }
    return *currency;
}

void Service::purchase(const std::string& productCode, double paidAmount) {
    // Save initial states
    Product initialProductState = getProduct(productCode);
    std::vector<Currency> initialCurrencyStates;
    for (Currency currency : vendingMachine.getCurrencies()) {
        initialCurrencyStates.push_back(getCurrency(currency.getValue()));
    }

    // Make the purchase
    vendingMachine.makePurchase(productCode, paidAmount);

    // Save undo action
    //history.push([=]() {
    //    vendingMachine.updateProduct(initialProductState);
    //    for (const Currency& currency : initialCurrencyStates) {
    //        vendingMachine.updateCurrency(currency);
    //    }
    //    });
}

std::vector<Product> Service::getProducts() const {
    return vendingMachine.getProducts();
}

std::vector<Currency> Service::getCurrencies() const {
    return vendingMachine.getCurrencies();
}

void Service::undo() {
    if (history.empty()) {
        throw std::runtime_error("No more actions to undo.");
    }
    history.top()();
    history.pop();
    // Save changes to files
    vendingMachine.saveProductsToFile();
    vendingMachine.saveCurrenciesToFile();
}
