#pragma once
// FileRepository.h
#include <string>
#include "Repository.h"

class FileRepository : public Repository {
public:
    FileRepository(const std::string& filename);
    ~FileRepository();

    void addProduct(Product product) override;
    void removeProduct(const std::string& code) override;
    std::vector<Product> getAllProducts() const override;

    void addCurrency(Currency currency) override;
    void removeCurrency(int value) override;
    void updateCurrency(const Currency& updatedCurrency) override;
    void updateProduct(const Product& updatedProduct) override;
    std::vector<Currency> getAllCurrencies() const override;

    Product* findProductByCode(const std::string& code) override;
    Currency* findCurrencyByValue(int value) override;

    void saveProductsToFile() const;
    void saveCurrenciesToFile() const;

private:
    std::string productFilename, currencyFilename;
    void loadProductsFromFile();
    void loadCurrenciesFromFile();
};
