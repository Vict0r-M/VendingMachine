// UI.cpp
#include "UI.h"
#include <iostream>
#include <sstream>
#include <map>

// Command function type
typedef void (UI::* CommandFunc)(const std::vector<std::string>&);

UI::UI(Service& service) : service(service), isAdmin(false) {}
UI::~UI() {}

void UI::start() {
    // Map command names to functions
    std::map<std::string, CommandFunc> userCommands;
    userCommands["1"] = &UI::displayUserMenu;
    userCommands["2"] = &UI::switchToAdminMenu;
    userCommands["3"] = &UI::undoCommand;
    userCommands["4"] = &UI::purchaseUI;
    userCommands["0"] = &UI::exitUI;

    // Map command names to functions for admin
    std::map<std::string, CommandFunc> adminCommands;
    adminCommands["1"] = &UI::displayAdminMenu;
    adminCommands["2"] = &UI::switchToUserMenu;
    adminCommands["3"] = &UI::undoCommand;
    adminCommands["4"] = &UI::addProductUI;
    adminCommands["5"] = &UI::addCurrencyUI;
    adminCommands["6"] = &UI::removeProductUI;
    adminCommands["7"] = &UI::removeCurrencyUI;
    adminCommands["8"] = &UI::displayProductsUI;
    adminCommands["9"] = &UI::displayCurrenciesUI;
    adminCommands["0"] = &UI::exitUI;

    // Display the user menu by default
    (this->*userCommands["1"])(std::vector<std::string>());

    while (true) {
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
            auto command = isAdmin ? adminCommands.find(commandName) : userCommands.find(commandName);
            if (command != (isAdmin ? adminCommands.end() : userCommands.end())) {
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

void UI::displayUserMenu(const std::vector<std::string>& args) {
    std::cout << "\nVending Machine - User Menu\n";
    std::cout << "---------------------------\n";
    std::cout << "1. Display user command menu\n";
    std::cout << "2. Switch to admin menu\n";
    std::cout << "3. Undo command\n";
    std::cout << "4. Make a purchase (code, inserted currency (value, type, quantity))\n";
    std::cout << "0. Exit\n";
    std::cout << "---------------------------\n";
}

void UI::displayAdminMenu(const std::vector<std::string>& args) {
    std::cout << "\nVending Machine - Admin Menu\n";
    std::cout << "----------------------------\n";
    std::cout << "1. Display admin command menu\n";
    std::cout << "2. Switch to user menu\n";
    std::cout << "3. Undo command\n";
    std::cout << "4. Add a product (code, name, price (in lei), quantity)\n";
    std::cout << "5. Add currency (value, type, quantity)\n";
    std::cout << "6. Remove a product completely (code)\n";
    std::cout << "7. Remove currency (value, type, quantity)\n";
    std::cout << "8. Display products\n";
    std::cout << "9. Display currencies\n";
    std::cout << "0. Exit\n";
    std::cout << "----------------------------\n";
}

void UI::switchToUserMenu(const std::vector<std::string>& args) {
    isAdmin = false;
    displayUserMenu(args);
}

void UI::switchToAdminMenu(const std::vector<std::string>& args) {
    isAdmin = true;
    displayAdminMenu(args);
}

void UI::addProductUI(const std::vector<std::string>& args) {
    if (args.size() < 4) {
        throw std::runtime_error("Adding a product requires 4 arguments.");
    }
    std::string code = args[0];
    std::string name = args[1];
    double price = std::stod(args[2]);   // convert string to double
    int quantity = std::stoi(args[3]);    // convert string to int

    if (price < 0 || quantity < 0) {
        throw std::runtime_error("The price and quantity of a product must be positive when added.");
    }

    Product product(code, name, price, quantity);
    service.addProduct(product);
}

void UI::removeProductUI(const std::vector<std::string>& args) {
    if (args.empty()) {
        throw std::runtime_error("Removing a product requires 1 argument.");
    }
    std::string code = args[0];
    service.removeProduct(code);
}

void UI::addCurrencyUI(const std::vector<std::string>& args) {
    if (args.size()!=3) {
        throw std::runtime_error("Adding currency requires 3 arguments.");
    }
    std::string currencyStr = "";
    int quantity = 0;
    currencyStr = args[0] + " " + args[1];
    quantity = std::stoi(args[2]);

    if (quantity < 0) {
        throw std::runtime_error("Quantity of a currency must be positive when added.");
    }

    service.addCurrency(currencyStr, quantity);
}

void UI::removeCurrencyUI(const std::vector<std::string>& args) {
    if (args.size() != 3) {
        throw std::runtime_error("Removing currency requires 2 arguments.");
    }
    std::string currencyStr = "";
    int quantity = 0;
    currencyStr = args[0] + " " + args[1];
    quantity = std::stoi(args[2]);
    service.removeCurrency(currencyStr, quantity);
}

void UI::purchaseUI(const std::vector<std::string>& args) {
    if (args.size() < 3 || args.size() % 3 != 1) {
        throw std::runtime_error("Purchasing a product requires the product code and pairs of currency type and quantity.");
    }
    std::string code = args[0];
    if (service.findProduct(code) == nullptr) {
        throw std::runtime_error("Product not found.");
    }
    double paidamount = 0;
    std::vector<std::pair<std::string, int>> insertedCurrency;  // Store inserted currency and quantity
    for (int i = 1; i < args.size(); i += 3) {
        std::string currencyStr = args[i] + " " + args[i + 1];
        int value = service.convertToBani(currencyStr);
        int quantity = std::stoi(args[i + 2]);
        paidamount += value * quantity;
        insertedCurrency.push_back(std::make_pair(currencyStr, quantity));
        service.addCurrency(currencyStr, quantity);
    }

    try {
        service.purchase(code, paidamount);
        std::cout << "Purchase successful.\n";
    }
    catch (const std::runtime_error& e) {    
        for (const auto& currencyPair : insertedCurrency) {
            service.removeCurrency(currencyPair.first, currencyPair.second);
        }
        throw;  // Re-throw the exception      
    }
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
        if (currency.getValue() <= 50) {
            if (currency.getValue() == 1) {
                std::cout << "Value: " << currency.getValue() << " ban" << ", Quantity: " << currency.getQuantity() << "\n";
            }
            else {
                std::cout << "Value: " << currency.getValue() << " bani" << ", Quantity: " << currency.getQuantity() << "\n";
            }
        }
        else {
            if (currency.getValue() == 100) {
                std::cout << "Value: " << currency.getValue() / 100 << " leu" << ", Quantity: " << currency.getQuantity() << "\n";
            }
            else {
                std::cout << "Value: " << currency.getValue() / 100 << " lei" << ", Quantity: " << currency.getQuantity() << "\n";
            }
        }
    }
}

void UI::undoCommand(const std::vector<std::string>& args) {
    service.undo();
    std::cout << "Last command undone successfully.";
}

void UI::exitUI(const std::vector<std::string>& args) {
    std::cout << "Exiting...";
    std::exit(0);
}
