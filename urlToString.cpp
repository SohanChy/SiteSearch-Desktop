#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include "prototypes.h"

using namespace std;

string pageString()
{
    ifstream t("testpage.html");
    string thisPage((istreambuf_iterator<char>(t)),istreambuf_iterator<char>());

    return thisPage;
}

