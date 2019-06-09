// Dalbit.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "Dalbit.h"
#include "../Lua53/lua.hpp"

const lua_State* dalbit::GetState()
{
	return L;
}

dalbit::dalbit()
{
	L = luaL_newstate();
	luaL_openlibs(L);
}

dalbit::dalbit(const char* fileSrc) : dalbit()
{
	luaL_dofile(L, fileSrc);
}

dalbit::~dalbit()
{
	lua_close(L);
}

void dalbit::CallLuaFunction(const char* func, const char* argSig, int resNum, ...)
{
	va_list vl;
	int argNum = 0;
	auto LuaStackCheck = [this](int addedStackNum)->bool {
		if (lua_checkstack(L, 1) == false)
		{
			Error(false, "CallLuaFunction: Stack is full!");
			lua_pop(L, addedStackNum);
			return false;
		}
		return true;
	};

	va_start(vl, resNum);

	if (LuaStackCheck(0) == false) return;

	lua_getglobal(L, func);

	while (*argSig != '\0')
	{
		if (LuaStackCheck(argNum + 1) == false) return;

		switch (*argSig++)
		{
		case 'n':
		case 'N':
			lua_pushnumber(L, va_arg(vl, double));
			break;
		case 'b':
		case 'B':
			lua_pushboolean(L, va_arg(vl, bool));
			break;
		case 's':
		case 'S':
			lua_pushstring(L, va_arg(vl, char*));
			break;
		}
		argNum += 1;
	}

	lua_pcall(L, argNum, resNum, 0);
	

	for (int i = resNum; i > 0; i--)
	{
		switch (lua_type(L, -i))
		{
		case LUA_TNUMBER:
			*va_arg(vl, double*) = lua_tonumber(L, -i);
			break;
		case LUA_TBOOLEAN:
			*va_arg(vl, bool*) = lua_toboolean(L, -i);
			break;
		case LUA_TSTRING:
			va_arg(vl, const char*) = lua_tostring(L, -i);
			break;
		}
	}

	lua_pop(L, resNum);
	va_end(vl);
}
