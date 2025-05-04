#include <iostream>
#include <string>
#include <fstream>
#include<limits>

using namespace std;

const int Max = 100;

struct customer
{
    string Id;
    string password;
    string name;
    string phone;
    string location;
};

customer customers[Max];
int customer_count = 0;

struct date
{
    string day, month, year;
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
int order_count = 0;

struct order
{
    int customerId;
    string productName[Max];
    double totalPrice;
    int numProducts;
} currentOrder[Max];

void saveToFile()
{
    // Save customers to file
    ofstream file("customers.txt");
    if (file.is_open()) {
        for (int i = 0; i < customer_count; i++) {
            file << customers[i].Id << " "
                << customers[i].password << " "
                << customers[i].name << " "
                << customers[i].phone << " "
                << customers[i].location << endl;
        }
        file.close();
        cout << "Data saved to file successfully." << endl;
    }
    else {
        cerr << "Error: Unable to open file for saving." << endl;
    }

    // Save products to file
    ofstream filee("products.txt");
    if (!filee.is_open())
    {
        cerr << "Error: Unable to open file to save products." << endl;
        return;
    }

    for (int i = 0; i < product_count; i++)
    {
        filee << products[i].code << " " << products[i].name << " " << products[i].Category << " "
            << products[i].productionDate.day << " " << products[i].productionDate.month << " " << products[i].productionDate.year << " "
            << products[i].expirationDate.day << " " << products[i].expirationDate.month << " " << products[i].expirationDate.year << " "
            << products[i].price << " " << products[i].quantity << endl;
    }

    filee.close();

	// Save products to file

	ofstream orderfile("orders.txt");
	if (!orderfile.is_open())
	{
		cerr << "Error: Unable to open file to save orders." << endl;
		return;
	}
	for (int i = 0;i < order_count;i++)
	{
		orderfile << currentOrder[i].customerId << " " << currentOrder[i].numProducts << " " << currentOrder[i].totalPrice << endl;
		for (int j = 0;j < currentOrder[i].numProducts;j++)
		{
			orderfile << currentOrder[i].productName[j] << " ";
		}
		orderfile << endl;
	}

	orderfile.close();
}
void signup()
{
    if (customer_count >= Max) {
        cout << "Error: Customer limit reached." << endl;
        return;
    }

    customer c;
    cout << "Enter your ID: ";
    cin >> c.Id;

    // Check for duplicate ID
    for (int i = 0; i < customer_count; i++) {
        if (customers[i].Id == c.Id) {
            cout << "Error: ID already exists. Please use a different ID." << endl;
            return;
        }
    }

    cout << "Enter your password: ";
    cin >> c.password;
    cout << "Enter your name: ";
    cin >> c.name;
    cout << "Enter your phone number: ";
    cin >> c.phone;
    cout << "Enter your location: ";
    cin >> c.location;

    // Add new customer to array
    customers[customer_count++] = c;

    cout << "Signup successful!" << endl;
   
}
void addProduct()
{
    if (product_count >= Max)
    {
        cout << "Error: Cannot add more products. Maximum limit reached." << endl;
        return;
    }

    product p;
    cout << "Enter product code: ";
    cin >> p.code;
    cin.ignore();
    cout << "Enter product name: ";
    //cin.ignore();
    getline(cin, p.name); // Fixed to handle multi-word product names

    // Predefined categories
    const string categories[] = { "Bakery", "Dairy", "Snacks", "Sweets", "Beverages" };
    int categoryChoice;

    while (true)
    {
        cout << "Choose a category:" << endl;
        for (int i = 0; i < 5; i++)
        {
            cout << i + 1 << ". " << categories[i] << endl;
        }

        cin >> categoryChoice;

        if (categoryChoice >= 1 && categoryChoice <= 5)
        {
            p.Category = categories[categoryChoice - 1];
            break;
        }
        else
        {
            cout << "Invalid category choice! Please try again." << endl;
        }
    }

    cout << "Enter production date (dd mm yyyy): ";
    cin >> p.productionDate.day >> p.productionDate.month >> p.productionDate.year;

    cout << "Enter expiration date (dd mm yyyy): ";
    cin >> p.expirationDate.day >> p.expirationDate.month >> p.expirationDate.year;

    cout << "Enter product price: ";
    cin >> p.price;

    cout << "Enter product quantity: ";
    cin >> p.quantity;

    // Add the product to the array
    products[product_count++] = p;


    cout << "Product added successfully!" << endl;
    //product_count++;
}

void editProduct()
{
    string codeToEdit;
    cout << "Enter the product code to edit: ";
    cin >> codeToEdit;

    bool found = false;

    for (int i = 0; i < product_count; i++)
    {
        if (products[i].code == codeToEdit)
        {
            found = true;
            cout << "Enter new product name: ";
            cin >> products[i].name;
            cout << "Enter new product category: ";
            cin >> products[i].Category;
            cout << "Enter new production date (dd mm yyyy): ";
            cin >> products[i].productionDate.day >> products[i].productionDate.month >> products[i].productionDate.year;
            cout << "Enter new expiration date (dd mm yyyy): ";
            cin >> products[i].expirationDate.day >> products[i].expirationDate.month >> products[i].expirationDate.year;
            cout << "Enter new product price: ";
            cin >> products[i].price;
            cout << "Enter new product quantity: ";
            cin >> products[i].quantity;
            cout << "Product updated successfully!" << endl;
            break;
        }
    }

    if (!found)
    {
        cout << "Product with code " << codeToEdit << " not found in the array." << endl;
    }
}
void deleteProduct(string codeToDelete)
{
    bool found = false;

    for (int i = 0; i < product_count; i++)
    {
        if (products[i].code == codeToDelete)
        {
            found = true;
            // Shift all products after the found product one position to the left
            for (int j = i; j < product_count - 1; j++)
            {
                products[j] = products[j + 1];
            }
            product_count--; // Decrease the product count
            cout << "Product with code " << codeToDelete << " has been deleted." << endl;
            break;
        }
    }

    if (!found)
    {
        cout << "Product with code " << codeToDelete << " not found." << endl;
    }
}

void showAllProducts()
{
    cout << "All Products:" << endl;
    cout << "--------------------------------------" << endl;
    for (int i = 0; i < product_count; ++i)
    {
        cout << "Code: " << products[i].code << endl;
        cout << "Name: " << products[i].name << endl;
        cout << "Production Date: " << products[i].productionDate.day << "/"
            << products[i].productionDate.month << "/" << products[i].productionDate.year << endl;
        cout << "Expiration Date: " << products[i].expirationDate.day << "/"
            << products[i].expirationDate.month << "/" << products[i].expirationDate.year << endl;
        cout << "Price: $" << products[i].price << endl;
        cout << "*" << endl;

    }
}

void createOrder()
{
    order newOrder;
    newOrder.numProducts = 0;
    newOrder.totalPrice = 0;

    cout << "Enter your customer ID: ";
    cin >> newOrder.customerId;

    string productName;
    string choice;
    while (true)
    {
        cout << "Enter product name: ";
        cin >> productName;

        bool found = false;
        for (int i = 0; i < product_count; i++)
        {
            if (products[i].name == productName)
            {
                found = true;
                newOrder.productName[newOrder.numProducts++] = productName;
                newOrder.totalPrice += products[i].price;
                break;
            }
        }

        if (!found)
        {
            cout << "Product not found!" << endl;
        }

        cout << "Do you want to add another product? (y/n): ";
        cin >> choice;
        if (choice == "n" || choice == "N")
            break;
    }

    currentOrder[order_count++] = newOrder;
    cout << "Order created successfully! Total price: $" << newOrder.totalPrice << endl;
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
void viewOrders_admin()
{

    if (order_count == 0)
    {
        cout << "No orders to display." << endl;
        return;
    }

    for (int i = 0; i < order_count; i++)
    {
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

void MenuAdmin()
{
    string choice;
    bool running = true;

    while (running)
    {
        cout << endl;
        cout << "****** Welcome to Ragab`s Sons Supermarket ******" << endl;
        cout << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Edit Product" << endl;
        cout << "3. Delete Product" << endl;
        cout << "4. Show All Products" << endl;
        cout << "5. View Orders" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

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
            string codeToDelete;
            cout << "Enter the product code to delete: ";
            cin >> codeToDelete;
            deleteProduct(codeToDelete);
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
            // Save all products before exiting the admin menu
            saveToFile();
            cout << "Exiting admin menu... All changes have been saved." << endl;
            running = false;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void editCustomerData(string idToEdit) {
    bool found = false;

    // Clean whitespace or leftover newline before using getline
    cin.ignore();

    for (int i = 0; i < customer_count; i++) {
        if (customers[i].Id == idToEdit) {
            found = true;
            cout << "Editing customer data for ID: " << customers[i].Id << endl;

            string newPassword, newName, newPhone, newLocation;

            cout << "Enter new password (or press Enter to keep current): ";
            getline(cin, newPassword);
            if (!newPassword.empty())
                customers[i].password = newPassword;

            cout << "Enter new name (or press Enter to keep current): ";
            getline(cin, newName);
            if (!newName.empty())
                customers[i].name = newName;

            cout << "Enter new phone number (or press Enter to keep current): ";
            getline(cin, newPhone);
            if (!newPhone.empty())
                customers[i].phone = newPhone;

            cout << "Enter new location (or press Enter to keep current): ";
            getline(cin, newLocation);
            if (!newLocation.empty())
                customers[i].location = newLocation;

            saveToFile();
            cout << "Customer data updated successfully." << endl;
            return;
        }
    }

    if (!found) {
        cout << "Customer ID not found." << endl;
    }
}

void viewOrder_user(int IDindex)
{

    bool found = false;
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
    if (!found)
    {
        cout << "there is no order created. " << endl;
        return;
    }
}

void displayProductMenu()
{
    if (product_count == 0)
    {
        cout << "No products available in the supermarket." << endl;
        return;
    }

    // Step 1: Display categories
    cout << "Available Categories:" << endl;
    cout << "1. Bakery" << endl;
    cout << "2. Dairy" << endl;
    cout << "3. Snacks" << endl;
    cout << "4. Sweets" << endl;
    cout << "5. Beverages" << endl;
    cout << "6. Dry Food" << endl;
    cout << "Enter the number of the category you want to view: ";
    int categoryChoice;
    cin >> categoryChoice;
    cin.ignore();

    // Step 2: Determine the selected category
    string selectedCategory;
    switch (categoryChoice)
    {
    case 1:
        selectedCategory = "Bakery";
        break;
    case 2:
        selectedCategory = "Dairy";
        break;
    case 3:
        selectedCategory = "Snacks";
        break;
    case 4:
        selectedCategory = "Sweets";
        break;
    case 5:
        selectedCategory = "Beverages";
        break;
    case 6:
        selectedCategory = "Dry Food";
        break;
    default:
        cout << "Invalid category choice!" << endl;
        return;
    }

    // Step 3: Display products in the selected category
    cout << "Products in " << selectedCategory << " category:" << endl;
    cout << "--------------------------------------" << endl;
    bool found = false;
    for (int i = 0; i < product_count; i++)
    {
        if (products[i].Category == selectedCategory)
        {
            found = true;
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

    if (!found)
    {
        cout << "No products available in the selected category." << endl;
    }
}

void user_menu()
{
    string choice;

    do
    {
        cout << endl;
        cout << "*Welcome to Ragab`s sons Supermarket*" << endl;
        cout << endl;
        cout << "1. Edit Customer Data" << endl;
        cout << "2. Display Menu" << endl;
        cout << "3. Create Order" << endl;
        cout << "4. View Order" << endl;
        cout << "5. Products Info" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice; // Read input as a string

        if (choice == "1")
        {
            string idToEdit;
            cout << "Enter the ID of the customer to edit: ";
            cin >> idToEdit;
            editCustomerData(idToEdit);
        }
        else if (choice == "2")
        {
            showAllProducts();
        }
        else if (choice == "3")
        {
            createOrder();
        }
        else if (choice == "4")
        {
            int IDindex;
            cout << "Please enter your ID : ";
            cin >> IDindex;
            viewOrder_user(IDindex);
        }
        else if (choice == "5")
        {
            displayProductMenu();
        }
        else if (choice == "6")
        {
            cout << "Logging out..." << endl;
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != "7"); // Loop will now exit correctly when "7" is entered.
}
void login() {
    const string adminId = "admin";
    const string adminPassword = "1234";

    string inputId;
    string inputPassword;

    while (true)
    {
        cout << "Enter your ID (or type 'cancel' to cancel): ";

        cin >> inputId;

        if (inputId == "cancel")
        {
            cout << "Login cancelled." << endl;
            break;

        }

        cout << "Enter your password: ";
        cin >> inputPassword;

        // Admin login check
        if (inputId == adminId && inputPassword == adminPassword)
        {
            cout << "Admin login successful!" << endl;
            MenuAdmin();
            return;
        }
        for (int i = 0; i < customer_count; i++)
        {
            if (customers[i].Id == inputId && customers[i].password == inputPassword)
            {
                cout << "welcome " << customers[i].name << endl;
                user_menu();
                return;
            }

        }
        cout << "the password or id is not true. try again" << endl;
    }
}
bool loadAllFromFile() {
    // Load customers
    ifstream custFile("customers.txt");
    if (custFile.is_open()) {
        customer_count = 0;
        while (custFile >> customers[customer_count].Id
            >> customers[customer_count].password
            >> customers[customer_count].name
            >> customers[customer_count].phone
            >> customers[customer_count].location) {
            customer_count++;
            if (customer_count >= Max) {
                cout << "Warning: Max customer limit reached while loading." << endl;
                break;
            }
        }
        custFile.close();

    }
    else {
        cerr << "Warning: customers.txt not found." << endl;
    }

    // Load products
    ifstream prodFile("products.txt");
    if (!prodFile.is_open()) {
        cerr << "Error: Unable to open products.txt for loading." << endl;
        return false;
    }

    product_count = 0;
    while (prodFile.peek() != EOF) {
        if (!(prodFile >> products[product_count].code)) break;
        prodFile.ignore(); 

        prodFile >> products[product_count].name;
        prodFile.ignore(); 
        prodFile >> products[product_count].Category;
        prodFile.ignore();
        prodFile >> products[product_count].productionDate.day;
        prodFile.ignore(); 
        prodFile >> products[product_count].productionDate.month;
        prodFile.ignore(); 
        prodFile >> products[product_count].productionDate.year;
        prodFile.ignore(); 
        prodFile >> products[product_count].expirationDate.day;
        prodFile.ignore();
        prodFile >> products[product_count].expirationDate.month;
        prodFile.ignore(); 
        prodFile >> products[product_count].expirationDate.year;
        prodFile.ignore(); 
        prodFile >> products[product_count].price;
        prodFile.ignore(); 
        prodFile >> products[product_count].quantity;
        prodFile.ignore(numeric_limits<streamsize>::max(), '\n'); // skip to next line

        product_count++;
        if (product_count >= Max) {
            cout << "Warning: Max product limit reached while loading." << endl;
            break;
        }
    }

    prodFile.close();

    // Load orders
	ifstream orderfile("orders.txt");
    if (!orderfile.is_open()) {

		cerr << "Error: Unable to open orders.txt for loading." << endl;
    }
	order_count = 0;
    while (orderfile.peek() != EOF) {
		orderfile >> currentOrder[order_count].customerId;
		orderfile >> currentOrder[order_count].numProducts;
		orderfile >> currentOrder[order_count].totalPrice;
		for (int j = 0; j < currentOrder[order_count].numProducts; j++)
		{
			orderfile >> currentOrder[order_count].productName[j];
		}
		order_count++;
    
    
    }


    return true;
}
int main()
{
    loadAllFromFile();
    string choice;
    do
    {
        cout << "1. Sign up" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice; // Read input as a string

        if (choice == "1")
        {
            signup();
        }
        else if (choice == "2")
        {
            login();
        }
        else if (choice == "3")
        {
            // Save all products to 'the file before exiting

            cout << "Exiting... All products have been saved." << endl;
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != "3");
    saveToFile();
    return 0;
}