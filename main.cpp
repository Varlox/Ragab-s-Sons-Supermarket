#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int Max = 100;

struct customer
{
    string Id; // Change from int to string
    string password;
    string name;
    string phone;
    string location;
};


customer customers[Max];
int customer_count = 0;

struct date
{
    int day, month, year;
};

struct product
{
    int quantity;
    string code;
    string name;
    string Category;
    date productionDate;
    date expirationDate;
    double price;
};

product products[Max];
int product_count = 0;

struct order
{

    int customerId;
    string productName[Max];
    double totalPrice;
    int numProducts;
}currentOrder[Max];

void signup()
{
    customer c;
    cout << "Enter your ID: ";
    cin >> c.Id;

    cout << "Enter your password: ";
    cin >> c.password;
    cout << "Enter your name: ";
    cin >> c.name;
    cout << "Enter your phone number: ";
    cin >> c.phone;
    cout << "Enter your location: ";
    cin >> c.location;

    // Check for duplicate ID
    ifstream infile("customers.txt");
    string existingId;
    string password, name, phone, location;
    while (infile >> existingId >> password >> name >> phone >> location)
    {
        if (existingId == c.Id)
        {
            cout << "Error: ID already exists. Please use a different ID." << endl;
            return;
        }
    }
    infile.close();

    // Save the customer data to a file
    ofstream file("customers.txt", ios::app);
    if (file.is_open())
    {
        file << c.Id << " " << c.password << " " << c.name << " " << c.phone << " " << c.location << endl;
        file.close();
        cout << "Signup successful! Data saved to file." << endl;
    }
    else
    {
        cerr << "Error: Unable to open file to save data." << endl;
    }
}

bool login() {

    string inputId;
    string inputPassword;
    bool loginSuccessful = false;

    cout << "Enter your ID: ";
    cin >> inputId;

    cout << "Enter your password: ";
    cin >> inputPassword;

    ifstream file("customers.txt");
    if (file.is_open())
    {
        string id;
        string password, name, phone, location;

        while (file >> id >> password >> name >> phone >> location)
        {
            if (id == inputId && password == inputPassword)
            {
                cout << "Login successful!" << endl;
                cout << "Welcome, " << name << "!" << endl;
                loginSuccessful = true;
                return loginSuccessful;
                // break;
            }
        }
        file.close();

        if (!loginSuccessful)
        {
            cout << "Invalid ID or password." << endl;
            cout << "Please try again." << endl;
            return loginSuccessful;
        }
    }
    else
    {
        cerr << "Error: Unable to open file to verify login." << endl;
    }
}
void editCustomerData()
{
    string idToEdit;
    cout << "Enter the ID of the customer to edit: ";
    cin >> idToEdit;

    ifstream infile("customers.txt");
    ofstream tempFile("temp.txt");
    if (infile.is_open() && tempFile.is_open())
    {
        string id, password, name, phone, location;
        bool found = false;

        while (infile >> id >> password >> name >> phone >> location)
        {
            if (id == idToEdit)
            {
                found = true;
                cout << "Editing customer data for ID: " << id << endl;
                cout << "Enter new password: ";
                cin >> password;
                cout << "Enter new name: ";
                cin >> name;
                cout << "Enter new phone number: ";
                cin >> phone;
                cout << "Enter new location: ";
                cin >> location;
            }
            tempFile << id << " " << password << " " << name << " " << phone << " " << location << endl;
        }
        infile.close();
        tempFile.close();

        remove("customers.txt");
        rename("temp.txt", "customers.txt");

        if (found)
        {
            cout << "Customer data updated successfully." << endl;
        }
        else
        {
            cout << "Customer ID not found." << endl;
        }
    }
    else
    {
        cerr << "Error: Unable to open file." << endl;
    }
}

void displayProductMenu()
{
    if (product_count == 0)
    {
        cout << "No products available in the supermarket." << endl;
        return;
    }
    for (int i = 0; i < product_count;++i) {
        cout << i + 1 << ". " << products[i].name << endl;
        cout << "   Code: " << products[i].code << endl;
        cout << "   Price: $" << products[i].price << endl;
        cout << "   Quantity: " << products[i].quantity << endl;
        cout << "   Production Date: " << products[i].productionDate.day << "/"
            << products[i].productionDate.month << "/" << products[i].productionDate.year << endl;
        cout << "   Expiration Date: " << products[i].expirationDate.day << "/"
            << products[i].expirationDate.month << "/" << products[i].expirationDate.year << endl;
        cout << "--------------------------------------" << endl;
    }
}
int order_count;
void viewOrders_admin() {

    cin >> order_count;
    if (order_count == 0)
    {
        cout << "No orders to display." << endl;
        return;
    }

    for (int i = 0;i < order_count;i++) {
        cout << "\nOrder #" << i + 1 << " for Customer ID: " << currentOrder[i].customerId << endl;
        cout << "Products: ";
        for (int j = 0; j < currentOrder[i].numProducts; j++)
        {
            cout << currentOrder[i].productName[j];
            if (j < currentOrder[i].numProducts - 1)
                cout << ", ";
        }
        cout << "\nTotal Price: $" << currentOrder[i].totalPrice << endl;
    }
}
void viewOrder_user() {
    int IDindex;
    bool found = false;
    cout << "Please enter your ID : ";
    cin >> IDindex;
    for (int i = 0; i < order_count; i++)
    {
        if (currentOrder[i].customerId == IDindex)
        {
            found = true;
            cout << "\nOrder #" << i + 1 << " Customer ID: " << currentOrder[i].customerId << endl;
            cout << "Products: ";
            for (int j = 0; j < currentOrder[i].numProducts; j++)
            {
                cout << currentOrder[i].productName[j];
                if (j < currentOrder[i].numProducts - 1)
                    cout << ", ";
            }
            cout << "\nTotal price: $" << currentOrder[i].totalPrice << endl;
        }
    }
    if (!found) {
        cout << "This user has no order yet . " << endl;
        return;
    }
}

