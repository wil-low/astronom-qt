#include "forms/MainForm.h"
#include <QApplication>
#include <QSettings>
#include <QCleanlooksStyle>

int main(int argc,char *argv[])
{
	// Make application
	QApplication app(argc, argv);
	app.setStyle(new QCleanlooksStyle);
	QCoreApplication::setApplicationName("Astronom");
	QCoreApplication::setOrganizationName("S&W Axis");
	QSettings::setDefaultFormat(QSettings::IniFormat);
	MainForm form;
	form.showMaximized();
	// Run the application
	return app.exec();
}
