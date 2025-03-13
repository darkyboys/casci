/*
 * Copyright (c) ghgltggamer 2025
 * Written by ghgltggamer 2025
 * Licensed under the MIT License - Please checkout the License file for more information
 * Checkout the README.md file for more information about the entire project.
 * CASCI - A Secure Format to store data & information in a secure way ysing patterns
 * CASCI - Stands for Characterised Alternate Secure Calendar Integral
*/

// Source
#include <cstddef>
#include <sstream>
#ifndef CASCI_LIB
#define CASCI_LIB 1

// Std Cxx Stl
#include <iostream>
#include <string>

class CASCI {
    private:
        std::string data;
    public:
        CASCI (std::string value) : data (value ) {}

        std::string encrypt (int pattern){
            std::string rval = "";
            std::stringstream data_stream (data);
            std::string temp, conv;
            std::string pattern_str = std::to_string(pattern);
            std::size_t pattern_index = 0;
            
            while (std::getline (data_stream, temp)){
                const char* characters = temp.c_str();
                
                for (std::size_t i = 0;i < temp.length();i++) {
                    // int pattern_number = 
                    conv += std::to_string(int (characters[i]) + 
                        ((std::to_string(pattern)[pattern_index])-'0')
                    ) + " ";
                    if (pattern_index == pattern_str.length()-1) pattern_index = 0;
                    else pattern_index += 1;
                    // std::cout << "'"<<((std::to_string(pattern)[pattern_index])-'0')+1+i<<"'\n";
                    // std::cout <<"'"<<((std::to_string(pattern)[1])-'0')+1<<"'\n";
                }
                conv += "\n";
                
            }
            rval = conv + "\n";


            return rval;
        }

        std::string decrypt (std::size_t pattern){
            std::string rval = "";
            std::string pattern_str = std::to_string(pattern);
            std::size_t pattern_index = 0;
            std::string current_chars = "";
            std::string pattern_decoded;

            for (std::size_t i = 0;i < data.length();i++){
                if (data [i] == '\n') {pattern_decoded += '\n'; continue;}
                if (data [i] == '\0') {continue;}
                if (pattern_index == pattern_str.length()) pattern_index = 0;
                if (data[i] == ' ') {
                    // std::string str_correct = pattern_str;
                    for (std::size_t x = 0;x < current_chars.length();x++) {
                        pattern_decoded += char (std::stoi(current_chars)-(pattern_str[pattern_index]-'0'));
                        // std::cout << char (std::stoi(current_chars)-(pattern_str[pattern_index]-'0'));
                        // std::cout << "'"<<pattern_str[pattern_index]<<"'\n";
                        pattern_index += 1;
                        current_chars.clear();
                    }
                }
                else current_chars += data[i];
            }
            rval = pattern_decoded;
            return rval;
        }

        ~CASCI (){}
};

#endif

// Ended by ghgltggamer