//******************************************************************
//
// Author: David Tullis (4/3/2021)
//
// Notes: This program will create a Tuple, no matter what's inside it,  
//        and attempt to add all that is numeric to a global variable, 
//        and cast all that is string-castable to a global variable.
//        Whatever is not accepted will be counted. The end result 
//        will be printed out by main().
// 
//        This program was built and tested with C++17.      
//
//******************************************************************


#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>


using namespace std;

/**
* These are the global variables.
* 'calc' handles all numeric values, 'wordList' handles all that can be cast to a string,
* and 'count' is the total number of unaccepted values.
********************************************************************/
string wordList;
double calc = 0;
double count = 0;




/**
* Each specialized template accepts a given type of variable.
* If it's numeric or castable to a string it will be handled accordingly.
* If it is an unaccepted value, it will go the default template and 
* increment the 'count'.
********************************************************************/
template <typename T>
void solve(T value){
    // cout << "Error: An unsupported variable type has been received." << endl;
    count += 1;
}

template <>
void solve<unsigned int>(unsigned int value){
    calc += value;
}

template <>
void solve<signed int>(signed int value){
    calc += value;
}

template <>
void solve<unsigned long int>(unsigned long int value){
    calc += value;
}

template <>
void solve<signed long int>(signed long int value){
    calc += value;
}

template <>
void solve<unsigned short int>(unsigned short int value){
    calc += value;
}

template <>
void solve<signed short int>(signed short int value){
    calc += value;
}

template <>
void solve<unsigned long long int>(unsigned long long int value){
    calc += value;
}

template <>
void solve<signed long long int>(signed long long int value){
    calc += value;
}

template <>
void solve<double>(double value){
    calc += value;
}

template <>
void solve<long double>(long double value){
    calc += value;
}

template <>
void solve<float>(float value){
    calc += value;
}

template <>
void solve<string>(string value){
    wordList += value;
}

template <>
void solve<char*>(char * value){
    wordList += value;
}

template <>
void solve<const char*>(const char * value){
    wordList += value;
}

template <>
void solve<signed char>(signed char value){
    wordList += value;
}

template <>
void solve<unsigned char>(unsigned char value){
    wordList += value;
}

template <>
void solve<char>(char value){
    wordList += value;
}


/**
* computation() creates an incrementable value. After each run through
* the function, it increments 'I' and recursively calls itself.
* When 'I' reaches the sizeof the Tuple (Ts), the flow of logic
* transfers to the secondary computation() function that has 'I'
* at the max size already. There the flow of logic releases and returns
* to the main() function.
********************************************************************/
template<size_t I = 0, typename... Ts>
inline typename enable_if<I == sizeof...(Ts), void>::type
  computation(tuple<Ts...>& tuple) { }

template<size_t I = 0, typename... Ts>
inline typename enable_if<I < sizeof...(Ts), void>::type
  computation(tuple<Ts...>& tuple) {
      
    //calls the template specialized solve() functions  
    solve(get<I>(tuple));
    //recursively calls itself and increments 'I'
    computation<I + 1, Ts...>(tuple);
    
  }



/**
* The driver. It creates the tuple and sends it to computation(tuple).
* It also outputs the end result of the global variables.
********************************************************************/
int main() {   
    using Tuple = tuple<const int, long double, const char, float, string, int, const char*, bool>;
    Tuple t{5, 0.2, 'c' , 46.f, "Where's the ", -10, " cat.", false};
    computation(t); 
    cout << calc << ", " << wordList << ", " << count << endl;
	return 0;
}
