#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>


class Library {
protected:
    std::string name;
    std::vector<std::string> availableBooks;

public:
    
    Library(const std::string& name) : name(name) {}

    
    virtual void borrowBook(const std::string& bookTitle) {
       
        auto it = std::find(availableBooks.begin(), availableBooks.end(), bookTitle);

        if (it == availableBooks.end()) {
            throw std::runtime_error("Книга \"" + bookTitle + "\" недоступна в библиотеке \"" + name + "\".");
        }

        
        availableBooks.erase(it);
        std::cout << "Книга \"" << bookTitle << "\" успешно выдана из библиотеки \"" << name << "\"." << std::endl;
    }


    virtual ~Library() {}

   
    void addBook(const std::string& bookTitle) {
        availableBooks.push_back(bookTitle);
    }

    std::string getName() const {
        return name;
    }
};


class FictionLibrary : public Library {
private:
    std::string genre;

public:

    FictionLibrary(const std::string& name, const std::string& genre) : Library(name), genre(genre) {}


    std::string getGenre() const {
        return genre;
    }
};


class NonFictionLibrary : public Library {
private:
    std::string subjectArea;

public:
    
    NonFictionLibrary(const std::string& name, const std::string& subjectArea) : Library(name), subjectArea(subjectArea) {}

    
    std::string getSubjectArea() const {
        return subjectArea;
    }
};

int main() {
    try {
        FictionLibrary fictionLibrary("Художественная библиотека", "Фантастика");
        fictionLibrary.addBook("Гарри Поттер");
        fictionLibrary.addBook("Властелин колец");
        fictionLibrary.borrowBook("Гарри Поттер");

        NonFictionLibrary nonFictionLibrary("Научная библиотека", "История");
        nonFictionLibrary.addBook("История России");
        nonFictionLibrary.addBook("Мировая история");
        nonFictionLibrary.borrowBook("Мировая история");

        
        fictionLibrary.borrowBook("Автостопом по галактике"); 

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}