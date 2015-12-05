#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <algorithm>

#include "prototypes.h"

using namespace std;


//code from SO, not mine.
//Understand this later
// templated version of my_equal so it could work with both char and wchar_t
template<typename charT>
struct my_equal {
    my_equal( const std::locale& loc ) : loc_(loc) {}
    bool operator()(charT ch1, charT ch2) {
        return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
    }
private:
    const std::locale& loc_;
};

// find substring (case insensitive)
template<typename T>
int ci_find_substr( const T& str1, const T& str2, const std::locale& loc = std::locale() )
{
    typename T::const_iterator it = std::search( str1.begin(), str1.end(),
        str2.begin(), str2.end(), my_equal<typename T::value_type>(loc) );
    if ( it != str1.end() ) return it - str1.begin();
    else return -1; // not found
}

//end of code from SO


string cleanUrl(string dirtyUrl)
{
            if(dirtyUrl.substr(0,7)== "http://")
            {
                dirtyUrl = dirtyUrl.substr(7,dirtyUrl.length()-7);
            }
            else if(dirtyUrl.substr(0,8)== "https://")
            {
                dirtyUrl = dirtyUrl.substr(8,dirtyUrl.length()-8);
            }

            if(dirtyUrl[dirtyUrl.length()-1]== '/')
            {
                dirtyUrl = dirtyUrl.substr(0,dirtyUrl.length()-1);
            }

            while(dirtyUrl.find("//") != string::npos)
            {
                dirtyUrl.erase(dirtyUrl.find("//"),1);
            }

    return dirtyUrl;
}

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

//extract links from a string containing html
vector<string> getLinks(string *pageString,string siteToSearch,vector<string> *LinkDatabase)
{
    const string aTagBegin("<a ");  //the beginning tag of a link
    const string aTagEnd("\"");     //the end of a link
    const string hrefEquals(" href=\"");

    vector<string> links;           //a vector of string to store the links
    size_t posBegin = 0;            //where to begin the position
    size_t posEnd = 0;              //where to end
    size_t found = pageString->find(aTagBegin);     //store the position of the first occurance of aTagBegin

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
                //cout<<endl<<"I am in here "<<tmpUrlHolder<<endl;
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

        //cout<<"OG: "<<tmpUrlHolder<<endl;
        tmpUrlHolder = cleanUrl(tmpUrlHolder);
        //cout<<"CL: "<<tmpUrlHolder<<endl;
        if(checkIfVisited(LinkDatabase,tmpUrlHolder) != true)
        {
        links.push_back(tmpUrlHolder);
        }
        else cout<<"NOT AGAIN!"<<endl;

        posBegin = posEnd;

    }
    while(pageString->find(aTagBegin,posBegin)!=string::npos);

    return links;
}

bool searchForKeyword(string &pageString,string &keyword)
{
    if(ci_find_substr(pageString,keyword) != -1)
    {
        return true;
    }

    return false;
}
