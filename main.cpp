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
int order_count;

struct order
{
  int customerId;
  string productName[Max];
  double totalPrice;
  int numProducts;
} currentOrder[Max];

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
  cin.ignore();
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
  if (product_count >= Max)
  {
    cout << "Error: Cannot add more products. Maximum limit reached." << endl;
    return;
  }

  product p;
  cout << "Enter product code: ";
  cin >> p.code;
  cout << "Enter product name: ";
  cin.ignore();
  getline(cin, p.name); // Fixed to handle multi-word product names

  // Predefined categories
  const string categories[] = {"Bakery", "Dairy", "Snacks", "Sweets", "Beverages"};
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
  products[product_count] = p;

  cout << "Product added successfully!" << endl;
  product_count++;
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
    cout << "***********" << endl;
    saveProductsToFile();
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

void searchProductByName(const string &name)
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
  int order_count;
  cin >> order_count;
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
      saveProductsToFile();
      cout << "Exiting admin menu... All changes have been saved." << endl;
      running = false;
    }
    else
    {
      cout << "Invalid choice. Please try again." << endl;
    }
  }
}

void editCustomerData(string idToEdit)
{
  ifstream infile("customers.txt");
  ofstream tempFile("temp.txt");

  if (!infile.is_open())
  {
    cerr << "Error: Unable to open 'customers.txt' for reading." << endl;
    return;
  }
  if (!tempFile.is_open())
  {
    cerr << "Error: Unable to open 'temp.txt' for writing." << endl;
    return;
  }

  string id, password, name, phone, location;
  bool found = false;

  while (infile >> id >> password >> name >> phone >> location)
  {
    if (id == idToEdit)
    {
      found = true;
      cout << "Editing customer data for ID: " << id << endl;

      cout << "Enter new password (or press Enter to keep current): ";
      string newPassword;
      cin.ignore();
      getline(cin, newPassword);
      if (!newPassword.empty())
      {
        password = newPassword;
      }

      cout << "Enter new name (or press Enter to keep current): ";
      string newName;
      getline(cin, newName);
      if (!newName.empty())
      {
        name = newName;
      }

      cout << "Enter new phone number (or press Enter to keep current): ";
      string newPhone;
      getline(cin, newPhone);
      if (!newPhone.empty())
      {
        phone = newPhone;
      }

      cout << "Enter new location (or press Enter to keep current): ";
      string newLocation;
      getline(cin, newLocation);
      if (!newLocation.empty())
      {
        location = newLocation;
      }
    }
    tempFile << id << " " << password << " " << name << " " << phone << " " << location << endl;
  }

  infile.close();
  tempFile.close();

  if (!found)
  {
    cout << "Customer ID not found." << endl;
    return;
  }

  if (remove("customers.txt") != 0)
  {
    cerr << "Error: Unable to delete the original 'customers.txt' file." << endl;
    return;
  }
  if (rename("temp.txt", "customers.txt") != 0)
  {
    cerr << "Error: Unable to rename 'temp.txt' to 'customers.txt'." << endl;
    return;
  }

  cout << "Customer data updated successfully." << endl;
}

/* void Display_Products_Menu() // user
{
  const string categories[] = {"bakery", "diary", "snacks", "sweets", "beverages", "dry food"};
  const string products[][5] = {
      {"phino bread", "balady bread", "lebanese bread", "french bread", "croissant"},
      {"milk", "cheese", "yogurt", "butter", ""},
      {"chips", "popcorn", "crackers", "", ""},
      {"chocolate", "candy", "cake", "cookies", "ice cream"},
      {"soda", "juice", "water", "coffee", "tea"},
      {"rice", "pasta", "flour", "sugar", "salt"}};

  cout << "Choose a category:" << endl;
  for (int i = 0; i < 6; i++)
  {
    cout << i + 1 << "-" << categories[i] << endl;
  }

  int categoryChoice;
  cin >> categoryChoice;

  if (categoryChoice < 1 || categoryChoice > 6)
  {
    cout << "Invalid category choice!" << endl;
    return;
  }
  cout << "the products in this category:" << endl;
  for (int i = 0; i < 5 && !products[categoryChoice - 1][i].empty(); i++)
  {
    cout << i + 1 << "-" << products[categoryChoice - 1][i] << endl;
  }
} */
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

void processOrder(int customerId)
{

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
    cout << "there is no order created. " << endl;
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
      int customerId;
      cout << "Please enter your ID :";
      cin >> customerId;
      processOrder(customerId);
    }
    else if (choice == "6")
    {
      displayProductMenu();
    }
    else if (choice == "7")
    {
      cout << "Logging out..." << endl;
    }
    else
    {
      cout << "Invalid choice. Please try again." << endl;
    }

  } while (choice != "7"); // Loop will now exit correctly when "7" is entered.
}

bool login()
{
  const string adminId = "admin";
  const string adminPassword = "1234";

  string inputId;
  string inputPassword;

  while (true)
  {
    cout << "Enter your ID (or type 'exit' to cancel): ";

    cin >> inputId;

    if (inputId == "exit")
    {
      cout << "Login cancelled." << endl;
      return false;
    }

    cout << "Enter your password: ";
    cin >> inputPassword;

    // Admin login check
    if (inputId == adminId && inputPassword == adminPassword)
    {
      cout << "Admin login successful!" << endl;
      MenuAdmin();
      return true;
    }

    // Customer login check
    ifstream file("customers.txt");
    if (file.is_open())
    {
      string id, password, name, phone, location;
      bool found = false;

      while (file >> id >> password >> name >> phone >> location)
      {
        if (id == inputId && password == inputPassword)
        {
          cout << "Login successful!" << endl;
          cout << "Welcome, " << name << "!" << endl;
          user_menu();
          file.close();
          return true;
        }
      }

      file.close();
      cout << "Invalid ID or password. Please try again." << endl;
    }
    else
    {
      cerr << "Error: Unable to open file to verify login." << endl;
      return false;
    }
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
      saveProductsToFile();
      cout << "Exiting... All products have been saved." << endl;
      break;
    }
    else
    {
      cout << "Invalid choice. Please try again." << endl;
    }
  } while (choice != "3");

  return 0;
}