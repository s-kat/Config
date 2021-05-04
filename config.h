#pragma once

#include "logs/log.h"
#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/writer.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"
#include "rapidjson/include/rapidjson/filereadstream.h"
#include "rapidjson/include/rapidjson/istreamwrapper.h"
#include "rapidjson/include/rapidjson/ostreamwrapper.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <stdint.h>
#include <type_traits>
#include <string>
#include <optional>

class Config {
private:
    std::string path_to_config_file;
    rapidjson::Document configuration;

public:
    Config() {};

    Config(std::string & path_to_parse) : path_to_config_file(path_to_parse) {
        std::ifstream input_file_stream(path_to_config_file);

        Log::getInstance().Log_trace("Start loading json from file: " + path_to_config_file + "\n");

        rapidjson::IStreamWrapper input_stream_wrapper (input_file_stream);
        configuration.ParseStream(input_stream_wrapper);

        Log::getInstance().Log_trace("Parsing json from file: " + path_to_config_file + " completed \n");

        input_file_stream.close();
    }

    void ViewJSON() const {
        rapidjson::StringBuffer buffer {};
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        configuration.Accept(writer);

        if (configuration.HasParseError()) {
            Log::getInstance().Log_trace("Error in parsing: " + std::to_string(configuration.GetParseError())  + "\n");
            Log::getInstance().Log_trace("Offset : " + std::to_string(configuration.GetErrorOffset()) + '\n');
            throw std::runtime_error("Error in parsing JSON file!");
            return;
        }
        const std::string jsonStr (buffer.GetString());

        Log::getInstance().Log_trace("Output json to stdout");
        std::cout << jsonStr << '\n';
    }

    bool ExistCheck(std::string key) {
        const char * c_key = key.c_str();
         if (configuration.HasMember(c_key)) {
             return true;
         } else {
             return false;
         }
    }

    std::string ValueType(std::string key) {
        const char * c_key = key.c_str();
        if (ExistCheck(key)) {
            if (configuration[c_key].IsInt()) {
                return "int";
            } else if (configuration[c_key].IsDouble()) {
                return "double";
            } else if (configuration[c_key].IsBool()) {
                return "bool";
            } else if (configuration[c_key].IsString()) {
                return "string";
            } else {
                return "NULL";
            }
        } else {
            return "NULL";
        }
    }

    std::optional<int> GetInt (std::string key) const {
        const char * c_key = key.c_str();

        if (!configuration.HasMember(c_key)) {
            Log::getInstance().Log_trace("Error: configuration does not have parameter:" + key + "\n");
            return std::nullopt;
            throw std::runtime_error("Missing parameter!");
        }

        if (configuration[c_key].IsInt()) {
            int64_t result = configuration[c_key].GetInt64();
            Log::getInstance().Log_trace("Get value: " + std::to_string(result) + " by parameter: " + key + "\n");
            return {result};
        } else {
            Log::getInstance().Log_trace("Error: value by parameter: " + key + " is not a integer\n");
            return std::nullopt;
        }
    }

    std::optional<std::string> GetString (std::string key) const {
        const char * c_key = key.c_str();

        if (!configuration.HasMember(c_key)) {
            Log::getInstance().Log_trace("Error: configuration does not have parameter:" + key + "\n");
            return std::nullopt;
        }

        if (configuration[c_key].IsString()) {
            std::string result = configuration[c_key].GetString();
            Log::getInstance().Log_trace("Get value: \"" + result + "\" by parameter: " + key + "\n");
            return {result};
        } else {
            Log::getInstance().Log_trace("Error: value by parameter: " + key + " is not a string\n");
            return std::nullopt;
        }
    }

    std::optional<double> GetDouble (std::string key) const {
        const char * c_key = key.c_str();

        if (!configuration.HasMember(c_key)) {
            Log::getInstance().Log_trace("Error: configuration does not have parameter:" + key + "\n");
            return std::nullopt;
        }

        if (configuration[c_key].IsDouble()) {
            double result = configuration[c_key].GetDouble();
            Log::getInstance().Log_trace("Get value: " + std::to_string(result) + " by parameter: " + key + "\n");
            return {result};
        } else {
            Log::getInstance().Log_trace("Error: value by parameter: " + key + " is not a double\n");
            return std::nullopt;
        }
    }

