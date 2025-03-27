#include <iostream>
#include <fstream>
#include <string>
#include "casci.hh"



int main (int argc , char * argv[]){
    std::string out_path = ".";
    if (argc == 1) std::cout <<"CASCI 2.0\n", std::exit ( 3 );
    if (argc == 3) std::cout <<"Error -> CASCI Need a pattern tooo!!!!\n", std::exit ( 3 );
    if (argc == 2) std::cout <<"Error -> CASCI Need a file name and a pattern tooo!!!!\n", std::exit ( 3 );
    if (argc == 4) out_path = argv[3], std::cout <<"'"<<out_path<<"'\n";
    
    else {
        if (std::string(argv[1]) == "encrypt" or std::string(argv[1]) == "e"){
        // std::cout <<"Compiling!\n";
            
            std::string file_name = argv [2];
            
            std::ifstream ifile (file_name);
            
            if (!ifile.is_open()) std::cout << "Error - > FIle not found!\n", std::exit ( 3 );
            
            std::string ecc, file, temp;
            
            while (std::getline (ifile, temp)){
            
                ecc += temp + "\n";
            
            }
            
            CASCI make = ecc;
            
            file += make.encrypt((std::string (argv[3])));

            
            
            std::ofstream ofile (out_path + "/" + file_name + ".casci");
            
            ofile << file;
        }
        else if (std::string(argv[1]) == "decrypt" or std::string(argv[1]) == "d"){
            // std::cout <<"Compiling!\n";
            
            std::string file_name = argv [2];
            
            if (file_name.rfind(".casci") == std::string::npos) std::cout <<"Error -> No valid CASCI File was assigned to decrypt!!!, Please assign file ends with '.casci' file extension!\n", std::exit ( 3 );

            std::ifstream ifile (file_name);
            
            if (!ifile.is_open()) std::cout << "Error - > FIle not found!\n", std::exit ( 3 );
            
            std::string ecc, file, temp;
            
            while (std::getline (ifile, temp)){
            
                ecc += temp + "\n";
            
            }
            
            CASCI make = ecc;
            
            file += make.decrypt((std::string (argv[3])));

            std::cout << out_path + "/" + file_name.substr(0, file_name.find(".casci"))<<"\n";
            
            std::ofstream ofile (out_path + "/" + file_name.substr(0, file_name.find(".casci")));
            
            ofile << file;
        }
        else std::cout <<"Error -> Unknown parameter <"<<argv[1]<<"> found!!! please use -d and -e for decrypt and encrypt!\n", std::exit ( 3 );
    }
}
