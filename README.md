l#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <thread>
#include <chrono>

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
    string customerId;
    string productName[Max];
    double totalPrice;
    int numProducts;
} currentOrder[Max];

void saveToFile()
{
    // Save customers to file
    ofstream file("customers.txt");
    if (file.is_open())
    {
        for (int i = 0; i < customer_count; i++)
        {
            file << customers[i].Id << " "
                << customers[i].password << " "
                << customers[i].name << " "
                << customers[i].phone << " "
                << customers[i].location << endl;
        }
        file.close();
        cout << "Data saved to file successfully." << endl;
    }
    else
    {
        cerr << "\033[1;31mError: Unable to open file for saving.\033[0m" << endl;
    }

    // Save products to file
    ofstream filee("products.txt");
    if (!filee.is_open())
    {
        cerr << "\033[1;31mError: Unable to open file to save products.\033[0m" << endl;
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

    // Save orders to file
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
    if (customer_count >= Max)
    {
        cout << "\033[1;31mError: Customer limit reached.\033[0m" << endl;
        return;
    }

    customer c;
    cout << "Enter your ID: ";
    cin >> c.Id;

    // Check for duplicate ID
    for (int i = 0; i < customer_count; i++)
    {
        if (customers[i].Id == c.Id)
        {
            cout << "\033[1;31mError: ID already exists. Please use a different ID.\033[0m" << endl;
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

    cout << "\033[1;32mSignup successful!\033[0m" << endl; // Green for success
}

bool isValidDate(int day, int month, int year)
{
    if (month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    if (month == 2)
    {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeap ? 29 : 28))
            return false;
    }
    return true;
}

void addProduct()
{
    if (product_count >= Max)
    {
        cout << "\033[1;31mError: Cannot add more products. Maximum limit reached.\033[0m" << endl;
        return;
    }

    product p;
    cout << "Enter product code: ";
    cin >> p.code;
    cin.ignore();
    cout << "Enter product name: ";
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
            cout << "\033[1;31mInvalid category choice! Please try again.\033[0m" << endl;
        }
    }

    // Validate production date
    while (true)
    {
        cout << "Enter production date (dd mm yyyy): ";
        cin >> p.productionDate.day >> p.productionDate.month >> p.productionDate.year;
        if (isValidDate(stoi(p.productionDate.day), stoi(p.productionDate.month), stoi(p.productionDate.year)))
        {
            break;
        }
        else
        {
            cout << "\033[1;31mInvalid production date! Please try again.\033[0m" << endl;
        }
    }

    // Validate expiration date
    while (true)
    {
        cout << "Enter expiration date (dd mm yyyy): ";
        cin >> p.expirationDate.day >> p.expirationDate.month >> p.expirationDate.year;
        if (isValidDate(stoi(p.expirationDate.day), stoi(p.expirationDate.month), stoi(p.expirationDate.year)))
        {
            break;
        }
        else
        {
            cout << "\033[1;31mInvalid expiration date! Please try again.\033[0m" << endl;
        }
    }

    cout << "Enter product price: ";
    cin >> p.price;

    cout << "Enter product quantity: ";
    cin >> p.quantity;

    // Add the product to the array
    products[product_count++] = p;

    cout << "\033[1;32mProduct added successfully!\033[0m" << endl; // Green for success
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

            // Validate production date
            while (true)
            {
                cout << "Enter new production date (dd mm yyyy): ";
                cin >> products[i].productionDate.day >> products[i].productionDate.month >> products[i].productionDate.year;
                if (isValidDate(stoi(products[i].productionDate.day), stoi(products[i].productionDate.month), stoi(products[i].productionDate.year)))
                {
                    break;
                }
                else
                {
                    cout << "\033[1;31mInvalid production date! Please try again.\033[0m" << endl;
                }
            }

            // Validate expiration date
            while (true)
            {
                cout << "Enter new expiration date (dd mm yyyy): ";
                cin >> products[i].expirationDate.day >> products[i].expirationDate.month >> products[i].expirationDate.year;
                if (isValidDate(stoi(products[i].expirationDate.day), stoi(products[i].expirationDate.month), stoi(products[i].expirationDate.year)))
                {
                    break;
                }
                else
                {
                    cout << "\033[1;31mInvalid expiration date! Please try again.\033[0m" << endl;
                }
            }

            cout << "Enter new product price: ";
            cin >> products[i].price;
            cout << "Enter new product quantity: ";
            cin >> products[i].quantity;
            cout << "\033[1;32mProduct updated successfully!\033[0m" << endl; // Green for success
            break;
        }
    }

    if (!found)
    {
        cout << "\033[1;31mProduct with code " << codeToEdit << " not found in the array.\033[0m" << endl;
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
            product_count--;                                                                               // Decrease the product count
            cout << "\033[1;32mProduct with code " << codeToDelete << " has been deleted.\033[0m" << endl; // Green for success
            break;
        }
    }

    if (!found)
    {
        cout << "\033[1;31mProduct with code " << codeToDelete << " not found.\033[0m" << endl;
    }
}

