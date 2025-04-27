#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

// Базовый класс ShoppingCart
class ShoppingCart {
protected:
    std::vector<std::string> items;

public:
    // Функция для добавления товара в корзину
    void addItem(const std::string& item) {
        items.push_back(item);
    }

    // Виртуальная функция checkout()
    virtual double checkout() const {
        if (items.empty()) {
            throw std::runtime_error("Невозможно выполнить checkout: корзина пуста.");
        }

        double total = 0.0;
        for (const auto& item : items) {
            total += getItemPrice(item); //Предположим, есть функция, возвращающая цену товара
        }
        return total;
    }

    // Виртуальная функция для получения цены товара (может быть переопределена)
    virtual double getItemPrice(const std::string& item) const {
        // Базовая реализация - все товары стоят 10.0
        return 10.0;
    }

    // Виртуальный деструктор
    virtual ~ShoppingCart() {}
};

// Производный класс RegularCart
class RegularCart : public ShoppingCart {
public:
    // Переопределение функции checkout() (для RegularCart ничего дополнительного не делаем)
    double checkout() const override {
        return ShoppingCart::checkout(); // Просто вызываем базовый checkout()
    }
};

// Производный класс DiscountedCart
class DiscountedCart : public ShoppingCart {
private:
    double discountRate; // Процент скидки (например, 0.1 для 10% скидки)

public:
    // Конструктор DiscountedCart
    DiscountedCart(double discountRate) : discountRate(discountRate) {
        if (discountRate < 0 || discountRate > 1) {
            throw std::invalid_argument("Размер скидки должен быть в диапазоне от 0 до 1.");
        }
    }

    // Переопределение функции checkout()
    double checkout() const override {
        double total = ShoppingCart::checkout(); // Получаем общую сумму из базового класса
        return total * (1 - discountRate);      // Применяем скидку
    }
};

int main() {
    try {
        RegularCart regularCart;
        regularCart.addItem("Книга");
        regularCart.addItem("Ручка");
        std::cout << "Сумма заказа (обычная корзина): " << regularCart.checkout() << std::endl;

        DiscountedCart discountedCart(0.2); // Скидка 20%
        discountedCart.addItem("Тетрадь");
        discountedCart.addItem("Карандаш");
        std::cout << "Сумма заказа (корзина со скидкой): " << discountedCart.checkout() << std::endl;

        // Попытка выполнить checkout для пустой корзины
        ShoppingCart emptyCart;
        emptyCart.checkout(); // Выбросит исключение

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}