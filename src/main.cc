#include <iostream>
#include <fstream>
#include <string>
#include "casciv2.hh"

int main(int argc, char* argv[]) {
    std::string out_path = ".";
    std::string operation;
    std::string file_name;
    std::string pattern;

    if (argc < 3) {
        std::cout << "CASCIV2 1.0\n";
        std::exit(3);
    }

    // Process command-line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "encrypt" || arg == "e") {
            operation = "encrypt";
        } else if (arg == "decrypt" || arg == "d") {
            operation = "decrypt";
        } else if (i == 1) {
            std::cout << "Error -> Unknown operation <" << arg << "> found! Please use 'encrypt' or 'decrypt'.\n";
            std::exit(3);
        } else if (i == 2) {
            file_name = arg;
        } else if (i == 3) {
            pattern = arg;
        } else if (i == 4) {
            out_path = arg;
        }
    }

    // Validate the operation and file name
    if (operation.empty()) {
        std::cout << "Error -> Operation not specified! Use 'encrypt' or 'decrypt'.\n";
        std::exit(3);
    }

    if (file_name.empty()) {
        std::cout << "Error -> File name not specified!\n";
        std::exit(3);
    }

    // Perform the operation
    if (operation == "encrypt") {
        std::ifstream ifile(file_name);
        if (!ifile.is_open()) {
            std::cout << "Error -> File not found!\n";
            std::exit(3);
        }

        std::string ecc, temp;
        while (std::getline(ifile, temp)) {
            ecc += temp + "\n";
        }

        CASCIV2 make = ecc;
        std::string file = make.encode(pattern);

        std::ofstream ofile(out_path + "/" + file_name + ".casci");
        ofile << file;

    } else if (operation == "decrypt") {
        if (file_name.rfind(".casci") == std::string::npos) {
            std::cout << "Error -> No valid CASCI file was assigned to decrypt! Please assign a file ending with '.casci'.\n";
            std::exit(3);
        }

        std::ifstream ifile(file_name);
        if (!ifile.is_open()) {
            std::cout << "Error -> File not found!\n";
            std::exit(3);
        }

        std::string ecc, temp;
        while (std::getline(ifile, temp)) {
            ecc += temp + "\n";
        }

        CASCIV2 make = ecc;
        std::string file = make.decode(pattern);

        std::ofstream ofile(out_path + "/" + file_name.substr(0, file_name.find(".casci")));
        ofile << file;
    }

    return 0;
}
