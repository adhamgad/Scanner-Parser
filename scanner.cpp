//
//  main.cpp
//  Compilers1st
//
//  Created by Adham Gad on 5,11//15.
//  Copyright © 2015 example. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iterator>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;

fstream readFile();
string checkCharacterType();
bool isIdentifier(char c);
bool isNumber(char c);
bool isSymbol(char c);
bool isReservedWord(vector<char> buffer);
bool sameType(char a , char b) ;

void outputBuffer(vector<char> buffer);

int main(int argc, const char * argv[]) {
    
    fstream file = readFile();

    typedef istreambuf_iterator<char> iter;
    vector<char> buffer ;
    
    ofstream outputFile("scanner_output.txt");
    
    //for (iter i(file), end ; i != end  ; i++) {
    while (file.is_open()) {
        for (iter i(file), end ; i != end  ; i++) {
        char c = *i;
        char temp = '\0';
        
        if (buffer.size() > 0) {
            temp = buffer.back();
        }
        
        if (c == ' ' || c == '\n') {
            if (buffer.size() > 0) {
                for (int i = 0; i < buffer.size(); i++) {
                    outputFile << buffer[i];
                }
                outputFile << " " << "->" << " ";
                char lastChar = buffer.back();
                
                if (isNumber(lastChar) == true) {
                    outputFile << "number" << "\n" ;
                }else if (isSymbol(lastChar) == true){
                    outputFile << "Special Symbol" << "\n" ;
                    
                }else if (isIdentifier(lastChar) == true){
                    if (isReservedWord(buffer)) {
                        outputFile << "Reserved Word" << "\n" ;
                    }else{
                        outputFile << "Identifier" << "\n" ;
                    }
                }
                buffer.clear();
                //buffer.push_back(c);
            }
            continue;
        }
        
        if (sameType(c , temp) == true || buffer.size() == 0) {
            buffer.push_back(c);
        }else{
            for (int i = 0; i < buffer.size(); i++) {
                outputFile << buffer[i]  ;
            }
            outputFile << " " << "->" << " ";
            
            char lastChar = buffer.back();
            
            if (isNumber(lastChar) == true) {
                outputFile << "number" << "\n" ;
            }else if (isSymbol(lastChar) == true){
                
                outputFile << "Special Symbol" << "\n" ;

            }else if (isIdentifier(lastChar) == true){
                if (isReservedWord(buffer)) {
                    outputFile << "Reserved Word" << "\n" ;
                }else{
                    outputFile << "Identifier" << "\n" ;
                }
            }
            buffer.clear();
            buffer.push_back(c);
        }
      }
     
        //outputFile << c << " ";
    
    
    for (int i = 0; i < buffer.size(); i++) {
        outputFile << buffer[i];
    }
    outputFile << " " << "->" << " ";
    char lastChar = buffer.back();
    
    if (isNumber(lastChar) == true) {
        outputFile << "number" << "\n" ;
    }else if (isSymbol(lastChar) == true){
        outputFile << "Special Symbol" << "\n" ;

        
    }else if (isIdentifier(lastChar) == true){
        if (isReservedWord(buffer)) {
            outputFile << "Reserved Word" << "\n" ;
        }else{
            outputFile << "Identifier" << "\n" ;
        }
        
    }
    buffer.clear();
        file.close();
    }
    
    return 0;
}

//Methods

fstream readFile() {
    fstream file("tiny_sample_code.txt");

    return file;
}

bool isNumber(char c){

    if (isdigit(c) == true) {
        return true;
    }
    return false;
}

bool isIdentifier(char c ) {
    
    if (isalpha(c) == true) {
        return true;
    }
    
    return false ;
}

bool isSymbol(char c) {
    vector<char> symbols = { '+', '-' , '*' , '/' , '=' , '<' , '(', ')', ';', ':' , '}' , '{' } ;
//    char symbols[] = ;
    for (int i = 0; i < symbols.size() ; i ++) {
        char temp = symbols[i];
        if (c == temp) {
            return true;
        }
    }
    
    return false;

}

bool sameType(char a , char b) {
    if ( (isNumber(a) && isNumber(b)) == true || (isIdentifier(a) && isIdentifier(b)) == true || ( isSymbol(a) && isSymbol(b)) == true ) {
        return true;
    }else{
        return false;
    }
    
}

bool isReservedWord(vector<char> buffer){
    string str(buffer.begin(),buffer.end());
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    vector<string> reservedWords = { "if", "then" , "else" ,"end" , "repeat" , "until" , "read" , "write" } ;
    //string reservedWords[8] =
    for (int i = 0; i < reservedWords.size(); i++) {
        string temp = reservedWords[i];
        if (str == temp) {
            return true;
        }
    }
    return false;
}


