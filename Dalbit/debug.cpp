#include "pch.h"
#include "framework.h"
#include "Dalbit.h"
#include "../Lua53/lua.hpp"

#include <iostream>

void dalbit::StackDump()
{
	int top = lua_gettop(L);

	for (int i = 0; i < top; i++)
	{
		std::cout << i << " ";

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
		default:
			std::cout << "(" << lua_typename(L, i) << ")";
			break;
		}

		std::cout << std::endl;
	}
}