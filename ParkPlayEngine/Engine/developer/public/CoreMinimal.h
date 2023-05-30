#pragma once
#include <iostream>
using namespace std;

//#define allows for macros

//defining a macro, anything after the second space will replace the macro
	   //macro			   //compiler version

// cout/log a white message to the console
#define PP_MSG_LOG(cn, msg) cout << cn << " | " << msg << endl;

//cout a red message to the console using ANSI colours
// \033 is the "escape code" to do unique things in the console
										//red colour						//undo escape changes
#define PP_MSG_ERR(cn, msg) cout << "\033[31m" << cn << " | " << msg << "\033[0m" << endl;

