#include <iostream>
#include <string>

using namespace std;

class Product {

public:
	string productName;
	int price;
	int quantity;

	Product(string productName, int price, int quantity) {
		this->productName = productName;
		this->price = price;
		this->quantity = quantity;
	};

	void calculateTotalConst() {
		int sum = 0;
		sum = sum + price*quantity;
		cout << "Total sum is " << sum << endl;
	}

	void displayProductDetails() {
		
		cout << "\nproduct name " << productName << endl;
		cout << "price " << price << endl;
		cout << "quantity " << quantity << endl;
		
	}

};

class Electronics: public Product {

public:
	int warrantyPeriod;
	string manufacturer;

	Electronics(string productName, int price, int quantity,int warrantyPeriod, string manufacturer) :
		Product(productName, price, quantity), warrantyPeriod(warrantyPeriod), manufacturer(manufacturer){
		this->warrantyPeriod = warrantyPeriod;
		this->manufacturer = manufacturer;

	}

	void extendWarranty() {
		int warranty = 0;
		warranty += warrantyPeriod;
		cout << "total garantu:" << warranty << endl;
	}

	void updateManufacturer(string newManufacturer) {
		manufacturer = newManufacturer;
		cout << "manufacturer " << manufacturer << endl;
	}
};

class Clothing : public Product {
public:
	int size;

	Clothing(string productName, int price, int quantity,int size):Product( productName, price, quantity),size(size){
		this->size = size;
	}

	void changeSize(int newsize) {
		int newSize=0;
		size = newSize;
		cout << "size" << size << endl;
	}

	void isSizeAvailable(int newsize) {
		int newSize;
		if (newSize = size){
			cout << "is available" << endl;
		}
		else {
			cout << "is not available(" << endl;
		}
	}
};

int main() {
	Product product1("milk", 23, 3);
	product1.displayProductDetails();
	product1.calculateTotalConst();

	Product product2("mik", 22, 32);
	product2.displayProductDetails();
	product2.calculateTotalConst();
	

	Electronics electronics1("mikser", 6543,54,54,"3ferfg");
	electronics1.displayProductDetails();
	electronics1.extendWarranty();
	electronics1.updateManufacturer("dfghjkl");
	
	Clothing cl1("T-shirt", 233, 2, 4);
	cl1.displayProductDetails();
	cl1.changeSize(4);
	cl1.isSizeAvailable(3);

}