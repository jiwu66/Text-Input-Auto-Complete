#include <iostream>
#include "trie.h"

int main() {
    std::string cmdline;
    trie data;

    while(true){
        if(std::cin.eof()){
            break;
        }

        std::getline(std::cin, cmdline);

        if(cmdline == "exit"){
            break;
        }

        if(cmdline == "print"){
            data.print();
        }

        if(cmdline == "empty"){
            bool empty = data.empty();
            if(empty == 1){
                std::cout << "empty 1" << std::endl;
            }
            else std::cout << "empty 0" << std::endl;
        }

        if(cmdline == "clear"){
            data.clear();
            std::cout << "success" << std::endl;
        }

        if(cmdline == "size"){
            int size = data.size();
            std::cout << "number of words is " << size << std::endl;
        }


        int pos = cmdline.find(" ");
        std::string cmd = cmdline.substr(0, pos);
        std::string input = cmdline.substr(pos + 1, cmdline.size() - pos - 1);

        if(cmd == "autocomplete"){
            data.autocomplete(input);
        }

        if((cmd == "i") || (cmd == "e") || (cmd == "s")) {

            bool valid = true;
            try{
                for(int i = 0; i < input.size(); i++){
                    if((input[i] > 122) || (input[i] < 97)){
                        throw illegal_exception("illegal argument");
                    }
                }
            }
            catch(illegal_exception& e){
                valid = false;
            }

            if(valid == 1) {
                if (cmd == "i") {
                    std::string i = data.insert(input);
                    std::cout << i << std::endl;
                }

                if (cmd == "e") {
                    std::string e = data.erase(input);
                    std::cout << e << std::endl;
                }

                if (cmd == "s") {
                    std::string s = data.search(input);
                    if (s == "found") {
                        std::cout << s << " " << input << std::endl;
                    } else std::cout << s << std::endl;
                }
            }
        }


    }

}