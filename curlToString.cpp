#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <curl/curl.h>

#include "prototypes.h"

using namespace std;


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


string pageString(string *pageUrl)
{
    cout<<"          ----------          "<<endl;

    char * tmpThisSiteUrl = new char [(pageUrl->length())+1];
    strcpy (tmpThisSiteUrl, pageUrl->c_str());

    CURL *curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();

    if(curl)
    {
    curl_easy_setopt(curl, CURLOPT_URL, tmpThisSiteUrl);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 2L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2L);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    const char *curl_easy_strerror(CURLcode errornum);

    cout<<readBuffer.substr(0,15)<<endl;
    cout<<"          >>>>>>>>>>          "<<endl;
    return readBuffer;
    }
  else return "failed to fetch site";

}

