// UI.h
#pragma once
#include "Service.h"

class UI {
private:
    Service& service;

public:
    UI(Service& service);
    ~UI();

    bool isAdmin;

    void start();

    void displayUserMenu(const std::vector<std::string>& args);
    void displayAdminMenu(const std::vector<std::string>& args);

    void switchToUserMenu(const std::vector<std::string>& args);
    void switchToAdminMenu(const std::vector<std::string>& args);

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
