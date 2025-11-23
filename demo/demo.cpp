#include <print>
#include <string>
#include "./bad_config_loader.hpp"
using namespace std::string_literals;
using namespace std::string_view_literals;

int main(){
    std::println("Error Handling Workshop - demo program");

    const std::string path = "data/config_ok.txt";

    if(!load_config(path)){
        std::println("load_config returned false.\nUsing whatever g_config was set to.");
    }

    std::println("Config:");
    std::println("  width:  {}", g_config.width);
    std::println("  height:  {}", g_config.height);
    std::println("  title:  {}", g_config.title);    

    // TODO in the workshop:
    // - Remove g_config.
    // - Change main() to use your new API.
    // - Handle errors explicitly here.

    return 0;
}
