// UI.cpp
#include "UI.h"
#include <iostream>
#include <sstream>
#include <map>

// Command function type
typedef void (UI::* CommandFunc)(const std::vector<std::string>&);

UI::UI(Service& service) : service(service) {}

UI::~UI() {}

void UI::start() {
    // Map command names to functions
    std::map<std::string, CommandFunc> commands;
    commands["1"] = &UI::addProductUI;
    commands["2"] = &UI::removeProductUI;
    commands["3"] = &UI::addCurrencyUI;
    commands["4"] = &UI::removeCurrencyUI;
    commands["5"] = &UI::purchaseUI;
    commands["6"] = &UI::displayProductsUI;
    commands["7"] = &UI::displayCurrenciesUI;
    commands["8"] = &UI::undoCommand;
    commands["0"] = &UI::exitUI;

    while (true) {
        displayMenu();
        std::cout << "\nEnter a command: ";
        std::string line;
        std::getline(std::cin, line);

        // Split line into command and arguments
        std::stringstream ss(line);
        std::string commandName;
        ss >> commandName;

        // Collect the rest of the arguments
        std::vector<std::string> args;
        std::string arg;
        while (ss >> arg) {
            args.push_back(arg);
        }

        try {
            // Find and execute the command
            auto command = commands.find(commandName);
            if (command != commands.end()) {
                (this->*command->second)(args);
            }
            else {
                std::cout << "Unknown command: " << commandName << '\n';
            }
        }
        catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }
}

void UI::displayMenu() {
    std::cout << "\nWelcome to the Vending Machine\n";
    std::cout << "1. Add a product (code, name, price, quantity)\n";
    std::cout << "2. Remove a product (code)\n";
    std::cout << "3. Add currency (value,quanitity,type(leu))\n";
    std::cout << "4. Remove currency (value, quantity)\n";
    std::cout << "5. Make a purchase (code, amount)\n";
    std::cout << "6. Display products\n";
    std::cout << "7. Display currencies\n";
    std::cout << "8. Undo command\n";
    std::cout << "0. Exit\n";
}

void UI::addProductUI(const std::vector<std::string>& args) {
    if (args.size() < 4) {
        throw std::runtime_error("Adding a product requires 4 arguments.\n");
    }
    std::string code = args[0];
    std::string name = args[1];
    double price = std::stod(args[2]);   // convert string to double
    int quantity = std::stoi(args[3]);    // convert string to int

    Product product(code, name, price, quantity);
    service.addProduct(product);
}

void UI::removeProductUI(const std::vector<std::string>& args) {
    if (args.empty()) {
        throw std::runtime_error("Removing a product requires 1 argument.\n");
    }
    std::string code = args[0];
    service.removeProduct(code);
}

void UI::addCurrencyUI(const std::vector<std::string>& args) {
    if (args.size()!=3) {
        throw std::runtime_error("Adding currency requires 3 arguments.\n");
    }
    std::string currencyStr = "";
    int quantity = 0;
    currencyStr = args[0] + " " + args[1];
    quantity = std::stoi(args[2]);

    service.addCurrency(currencyStr, quantity);
}

void UI::removeCurrencyUI(const std::vector<std::string>& args) {
    if (args.size() != 3) {
        throw std::runtime_error("Removing currency requires 2 arguments.\n");
    }
    std::string currencyStr = "";
    int quantity = 0;
    currencyStr = args[0] + " " + args[1];
    service.removeCurrency(currencyStr, quantity);
}

void UI::purchaseUI(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw std::runtime_error("Purchasing a product requires 2 arguments.\n");
    }
    std::string code = args[0];
    int amount = std::stoi(args[1]);    // convert string to int
    service.purchase(code, amount);
}

void UI::displayProductsUI(const std::vector<std::string>& args) {
    std::vector<Product> products = service.getProducts();
    for (const auto& product : products) {
        std::cout << "Code: " << product.getCode() << ", Name: " << product.getName()
            << ", Price: " << product.getPrice() << ", Quantity: " << product.getQuantity() << "\n";
    }
}

void UI::displayCurrenciesUI(const std::vector<std::string>& args) {
    std::vector<Currency> currencies = service.getCurrencies();
    for (const auto& currency : currencies) {
        std::cout << "Value: " << currency.getValue() << ", Quantity: " << currency.getQuantity() << "\n";
    }
}

void UI::undoCommand(const std::vector<std::string>& args) {
    service.undo();
    std::cout << "Last command undone successfully.\n";
}

void UI::exitUI(const std::vector<std::string>& args) {
    std::cout << "Exiting...";
    std::exit(0);
}