void showAllProducts()
{
    cout << "All Products:" << endl;
    cout << "--------------------------------------" << endl;
    for (int i = 0; i < product_count; i++)
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

void showAllProductsPaginated()
{
    const int itemsPerPage = 5;
    int currentPage = 0;

    while (true)
    {
        int start = currentPage * itemsPerPage;
        int end = min(start + itemsPerPage, product_count);

        cout << "Products (Page " << currentPage + 1 << "):" << endl;
        for (int i = start; i < end; i++)
        {
            cout << i + 1 << ". " << products[i].name << " - $" << products[i].price << endl;
        }

        if (end == product_count)
        {
            cout << "End of list." << endl;
            break;
        }

        cout << "Press 'n' for next page or 'q' to quit: ";
        char choice;
        cin >> choice;
        if (choice == 'q')
            break;
        currentPage++;
    }
}

void createOrder(string inputId)
{
    if (order_count >= Max)
    {
        cout << "\033[1;31mError: Cannot create more orders. Maximum limit reached.\033[0m" << endl;
        return;
    }

    order newOrder;
    newOrder.numProducts = 0;
    newOrder.totalPrice = 0;
    newOrder.customerId = inputId;

    string productName;
    string choice;
    while (true)
    {
        cout << "Enter product name: ";
        cin >> productName;

        bool found = false;
        for (int i = 0; i < product_count; i++)
        {
            if (products[i].name == productName) // Match product name
            {
                found = true;

                int quantity;
                cout << "Enter quantity: ";
                cin >> quantity;

                // Check if sufficient quantity is available
                if (quantity > products[i].quantity)
                {
                    cout << "\033[1;31mError: Only " << products[i].quantity << " units available in stock.\033[0m" << endl;
                    break;
                }

                // Add product to the order
                newOrder.productName[newOrder.numProducts++] = productName;
                newOrder.totalPrice += products[i].price * quantity;

                // Deduct quantity from stock
                products[i].quantity -= quantity;

                cout << "\033[1;32mProduct added to order successfully!\033[0m" << endl; // Green for success
                break;
            }
        }

        if (!found)
        {
            cout << "\033[1;31mError: Product not found!\033[0m" << endl;
        }

        cout << "Do you want to add another product? (y/n): ";
        cin >> choice;
        if (choice == "n" || choice == "N")
            break;
    }

    if (newOrder.numProducts > 0)
    {
        currentOrder[order_count++] = newOrder;
        cout << "\033[1;32mOrder created successfully! Total price: $" << newOrder.totalPrice << "\033[0m" << endl; // Green for success
    }
    else
    {
        cout << "\033[1;31mNo valid products were added to the order. Order was not created.\033[0m" << endl;
    }
}

void viewOrders_admin()
{

    if (order_count == 0)
    {
        cout << "\033[1;31mNo orders to display.\033[0m" << endl; // Red text
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
        cout << endl;
        cout << "=========================================" << endl;
        cout << "\033[1;32m         Ragab's Sons Supermarket        \033[0m" << endl; // Green text
        cout << "\033[1;32m         Admin Dashboard                 \033[0m" << endl;
        cout << "=========================================" << endl;
        cout << "Total Customers: " << customer_count << endl;
        cout << "Total Products: " << product_count << endl;
        cout << "Total Orders: " << order_count << endl;
        cout << "=========================================" << endl;
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
            cout << "\033[1;31mInvalid choice. Please try again.\033[0m" << endl; // Red text
        }
    }
}

