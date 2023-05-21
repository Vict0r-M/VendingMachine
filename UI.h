// UI.h
#pragma once
#include "Service.h"

class UI {
private:
    Service& service;

public:
    UI(Service& service);
    ~UI();

    void start();
    void displayMenu();
    void addProductUI(const std::vector<std::string>& args);
    void removeProductUI(const std::vector<std::string>& args);
    void addCurrencyUI(const std::vector<std::string>& args);
    void removeCurrencyUI(const std::vector<std::string>& args);
    void purchaseUI(const std::vector<std::string>& args);
    void displayProductsUI(const std::vector<std::string>& args);
    void displayCurrenciesUI(const std::vector<std::string>& args);
    void undoCommand(const std::vector<std::string>& args);
    void exitUI(const std::vector<std::string>& args);
};
