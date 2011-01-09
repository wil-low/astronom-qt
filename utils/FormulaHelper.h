#ifndef FORMULAHELPER_H
#define FORMULAHELPER_H
#include <QString>
struct lua_State;

class FormulaHelper
{
public:
    FormulaHelper();
	~FormulaHelper();
	void setVariable (const QString& name, double val);
	QString evaluate (const QString& str);

private:
	lua_State* luaState_;
};

#endif // FORMULAHELPER_H
