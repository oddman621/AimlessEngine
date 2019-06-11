#pragma once

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
	public:
		static const int BLOCKSIZE = sizeof(double);
		static const int UNITSIZE = sizeof(char);
		static const int POOLSIZE = 8;

	private:
		unsigned char varMemPool[BLOCKSIZE*UNITSIZE*POOLSIZE];
		std::function<int(lua_State*)> closureFunction;

	public:
		lua_CFunction MakeClosure(const char* argSig, double(*fp)(void** vars));
	};
}