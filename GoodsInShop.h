#pragma once
#include "GoodsInStock.h"
class GoodsInShop :public GoodsInStock
{
private:
	float markup;
	string expiryPeriod;

public:
	GoodsInShop() {
		markup = 0.0;
		expiryPeriod = "";
	}

	GoodsInShop(string expiryPeriod, float markup)
	{
		this->expiryPeriod = expiryPeriod;
		this->markup = markup;
	}

	//getters and setters
	float getMarkup() const { return markup; }
	string getExpiryPeriod() const { return expiryPeriod; }

	void setMarkup(float newMarkup) { markup = newMarkup; }
	void setExpiryPeriod(const string& newexpiryPeriod) { expiryPeriod = newexpiryPeriod; }


	//virtual method 
	float getFullPrice() const override{
		return price + (price * markup / 100);
	}


	// Overloaded stream operators
	friend ostream& operator<<(ostream& output, const GoodsInShop& obj) {
		output << static_cast<const GoodsInStock&>(obj) << endl
			<< "Markup: " << obj.markup << "%" << endl
			<< "Expiry period: " << obj.expiryPeriod << endl << endl;
		return output;
	}

	friend istream& operator>>(istream& input, GoodsInShop& obj) {
		input >> static_cast<GoodsInStock&>(obj);

		// Validate markup input
		while (true) {
			cout << "Enter markup: ";
			if (input >> obj.markup) {
				if (obj.markup < 0) {
					cout << "Markup cannot be negative. Please enter a valid markup." << endl;
				}
				else {
					break; 
				}
			}
			else {
				cout << "Invalid input for markup. Please enter a valid number." << endl;
				input.clear(); 
				input.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}

		cout << "Enter expiry period: ";
		input >> obj.expiryPeriod;

		return input;
	}
};
