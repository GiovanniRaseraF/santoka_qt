#include <sstream>
#include <iostream>
#include <string>
#include <vector>

int main(){
    int ch{0}, id{0}, flag{0}, dlc{0};
    double time{0.0};
    std::string direction = {};
    std::vector<int> nums;

    // discard first line
    std::getline(std::cin, direction);
    std::string line;
    int index = 0;
    while(!std::cin.eof()){
        index++;
        //std::cout << std::dec << index << std::endl;
        std::getline(std::cin, line);

        if (line != "Logging stopped."){
            nums = {};
            // Parse data
            std::stringstream sline{line};
            std::string check = sline.str();

            if (check.find("ErrorFrame") == std::string::npos){
                sline >> ch >> id >> dlc;

                for(int i = 0; i < dlc; i++){
                    int value;
                    sline >> value;

                    nums.push_back(value);
                }
                for(int i = dlc; i < 8; i++){
                    nums.push_back(0);
                }

                sline >> time;
                sline >> direction;

                std::string base = "std::tuple<uint16_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t>"; 
                //std::tuple<uint16_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t>{vales}
                // Printing
                std::cout << base << "{" << id << ", ";
                int counter = 0;
                for(int vals : nums){
                    if(counter < 7)
                        std::cout << vals << ", ";
                    else
                        std::cout << vals;

                    counter ++;
                }
                
                std::cout << "}," << std::endl;             
            }
        }else{
            //std::cout << line;
        }
        nums = {};   
    }
}
