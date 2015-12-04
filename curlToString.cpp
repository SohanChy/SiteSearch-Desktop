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


string pageString(char pageUrl[1000])
{
    /*ifstream t("testpage.html");
    string thisPage((istreambuf_iterator<char>(t)),istreambuf_iterator<char>());*/

  CURL *curl;
  CURLcode res;
  string readBuffer;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, pageUrl);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    //cout << readBuffer << endl;
    return readBuffer;
  }
  else return "failed to fetch site";

}

