#include <iostream>
#include <string>
#include <vector>
#include "prototypes.h"

using namespace std;

vector<string> getLinks(string *pageString,string siteToSearch)
{
    const string aTagBegin("<a ");
    const string aTagEnd("\"");
    const string hrefEquals(" href=\"");

    vector<string> links;
    size_t posBegin = 0;
    size_t posEnd = 0;
    size_t found = pageString->find(aTagBegin);

    do
    {
        found     = pageString->find(aTagBegin,posBegin);
        posBegin  = found;
        //cout<<"posBegin1:"<<posBegin<<"--"<<posEnd<<endl;

        found     = pageString->find(hrefEquals,posBegin);
        if(found!=string::npos)
            {
            posBegin  = found + hrefEquals.length();
            }
            else
            {
                posBegin = posBegin+5;
                continue;
            }

        //cout<<"posBegin2:"<<posBegin<<"--"<<posEnd<<endl;

        posEnd    = pageString->find(aTagEnd,posBegin);

            string tmpUrlHolder = pageString->substr(posBegin,posEnd-posBegin);

            if(tmpUrlHolder.substr(0,7)== "http://")
            {
                tmpUrlHolder = tmpUrlHolder.substr(7,tmpUrlHolder.length()-7);
                if(tmpUrlHolder.find(siteToSearch) == string::npos)
                {
                    posBegin++;
                    continue;
                }
            }
            else if(tmpUrlHolder.substr(0,8)== "https://")
            {
                tmpUrlHolder = tmpUrlHolder.substr(8,tmpUrlHolder.length()-8);
                if(tmpUrlHolder.find(siteToSearch) == string::npos)
                {
                    posBegin++;
                    continue;
                }
            }
            else if(tmpUrlHolder.substr(0,1)== "/")
            {
                tmpUrlHolder.insert(0,siteToSearch);
            }
            else
            {
                cout<<endl<<"I am in here "<<tmpUrlHolder<<endl;
                tmpUrlHolder.insert(0,siteToSearch+"/");
            }



        if(tmpUrlHolder[tmpUrlHolder.length()-4] == '.')
        {
            string extension = tmpUrlHolder.substr(tmpUrlHolder.length()-3,tmpUrlHolder.length());

            if(extension!="htm" && extension!="php" && extension!="asp")
            {
                posBegin++;
                continue;
            }

        }


        links.push_back(tmpUrlHolder);

        posBegin = posEnd;

    }
    while(pageString->find(aTagBegin,posBegin)!=string::npos);

    return links;
}

bool searchPageStringForKeyword(string *pageString,string keyword)
{
    if(pageString->find(keyword) != string::npos)
    {
        return true;
    }

    return false;
}
