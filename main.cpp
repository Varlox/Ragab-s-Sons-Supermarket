#include <iostream>
#include <string>
#include <fstream>
using namespace std;
const int Max = 100;
struct customer
{
  int Id;
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

void signup(customer &c)
{
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
  customers[customer_count] = c;
  customer_count++;
  cout << "Signup successful!" << endl;

  ofstream file("customers.txt", ios::app); // Open file in append mode
  if (file.is_open())
  {
    file << c.Id << " " << c.password << " " << c.name << " " << c.phone << " " << c.location << endl;
    file.close();
    cout << "Signup successful! Data saved to file." << endl;
  }
  else
  {
    cout << "Error: Unable to open file to save data." << endl;
  }
}

void login()
{
  int inputId;
  string inputPassword;
  bool loginSuccessful = false;

  cout << "Enter your ID: ";
  cin >> inputId;
  cout << "Enter your password: ";
  cin >> inputPassword;

  ifstream file("customers.txt"); // Open the file for reading
  if (file.is_open())
  {
    int id;
    string password, name, phone, location;

    // Read each line from the file and check credentials
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
    cout << "Error: Unable to open file to verify login." << endl;
  }
}

int main()
{
  int choice;
  customer c;
  do
  {
    cout << "1. Signup" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      signup(c);
      break;
    case 2:
      login();
      break;
    case 3:
      cout << "Exiting..." << endl;
      break;
    default:
      cout << "Invalid choice. Please try again." << endl;
      break;
    }
  } while (choice != 3);

  return 0;
}