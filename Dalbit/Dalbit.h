#pragma once

#define BLOCKSIZE sizeof(double)
#define UNITSIZE sizeof(char)
#define POOLSIZE 8
#define GETVAR(T,I,V) *(T*)V[I*BLOCKSIZE*UNITSIZE]

#include <functional>

struct lua_State;


#include "../Lua53/lua.hpp"


namespace Dalbit
{
	void CallLuaFunction(lua_State* L, const char* func, const char* argSig, int resNum, ...);
	void StackDump(lua_State* L);


	class LuaCFunctionClosure
	{
	private:
		unsigned char varMemPool[BLOCKSIZE*UNITSIZE*POOLSIZE];
		std::function<int(lua_State*)> closureFunction;
	};
}