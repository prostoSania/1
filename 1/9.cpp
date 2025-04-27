#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>


class Document {
protected:
    std::string filename;

public:
    
    Document(const std::string& filename) : filename(filename) {}

    
    virtual void save() const {
        std::cout << "Saving document to " << filename << std::endl;
        
    }

   
    virtual ~Document() {}

    std::string getFilename() const {
        return filename;
    }
};


class PDFDocument : public Document {
private:
    std::string content; 

public:
    
    PDFDocument(const std::string& filename, const std::string& content) : Document(filename), content(content) {}

    
    void save() const override {
        std::ofstream outfile(filename, std::ios::binary); 
        if (!outfile.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для сохранения PDF: " + filename);
        }

        outfile << "%PDF-1.5\n"; 
        outfile << content;       

        outfile.close();
        if (outfile.fail()) { 
            throw std::runtime_error("Не удалось сохранить PDF файл: " + filename);
        }
        std::cout << "PDF документ успешно сохранен в " << filename << std::endl;
    }
};


class WordDocument : public Document {
private:
    std::string text; 

public:
    
    WordDocument(const std::string& filename, const std::string& text) : Document(filename), text(text) {}

    
    void save() const override {
        std::ofstream outfile(filename); 
        if (!outfile.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для сохранения Word документа: " + filename);
        }

        outfile << "<worddocument>\n"; 
        outfile << text;               
        outfile << "\n</worddocument>\n"; 

        outfile.close();
        if (outfile.fail()) {
            throw std::runtime_error("Не удалось сохранить Word документ: " + filename);
        }
        std::cout << "Word документ успешно сохранен в " << filename << std::endl;
    }
};

int main() {
    try {
        PDFDocument pdf("example.pdf", "This is a sample PDF document.");
        pdf.save();

        WordDocument word("example.docx", "This is a sample Word document.");
        word.save();

        
        WordDocument invalidWord("/invalid/path/to/doc.docx", "This will not save");
        invalidWord.save(); 

    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка времени выполнения: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Общая ошибка: " << e.what() << std::endl;
    }

    return 0;
}