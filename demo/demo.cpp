#include <print>
#include <string>
#include "./bad_config_loader.hpp"
using namespace std::string_literals;
using namespace std::string_view_literals;

int main(){
    std::println("Error Handling Workshop - demo program");

    const std::string path = "../data/config_ok.txt";
    

    try {
        Config conf(path);

        std::println("Config:");
        std::println("  width:  {}", conf.width);
        std::println("  height:  {}", conf.height);
        std::println("  title:  {}", conf.title);
    }
    catch (ConfigErr e) {
        std::println("  Config error:  {}", e.what());
    }
    catch (std::exception e) {
        std::println("  unknown error:  {}", e.what());
    }

    return 0;
}
