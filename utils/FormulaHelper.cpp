#include "FormulaHelper.h"
#include <QDebug>

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

FormulaHelper::FormulaHelper()
{
	luaState_ = lua_open();
	luaopen_base(luaState_);
	luaopen_math(luaState_);
}

FormulaHelper::~FormulaHelper()
{
	lua_close(luaState_);
}

QString FormulaHelper::evaluate (const QString& str)
{
	QString result;
	result = "__result__=(" + str + ")";
	int error = luaL_dostring(luaState_, result.toAscii().data());
	if (error) {
		result = "Lua error: ";
		result += lua_tostring(luaState_, -1);
		lua_pop(luaState_, 1);
	}
	else {
		lua_getglobal(luaState_, "__result__");
		result = lua_tostring(luaState_, -1);
		lua_pop(luaState_, 1);
	}
	return result;
}

void FormulaHelper::setVariable (const QString& name, double val)
{
	lua_pushnumber(luaState_, val);
	lua_setglobal(luaState_, name.toAscii().data());
}
