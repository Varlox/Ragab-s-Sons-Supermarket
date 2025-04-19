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

bool login()
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
				return loginSuccessful;
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

void viewProductDetails() {}

void createOrder() {}

void viewOrder() {}

void processOrder() {}

void addProduct() {}

void editProduct() {}

void deleteProduct() {}

void MenuLogin() {
	int choice;
	
	do {
		cout << endl;
		cout << "***************Welcome to Ragab`s sons Supermarket***************" << endl;
		cout << endl;
		cout << "1. Edit Customer Data" << endl;
		cout << "2. display Menu" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			editCustomerData();
			break;
		case 2:
			displayProductMenu();
			break;
		case 3:
			cout << "Exiting..." << endl;
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
			break;

		}
	} while (choice != 3);
}


int main()
{
	int choice;
	do
	{
		cout << "1. Signup" << endl;
		cout << "2. Login" << endl;
		cout << "5. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			signup();
			break;
		case 2:
			if (login() == true) {
				MenuLogin();
				break;
			}
			else
				login();
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
