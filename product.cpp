#include "product.h"

Product::Product(int productID, string productName, int price, int stock, string category) :
	productID_(productID), productName_(productName), price_(price), stock_(stock), category_(category) {}

int Product::getID() const
{
	return productID_;
}

string Product::getName()
{
	return productName_;
}

void Product::setName(string& productName) {
	productName_ = productName;
}

int Product::getPrice()
{
	return price_*1000;
}
void Product::setPrice(int price)
{
	price_ = price;
}

int Product::getStock()
{
	return stock_;
}
void Product::setStock(int stock)
{
	stock_ = stock;
}

string Product::category()
{
	return category_;
}

void Product::setcatg(string& category) {
	category_ = category;
}

void Product::calcInventory(int stock)
{
	float result;
	result = (price_)* stock;
	if (stock > stock_)
		cout << "!!재고가 부족합니다!!" << endl;
	else
		cout << "총 주문금액 : " << result/10 << "만원" << endl;

}