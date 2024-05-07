#pragma once
#include <iostream>
#include <string>
using namespace std;
class GoodsInStock
{
protected:
	string name;
	string manufactureDate;
	string certificatesOfQuality;
	float price;

public:

	GoodsInStock()
	{
		name = "";
		manufactureDate = "";
		certificatesOfQuality = "";
		price = 0.0;
	}

	GoodsInStock(string name, string manufactureDate, string certificatesOfQuality, float price)
	{
		this->name = name;
		this->manufactureDate = manufactureDate;
		this->certificatesOfQuality = certificatesOfQuality;
		this->price = price;
	}


	GoodsInStock(const GoodsInStock& other) {
		name = other.name;
		manufactureDate = other.manufactureDate;
		certificatesOfQuality = other.certificatesOfQuality;
		price = other.price;
	}


	GoodsInStock(GoodsInStock&& other) noexcept {
		name = move(other.name);
		manufactureDate = move(other.manufactureDate);
		certificatesOfQuality = move(other.certificatesOfQuality);
		price = move(other.price);
	}


	//getters and setters
	string getName() const { return name; }
	string getManufactureDate() const { return manufactureDate; }
	string getCertificatesOfQuality() const { return certificatesOfQuality; }
	float getPrice() const { return price; }

	void setName(const string& newName){ name = newName; }
	void setManufactureDate(const string& newManufactureDate) { manufactureDate = newManufactureDate; }
	void setCertificatesOfQuality(const string& newCertificatesOfQuality) { certificatesOfQuality = newCertificatesOfQuality; }
	void setPrice(const float& newPrice) { price = newPrice; }


	// Overloaded stream operators
	friend istream& operator>>(istream& input, GoodsInStock& obj) {
		cout << "Enter name of good: ";
		input >> obj.name;

		cout << "Enter manufacture date: ";
		input >> obj.manufactureDate;

		cout << "Enter certificates of quality: ";
		input >> obj.certificatesOfQuality;


		// Validate price input
		while (true) {
			cout << "Enter price: ";
			if (input >> obj.price) {
				if (obj.price <= 0) {
					cout << "Price cannot be negative. Please enter a valid price." << endl;
				}
				else {
					break; 
				}
			}
			else {
				cout << "Invalid input for price. Please enter a valid number." << endl;
				input.clear(); 
				input.ignore(numeric_limits<streamsize>::max(), '\n'); 
			}
		}

		return input;
	}

	friend ostream& operator<<(ostream& output, const GoodsInStock& obj) {
		output << "Name: " << obj.name << endl;
		output << "Manufacture Date: " << obj.manufactureDate << endl;
		output << "Quality Certificate: " << obj.certificatesOfQuality << endl;
		output << "Price: " << obj.getFullPrice();
		return output;
	}

	// Overloaded operators
	GoodsInStock& operator=(const GoodsInStock& other) {
		if (this != &other) {
			name = other.name;
			price = other.price;
			manufactureDate = other.manufactureDate;
			certificatesOfQuality = other.certificatesOfQuality;
		}
		return *this;
	}

	GoodsInStock& operator+(float amount) {
		price += amount;
		return *this;
	}

	GoodsInStock& operator-(float amount) {
		price -= amount;
		return *this;
	}

	//virtual method 
	virtual float getFullPrice() const {
		return price;
	}

	~GoodsInStock() {}
};


