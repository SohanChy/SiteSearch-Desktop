#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include <iostream>
#include <vector>

using namespace std;



vector<string> getLinks(string *pageString,string siteToSearch);
string pageString(char pageUrl[1000]);
bool searchPageStringForKeyword(string *pageString,string keyword);
void printVectorString(vector<string> *vectorString);

#endif // PROTOTYPES_H_INCLUDED
