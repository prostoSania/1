#include <iostream>
#include <string>
#include <stdexcept>

// Базовый класс WeatherService
class WeatherService {
public:
    // Виртуальная функция getForecast()
    virtual std::string getForecast(const std::string& city) const {
        throw std::runtime_error("Метод getForecast() не реализован для базового класса WeatherService.");
    }

    // Виртуальный деструктор
    virtual ~WeatherService() {}
};

// Производный класс LocalWeatherService
class LocalWeatherService : public WeatherService {
private:
    std::string localData; // Локальные данные о погоде

public:
    // Конструктор LocalWeatherService
    LocalWeatherService(const std::string& localData) : localData(localData) {
        if (localData.empty()) {
            throw std::invalid_argument("Локальные данные о погоде не могут быть пустыми.");
        }
    }

    // Переопределение функции getForecast()
    std::string getForecast(const std::string& city) const override {
        // Имитируем получение прогноза для города из локальных данных
        if (localData.find(city) != std::string::npos) {
            return "Прогноз для " + city + ": " + localData;
        } else {
            throw std::runtime_error("Нет данных о погоде для города " + city + " в локальном хранилище.");
        }
    }
};

// Производный класс RemoteWeatherService
class RemoteWeatherService : public WeatherService {
private:
    std::string apiEndpoint; // URL API для получения прогноза

public:
    // Конструктор RemoteWeatherService
    RemoteWeatherService(const std::string& apiEndpoint) : apiEndpoint(apiEndpoint) {
        if (apiEndpoint.empty()) {
            throw std::invalid_argument("URL API не может быть пустым.");
        }
    }

    // Переопределение функции getForecast()
    std::string getForecast(const std::string& city) const override {
        // Имитируем получение прогноза из удаленного API
        // В реальном коде здесь будет запрос к API по apiEndpoint
        if (city == "ErrorCity") {
            throw std::runtime_error("Ошибка при получении данных о погоде для города " + city + " из удаленного API.");
        } else {
            return "Прогноз для " + city + " из удаленного API: Солнечно.";
        }
    }
};

int main() {
    try {
        LocalWeatherService localService("Солнечно в Москве, Дождь в Лондоне");
        std::cout << localService.getForecast("Москва") << std::endl;
        // std::cout << localService.getForecast("Париж") << std::endl; // Выбросит исключение

        RemoteWeatherService remoteService("http://example.com/weather");
        std::cout << remoteService.getForecast("Токио") << std::endl;
        // std::cout << remoteService.getForecast("ErrorCity") << std::endl; // Выбросит исключение

        // Попытка создать LocalWeatherService с пустыми данными
        LocalWeatherService invalidService(""); // Выбросит исключение

        //Попытка получить прогноз из базового класса
        WeatherService baseService;
        baseService.getForecast("Nowhere");

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}