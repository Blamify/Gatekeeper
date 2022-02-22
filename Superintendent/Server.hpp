#pragma once

#define WIN32_LEAN_AND_MEAN
#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <windows.h>
#include <httplib.h>
#include <openssl/err.h>
#include <winhttp.h>
#include <wincred.h>
#include <stdio.h>
#include <tchar.h>
#include <algorithm>
#include <bitset>
#include <limits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <map>

#define RC reinterpret_cast

using namespace std;
using namespace httplib;