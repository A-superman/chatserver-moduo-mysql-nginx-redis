#include <iostream>  
#include <boost/lexical_cast.hpp>  

int main() {  
    int number = 123;  
    std::string str = boost::lexical_cast<std::string>(number);  
    std::cout << "Number as string: " << str << std::endl;  
    return 0;  
}
