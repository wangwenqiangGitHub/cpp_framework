#include <https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp>
#include <iostream>
#include <vector>

using json = nlohmann::json;

class xml_sax : public json::json_sax_t {
   public:
    bool null() override { return true; }
    bool boolean(bool val) override { return true; }
    bool number_integer(number_integer_t val) override {
        m_xml += "<value type=\"number\">";
        m_xml += std::to_string(val);
        m_xml += "</value>\n";
        m_xml += "</key_value>\n";
        return true;
    }
    bool number_unsigned(number_unsigned_t val) override {
        m_xml += "<value type=\"number\">";
        m_xml += std::to_string(val);
        m_xml += "</value>\n";
        m_xml += "</key_value>\n";
        return true;
    }
    bool number_float(number_float_t val, const string_t& s) override {
        m_xml += "<value type=\"number\">";
        m_xml += std::to_string(val);
        m_xml += "</value>\n";
        m_xml += "</key_value>\n";
        return true;
    }
    bool string(string_t& val) override {
        m_xml += "<value type=\"string\">";
        m_xml += val;
        m_xml += "</value>\n";
        m_xml += "</key_value>\n";
        return true;
    }
    bool start_array(std::size_t elements) override { return true; }
    bool end_array() override { return true; }
    bool binary(json::binary_t& val) override { return true; }

    bool parse_error(std::size_t position, const std::string& last_token,
                     const json::exception& ex) override {
        throw ex;
        return false;
    }

    bool start_object(std::size_t elements) override {
        m_xml += "<object>\n";
        return true;
    }

    bool end_object() override {
        m_xml += "</object>\n";
        return true;
    }

    bool key(string_t& val) override {
        m_xml += "<key_value>\n<key>";
        m_xml += val;
        m_xml += "</key>\n";
        return true;
    }

    const std::string xml() const { return m_xml; }

   private:
    std::vector<std::vector<std::string>> m_stack;
    std::string m_xml;
};

int main() {
    xml_sax sax;
    json j = {{"foo", 42}, {"bar", "baz"}};
    auto str = j.dump();
    if (json::sax_parse(str, &sax)) {
        std::cout << sax.xml() << "\n";
    }
}

