#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Class to represent a person
class Person {
protected:
    string fullName;
    string email;
    string phoneNumber;
    string address;

public:
    // Constructor
    Person(const string& fullName, const string& email, const string& phoneNumber, const string& address)
        : fullName(fullName), email(email), phoneNumber(phoneNumber), address(address) {}

    // Getter methods
    string getFullName() const { return fullName; }
    string getEmail() const { return email; }
    string getPhoneNumber() const { return phoneNumber; }
    string getAddress() const { return address; }
};

// Class to represent a customer
class Customer : public Person {
private:
    static int nextId; // Static member to generate unique IDs for customers
    string id;

public:
    // Constructor
    Customer(const string& fullName, const string& email, const string& phoneNumber, const string& address)
        : id("C" + to_string(nextId++)), Person(fullName, email, phoneNumber, address) {}

    // Getter method for ID
    string getId() const { return id; }

    // Method to check if two customers are equal based on ID
    bool operator==(const Customer& other) const {
        return id == other.getId();
    }
};

int Customer::nextId = 1; // Initialize static member

// Class to represent an artist
class Artist : public Person {
private:
    string style;

public:
    // Constructor
    Artist(const string& fullName, const string& email, const string& phoneNumber, const string& address, const string& style)
        : style(style), Person(fullName, email, phoneNumber, address) {}

    // Getter method for style
    string getStyle() const { return style; }

    // Method to check if two artists are equal based on fullName and style
    bool operator==(const Artist& other) const {
        return fullName == other.getFullName() && style == other.getStyle();
    }
};

// Art Gallery Management System
class GalleryManagementSystem {
private:
    vector<Customer> customers;
    vector<Artist> artists;

public:
    // Method to add a new customer
    void addCustomer(const Customer& customer) {
        // Check if customer already exists
        if (find(customers.begin(), customers.end(), customer) != customers.end()) {
            cout << "Customer with the same details already exists.\n";
            return;
        }
        customers.push_back(customer);
        cout << "Customer added successfully with ID: " << customer.getId() << endl;
    }

    // Method to add a new artist
    void addArtist(const Artist& artist) {
        // Check if artist already exists
        if (find(artists.begin(), artists.end(), artist) != artists.end()) {
            cout << "Artist with the same details already exists.\n";
            return;
        }
        artists.push_back(artist);
        cout << "Artist added successfully.\n";
    }

    // Method to display all customers
    void displayAllCustomers() const {
        cout << "All Customers:\n";
        for (const auto& customer : customers) {
            cout << "ID: " << customer.getId() << ", Name: " << customer.getFullName() << ", Email: " << customer.getEmail()
                << ", Phone: " << customer.getPhoneNumber() << ", Address: " << customer.getAddress() << endl;
        }
    }

    // Method to display all artists
    void displayAllArtists() const {
        cout << "All Artists:\n";
        for (const auto& artist : artists) {
            cout << "Name: " << artist.getFullName() << ", Email: " << artist.getEmail()
                << ", Phone: " << artist.getPhoneNumber() << ", Address: " << artist.getAddress()
                << ", Style: " << artist.getStyle() << endl;
        }
    }
};

int main() {
    GalleryManagementSystem gallerySystem;

    char choice;
    do {
        char personType;
        cout << "Enter 'C' for Customer or 'A' for Artist: ";
        cin >> personType;  

        string fullName, email, phoneNumber, address, style;

        cout << "Enter Full Name: ";
        cin.ignore();
        getline(cin, fullName);

        cout << "Enter Email: ";
        cin >> email;

        cout << "Enter Phone Number: ";
        cin >> phoneNumber;

        cout << "Enter Address: ";
        cin.ignore();
        getline(cin, address);

        if (personType == 'A' || personType == 'a') {
            cout << "Enter Art Style: ";
            getline(cin, style);

            Artist newArtist(fullName, email, phoneNumber, address, style);
            gallerySystem.addArtist(newArtist);
        }
        else {
            Customer newCustomer(fullName, email, phoneNumber, address);
            gallerySystem.addCustomer(newCustomer);
        }

        cout << "Do you want to add another person? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    // Display all customers
    gallerySystem.displayAllCustomers();

    // Display all artists
    gallerySystem.displayAllArtists();

    return 0;
}
