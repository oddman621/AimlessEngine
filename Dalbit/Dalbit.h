#pragma once

class dalbit
{
private:
	struct lua_State* L;
public:
	dalbit();
	dalbit(const char* fileSrc);
	virtual ~dalbit();

public:
	const struct lua_State* GetState();

protected:
	void Error(bool resetLua, const char* errFmt, ...);
public:
	void CallLuaFunction(const char* func, const char* argSig, int resNum, ...);

#ifdef _DEBUG
public:
	void StackDump();
#endif
};