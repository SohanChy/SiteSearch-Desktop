#include <iostream>
#include <string>
#include <vector>
#include "prototypes.h"

using namespace std;

vector<string> getLinks(string page,string siteToSearch)
{
    const string aTagBegin("<a");
    const string aTagEnd("\">");
    const string hrefEquals("href=\"");

    vector<string> links;
    size_t posBegin = 0;
    size_t posEnd = 0;
    size_t found = page.find(aTagBegin);

    do
    {
        found     = page.find(aTagBegin,posBegin);
        posBegin  = found;
        //cout<<"posBegin1:"<<posBegin<<"--"<<posEnd<<endl;

        found     = page.find(hrefEquals,posBegin);
        if(found!=string::npos)
            {
            posBegin  = found + hrefEquals.length();
            }
            else
            {
                posBegin++;
                continue;
            }

        //cout<<"posBegin2:"<<posBegin<<"--"<<posEnd<<endl;

        posEnd    = page.find(aTagEnd,posBegin);
            string tmpUrlHolder = page.substr(posBegin,posEnd-posBegin);
            if(tmpUrlHolder.find("http://")!= string::npos)
            {
                tmpUrlHolder = tmpUrlHolder.substr(7,tmpUrlHolder.length()-7);
                if(tmpUrlHolder.find(siteToSearch) == string::npos)
                {
                    posBegin++;
                    continue;
                }
            }
        links.push_back(tmpUrlHolder);

        posBegin = posEnd;

    }
    while(page.find(aTagBegin,posBegin)!=string::npos);

    return links;
}
