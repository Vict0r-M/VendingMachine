// VendingMachine.cpp
#include "VendingMachine.h"
#include "FileRepository.h"
#include <algorithm>

VendingMachine::VendingMachine(const std::string& productFile, const std::string& currencyFile)
    : productRepo(productFile), currencyRepo(currencyFile) {
    // Load the currencies from the file into the coins and bills vectors
    for (const auto& currency : currencyRepo.getAllCurrencies()) {
        if (currency.getValue() <= 0.5) {
            // This is a coin
            coins.push_back(currency);
        }
        else {
            // This is a bill
            bills.push_back(currency);
        }
    }
}

VendingMachine::~VendingMachine() {}

std::vector<Product> VendingMachine::getProducts() const {
    return productRepo.getAllProducts();
}

std::vector<Currency> VendingMachine::getCurrencies() const {
    return currencyRepo.getAllCurrencies();
}

std::vector<Currency> VendingMachine::getCoins() const {
    return coins;
}

std::vector<Currency> VendingMachine::getBills() const {
    return bills;
}

void VendingMachine::addProduct(const Product& product) {
    productRepo.addProduct(product);
}

void VendingMachine::removeProduct(const std::string& code) {
    productRepo.removeProduct(code);
}

void VendingMachine::addCurrency(int value, int quantity) {
    Currency currency(value, quantity);
    currencyRepo.addCurrency(currency);
    if (value <= 50) {
        // This is a coin
        coins.push_back(currency);
    }
    else {
        // This is a bill
        bills.push_back(currency);
    }
}

void VendingMachine::removeCurrency(int value, int quantity) {
    // First, we need to check if we have enough coins or bills of the specific value
    std::vector<Currency>* currencyContainer;
    if (value <= 50) {
        // This is a coin
        currencyContainer = &coins;
    }
    else {
        // This is a bill
        currencyContainer = &bills;
    }

    int count = std::count_if(currencyContainer->begin(), currencyContainer->end(), [value](Currency& currency) {
        return currency.getValue() == value;
        });

    if (count < quantity) {
        throw std::runtime_error("Not enough currency of this value to remove");
    }

    // Remove the currency from the coins or bills vector
    for (int i = 0; i < quantity; i++) {
        auto it = std::find_if(currencyContainer->begin(), currencyContainer->end(), [value](Currency& currency) {
            return currency.getValue() == value;
            });
        currencyContainer->erase(it);
    }

    // Finally, we need to update the currencyRepo
    Currency currency = *currencyRepo.findCurrencyByValue(value);
    currency.setQuantity(currency.getQuantity() - quantity);
    currencyRepo.updateCurrency(currency);
}

Product* VendingMachine::findProduct(const std::string& code) {
    return productRepo.findProductByCode(code);
}

Currency* VendingMachine::findCurrency(int value) {
    return currencyRepo.findCurrencyByValue(value);
}

bool VendingMachine::canMakeChange(int amount) const {
    int remaining = amount;

    for (const Currency& currency : coins) {
        int value = currency.getValue();
        int count = currency.getQuantity();

        while (remaining >= value && count > 0) {
            remaining -= value;
            count--;
        }

        if (remaining == 0) {
            return true;
        }
    }

    return remaining == 0;
}

void VendingMachine::updateProduct(const Product& product) {
    Product* current = findProduct(product.getCode());
    if (current == nullptr) {
        throw std::runtime_error("Product not found");
    }
    *current = product;
}

void VendingMachine::updateCurrency(const Currency& currency) {
    Currency* current = findCurrency(currency.getValue());
    if (current == nullptr) {
        throw std::runtime_error("Currency not found");
    }
    *current = currency;
}

void VendingMachine::makePurchase(const std::string& productCode, int paidAmount) {
    Product* product = findProduct(productCode);

    if (product == nullptr) {
        throw std::runtime_error("Product not found");
    }

    if (product->getQuantity() == 0) {
        throw std::runtime_error("Product out of stock");
    }

    int price = static_cast<int>(product->getPrice() * 100); // Convert price to integer (in bani)
    int change = paidAmount - price;

    if (change < 0) {
        throw std::runtime_error("Insufficient amount paid");
    }

    if (!canMakeChange(change)) {
        throw std::runtime_error("Vending machine cannot provide change");
    }

    // Update product quantity
    product->setQuantity(product->getQuantity() - 1);

    // Provide change and update coins
    int remaining = change;
    for (Currency& currency : coins) {
        int value = currency.getValue();
        int count = currency.getQuantity();

        while (remaining >= value && count > 0) {
            remaining -= value;
            count--;
        }

        currency.setQuantity(count);

        if (remaining == 0) {
            break;
        }
    }

    // Save changes to files
    productRepo.saveProductsToFile();
    currencyRepo.saveCurrenciesToFile();
}

void VendingMachine::saveProductsToFile() const {
    productRepo.saveProductsToFile();
}

void VendingMachine::saveCurrenciesToFile() const {
    currencyRepo.saveCurrenciesToFile();
}
