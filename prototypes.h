#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include <iostream>
#include <vector>
using namespace std;

vector<string> getLinks(string page,string siteToSearch);
string pageString(char pageUrl[1000]);
bool searchPageForKeyword(string page,string keyword);

#endif // PROTOTYPES_H_INCLUDED