void processOrder()
{
    int customerId;
        cout << "Please enter your ID :";
        cin >> customerId;
    bool found = false;

    for (int i = 0; i < order_count; i++)
    {
        if (currentOrder[i].customerId == customerId)
        {
            found = true;
            double total = 0;
            for (int j = 0; j < currentOrder[i].numProducts;)
            {
                string p_name = currentOrder[i].productName[j];
                for (int k = 0; k < product_count; k++)
                {
                    if (products[k].name == p_name)
                    {
                        total += products[k].price;
                        break;
                    }
                }
            }
            cout << "Total price : " << total << endl;
            break;
        }

    }
    if (!found)
    {
        cout << "This user has no order yet . " << endl;
    }
}
void print_products() {
    if (product_count == 0) {
        cout << "No available products" << endl;
        return;

    }
    for (int i = 0; i < product_count; ++i) {
        cout << "Code: " << products[i].code << endl;
        cout << "Name: " << products[i].name << endl;
        cout << "Production Date: " << products[i].productionDate.day << "/"
            << products[i].productionDate.month << "/" << products[i].productionDate.year << endl;
        cout << "Expiration Date: " << products[i].expirationDate.day << "/"
            << products[i].expirationDate.month << "/" << products[i].expirationDate.year << endl;
        cout << "Price: $" << products[i].price << endl;
        cout << "***********" << endl;
    }
}
void saveProductsToFile()
{
    ofstream file("products.txt");
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file to save products." << endl;
        return;
    }

    for (int i = 0; i < product_count; i++)
    {
        file << products[i].code << " " << products[i].name << " " << products[i].Category << " "
            << products[i].productionDate.day << " " << products[i].productionDate.month << " " << products[i].productionDate.year << " "
            << products[i].expirationDate.day << " " << products[i].expirationDate.month << " " << products[i].expirationDate.year << " "
            << products[i].price << " " << products[i].quantity << endl;
    }

    file.close();
}

void addProduct()
{
    product p;
    cout << "Enter product code: ";
    cin >> p.code;
    cout << "Enter product name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Enter product category: ";
    cin.ignore();
    getline(cin, p.Category);
    cout << "Enter production date (dd mm yyyy): ";
    cin >> p.productionDate.day >> p.productionDate.month >> p.productionDate.year;
    cout << "Enter expiration date (dd mm yyyy): ";
    cin >> p.expirationDate.day >> p.expirationDate.month >> p.expirationDate.year;
    cout << "Enter product price: ";
    cin >> p.price;
    cout << "Enter product quantity: ";
    cin >> p.quantity;
    products[product_count] = p;

    // Save the product data to a file
    saveProductsToFile();
    cout << "Product added successfully!" << endl;
    product_count++;
}

void editProduct()
{
    product p;
    cout << "Enter the product code to edit: ";
    cout << "Enter new product code: ";
    cin >> p.code;
    cout << "Enter new product name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Enter new product category: ";
    cin.ignore();
    getline(cin, p.Category);
    cout << "Enter new production date (dd mm yyyy): ";
    cin >> p.productionDate.day >> p.productionDate.month >> p.productionDate.year;
    cout << "Enter new expiration date (dd mm yyyy): ";
    cin >> p.expirationDate.day >> p.expirationDate.month >> p.expirationDate.year;
    cout << "Enter new product price: ";
    cin >> p.price;
    cout << "Enter new product quantity: ";
    cin >> p.quantity;

    // Save the updated product data to a file
    saveProductsToFile();
    cout << "Product updated successfully!" << endl;
    product_count++;
}