    std::optional<bool> GetBool (std::string key) const {
        const char * c_key = key.c_str();
        if (!configuration.HasMember(c_key)) {
            Log::getInstance().Log_trace("Error: configuration does not have parameter:" + key + "\n");
            return std::nullopt;
        }

        if (configuration[c_key].IsBool()) {
            bool result = configuration[c_key].GetBool();
            Log::getInstance().Log_trace("Get value: " + std::to_string(result) + " by parameter: " + key + "\n");
            return {result};
        } else {
            Log::getInstance().Log_trace("Error: value by parameter: " + key + " is not a boolean\n");
            return std::nullopt;
        }
    }

    int AddStr(const std::string parameter, std::string element ) {
        // check if parameter in the json file already exists
        if (configuration.HasMember(parameter.c_str())) {
            Log::getInstance().Log_trace("Parameter:\"" + parameter + "\" already exist!\n");
            // if exists then do nothing and return -1
            return -1;
        }
        // if not exists add parameter to json
        rapidjson::Value key;
        key.SetString(rapidjson::StringRef(parameter.c_str()));

        rapidjson::Value val;
        val.SetString(rapidjson::StringRef(element.c_str()));
        configuration.AddMember(key, val, configuration.GetAllocator());
        Log::getInstance().Log_trace("Add parameter:\"" + parameter + "\n");
        return 0;
    }

    template <typename T>
    int AddValue(const std::string parameter, T element ) {
        // check if parameter in the json file already exists
        if (configuration.HasMember(parameter.c_str())) {
            Log::getInstance().Log_trace("Parameter:\"" + parameter + "\" already exist!\n");
            // if exists then do nothing and return -1
            return -1;
        }
        // if not exists add parameter to json
        rapidjson::Value index(parameter.c_str(), parameter.size(), configuration.GetAllocator()); // copy string
        configuration.AddMember(index, element, configuration.GetAllocator());
        Log::getInstance().Log_trace("Add parameter:\"" + parameter + "\n");
        return 0;
    }

    void SaveJson(std::string path_to_save_file = "") {
        // if path_to_save_file is not provide, overwrite source file
        if (path_to_save_file == "") {
            path_to_save_file = path_to_config_file;
        }
        std::ofstream output_file_stream(path_to_save_file);
        rapidjson::OStreamWrapper output_stream_wrapper(output_file_stream);
 
        rapidjson::Writer<rapidjson::OStreamWrapper> writer(output_stream_wrapper);
        configuration.Accept(writer);
        Log::getInstance().Log_trace("Save configuration on the path: " + path_to_save_file + "\n");
        output_file_stream.close();
    }

    void RemoveValue(std::string key) {
        const char * c_key = key.c_str();
        if (!configuration.HasMember(c_key)) {
            Log::getInstance().Log_trace("Error: configuration does not have parameter:" + key + "\n");
            throw std::runtime_error("Missing parameter!");
        }
        Log::getInstance().Log_trace("Delete value from configuration with key:" + key + "\n");
        configuration.RemoveMember(c_key);
    }

    int UpdateString(std::string key, std::string value) {
        auto c_key = key.c_str();
        // check if parameter in the json file already exists
        if (configuration.HasMember(c_key)) {
            Log::getInstance().Log_trace("Parameter:\"" + key + "\" updated to:" + value + "\n");
            configuration[c_key].SetString(rapidjson::StringRef(value.c_str()));
            return 0;
        } else {
            Log::getInstance().Log_trace("Parameter:\"" + key + "\" does not exist!\n");
            return -1;
        }
    }
    template <typename T>
    int Update(std::string key, T value) {
        auto c_key = key.c_str();
        // check if parameter in the json file already exists
        if (configuration.HasMember(c_key)) {
            Log::getInstance().Log_trace("Parameter:\"" + key + "\" updated to:" + std::to_string(value) + "\n");
            configuration[c_key] = value;
            return 0;
        } else {
            Log::getInstance().Log_trace("Parameter:\"" + key + "\" does not exist!\n");
            return -1;
        }
    }


    ~Config() {
        Log::getInstance().Log_trace("Quit");
    }
};
