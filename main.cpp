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
  int code, quantity;
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
struct Product
{
  int id;
  string name;
  float price;
  int quantity;
};
void View_product_details(Product products[])
{
  const int size = 30;
  int productId;
  cout << "Enter Product ID to view details: ";
  cin >> productId;
  bool found = true;
  for (int i = 0; i < size; i++)
  {
    if (products[i].id == productId)
    {
      cout << "Product ID: " << products[i].id << endl;
      cout << "Name: " << products[i].name << endl;
      cout << "Price= " << products[i].price << " $" << endl;
      cout << "Quantity= " << products[i].quantity << endl;
      found = true;
      break;
    }
    if (!found)
    {
      cout << "Product not found!" << endl;
    }
  }
}
void Display_Products_Menu()
{
  int number_of_Category;
  cout << "choose which category what you want:" << endl;
  cout << "1-bakery\n2-diary\n3-snacks\n4-sweets\n5-beverages\n6-dry food" << endl;

  while (true)
  {
    cin >> number_of_Category;
    switch (number_of_Category)
    {
    case 1:
      int number_of_products_in_bakery;
      cout << "select what you want:" << endl;
      cout << "1-phino bread\n2-balady bread\n3-lebanese bread\n4-french bread \n5-corroisant" << endl;
      while (true)
      {
        cin >> number_of_products_in_bakery;
        if (number_of_products_in_bakery < 1 || number_of_products_in_bakery > 5)
          cout << "invalid choise! try again" << endl;
        else
          break;
      }
      break;
    case 2:
      cout << "select what you want:" << endl;
      int number_of_products_in_diary;
      cout << "1-milk\n2-yogurt\n3-cheese\n4-butter" << endl;
      while (true)
      {
        cin >> number_of_products_in_diary;
        if (number_of_products_in_diary < 1 || number_of_products_in_diary > 4)
          cout << "invalid choise! try again" << endl;
        else
          break;
      }
      break;
    case 3:
      cout << "select what you want:" << endl;
      int number_of_products_in_snacks;
      cout << "1-chips\n2-pop corn\n3-nuts" << endl;
      while (true)
      {
        cin >> number_of_products_in_snacks;
        if (number_of_products_in_snacks < 1 || number_of_products_in_snacks > 3)
          cout << "invalid choise! try again" << endl;
        else
          break;
      }
      break;
    case 4:
      cout << "select what you want:" << endl;
      int number_of_products_in_sweets;
      cout << "1-candy\n2-choclates\n3-ice cream\n4-cookies\n5-biscuits" << endl;
      while (true)
      {
        cin >> number_of_products_in_sweets;
        if (number_of_products_in_sweets < 1 || number_of_products_in_sweets > 5)
          cout << "invalid choise! try again" << endl;
        else
          break;
      }
      break;
    case 5:
      cout << "select what you want:" << endl;
      int number_of_products_in_beverages;
      cout << "1-water\n2-juice\n3-cola\n4-tea\n5-coffee" << endl;
      while (true)
      {
        cin >> number_of_products_in_beverages;
        if (number_of_products_in_beverages < 1 || number_of_products_in_beverages > 5)
          cout << "invalid choise! try again" << endl;
        else
          break;
      }
      break;
    case 6:
      cout << "select what you want:" << endl;
      int number_of_Products_in_Dry_food;
      cout << "1-rice\n2-pasta\n3-flour\n4-sugar\n5-yeast" << endl;
      while (true)
      {
        cin >> number_of_Products_in_Dry_food;
        if (number_of_Products_in_Dry_food < 1 || number_of_Products_in_Dry_food > 5)
          cout << "invalid choise! try again" << endl;
        else
          break;
      }
      break;
    default:
      cout << "invalid choice!try again" << endl;
      break;
    }
    break;
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

void login()
{
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
        break;
      }
    }
    file.close();

    if (!loginSuccessful)
    {
      cout << "Invalid ID or password." << endl;
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

int main()
{
  int choice;
  do
  {
    cout << "1. Signup" << endl;
    cout << "2. Login" << endl;
    cout << "3. Edit Customer Data" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      signup();
      break;
    case 2:
      login();
      break;
    case 3:
      editCustomerData();
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