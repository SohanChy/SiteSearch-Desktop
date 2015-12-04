#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>

#include "prototypes.h"

using namespace std;

bool checkIfVisited(vector<string> *linkDatabase, string link)
{
        for(vector<string>::const_iterator i = linkDatabase->begin(); i != linkDatabase->end(); i++)
        {
            string tmpLink = *i;
            if(tmpLink == link)
                {
                    return true;
                }
        }
        return false;
}

void printVectorString(vector<string> *vectorString) {

    for(vector<string>::const_iterator i = vectorString->begin(); i != vectorString->end(); i++)
        {
        cout<<*i<<endl;
        }
}

int main()
{
    freopen("output.txt","w",stdout);

    char siteUrl[1000]="http://103.3.226.207";
    string keyword = "Sohan";

    string siteAsString = pageString(siteUrl);
    vector<string> siteLinks = getLinks(&siteAsString,siteUrl);


    vector<string> visitedLinks;

    printVectorString(&siteLinks);


    for(vector<string>::const_iterator i = siteLinks.begin(); i != siteLinks.end(); i++)
        {
            if(checkIfVisited(&visitedLinks, *i) == false)
                {
                char * tmpThisSiteUrl = new char [(i->length())+1];
                strcpy (tmpThisSiteUrl, i->c_str());
                cout<<"Fetching url "<<tmpThisSiteUrl<<" @@@"<<endl;

                string tmpSiteHtml = pageString(tmpThisSiteUrl);


                vector<string> thisPagesLinks = getLinks(&tmpSiteHtml,siteUrl);
                visitedLinks.push_back(*i);

                cout<<"---------------------------------"<<endl;
                printVectorString(&thisPagesLinks);
                cout<<"---------------------------------"<<endl;
                }
        }



    if(searchPageStringForKeyword(&siteAsString,keyword))
    {
        cout<<endl<<"FOUND"<<endl;
    }
    else
    {
        cout<<endl<<"NOT FOUND"<<endl;
    }



    return 0;
}
