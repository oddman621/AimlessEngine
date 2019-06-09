#pragma once

class dalbit
{
private:
	struct lua_State* L;
public:
	dalbit();
	virtual ~dalbit();

public:
	void StackDump();
};