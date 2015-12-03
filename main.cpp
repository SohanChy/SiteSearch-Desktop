#include <iostream>
#include <vector>
#include <string>
#include "prototypes.h"

using namespace std;

int main()
{
    string site="172.27.27.246";

    vector<string> siteLinks = getLinks(pageString(),site);

    for(vector<string>::const_iterator i = siteLinks.begin(); i != siteLinks.end(); i++)
        {
        cout<<*i<<endl;
        }

    return 0;
}
