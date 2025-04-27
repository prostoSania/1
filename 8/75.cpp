#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
#include <map>

class DataProcessor {
protected:
    virtual void validateData(const std::string& data) const {
        if (data.empty()) {
            throw std::invalid_argument("Data cannot be empty");
        }
    }

public:
    virtual ~DataProcessor() = default;

    virtual std::map<std::string, std::string> processData(const std::string& data) = 0;

    virtual std::string getProcessorType() const = 0;
};

class CSVDataProcessor : public DataProcessor {
private:
    char delimiter;

    void validateData(const std::string& data) const override {
        DataProcessor::validateData(data);
        if (data.find(delimiter) == std::string::npos) {
            throw std::invalid_argument("CSV data must contain delimiter");
        }
    }

public:
    explicit CSVDataProcessor(char delim = ',') : delimiter(delim) {}

    std::map<std::string, std::string> processData(const std::string& data) override {
        validateData(data);

        std::map<std::string, std::string> result;
        std::istringstream ss(data);
        std::string line;

        // Чтение заголовков
        if (!std::getline(ss, line)) {
            throw std::runtime_error("Failed to read CSV headers");
        }

        std::vector<std::string> headers;
        std::istringstream headerStream(line);
        std::string header;
        while (std::getline(headerStream, header, delimiter)) {
            headers.push_back(header);
        }

        // Чтение данных
        if (!std::getline(ss, line)) {
            throw std::runtime_error("Failed to read CSV data");
        }

        std::vector<std::string> values;
        std::istringstream valueStream(line);
        std::string value;
        while (std::getline(valueStream, value, delimiter)) {
            values.push_back(value);
        }

        if (headers.size() != values.size()) {
            throw std::runtime_error("CSV headers and values count mismatch");
        }

        for (size_t i = 0; i < headers.size(); ++i) {
            result[headers[i]] = values[i];
        }

        return result;
    }

    std::string getProcessorType() const override {
        return "CSV Data Processor";
    }
};

class XMLDataProcessor : public DataProcessor {
protected:
    void validateData(const std::string& data) const override {
        DataProcessor::validateData(data);
        if (data.find('<') == std::string::npos ||
            data.find('>') == std::string::npos) {
            throw std::invalid_argument("Invalid XML format");
        }
    }

public:
    std::map<std::string, std::string> processData(const std::string& data) override {
        validateData(data);

        std::map<std::string, std::string> result;
        size_t pos = 0;

        while (true) {
            size_t startTag = data.find('<', pos);
            if (startTag == std::string::npos) break;

            size_t endTag = data.find('>', startTag);
            if (endTag == std::string::npos) {
                throw std::runtime_error("Malformed XML tag");
            }

            std::string tag = data.substr(startTag + 1, endTag - startTag - 1);
            size_t endStartTag = data.find("</" + tag + ">", endTag);

            if (endStartTag == std::string::npos) {
                throw std::runtime_error("Missing closing tag for: " + tag);
            }

            std::string value = data.substr(endTag + 1, endStartTag - endTag - 1);
            result[tag] = value;

            pos = endStartTag + tag.length() + 3;
        }

        if (result.empty()) {
            throw std::runtime_error("No valid XML tags found");
        }

        return result;
    }

    std::string getProcessorType() const override {
        return "XML Data Processor";
    }
};

class JSONDataProcessor : public DataProcessor {
protected:
    void validateData(const std::string& data) const override {
        DataProcessor::validateData(data);
        if (data.find('{') == std::string::npos ||
            data.find('}') == std::string::npos ||
            data.find(':') == std::string::npos) {
            throw std::invalid_argument("Invalid JSON format");
        }
    }

public:
    std::map<std::string, std::string> processData(const std::string& data) override {
        validateData(data);

        std::map<std::string, std::string> result;
        size_t start = data.find('{');
        size_t end = data.find('}', start);

        if (start == std::string::npos || end == std::string::npos) {
            throw std::runtime_error("Malformed JSON structure");
        }

        std::string content = data.substr(start + 1, end - start - 1);
        size_t colonPos = content.find(':');

        if (colonPos == std::string::npos) {
            throw std::runtime_error("Missing key-value separator in JSON");
        }

        std::string key = content.substr(0, colonPos);
        std::string value = content.substr(colonPos + 1);

        // Удаление лишних пробелов и кавычек
        key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
        value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());

        if (key.front() == '"' && key.back() == '"') {
            key = key.substr(1, key.length() - 2);
        }

        if (value.front() == '"' && value.back() == '"') {
            value = value.substr(1, value.length() - 2);
        }

        if (key.empty() || value.empty()) {
            throw std::runtime_error("Empty key or value in JSON");
        }

        result[key] = value;
        return result;
    }

    std::string getProcessorType() const override {
        return "JSON Data Processor";
    }
};

void testDataProcessor(DataProcessor& processor, const std::string& testData) {
    try {
        std::cout << "Testing " << processor.getProcessorType() << " with data:\n"
            << testData << "\nResult:\n";

        auto result = processor.processData(testData);
        for (const auto& [key, value] : result) {
            std::cout << key << " => " << value << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Processing error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        CSVDataProcessor csvProcessor;
        XMLDataProcessor xmlProcessor;
        JSONDataProcessor jsonProcessor;

        std::string csvData = "name,age,email\nJohn Doe,30,john@example.com";
        std::string xmlData = "<user><name>John Doe</name><age>30</age><email>john@example.com</email></user>";
        std::string jsonData = R"({"name": "John Doe", "age": 30, "email": "john@example.com"})";

        testDataProcessor(csvProcessor, csvData);
        testDataProcessor(xmlProcessor, xmlData);
        testDataProcessor(jsonProcessor, jsonData);



    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}