void editCustomerData(string idToEdit)
{
    bool found = false;

    // Clean whitespace or leftover newline before using getline
    cin.ignore();

    for (int i = 0; i < customer_count; i++)
    {
        if (customers[i].Id == idToEdit)
        {
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

    if (!found)
    {
        cout << "\033[1;31mCustomer ID not found.\033[0m" << endl; // Red text
    }
}

void viewOrder_user(string IDindex)
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
        cout << "\033[1;31mThere is no order created. \033[0m" << endl; // Red text
        return;
    }
}

void displayProductMenu()
{
    if (product_count == 0)
    {
        cout << "\033[1;31mNo products available in the supermarket.\033[0m" << endl; // Red text
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
        cout << "\033[1;31mInvalid category choice!\033[0m" << endl; // Red text
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
        cout << "\033[1;31mNo products available in the selected category.\033[0m" << endl; // Red text
    }
}

void searchProduct()
{
    string searchName;
    cout << "Enter product name to search: ";
    cin.ignore();
    getline(cin, searchName);

    bool found = false;
    for (int i = 0; i < product_count; i++)
    {
        if (products[i].name == searchName)
        {
            found = true;
            cout << "Product found: " << endl;
            cout << "Code: " << products[i].code << endl;
            cout << "Name: " << products[i].name << endl;
            cout << "Price: $" << products[i].price << endl;
            cout << "Quantity: " << products[i].quantity << endl;
            break;
        }
    }

    if (!found)
    {
        cout << "\033[1;31mProduct not found.\033[0m" << endl;
    }
}

void collectFeedback()
{
    string feedback;
    cout << "We value your feedback! Please share your thoughts: ";
    cin.ignore();
    getline(cin, feedback);

    ofstream feedbackFile("feedback.txt", ios::app);
    if (feedbackFile.is_open())
    {
        feedbackFile << feedback << endl;
        feedbackFile.close();
        cout << "\033[1;32mThank you for your feedback!\033[0m" << endl;
    }
}

void user_menu(string inputId, string name)
{
    string choice;
    do
    {
        // Display the menu header
        cout << endl;
        cout << "=========================================" << endl;
        cout << "\033[1;32m         Ragab's Sons Supermarket        \033[0m" << endl; // Green text
        cout << "=========================================" << endl;
        cout << "Welcome, " << name << "!" << endl;
        cout << "Please select an option from the menu below:" << endl;
        cout << "-----------------------------------------" << endl;

        cout << "1. Edit Customer Data" << endl;
        cout << "2. Display All Products " << endl; // New option for paginated view
        cout << "3. Create Order" << endl;
        cout << "4. View Your Orders" << endl;
        cout << "5. Browse Products by Category" << endl;
        cout << "6. Search Product" << endl;
        cout << "7. Provide Feedback" << endl;
        cout << "8. Logout" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1")
        {
            cout << "\n--- Edit Customer Data ---" << endl;
            editCustomerData(inputId);
        }
        else if (choice == "2") // Call the paginated function
        {
            cout << "\n--- Display All Products (Paginated) ---" << endl;
            showAllProductsPaginated();
        }
        else if (choice == "3")
        {
            cout << "\n--- Create Order ---" << endl;
            createOrder(inputId);
        }
        else if (choice == "4")
        {
            cout << "\n--- View Your Orders ---" << endl;
            viewOrder_user(inputId);
        }
        else if (choice == "5")
        {
            cout << "\n--- Browse Products by Category ---" << endl;
            displayProductMenu();
        }
        else if (choice == "6")
        {
            cout << "\n--- Search Product ---" << endl;
            searchProduct();
        }
        else if (choice == "7")
        {
            cout << "\n--- Provide Feedback ---" << endl;
            collectFeedback();
        }
        else if (choice == "8")
        {
            cout << "\nLogging out... Thank you for visiting Ragab's Sons Supermarket!" << endl;
            break;
        }
        else
        {
            cout << "\033[1;31m\nInvalid choice. Please try again.\033[0m" << endl; // Red text
        }

        cout << "-----------------------------------------" << endl;

    } while (choice != "8");
}

