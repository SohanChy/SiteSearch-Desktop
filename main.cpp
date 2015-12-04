#include <iostream>
#include <vector>
#include <string>
#include "prototypes.h"

using namespace std;

void printVectorString(vector<string> *vectorString) {

    for(vector<string>::const_iterator i = vectorString->begin(); i != vectorString->end(); i++)
        {
        cout<<*i<<endl;
        }
}

int main()
{
    char siteUrl[1000]="google.com";

    vector<string> siteLinks = getLinks(pageString(siteUrl),siteUrl);

    printVectorString(&siteLinks);



    return 0;
}
