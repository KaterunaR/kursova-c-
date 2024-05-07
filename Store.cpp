#pragma once
#include <vector>
#include <fstream>
#include "GoodsInShop.h"
class Store {
private:
    vector<GoodsInShop> inventory;

public:
    Store() {}

    // Method to add item to store
    void addItem(const GoodsInShop& item) {
        inventory.push_back(item);
    }

    // Method to remove item from store
    void removeItem(const string& itemName) {
        auto it = remove_if(inventory.begin(), inventory.end(), [&](const GoodsInShop& item) {
            return item.getName() == itemName;
            });

        if (it != inventory.end()) {
            inventory.erase(it, inventory.end());
            cout << "Item '" << itemName << "' was successfully deleted." << endl;
        }
        else {
            cout << "There is no item with the name '" << itemName << "'." << endl;
        }
    }

    // Method to calculate profit
    float calculateProfit() const {
        float totalProfit = 0.0;
        for (const auto& item : inventory) {
            totalProfit += (item.getFullPrice() - item.getPrice());
        }
        return totalProfit;
    }

    // Iterator class for Store
    class Iterator {
    private:
        vector<GoodsInShop>::iterator ptr;

    public:
        Iterator(vector<GoodsInShop>::iterator p) : ptr(p) {}

        GoodsInShop& operator*() const {
            return *ptr;
        }

        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }
    };

    Iterator begin() {
        return Iterator(inventory.begin());
    }

    Iterator end() {
        return Iterator(inventory.end());
    }


    void saveToFile(const string& filename) const {
        ofstream outputFile(filename, ios::app);
        if (outputFile.is_open()) {
            for (const auto& item : inventory) {
                outputFile << "Name: " << item.getName() << endl;
                outputFile << "Manufacture Date: " << item.getManufactureDate() << endl;
                outputFile << "Certificates of Quality: " << item.getCertificatesOfQuality() << endl;
                outputFile << "Price: " << item.getPrice() << endl;
                outputFile << "Markup: " << item.getMarkup() << endl;
                outputFile << "Expiry Period: " << item.getExpiryPeriod() << endl;
                outputFile << endl; 
            }
            outputFile.close();
            cout << "Data successfully saved to file: " << filename << endl;
        }
        else {
            cout << "Unable to open file" << endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            string line;
            GoodsInShop newItem;
            while (getline(inputFile, line)) {
                if (line.empty()) {
                    addItem(newItem);
                    newItem = GoodsInShop();
                }
                else {
                    size_t colonPos = line.find(':');
                    string fieldName = line.substr(0, colonPos);
                    string value = line.substr(colonPos + 2); 
                    if (fieldName == "Name") {
                        newItem.setName(value);
                    }
                    else if (fieldName == "Manufacture Date") {
                        newItem.setManufactureDate(value);
                    }
                    else if (fieldName == "Certificates of Quality") {
                        newItem.setCertificatesOfQuality(value);
                    }
                    else if (fieldName == "Price") {
                        newItem.setPrice(stof(value));
                    }
                    else if (fieldName == "Markup") {
                        newItem.setMarkup(stof(value));
                    }
                    else if (fieldName == "Expiry Period") {
                        newItem.setExpiryPeriod(value);
                    }
                }
            }
            // Add the last item
            if (!newItem.getName().empty()) {
                addItem(newItem);
            }
            inputFile.close();
            cout << "Data successfully loaded from file: " << filename << endl;
        }
        else {
            cout << "Unable to open file" << endl;
        }
    }
  




    // Method to display menu
    void displayMenu() {
        cout << "===== Store Menu =====" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Delete Item" << endl;
        cout << "3. Display Items" << endl;
        cout << "4. Calculate Profit" << endl;
        cout << "5. Save Inventory to File" << endl;
        cout << "6. Load Inventory from File" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
    }

    // Method for user choice
    void processChoice(int choice) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number." << endl;
            return;
        }

        switch (choice) {
        case 1: {
            GoodsInShop newItem;
            cin >> newItem;
            addItem(newItem);
            break;
        }
        case 2: {
            string itemName;
            cout << "Enter the name of the item to remove: ";
            cin >> itemName;
            removeItem(itemName);
            break;
        }
        case 3: {
            cout << endl << endl;
            cout << "==== Items in store ====" << endl;
            for (const auto& item : inventory) {
                cout << item << endl;
            }
            cout << "========================" << endl << endl;
            break;
        }
        case 4: {
            cout << endl << "Total profit: $" << calculateProfit() << endl << endl;
            break;
        }
        case 5: {
            string filename;
            cout << "Enter filename to save: ";
            cin >> filename;
            saveToFile(filename);
            break;
        }
        case 6: {
            string filename;
            cout << "Enter filename to load: ";
            cin >> filename;
            loadFromFile(filename);
            break;
        }
        case 7: {
            cout << "Exiting program" << endl;
            break;
        }
        default: {
            cout << "Invalid choice" << endl;
            break;
        }
        }
    }
};


