#pragma once

// C++와 Lua간 바인딩을 지원하는 라이브러리
// 이 라이브러리가 직접 메소드들과 루아를 바인딩해주지 않음
// TODO: 객체화(각 객체가 루아인스턴스를 생성 및 관리하고, 루아스크립트를 불러와 직접 바인딩을 하거나, 바인딩을 제공해준다.)

#include "../Lua53/lua.hpp"

struct lua_State;

namespace Dalbit
{
	void CallLuaFunction(lua_State* L, const char* func, const char* argSig, int resNum, ...);
	void StackDump(lua_State* L);
}