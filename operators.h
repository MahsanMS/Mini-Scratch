// Operators
#ifndef OPERATORS_H
#define OPERATORS_H

#include <iostream>
#include <string>
#include <cmath>

//==================================
//Mathematical Operators:

//Addition
float sum(float a, float b) { return a+b; }

//Subtraction
float subtract(float a, float b) { return a-b; }

//Multiplication
float multiply(float a, float b) { return a*b; }

//Division
float divide(float a, float b) {
    if(b==0) { std::cout<<"Error: Division by zero!\n"; return 0; }
    return a/b;
}

//Remainder
float remainder(float a, float b) {
    if(b==0) { std::cout<<"Error: Cannot calculate remainder with zero divisor!\n"; return 0; }
    return std::fmod(a,b);
}

//Absolute value
float absolute(float a) {
    if(a>=0) return a;
    else return -a;
}

//Square root
float square_root(float a) {
    if(a<0) { std::cout<<"Error: Cannot calculate square root of negative number!\n"; return 0; }
    return std::sqrt(a);
}

//Floor
float floor(float a) { return std::floor(a); }

//Ceil
float ceil(float a) { return std::ceil(a); }

//Sine (input in degrees)
float sin(float d) {
    float radian = d*3.14159265f/180.0f;
    return std::sin(radian);
}

//Cosine (input in degrees)
float cos(float d) {
    float radian = d*3.14159265f/180.0f;
    return std::cos(radian);
}

//==================================
//Comparison Operators:

//Less than
bool less_than(float a, float b) { return a<b; }

//Greater than
bool greater_than(float a, float b) { return a>b; }

//Equal
bool equal(float a, float b) { return a==b; }

//Less than or equal
bool less_or_equal(float a, float b) { return a<=b; }

//Greater than or equal
bool greater_or_equal(float a, float b) { return a>=b; }

//==================================
//Logical Operators:

//AND
bool logical_and(bool a, bool b) { return a&&b; }

//OR
bool logical_or(bool a, bool b) { return a||b; }

//NOT
bool logical_not(bool a) { return !a; }

//XOR
bool logical_xor(bool a, bool b) { return a^b; }

//==================================
//String Operators:

//Length of string
int length_of_string(const std::string& str) { return str.length(); }

//Nth character of string
char nth_of_string(const std::string& str, int n) {
    if(n<1||n>str.length()) { return '\0'; }
    return str[n-1];
}

//Merge strings
std::string merge_two_strings(const std::string& str1, const std::string& str2) {
    return str1+str2;
}

#endif