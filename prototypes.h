#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include <iostream>
#include <vector>

using namespace std;



vector<string> getLinks(string *pageString,string siteToSearch,vector<string> *LinkDatabase);

string pageString(string *pageUrl);

string cleanUrl(string dirtyUrl);

bool checkIfVisited(vector<string> *linkDatabase, string link);

bool searchForKeyword(string &pageString,string &keyword);

void printVectorString(vector<string> *vectorString);

#endif // PROTOTYPES_H_INCLUDED
