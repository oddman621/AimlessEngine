#pragma once

// C++과 Lua간 바인딩을 지원하는 라이브러리
// 이 라이브러리가 직접 메소드들과 루아를 바인딩해주지 않음

#include "../Lua53/lua.hpp"

struct lua_State;

namespace Dalbit
{
	void CallLuaFunction(lua_State* L, const char* func, const char* argSig, int resNum, ...);
	void StackDump(lua_State* L);
}