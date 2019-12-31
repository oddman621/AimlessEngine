// Dalbit.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "dalbit/Dalbit.h"
#include "../include/lua/lua.hpp"

#include <iostream>




int l_err(lua_State* L)
{
	fprintf(stderr, "[lua:%s] %s\n", lua_tostring(L, 0), lua_tostring(L, 1)); // Last Error
	return 0;
}

// (루아인스턴스, 루아함수이름, 매개변수타입들, 리턴갯수, [루아함수 인자...], [리턴 인자...포인터에 의해 대입됨])
// 이걸 직접 쓰기보단, 백엔드측에서 어떤 루아함수를 C함수에 바인딩할 때 쓰는 용도가 더 알맞을 것이다.
/*
	예를 들어: string, number, bool을 매개변수로 하고 bool, number를 반환하는 myluafunc이라는 루아함수를 호출할 때,
	
	lua_State* L;
	bool ret1;
	double ret2;
	Dalbit::CallLuaFunction(L, "myluafunc", "snb", 2, "mystring", 123.456, false, &ret1, &ret2);
*/
void Dalbit::CallLuaFunction(lua_State* L, const char* func, const char* argSig, int resNum, ...)
{
	va_list vl;
	int argNum = 0;
	int errFunc = 0;
	const char* stackNotEnoughMsg = "CallLuaFunction:StackNotEnough";

	va_start(vl, resNum);

	//스택 체크 후 루아 함수이름 삽입
	luaL_checkstack(L, 1, stackNotEnoughMsg);
	lua_getglobal(L, func);
	errFunc = lua_gettop(L);

	//스택 체크 후 에러 출력시킬 cfunction 삽입
	luaL_checkstack(L, 1, stackNotEnoughMsg);
	lua_pushcfunction(L, l_err);
	lua_insert(L, errFunc);

	//스택 체크하며 argSig에 맞춰 가변인자 차례대로 스택추가
	while (*argSig != '\0')
	{
		luaL_checkstack(L, 1, stackNotEnoughMsg);
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

	//스택을 이용해 루아함수 실행
	lua_pcall(L, argNum, resNum, errFunc);
	

	//resNum에 맞춰 가변인자에 대입(참조를 이용)
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

	lua_pop(L, resNum+1);
	va_end(vl);
}

// TODO: switch-case 문을 Map 또는 HashMap으로 변경(가독성 UP)

void Dalbit::StackDump(lua_State* L)
{
	class LuaStackName {
	private:
		const char* list[LUA_NUMTAGS + 1] = {
			list[LUA_TNONE + 1] = "NON",
			list[LUA_TNIL + 1] = "NIL",
			list[LUA_TBOOLEAN + 1] = "BOL",
			list[LUA_TLIGHTUSERDATA + 1] = "LUR",
			list[LUA_TNUMBER + 1] = "NUM",
			list[LUA_TTABLE + 1] = "TAB",
			list[LUA_TSTRING + 1] = "STR",
			list[LUA_TFUNCTION + 1] = "FUN",
			list[LUA_TUSERDATA + 1] = "USR",
			list[LUA_TTHREAD + 1] = "THD",
		};

	public:
		const char* operator[](int i) const
		{
			//i가 올바른 숫자범위일 경우 list[i+1], 아닐 경우 "ERR"
			return (i >= 0 && i <= LUA_NUMTAGS) ? list[i + 1] : "ERR";
		}
	} static const stackName;

	int top = lua_gettop(L);

	std::cout << std::endl << "(ADDR:" << L << ") TOP = " << top << std::endl;

	for (int i = 0; i <= top; i++)
	{
		std::cout << "STACK " << i << " : (" << stackName[lua_type(L, i)] << ") ";

		switch (lua_type(L, i))
		{
		case LUA_TNUMBER:
			std::cout << lua_tonumber(L, i);
			break;
		case LUA_TBOOLEAN:
			std::cout << lua_toboolean(L, i);
			break;
		case LUA_TSTRING:
			std::cout << lua_tostring(L, i);
			break;
		}

		std::cout << std::endl;
	}
	std::cout << std::endl;
}