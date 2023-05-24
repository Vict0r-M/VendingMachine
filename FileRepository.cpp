// FileRepository.cpp
#include <fstream>
#include "FileRepository.h"

FileRepository::FileRepository(const std::string& filename) : Repository(), productFilename(filename), currencyFilename(filename) {
    void loadProductsFromFile();
    void loadCurrenciesFromFile();
}

FileRepository::~FileRepository() {
    saveProductsToFile();
    saveCurrenciesToFile();
}

void FileRepository::addProduct(Product product) {
    Repository::addProduct(product);
    saveProductsToFile();
    saveCurrenciesToFile();
}

void FileRepository::removeProduct(const std::string& code) {
    Repository::removeProduct(code);
    saveProductsToFile();
    saveCurrenciesToFile();
}

std::vector<Product> FileRepository::getAllProducts() const {
    return Repository::getAllProducts();
}

void FileRepository::addCurrency(Currency currency) {
    Repository::addCurrency(currency);
    saveProductsToFile();
    saveCurrenciesToFile();
}

void FileRepository::removeCurrency(int value) {
    Repository::removeCurrency(value);
    saveProductsToFile();
    saveCurrenciesToFile();
}

std::vector<Currency> FileRepository::getAllCurrencies() const {
    return Repository::getAllCurrencies();
}

void FileRepository::updateProduct(const Product& updatedProduct) {
    Repository::updateProduct(updatedProduct);
    saveProductsToFile();
}

void FileRepository::updateCurrency(const Currency& updatedCurrency) {
    Repository::updateCurrency(updatedCurrency);
    saveCurrenciesToFile();
}

void FileRepository::loadProductsFromFile() {
    std::ifstream in(productFilename);

    if (!in) {
        throw std::runtime_error("Could not open file for reading");
    }

    Product product;
    while (in >> product) {
        Repository::addProduct(product);
    }

    in.close();
}

void FileRepository::loadCurrenciesFromFile() {
    std::ifstream in(currencyFilename);

    if (!in) {
        throw std::runtime_error("Could not open file for reading");
    }

    Currency currency;
    while (in >> currency) {
        Repository::addCurrency(currency);
    }

    in.close();
}

void FileRepository::saveProductsToFile() const {
    std::ofstream out(productFilename);

    if (!out) {
        throw std::runtime_error("Could not open file for writing");
    }

    for (const auto& product : Repository::getAllProducts()) {
        out << product << "\n";
    }

    out.close();
}

void FileRepository::saveCurrenciesToFile() const {
    std::ofstream out(currencyFilename);

    if (!out) {
        throw std::runtime_error("Could not open file for writing");
    }

    for (const auto& currency : Repository::getAllCurrencies()) {
        out << currency << "\n";
    }

    out.close();
}

Product* FileRepository::findProductByCode(const std::string& code) {
    // Load the products from the file
    return Repository::findProductByCode(code);
}

Currency* FileRepository::findCurrencyByValue(int value) {
    // Load the currencies from the file
    return Repository::findCurrencyByValue(value);
}
