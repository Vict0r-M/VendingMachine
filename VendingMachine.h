// VendingMachine.h
#pragma once
#include "FileRepository.h"

class VendingMachine {
private:
    FileRepository productRepo;
    FileRepository currencyRepo;
    std::vector<Currency> coins;
    std::vector<Currency> bills;

public:
    VendingMachine(const std::string& productFile, const std::string& currencyFile);
    ~VendingMachine();

    std::vector<Product> getProducts() const;
    std::vector<Currency> getCurrencies() const;
    std::vector<Currency> getCoins() const;
    std::vector<Currency> getBills() const;

    void addProduct(const Product& product);
    void removeProduct(const std::string& code);
    void addCurrency(int value, int quantity);
    void removeCurrency(int value, int quantity);

    void updateProduct(const Product& product);
    void updateCurrency(const Currency& currency);

    Product* findProduct(const std::string& code);
    Currency* findCurrency(int value);

    bool canMakeChange(int amount) const;
    void makePurchase(const std::string& productCode, int paidAmount);

    void saveProductsToFile() const;
    void saveCurrenciesToFile() const;
};
