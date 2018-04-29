#ifndef _SLM_H_
#define _SLM_H_

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;

#include "slm_data.h"
#include "slm_serialization.h"

#define MAX_LEN_KEY			128
#define MAX_LEN_VALUE		256
#define MAX_LEN_FILENAME	32

#endif // _SLM_H_