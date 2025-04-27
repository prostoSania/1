#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>


class Order {
protected:
    int orderId;
    std::vector<std::string> items;
    double totalAmount;

public:
    
    Order(int orderId, const std::vector<std::string>& items) : orderId(orderId), items(items) {
        if (orderId <= 0) {
            throw std::invalid_argument("ID заказа должен быть положительным числом.");
        }
        if (items.empty()) {
            throw std::invalid_argument("Список товаров в заказе не может быть пустым.");
        }

        
        totalAmount = items.size() * 10.0;
    }

    virtual void process() const {
        std::cout << "Обработка заказа #" << orderId << " на сумму " << totalAmount << std::endl;
        
    }

   
    virtual ~Order() {}

    int getOrderId() const {
        return orderId;
    }

    double getTotalAmount() const {
        return totalAmount;
    }
};


class OnlineOrder : public Order {
private:
    std::string shippingAddress;

public:
 
    OnlineOrder(int orderId, const std::vector<std::string>& items, const std::string& shippingAddress)
        : Order(orderId, items), shippingAddress(shippingAddress) {
        if (shippingAddress.empty()) {
            throw std::invalid_argument("Адрес доставки не может быть пустым для онлайн-заказа.");
        }
    }

    
    void process() const override {
        Order::process(); 
        std::cout << "Отправка онлайн-заказа #" << getOrderId() << " по адресу: " << shippingAddress << std::endl;
    }

    std::string getShippingAddress() const {
        return shippingAddress;
    }
};


class InStoreOrder : public Order {
private:
    int customerId;

public:
 
    InStoreOrder(int orderId, const std::vector<std::string>& items, int customerId)
        : Order(orderId, items), customerId(customerId) {
        if (customerId <= 0) {
            throw std::invalid_argument("ID покупателя должен быть положительным числом для заказа в магазине.");
        }
    }


    void process() const override {
        Order::process(); 
        std::cout << "Обработка заказа #" << getOrderId() << " в магазине для покупателя ID: " << customerId << std::endl;
    }

    int getCustomerId() const {
        return customerId;
    }
};

int main() {
    try {
        OnlineOrder onlineOrder(123, {"Книга", "Ручка"}, "ул. Примерная, 10");
        onlineOrder.process();

        InStoreOrder inStoreOrder(456, {"Тетрадь", "Карандаш"}, 789);
        inStoreOrder.process();

      
        OnlineOrder invalidOnlineOrder(789, {"Ластик"}, ""); 
        invalidOnlineOrder.process();
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}