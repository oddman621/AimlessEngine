#pragma once

struct lua_State;


#include "../Lua53/lua.hpp"


namespace Dalbit
{
	void CallLuaFunction(lua_State* L, const char* func, const char* argSig, int resNum, ...);
	void StackDump(lua_State* L);
}