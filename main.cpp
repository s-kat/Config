#include "config.h"
#include <iostream>
#include <string>



int main() {
    std::string path = "big.json";
    class Config new_json(path);
    new_json.viewJSON();
    

    int res = 0;
    std::string key = "param2";
    new_json.getValue(key, res);
    std::cout << res << "-integer \n";
    
    std::string st;
    std::string key2 = "param1";
    new_json.getValue(key2, st);
    std::cout << st << "-string \n";

    bool res_bool;
    std::string key4 = "param3";
    new_json.getValue(key4, res_bool);
    std::cout << res_bool << "-bool\n";

    new_json.AddValue("data", 45);

    new_json.AddValue("blabal", true);
    new_json.SaveJson();
    return 0;
}