void deleteProduct()
{
    string codeToDelete;
    cout << "Enter the product code to delete: ";
    cin >> codeToDelete;

    ifstream infile("products.txt");
    ofstream tempFile("temp.txt");

    if (!infile.is_open() || !tempFile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    bool found = false;
    product p;

    while (infile >> p.code >> p.name >> p.Category >> p.productionDate.day >> p.productionDate.month >> p.productionDate.year >> p.expirationDate.day >> p.expirationDate.month >> p.expirationDate.year >> p.price >> p.quantity)
    {
        if (p.code == codeToDelete)
        {
            found = true;
            cout << "Product with code " << codeToDelete << " has been deleted." << endl;
        }
        else
        {
            // Write all other products to the temp file
            tempFile << p.code << " " << p.name << " " << p.Category << " "
                << p.productionDate.day << " " << p.productionDate.month << " " << p.productionDate.year << " "
                << p.expirationDate.day << " " << p.expirationDate.month << " " << p.expirationDate.year << " "
                << p.price << " " << p.quantity << endl;
        }
    }
    infile.close();
    tempFile.close();
    product_count--;

    // Replace the original file with the updated file
    remove("products.txt");
    rename("temp.txt", "products.txt");

    if (!found)
    {
        cout << "Product with code " << codeToDelete << " not found." << endl;
    }
}

void showAllProducts()
{
    cout << "All Products:" << endl;
    cout << "--------------------------------------" << endl;
    for (int i = 0; i < product_count; ++i) {
        cout << "Code: " << products[i].code << endl;
        cout << "Name: " << products[i].name << endl;
        cout << "Production Date: " << products[i].productionDate.day << "/"
            << products[i].productionDate.month << "/" << products[i].productionDate.year << endl;
        cout << "Expiration Date: " << products[i].expirationDate.day << "/"
            << products[i].expirationDate.month << "/" << products[i].expirationDate.year << endl;
        cout << "Price: $" << products[i].price << endl;
        cout << "***********" << endl;
        saveProductsToFile();
    }
}

void createOrder()
{
    int created_order = 0;
    string choise_product, choise_category, answer;
    do {
        cout << "please enter your wanted product : ";
        cin.ignore();
        getline(cin, choise_product);
        cout << "please enter your wanted category : ";
        cin.ignore();
        getline(cin, choise_category);
        cout << "Do you want to add product ?(yes/no) : ";
        cin.ignore();
        getline(cin, answer);
    } while (answer == "yes");
    if (answer == "no" || answer == "No" || answer == "NO")
    {
        cout << "the order created successfully !" << endl;
    }
    created_order++;
}
void searchProductByName(const string& name)
{
    bool found = false;
    for (int i = 0; i < product_count; i++)
    {
        if (products[i].name == name)
        {
            found = true;
            cout << "Product found: " << products[i].name << endl;
            cout << "Code: " << products[i].code << ", Price: $" << products[i].price << endl;
            break;
        }
    }

    if (!found)
    {
        cout << "Product not found." << endl;
    }
}

void MenuAdmin()
{
    string choice;
    bool running = true;

    while (running)
    {
        cout << endl;
        cout << "******Welcome to Ragab`s sons Supermarket******" << endl;
        cout << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Edit Product" << endl;
        cout << "3. Delete Product" << endl;
        cout << "4. Show All Products" << endl;
        cout << "5. View Orders" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        getline(cin, choice); // Read input as a string

        if (choice == "1")
        {
            addProduct();
        }
        else if (choice == "2")
        {
            editProduct();
        }
        else if (choice == "3")
        {
            deleteProduct();
        }
        else if (choice == "4")
        {
            showAllProducts();
        }
        else if (choice == "5")
        {
            viewOrders_admin();
        }
        else if (choice == "6")
        {
            cout << "Exiting..." << endl;
            running = false;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void user_menu()
{
    string choice;

    do
    {
        cout << endl;
        cout << "******Welcome to Ragab`s sons Supermarket******" << endl;
        cout << endl;
        cout << "1. Edit Customer Data" << endl;
        cout << "2. Display Menu" << endl;
        cout << "3. Create Order" << endl;
        cout << "4. View Order" << endl;
        cout << "5. Calculate Total Price" << endl;
        cout << "6. Products Info" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        getline(cin, choice); // Read input as a string

        if (choice == "1")
        {
            editCustomerData();
        }
        else if (choice == "2")
        {
            displayProductMenu();
        }
        else if (choice == "3")
        {
            createOrder();
        }
        else if (choice == "4")
        {
            viewOrder_user();
        }
        else if (choice == "5")
        {
            processOrder();
        }
        else if (choice == "6")
        {
            print_products();
        }
        else if (choice == "7")
        {
            cout << "Logging out..." << endl;
            return;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != "7");
}

int login_menu() {
    int choice;
    cout << "1. Admin" << endl;
    cout << "2. User" << endl;
    cin >> choice;
    if (choice == 1) {
        //        Admin_login();
        MenuAdmin();
        return choice;
    }
    if (choice == 2) {
        login();
        user_menu();
        return choice;
    }

}



int main()
{
    string choice;
    do
    {
        cout << "1. Sign up" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        getline(cin, choice); // Read input as a string

        if (choice == "1")
        {
            signup();
        }
        else if (choice == "2")
        {
            login_menu();
        }
        else if (choice == "3")
        {
            cout << "Exiting..." << endl;
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != "3");

    return 0;
}
