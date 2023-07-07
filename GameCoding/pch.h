#pragma once

#include "Types.h"
#include "Defines.h"
#include "Enums.h"
#include "Utils.h"

#include <Windows.h>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

#include <format>

// 메모리 릭을 확인해준다
#define _CRTDEBG_MAP_ALLOC 
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
// 현재 실행되고 있는 파일이름, 몇번째줄인지 추적 가능
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
#endif
