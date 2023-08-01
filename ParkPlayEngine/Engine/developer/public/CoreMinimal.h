#pragma once
#include <iostream>
#include <vector>
#include <string>

//#define allows for macros

//defining a macro, anything after the second space will replace the macro
	   //macro			   //compiler version

// cout/log a white message to the console
#define PP_MSG_LOG(cn, msg) std::cout << cn << " | " << msg << std::endl;

//cout a red message to the console using ANSI colours
// \033 is the "escape code" to do unique things in the console
										//red colour						//undo escape changes
#define PP_MSG_ERR(cn, msg) std::cout << "\033[31m" << cn << " | " << msg << "\033[0m" << std::endl;

// type define vector as a TArray and template the type name
// at compile time the compiler will replace "TArray" with std::vector<typename>
template <typename T>
using TArray = std::vector<T>;

// at compile time replace all instances of PPUint with unsigned int
typedef unsigned int PPUint;

//Simplified string
typedef std::string PPString;

enum EENGINETEX : PPUint {
	ETGrey50 = 0,		//0
	ETBlue,			//1
	ETRed,			//2
	ETGreen			//3
};
