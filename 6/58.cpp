#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>


class DataProcessor {
protected:

    void checkDataNotEmpty(const std::string& data) const {
        if (data.empty()) {
            throw std::invalid_argument("Data cannot be empty");
        }
    }


    virtual bool isValidData(const std::string& data) const {
        return !data.empty();
    }

public:
    virtual ~DataProcessor() = default;


    virtual std::map<std::string, std::string> process(const std::string& data) = 0;


    virtual std::string getProcessorType() const = 0;
};


class CSVProcessor : public DataProcessor {
private:
    char delimiter;


    bool isValidData(const std::string& data) const override {
        size_t delimiterCount = std::count(data.begin(), data.end(), delimiter);
        return delimiterCount > 0 && data.find('\n') != std::string::npos;
    }

public:
    explicit CSVProcessor(char delim = ',') : delimiter(delim) {}

    std::map<std::string, std::string> process(const std::string& data) override {
        checkDataNotEmpty(data);

        if (!isValidData(data)) {
            throw std::runtime_error("Invalid CSV format");
        }

        std::map<std::string, std::string> result;
        std::vector<std::string> lines;
        size_t pos = 0;
        size_t end;


        while ((end = data.find('\n', pos)) != std::string::npos) {
            lines.push_back(data.substr(pos, end - pos));
            pos = end + 1;
        }
        lines.push_back(data.substr(pos));


        if (lines.empty()) {
            throw std::runtime_error("No data in CSV");
        }

        std::vector<std::string> headers;
        pos = 0;
        while ((end = lines[0].find(delimiter, pos)) != std::string::npos) {
            headers.push_back(lines[0].substr(pos, end - pos));
            pos = end + 1;
        }
        headers.push_back(lines[0].substr(pos));


        if (lines.size() < 2) {
            throw std::runtime_error("Missing data row in CSV");
        }

        std::vector<std::string> values;
        pos = 0;
        while ((end = lines[1].find(delimiter, pos)) != std::string::npos) {
            values.push_back(lines[1].substr(pos, end - pos));
            pos = end + 1;
        }
        values.push_back(lines[1].substr(pos));


        if (headers.size() != values.size()) {
            throw std::runtime_error("CSV headers and values count mismatch");
        }


        for (size_t i = 0; i < headers.size(); ++i) {
            result[headers[i]] = values[i];
        }

        return result;
    }

    std::string getProcessorType() const override {
        return "CSV Processor (delimiter: '" + std::string(1, delimiter) + "')";
    }
};


class JSONProcessor : public DataProcessor {
private:

    bool isValidData(const std::string& data) const override {
        return data.find('{') != std::string::npos &&
            data.find('}') != std::string::npos &&
            data.find(':') != std::string::npos;
    }

public:
    std::map<std::string, std::string> process(const std::string& data) override {
        checkDataNotEmpty(data);

        if (!isValidData(data)) {
            throw std::runtime_error("Invalid JSON format");
        }

        std::map<std::string, std::string> result;
        size_t start = data.find('{');
        size_t end = data.find('}');

        if (start == std::string::npos || end == std::string::npos || start >= end) {
            throw std::runtime_error("Malformed JSON structure");
        }

        std::string content = data.substr(start + 1, end - start - 1);
        size_t colonPos = content.find(':');

        if (colonPos == std::string::npos) {
            throw std::runtime_error("Missing key-value separator in JSON");
        }

        std::string key = content.substr(0, colonPos);
        std::string value = content.substr(colonPos + 1);


        key.erase(std::remove(key.begin(), key.end(), '"'), key.end());
        key.erase(std::remove(key.begin(), key.end(), ' '), key.end());
        value.erase(std::remove(value.begin(), value.end(), '"'), value.end());
        value.erase(std::remove(value.begin(), value.end(), ' '), value.end());

        if (key.empty() || value.empty()) {
            throw std::runtime_error("Empty key or value in JSON");
        }

        result[key] = value;
        return result;
    }

    std::string getProcessorType() const override {
        return "JSON Processor";
    }
};


class XMLProcessor : public DataProcessor {
private:

    bool isValidData(const std::string& data) const override {
        return data.find('<') != std::string::npos &&
            data.find('>') != std::string::npos &&
            data.find("</") != std::string::npos;
    }

public:
    std::map<std::string, std::string> process(const std::string& data) override {
        checkDataNotEmpty(data);

        if (!isValidData(data)) {
            throw std::runtime_error("Invalid XML format");
        }

        std::map<std::string, std::string> result;
        size_t startTag = data.find('<');
        size_t endTag = data.find('>', startTag);

        if (startTag == std::string::npos || endTag == std::string::npos) {
            throw std::runtime_error("Malformed XML tag");
        }

        std::string tag = data.substr(startTag + 1, endTag - startTag - 1);
        size_t endStartTag = data.find("</" + tag + ">");

        if (endStartTag == std::string::npos) {
            throw std::runtime_error("Missing closing tag in XML");
        }

        std::string value = data.substr(endTag + 1, endStartTag - endTag - 1);

        if (tag.empty() || value.empty()) {
            throw std::runtime_error("Empty tag or value in XML");
        }

        result[tag] = value;
        return result;
    }

    std::string getProcessorType() const override {
        return "XML Processor";
    }
};


void testProcessor(DataProcessor& processor, const std::string& testData) {
    try {
        std::cout << "\nTesting " << processor.getProcessorType() << " with data:\n"
            << testData << std::endl;

        auto result = processor.process(testData);

        std::cout << "Processing successful. Result:" << std::endl;
        for (const auto& [key, value] : result) {
            std::cout << "  " << key << " => " << value << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Processing error: " << e.what() << std::endl;
    }
}

int main() {
    try {

        CSVProcessor csvProcessor;
        JSONProcessor jsonProcessor;
        XMLProcessor xmlProcessor;


        std::string csvData = "name,age,email\nJohn Doe,30,john@example.com";
        std::string jsonData = R"({"username": "johndoe", "status": "active"})";
        std::string xmlData = R"(<user><id>12345</id><role>admin</role></user>)";


        testProcessor(csvProcessor, csvData);
        testProcessor(jsonProcessor, jsonData);
        testProcessor(xmlProcessor, xmlData);



    }
    catch (const std::exception& e) {
        std::cerr << "Initialization error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}