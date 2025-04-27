#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>


class DataReader {
public:
    virtual ~DataReader() = default;

    virtual std::vector<std::vector<std::string>> readData(const std::string& filename) = 0;

protected:

    void checkFileExists(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.good()) {
            throw std::runtime_error("File not found: " + filename);
        }
    }
};

class CSVReader : public DataReader {
public:
    std::vector<std::vector<std::string>> readData(const std::string& filename) override {
        checkFileExists(filename);

        std::vector<std::vector<std::string>> data;
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line)) {
            std::vector<std::string> row;
            size_t start = 0, end = line.find(',');

            while (end != std::string::npos) {
                row.push_back(line.substr(start, end - start));
                start = end + 1;
                end = line.find(',', start);
            }
            row.push_back(line.substr(start));

            if (!data.empty() && row.size() != data[0].size()) {
                throw std::runtime_error("Invalid CSV format: inconsistent number of columns");
            }

            data.push_back(row);
        }

        if (data.empty()) {
            throw std::runtime_error("Empty CSV file");
        }

        return data;
    }
};

class XMLReader : public DataReader {
public:
    std::vector<std::vector<std::string>> readData(const std::string& filename) override {
        checkFileExists(filename);

        std::vector<std::vector<std::string>> data;
        std::ifstream file(filename);
        std::string line;
        bool inRow = false;
        std::vector<std::string> currentRow;

        while (std::getline(file, line)) {
            if (line.find("<row>") != std::string::npos) {
                if (inRow) {
                    throw std::runtime_error("Invalid XML format: nested <row> tags");
                }
                inRow = true;
                currentRow.clear();
            }
            else if (line.find("<cell>") != std::string::npos) {
                if (!inRow) {
                    throw std::runtime_error("Invalid XML format: <cell> outside <row>");
                }
                size_t start = line.find("<cell>") + 6;
                size_t end = line.find("</cell>");
                if (end == std::string::npos) {
                    throw std::runtime_error("Invalid XML format: unclosed <cell>");
                }
                currentRow.push_back(line.substr(start, end - start));
            }
            else if (line.find("</row>") != std::string::npos) {
                if (!inRow) {
                    throw std::runtime_error("Invalid XML format: closing </row> without opening");
                }
                inRow = false;
                data.push_back(currentRow);
            }
        }

        if (inRow) {
            throw std::runtime_error("Invalid XML format: unclosed <row>");
        }

        if (data.empty()) {
            throw std::runtime_error("Empty XML file");
        }

        return data;
    }
};

void printData(const std::vector<std::vector<std::string>>& data) {
    for (const auto& row : data) {
        for (const auto& cell : row) {
            std::cout << cell << "\t";
        }
        std::cout << std::endl;
    }
}

int main() {
    try {
        CSVReader csvReader;
        auto csvData = csvReader.readData("data.csv");
        std::cout << "CSV Data:" << std::endl;
        printData(csvData);

        XMLReader xmlReader;
        auto xmlData = xmlReader.readData("data.xml");
        std::cout << "\nXML Data:" << std::endl;
        printData(xmlData);

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}