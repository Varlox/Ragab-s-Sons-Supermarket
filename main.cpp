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
};
struct Date
{
  int day;
  int month;
  int year;
};
void MenuLogin()
{
  int choice;

  do
  {
    cout << endl;
    cout << "******Welcome to Ragab`s sons Supermarket******" << endl;
    cout << endl;
    cout << "1. Edit Customer Data" << endl;
    cout << "2. display Menu" << endl;
    cout << "3. Create Order" << endl;
    cout << "4. View Order" << endl;
    cout << "5. Calculate Total Price" << endl;
    cout << "6. Exit" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
      editCustomerData();
      break;
    case 2:
      displayProductMenu();
      break;
    case 3:
      createOrder();
      break;
    case 4:
      int IDindex;
      cout << "Please enter ypur ID : ";
      cin >> IDindex;
      viewOrder_user(IDindex);
      break;
    case 5:
      cout << "Please enter ypur ID : ";
      cin >> IDindex;
      processOrder(IDindex);
      break;
    case 6:
      cout << "Logging out..." << endl;
      return;
    default:
      cout << "Invalid choice. Please try again." << endl;
      break;
    }
  } while (choice != 6);
}
int order_count = 0;
order currentOrder[Max];

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

void viewOrder_user(int IDindex)
{

  bool found = false;

  for (int i = 0; i < order_count; i++)
  {
    if (currentOrder[i].customerId == IDindex)
    {
      found = true;
      cout << "\nrder #" << i + 1 << " Customer ID: " << currentOrder[i].customerId << endl;
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
    cout << "This user has no order yet . " << endl;
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
      for (int j = 0; j < currentOrder[i].numProducts; j++)
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
// Function to view product details
void View_product_details(product products[])
{
  const int size = 30;
  string productId;
  cout << "Enter Product ID to view details: ";
  cin >> productId;

  bool found = false;
  for (int i = 0; i < size; i++)
  {
    if (products[i].code == productId)
    {
      cout << "Product ID: " << products[i].code << endl;
      cout << "Name: " << products[i].name << endl;
      cout << "Price: " << products[i].price << " $" << endl;
      cout << "Quantity: " << products[i].quantity << endl;
      cout << "Production Date: " << products[i].productionDate.day << "/"
           << products[i].productionDate.month << "/"
           << products[i].productionDate.year << endl;
      cout << "Expiry Date: " << products[i].expirationDate.day << "/"
           << products[i].expirationDate.month << "/"
           << products[i].expirationDate.year << endl;
      found = true;
      break;
    }
  }

  if (!found)
  {
    cout << "Product not found!" << endl;
  }
}

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

bool login(string inputId, string inputPassword)
{
  bool loginSuccessful = false;

  cout << "Enter your ID: ";
  cin >> inputId;

  cout << "Enter your password: ";
  cin >> inputPassword;

  for (int i = 0; i < customer_count; i++)
  {
    if (customers[i].Id == inputId && customers[i].password == inputPassword)
    {
      cout << "Login successful!" << endl;
      cout << "Welcome, " << customers[i].name << "!" << endl;
      loginSuccessful = true;
      break;
    }
  }

  // ifstream file("customers.txt");
  // if (file.is_open())
  // {
  //   string id;
  //   string password, name, phone, location;

  //   while (file >> id >> password >> name >> phone >> location)
  //   {
  //     if (id == inputId && password == inputPassword)
  //     {
  //       cout << "Login successful!" << endl;
  //       cout << "Welcome, " << name << "!" << endl;
  //       loginSuccessful = true;
  //       return loginSuccessful;
  //     }
  //   }
  //   file.close();

  //   if (!loginSuccessful)
  //   {
  //     cout << "Invalid ID or password." << endl;
  //     cout << "Please try again." << endl;
  //   }
  // }
  // else
  // {
  //   cerr << "Error: Unable to open file to verify login." << endl;
  // }
}
void editCustomerData(string idToEdit)
{
  cout << "Enter the ID of the customer to edit: ";
  cin >> idToEdit;

  bool found = false;

  for (int i = 0; i < customer_count; i++)
  {
    if (customers[i].Id == idToEdit)
    {
      found = true;
      cout << "Editing customer data for ID: " << idToEdit << endl;
      cout << "Enter new password: ";
      cin >> customers[i].password;
      cout << "Enter new name: ";
      cin >> customers[i].name;
      cout << "Enter new phone number: ";
      cin >> customers[i].phone;
      cout << "Enter new location: ";
      cin >> customers[i].location;
      cout << "Customer data updated successfully." << endl;
      break;
    }
  }

  if (!found)
  {
    cout << "Customer ID not found." << endl;
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

void createOrder()
{
  order newOrder;
  newOrder.numProducts = 0;
  newOrder.totalPrice = 0;

  string productName;
  char choice;
  do
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
  } while (choice == 'y' || choice == 'Y');

  currentOrder[order_count++] = newOrder;
  cout << "Order created successfully! Total price: $" << newOrder.totalPrice << endl;
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
  cin >> p.name;
  cout << "Enter product category: ";
  cin >> p.Category;
  cout << "Enter production date (dd mm yyyy): ";
  cin >> p.productionDate.day >> p.productionDate.month >> p.productionDate.year;
  cout << "Enter expiration date (dd mm yyyy): ";
  cin >> p.expirationDate.day >> p.expirationDate.month >> p.expirationDate.year;
  cout << "Enter product price: ";
  cin >> p.price;
  cout << "Enter product quantity: ";
  cin >> p.quantity;

  products[product_count++] = p; // Add product to the array
  cout << "Product added successfully!" << endl;
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
      cout << "Editing product with code " << codeToEdit << endl;
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

  cout << "Enter the product code to delete: ";
  cin >> codeToDelete;

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
  for (int i = 0; i < product_count; i++)
  {
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

void MenuLogin()
{
  int choice;

  do
  {
    cout << endl;
    cout << "***************Welcome to Ragab`s sons Supermarket***************" << endl;
    cout << endl;
    cout << "1. Edit Customer Data" << endl;
    cout << "2. display Menu" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
      editCustomerData();
      break;
    case 2:
      displayProductMenu();
      break;
    case 3:
      cout << "Logging out..." << endl;
      return;
    default:
      cout << "Invalid choice. Please try again." << endl;
      break;
    }
  } while (choice != 3);
}

void MenuAdmin()
{
  int choice;
  do
  {
    cout << endl;
    cout << "***************Welcome to Ragab`s sons Supermarket***************" << endl;
    cout << endl;
    cout << "1. Add Product" << endl;
    cout << "2. Edit Product" << endl;
    cout << "3. Delete Product" << endl;
    cout << "4. Show All Products" << endl;
    cout << "5. View Orders" << endl;
    cout << "6. Process Order" << endl;
    cout << "7. Exit" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
      addProduct();
      break;
    case 2:
      editProduct();
      break;
    case 3:
      deleteProduct();
      break;
    case 4:
      showAllProducts();
      break;
    case 5:
      viewOrders_admin();
      break;
    case 6:
      int customerId;
      cout << "Enter customer ID to process order: ";
      cin >> customerId;
      processOrder(customerId);
      break;
    case 7:
      cout << "Exiting..." << endl;
      break;
    default:
      cout << "Invalid choice. Please try again." << endl;
      break;
    }
  } while (choice != 7);
}

void Display_Products_Menu()
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

  cout << "Select a product from " << categories[categoryChoice - 1] << ":" << endl;
  for (int i = 0; i < 5 && !products[categoryChoice - 1][i].empty(); i++)
  {
    cout << i + 1 << "-" << products[categoryChoice - 1][i] << endl;
  }

  int productChoice;
  cin >> productChoice;

  if (productChoice < 1 || productChoice > 5 || products[categoryChoice - 1][productChoice - 1].empty())
  {
    cout << "Invalid product choice!" << endl;
    return;
  }

  cout << "You selected: " << products[categoryChoice - 1][productChoice - 1] << endl;
}

int main()
{
  int choice;
  do
  {
    cout << "1. Signup" << endl;
    cout << "2. Login" << endl;
    cout << "3. Admin Login" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      signup();
      break;
    case 2:
      if (login())
      {
        MenuLogin();
      }
      break;
    case 3:
      MenuAdmin();
      break;
    case 4:
      cout << "Exiting..." << endl;
      break;
    default:
      cout << "Invalid choice. Please try again." << endl;
      break;
    }
  } while (choice != 4);

  return 0;
}
