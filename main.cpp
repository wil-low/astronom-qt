#include "forms/MainForm.h"
#include <QApplication>
#include <QSettings>

int main(int argc,char *argv[])
{
	// Make application
	QApplication app(argc, argv);
	QCoreApplication::setApplicationName("Astronom");
	QCoreApplication::setOrganizationName("S&W Axis");
	QSettings::setDefaultFormat(QSettings::IniFormat);
	MainForm form;
	form.show();
	// Run the application
	return app.exec();
}
