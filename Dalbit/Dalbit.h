#pragma once

class dalbit
{
private:
	class lua_State* L;
public:
	void StackDump();
};