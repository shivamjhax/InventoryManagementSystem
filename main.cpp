
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>
using namespace std;

struct Product {
    int id;
    string name;
    double price;
    int quantity;
};

vector<Product> products;

// Find Product Index
int findProduct(int id) {
    for (int i = 0; i < products.size(); i++) {
        if (products[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Add Product

void addProduct() {
    Product p;

    cout << "\nEnter Product ID: ";

    if (!(cin >> p.id)) {
        cout << "\nInvalid Product ID!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (findProduct(p.id) != -1) {
        cout << "\nProduct ID already exists!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Product Name: ";
    getline(cin, p.name);

    if (p.name.empty()) {
        cout << "\nProduct name cannot be empty!\n";
        return;
    }

    cout << "Enter Product Price: ";

    if (!(cin >> p.price) || p.price <= 0) {
        cout << "\nInvalid price! Enter numbers only.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Enter Product Quantity: ";

    if (!(cin >> p.quantity) || p.quantity < 0) {
        cout << "\nInvalid quantity! Enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    products.push_back(p);

    cout << "\nProduct added successfully!\n";
}

// View All Products
void viewProducts() {
    if (products.empty()) {
        cout << "\nNo products available!\n";
        return;
    }

    cout << "\n========== PRODUCT LIST ==========\n";

    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(12) << "Price"
         << setw(10) << "Quantity" << endl;

    for (const Product &p : products) {
        cout << left << setw(10) << p.id
             << setw(20) << p.name
             << setw(12) << fixed << setprecision(2) << p.price
             << setw(10) << p.quantity << endl;
    }
}

// Search Product

void searchProduct() {
    int id;

    cout << "\nEnter Product ID to search: ";

    if (!(cin >> id)) {
        cout << "\nInvalid Product ID! Enter numbers only.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findProduct(id);

    if (index == -1) {
        cout << "\nProduct not found!\n";
        return;
    }

    Product p = products[index];

    cout << "\nProduct Found!\n";
    cout << "ID: " << p.id << endl;
    cout << "Name: " << p.name << endl;
    cout << "Price: Rs. " << p.price << endl;
    cout << "Quantity: " << p.quantity << endl;
}

// Update Product


void updateProduct() {
    int id;

    cout << "\nEnter Product ID to update: ";

    if (!(cin >> id)) {
        cout << "\nInvalid Product ID! Enter numbers only.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findProduct(id);

    if (index == -1) {
        cout << "\nProduct not found!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter New Product Name: ";
    getline(cin, products[index].name);

    if (products[index].name.empty()) {
        cout << "\nProduct name cannot be empty!\n";
        return;
    }

    cout << "Enter New Price: ";

    if (!(cin >> products[index].price) ||
        products[index].price <= 0) {
        cout << "\nInvalid price!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Enter New Quantity: ";

    if (!(cin >> products[index].quantity) ||
        products[index].quantity < 0) {
        cout << "\nInvalid quantity!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "\nProduct updated successfully!\n";
}



// Delete Product
void deleteProduct() {
    int id;

    cout << "\nEnter Product ID to delete: ";
    cin >> id;

    int index = findProduct(id);

    if (index == -1) {
        cout << "\nProduct not found!\n";
        return;
    }

    products.erase(products.begin() + index);

    cout << "\nProduct deleted successfully!\n";
}

// Update Stock
void updateStock() {
    int id, amount, choice;

    cout << "\nEnter Product ID: ";
    cin >> id;

    int index = findProduct(id);

    if (index == -1) {
        cout << "\nProduct not found!\n";
        return;
    }

    cout << "\n1. Add Stock\n";
    cout << "2. Remove Stock\n";
    cout << "Enter choice: ";
    cin >> choice;

    cout << "Enter Quantity: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "\nInvalid quantity!\n";
        return;
    }

    if (choice == 1) {
        products[index].quantity += amount;
        cout << "\nStock increased successfully!\n";
    }
    else if (choice == 2) {
        if (amount > products[index].quantity) {
            cout << "\nInsufficient stock!\n";
            return;
        }

        products[index].quantity -= amount;
        cout << "\nStock decreased successfully!\n";
    }
    else {
        cout << "\nInvalid choice!\n";
    }
}

// Low Stock Alert
void lowStockAlert() {
    bool found = false;

    cout << "\n========== LOW STOCK ALERT ==========\n";

    for (const Product &p : products) {
        if (p.quantity <= 5) {
            cout << "\nID: " << p.id
                 << "\nName: " << p.name
                 << "\nRemaining Quantity: " << p.quantity << endl;

            found = true;
        }
    }

    if (!found) {
        cout << "\nNo low-stock products!\n";
    }
}

// Generate Bill
void generateBill() {
    int id, quantity;
    double total = 0;

    char more;

    cout << "\n========== CUSTOMER BILL ==========\n";

    do {
        cout << "\nEnter Product ID: ";
        cin >> id;

        int index = findProduct(id);

        if (index == -1) {
            cout << "\nProduct not found!\n";
        }
        else {
            cout << "Enter Quantity: ";
            cin >> quantity;

            if (quantity <= 0) {
                cout << "\nInvalid quantity!\n";
            }
            else if (quantity > products[index].quantity) {
                cout << "\nInsufficient stock!\n";
            }
            else {
                double amount = products[index].price * quantity;

                total += amount;
                products[index].quantity -= quantity;

                cout << "\nProduct: " << products[index].name;
                cout << "\nAmount: Rs. " << amount << endl;
            }
        }

        cout << "\nAdd another product? (y/n): ";
        cin >> more;

    } while (more == 'y' || more == 'Y');

    cout << "\n========== FINAL BILL ==========\n";
    cout << "Total Amount: Rs. " << fixed
         << setprecision(2) << total << endl;
}

// Total Inventory Value
void totalInventoryValue() {
    double total = 0;

    for (const Product &p : products) {
        total += p.price * p.quantity;
    }

    cout << "\nTotal Inventory Value: Rs. "
         << fixed << setprecision(2) << total << endl;
}

// Save Products to File
void saveProducts() {
    ofstream file("products.txt");

    if (!file) {
        cout << "\nError saving data!\n";
        return;
    }

    for (const Product &p : products) {
        file << p.id << "|"
             << p.name << "|"
             << p.price << "|"
             << p.quantity << endl;
    }

    file.close();
}

// Load Products from File
void loadProducts() {
    ifstream file("products.txt");

    if (!file) {
        return;
    }

    products.clear();

    Product p;
    string line;

    while (getline(file, line)) {
        size_t a = line.find('|');
        size_t b = line.find('|', a + 1);
        size_t c = line.find('|', b + 1);

        if (a == string::npos ||
            b == string::npos ||
            c == string::npos) {
            continue;
        }

        try {
            p.id = stoi(line.substr(0, a));
            p.name = line.substr(a + 1, b - a - 1);
            p.price = stod(line.substr(b + 1, c - b - 1));
            p.quantity = stoi(line.substr(c + 1));

            if (p.price > 0 && p.quantity >= 0 &&
                findProduct(p.id) == -1) {
                products.push_back(p);
            }
        }
        catch (...) {
            continue;
        }
    }

    file.close();
}

// Main Function
int main() {
    int choice;

    loadProducts();

    do {
        cout << "\n===== INVENTORY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Product\n";
        cout << "2. View All Products\n";
        cout << "3. Search Product\n";
        cout << "4. Update Product\n";
        cout << "5. Delete Product\n";
        cout << "6. Update Stock\n";
        cout << "7. Low Stock Alert\n";
        cout << "8. Generate Bill\n";
        cout << "9. Total Inventory Value\n";
        cout << "0. Exit\n";

        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cout << "\nInvalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {

            case 1:
                addProduct();
                break;

            case 2:
                viewProducts();
                break;

            case 3:
                searchProduct();
                break;

            case 4:
                updateProduct();
                break;

            case 5:
                deleteProduct();
                break;

            case 6:
                updateStock();
                break;

            case 7:
                lowStockAlert();
                break;

            case 8:
                generateBill();
                break;

            case 9:
                totalInventoryValue();
                break;

            case 0:
                saveProducts();
                cout << "\nData saved. Exiting program...\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
