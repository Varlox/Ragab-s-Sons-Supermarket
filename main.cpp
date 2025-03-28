#include <iostream>
#include <string>
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

void login(customer &c)
{

  do
  {
    cout << "Enter your ID: ";
    cin >> c.Id;
    cout << "Enter your password: ";
    cin >> c.password;
    if (c == customers[0].Id && c.password == customers[0].password)
    {
      cout << "Login successful!" << endl;
      cout << "Welcome, " << customers[0].name << "!" << endl;
      continue;
    }
    else
    {
      cout << "Invalid ID or password." << endl;
    }
  } while (c != customers[0].Id && c.password != customers[0].password);
}