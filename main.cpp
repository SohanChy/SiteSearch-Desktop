#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>

#include "prototypes.h"

using namespace std;




void printVectorString(vector<string> *vectorString) {

    cout<<"----printing vector string----"<<endl;
    for(vector<string>::const_iterator i = vectorString->begin(); i != vectorString->end(); i++)
        {
        cout<<*i<<endl;
        }
    cout<<"----end of vector string----"<<endl;
}

int main()
{
    //freopen("output.txt","w",stdout);

    cout<<"Please enter website address: (eg: www.cplusplus.com)"<<endl;
    string siteUrl="";
    getline(cin,siteUrl);
    siteUrl = cleanUrl(siteUrl);

    cout<<"Enter keyword to search: (eg: array)"<<endl;
    string keyword = "";
    getline(cin,keyword);

    vector<string> visitedLinks;    //store visited links here
    visitedLinks.push_back(siteUrl);

    string siteAsString = pageString(&siteUrl);
    vector<string> linksToVisit = getLinks(&siteAsString,siteUrl,&visitedLinks);

    //printVectorString(&linksToVisit);

    while(linksToVisit.empty() != true)
    {
        cout<<"****Links To Visit: "<<linksToVisit.size()<<"****"<<endl;
        //printVectorString(&linksToVisit);
        cout<<"****VISITED LINKS: "<<visitedLinks.size()<<"****"<<endl;
        //printVectorString(&visitedLinks);

        if(checkIfVisited(&visitedLinks,linksToVisit.front()) != true)
        {
            cout<<"####Visiting: "<<linksToVisit.front()<<"####"<<endl;

            string tmpSiteHtml = pageString(&linksToVisit.front());

            if(searchForKeyword(tmpSiteHtml,keyword))
            {
                cout<<"----- FOUND!!! -----"<<endl
                <<"Url: "<<linksToVisit.front()<<endl;
                break;
            }

            vector<string> tmpExtractedLinks = getLinks(&tmpSiteHtml,linksToVisit.front(),&linksToVisit);

            cout<<"****EXTRACTED LINKS: "<<tmpExtractedLinks.size()<<"****"<<endl;
            //printVectorString(&tmpExtractedLinks);

            visitedLinks.push_back(linksToVisit.front());
            linksToVisit.erase(linksToVisit.begin());

            linksToVisit.insert(linksToVisit.end(),tmpExtractedLinks.begin(),tmpExtractedLinks.end());
        }
        else
        {
            linksToVisit.erase(linksToVisit.begin());

        }
    }



    return 0;
}
