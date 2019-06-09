﻿// Dalbit.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "Dalbit.h"
#include "../Lua53/lua.hpp"


using namespace std;

dalbit::dalbit()
{
	L = luaL_newstate();
	luaL_openlibs(L);
}

dalbit::~dalbit()
{
	lua_close(L);
}
