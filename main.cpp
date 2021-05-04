#include "config.h"
#include <iostream>
#include <string>
#include <optional>
#include <typeinfo>


template <typename T>
void PrintAcces(std::string key, std::optional<T> val) {
    if (val) {
        std::cout << "Success: Get value: " << *val << ". On parameter:\"" << key << "\" with type <" << typeid(*val).name() << ">\n";
    } else {
        std::cout << "Fail: It was not possible to get the value with type <" <<  typeid(*val).name() << "> by parameter: " << key << "\n";
    }
    std::cout << "----------------------------------------------------------------------------------------------------------\n";
}

int main() {
    // Indicate the path to json file
    std::string path = "big.json";
    // Make Config object
    class Config json(path);

    // Show Config
    json.ViewJSON();

    // Try to get value by key
    std::cout << "\n######< Checking the getting of parameters >######\n";
    //int values
    std::optional<int> int1 = json.GetInt("param_int1");
    PrintAcces("param_int1", int1);

    std::optional<int> int2 = json.GetInt("param_int123");
    PrintAcces("param_int123", int2);

    // double values
    std::optional<double> d1 = json.GetDouble("param_double1");
    PrintAcces("param_double1", d1);

    std::optional<double> d2 = json.GetDouble("param_int1");
    PrintAcces("param_int1", d2);

    // string values
    std::optional<std::string> str1 = json.GetString("param_str1");
    PrintAcces("param_str1", str1);


    std::optional<std::string> str2 = json.GetString("asd_str1");
    PrintAcces("asd_str1", str2);


    // bool values
    std::optional<bool> bool1 = json.GetBool("param_bool1");
    PrintAcces("param_bool1", bool1);

    std::optional<bool> bool2 = json.GetBool("param_bool2");
    PrintAcces("param_bool2", bool2);

    // Print type of values
    std::cout << "\n######< Checking types of parameters >######\n";
    std::cout << "Type of parameter \"param_bool1\" is " << json.ValueType("param_bool1") << "\n";
    std::cout << "Type of parameter \"param_str1\" is "  << json.ValueType("param_str1") << "\n";
    std::cout << "Type of parameter \"param_double1\" is " << json.ValueType("param_double1") << "\n";
    std::cout << "Type of parameter \"param_int1\" is " << json.ValueType("param_int1") << "\n";
    std::cout << "Type of parameter \"not_exist\" is " << json.ValueType("not_exist") << "\n";
    
    // Check if parameter is exist
    std::cout << "\n######< Checking the existence of parameters >######\n";
    if (json.ExistCheck("param_int1")) {
        std::cout << "Parameter \"param_int1\" is exist\n";
    } else {
        std::cout << "Parameter \"param_int1\" does not exist\n";
    }

    if (json.ExistCheck("asd")) {
        std::cout << "Parameter \"asd\" is exist\n";
    } else {
        std::cout << "Parameter \"asd\" does not exist\n";
    }

    // Add value to configuration
    
    std::cout << "\n######< Checking adding parameters >######\n";
    json.AddValue("new_int1", 123);
    json.AddValue("new_bool", true);
    json.AddValue("new_double", 0.0324);
    json.AddStr("new_str", "new_str");
    // View changes
    json.ViewJSON();

    // Update value by parameter;
    std::cout << "\n######< Checking updatings parameters >######\n";
    json.UpdateString("new_str", "real_str");
    json.Update("new_double", 100000000);
    json.Update("new_int1", 0.24325);
    json.Update("new_double", true);
    // view changes
    json.ViewJSON();

    // Delete parameters
    std::cout << "\n######< Checking deleting parameters >######\n";
    json.RemoveValue("new_double");
    json.RemoveValue("new_str");
    // view changes
    json.ViewJSON();

    // save json to new file
    json.SaveJson("new_big.json");

    return 0;
}
