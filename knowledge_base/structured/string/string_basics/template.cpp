#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int main() {
    // C-style strings
    char cstr1[100] = "hello";
    char cstr2[100] = "world";
    char buffer[200];
    
    // strlen
    cout << "Length of cstr1: " << strlen(cstr1) << endl;
    
    // strcmp
    int cmp = strcmp(cstr1, cstr2);
    cout << "Comparison result: " << cmp << endl;
    
    // strcpy
    strcpy(buffer, cstr1);
    cout << "After strcpy: " << buffer << endl;
    
    // strcat
    strcat(buffer, " ");
    strcat(buffer, cstr2);
    cout << "After strcat: " << buffer << endl;
    
    // strstr
    char* sub = strstr(buffer, "world");
    if (sub) cout << "Found substring at position: " << (sub - buffer) << endl;
    
    // C++ strings
    string s1 = "competitive";
    string s2 = "programming";
    
    // Concatenation
    string s3 = s1 + " " + s2;
    cout << "C++ string: " << s3 << endl;
    
    // Substring
    string sub2 = s3.substr(0, 11);
    cout << "Substring: " << sub2 << endl;
    
    // Find
    size_t pos = s3.find("prog");
    if (pos != string::npos) cout << "Found at: " << pos << endl;
    
    return 0;
}