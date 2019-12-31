#pragma once

// C++�� Lua�� ���ε��� �����ϴ� ���̺귯��
// �� ���̺귯���� ���� �޼ҵ��� ��Ƹ� ���ε������� ����
// TODO: ��üȭ(�� ��ü�� ����ν��Ͻ��� ���� �� �����ϰ�, ��ƽ�ũ��Ʈ�� �ҷ��� ���� ���ε��� �ϰų�, ���ε��� �������ش�.)

#include "../Lua53/lua.hpp"

struct lua_State;

namespace Dalbit
{
	void CallLuaFunction(lua_State* L, const char* func, const char* argSig, int resNum, ...);
	void StackDump(lua_State* L);
}