void login()
{
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
            cout << "\033[1;33mLogin cancelled.\033[0m" << endl; // Yellow for cancellation
            break;
        }

        cout << "Enter your password: ";
        cin >> inputPassword;

        // Admin login check
        if (inputId == adminId && inputPassword == adminPassword)
        {
            cout << "\033[1;32mAdmin login successful!\033[0m" << endl; // Green for success
            MenuAdmin();
            return;
        }

        // Customer login check
        for (int i = 0; i < customer_count; i++)
        {
            if (customers[i].Id == inputId && customers[i].password == inputPassword)
            {
                cout << "Loading";
                for (int i = 0; i < 3; i++)
                {
                    cout << ".";
                    this_thread::sleep_for(chrono::milliseconds(500));
                }
                cout << " Done!" << endl;
                cout << "\033[1;32mLogin successful!\033[0m" << endl; // Green for success
                user_menu(inputId, customers[i].name);
                return;
            }
        }

        cout << "\033[1;31mThe password or the ID is incorrect. Try again.\033[0m" << endl; // Red for error
        cout << "If you don't have an account, please sign up." << endl;
    }
}

bool loadAllFromFile()
{
    // Load customers
    ifstream custFile("customers.txt");
    if (custFile.is_open())
    {
        customer_count = 0;
        while (custFile >> customers[customer_count].Id >> customers[customer_count].password >> customers[customer_count].name >> customers[customer_count].phone >> customers[customer_count].location)
        {
            customer_count++;
            if (customer_count >= Max)
            {
                cout << "\033[1;33mWarning: Max customer limit reached while loading.\033[0m" << endl; // Yellow for warnings
                break;
            }
        }
        custFile.close();
    }
    else
    {
        cerr << "Warning: customers.txt not found." << endl;
    }

    // Load products
    ifstream prodFile("products.txt");
    if (!prodFile.is_open())
    {
        cerr << "Error: Unable to open products.txt for loading." << endl;
        return false;
    }

    product_count = 0;
    while (prodFile.peek() != EOF)
    {
        if (!(prodFile >> products[product_count].code))
            break;
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
        if (product_count >= Max)
        {
            cout << "\033[1;33mWarning: Max product limit reached while loading.\033[0m" << endl; // Yellow for warnings
            break;
        }
    }

    prodFile.close();

    // Load orders
    ifstream orderfile("orders.txt");
    if (!orderfile.is_open())
    {
        cerr << "Error: Unable to open orders.txt for loading." << endl;
        return false; 
    }

    order_count = 0;
    while (orderfile >> currentOrder[order_count].customerId) 
    {
        if (!(orderfile >> currentOrder[order_count].numProducts >> currentOrder[order_count].totalPrice))
        {
            cerr << "Error: Invalid data format in orders.txt." << endl;
            break; 
        }

        for (int j = 0; j < currentOrder[order_count].numProducts; j++)
        {
            if (!(orderfile >> currentOrder[order_count].productName[j]))
            {
                cerr << "Error: Invalid product data in orders.txt." << endl;
                break; 
            }
        }

        order_count++;
        if (order_count >= Max)
        {
            cerr << "Warning: Maximum order limit reached while loading." << endl;
            break; 
        }
    }

    orderfile.close();
    return true;
}

void displayHelp()
{
    cout << "Help Menu:" << endl;
    cout << "1. Sign up: Create a new customer account." << endl;
    cout << "2. Login: Log in to your account." << endl;
    cout << "3. Exit: Exit the program." << endl;
}

void displayWelcomeScreen()
{
    cout << "*****************************************" << endl;
    cout << "\033[1;32m*       Welcome to Ragab's Sons         *\033[0m" << endl;
    cout << "\033[1;32m*          Supermarket System           *\033[0m" << endl;
    cout << "*****************************************" << endl;
    cout << "Your one-stop shop for all your needs!" << endl;
}

int main()
{
    displayWelcomeScreen();
    loadAllFromFile();
    string choice;
    do
    {
        cout << endl;
        cout << "=========================================" << endl;
        cout << "\033[1;32mWelcome to Ragab's Sons Supermarket!\033[0m" << endl; // Green text
        cout << "=========================================" << endl;
        cout << endl;
        cout << "1. Sign up" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "4. Help" << endl;
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
            cout << "\033[1;32mThank you for using Ragab's Sons Supermarket System!\033[0m" << endl;
            cout << "\033[1;32mWe hope to see you again soon. Goodbye!\033[0m" << endl;
            break;
        }
        else if (choice == "4")
        {
            displayHelp();
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != "3");
    saveToFile();
    return 0;
}