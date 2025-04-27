#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class FileReader {
protected:
    std::string filePath;

    void checkFileExists() const {
        std::ifstream file(filePath);
        if (!file.good()) {
            throw std::runtime_error("File not found: " + filePath);
        }
    }

public:
    explicit FileReader(const std::string& path) : filePath(path) {}
    virtual ~FileReader() = default;

    virtual std::string read() = 0;
    virtual std::string getFileType() const = 0;
};

class TextFileReader : public FileReader {
public:
    explicit TextFileReader(const std::string& path) : FileReader(path) {}

    std::string read() override {
        checkFileExists();

        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open text file: " + filePath);
        }

        std::string content((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());

        if (file.fail() && !file.eof()) {
            throw std::runtime_error("Error reading text file: " + filePath);
        }

        return content;
    }

    std::string getFileType() const override {
        return "Text File";
    }
};

class BinaryFileReader : public FileReader {
public:
    explicit BinaryFileReader(const std::string& path) : FileReader(path) {}

    std::string read() override {
        checkFileExists();

        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open binary file: " + filePath);
        }

        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);
        file.read(buffer.data(), size);

        if (file.fail() && !file.eof()) {
            throw std::runtime_error("Error reading binary file: " + filePath);
        }

        return std::string(buffer.begin(), buffer.end());
    }

    std::string getFileType() const override {
        return "Binary File";
    }
};

class JsonFileReader : public FileReader {
public:
    explicit JsonFileReader(const std::string& path) : FileReader(path) {}

    std::string read() override {
        checkFileExists();

        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open JSON file: " + filePath);
        }

        json j;
        try {
            file >> j;
        }
        catch (const json::parse_error& e) {
            throw std::runtime_error("JSON parse error: " + std::string(e.what()));
        }

        if (file.fail() && !file.eof()) {
            throw std::runtime_error("Error reading JSON file: " + filePath);
        }

        return j.dump(4); 
    }

    std::string getFileType() const override {
        return "JSON File";
    }
};

void testFileReader(FileReader& reader) {
    try {
        std::cout << "Reading " << reader.getFileType() << " at " << reader.read() << std::endl;
        std::string content = reader.read();
        std::cout << "Successfully read " << content.size() << " bytes" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        TextFileReader textReader("example.txt");
        BinaryFileReader binaryReader("example.bin");
        JsonFileReader jsonReader("example.json");

        testFileReader(textReader);
        testFileReader(binaryReader);
        testFileReader(jsonReader);

    }
    catch (const std::exception& e) {
        std::cerr << "Initialization error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}