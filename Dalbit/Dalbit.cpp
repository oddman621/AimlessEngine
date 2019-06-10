// Dalbit.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "Dalbit.h"
#include "../Lua53/lua.hpp"

#include <iostream>

int l_err(lua_State* L)
{
	fprintf(stderr, "[lua:%s] %s\n", lua_tostring(L, 0), lua_tostring(L, 1)); // Last Error
	return 0;
}

void Dalbit::CallLuaFunction(lua_State* L, const char* func, const char* argSig, int resNum, ...)
{
	va_list vl;
	int argNum = 0;
	int errFunc = 0;
	auto LuaLCheckStack = [L]() {luaL_checkstack(L, 1, "CallLuaFunction:StackNotEnough"); };

	va_start(vl, resNum);

	LuaLCheckStack();
	lua_getglobal(L, func);
	errFunc = lua_gettop(L);

	LuaLCheckStack();
	lua_pushcfunction(L, l_err);
	lua_insert(L, errFunc);

	while (*argSig != '\0')
	{
		LuaLCheckStack();
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

	lua_pcall(L, argNum, resNum, errFunc);
	

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
			*va_arg(vl, const char**) = lua_tostring(L, -i);
			break;
		}
	}

	lua_pop(L, resNum+1/*errFunc*/);
	va_end(vl);
}

void Dalbit::StackDump(lua_State* L)
{
	int top = lua_gettop(L);

	std::cout << std::endl << "(ADDR:" << L << ") TOP = " << top << std::endl;

	for (int i = 0; i <= top; i++)
	{
		std::cout << "STACK " << i << " : ";

		switch (lua_type(L, i))
		{
		case LUA_TNUMBER:
			std::cout << "(NUM) " << lua_tonumber(L, i);
			break;
		case LUA_TBOOLEAN:
			std::cout << "(BOL) " << lua_toboolean(L, i);
			break;
		case LUA_TSTRING:
			std::cout << "(STR) " << lua_tostring(L, i);
			break;
		case LUA_TNIL:
			std::cout << "(NIL)";
			break;
		case LUA_TNONE:
			std::cout << "(NON)";
			break;
		case LUA_TTHREAD:
			std::cout << "(TRD)";
			break;
		case LUA_TFUNCTION:
			std::cout << "(FUN)";
			break;
		case LUA_TTABLE:
			std::cout << "(TBL)";
			break;
		case LUA_TUSERDATA:
			std::cout << "(DAT)";
			break;
		case LUA_TLIGHTUSERDATA:
			std::cout << "(LDT)";
			break;
		default:
			std::cout << "(" << lua_typename(L, i) << ")";
			break;
		}

		std::cout << std::endl;
	}
	std::cout << std::endl;
}