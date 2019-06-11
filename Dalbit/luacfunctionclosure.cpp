#include "pch.h"
#include "framework.h"
#include "Dalbit.h"
#include "../Lua53/lua.hpp"
//#include <typeinfo>

lua_CFunction Dalbit::LuaCFunctionClosure::MakeClosure(const char* argSig, double(*fp)(void** vars))
{
	int luaReturnType = LUA_TNUMBER;

	closureFunction = [=](lua_State* L)->int
	{
		int argNum = 0;
		const char* argSigLocal = argSig;
		while (*argSigLocal && *argSigLocal != '\0')
		{
			switch (*argSigLocal++)
			{
			case 'n':
			case 'N':
				GETVAR(double, argNum, varMemPool) = lua_tonumber(L, argNum + 1);
				break;
			case 'b':
			case 'B':
				GETVAR(bool, argNum, varMemPool) = lua_toboolean(L, argNum + 1);
				break;
			case 's':
			case 'S':
				GETVAR(const char*, argNum, varMemPool) = lua_tostring(L, argNum + 1);
				break;
			}
			argNum += 1;
		}
		double* retVal = new double;
		*retVal = fp((void**)& varMemPool);
		switch (luaReturnType)
		{
		case LUA_TNUMBER:
			lua_pushnumber(L, *(double*)retVal);
			break;
		case LUA_TBOOLEAN:
			lua_pushboolean(L, *(bool*)retVal);
			break;
		case LUA_TSTRING:
			lua_pushstring(L, *(const char**)retVal);
			break;
		}
		delete retVal;

		return luaReturnType == LUA_TNONE ? 0 : 1;
	};

	return *closureFunction.target<int(*)(lua_State*)>();
}