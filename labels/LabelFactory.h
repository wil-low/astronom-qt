#ifndef LABELFACTORY_H
#define LABELFACTORY_H

class QWidget;
class BodyProps;
class AstroLabel;

class LabelFactory
{
public:
    LabelFactory();
	static AstroLabel* construct(QWidget* parent, int chart_id, const BodyProps& props);
};

#endif // LABELFACTORY_H
