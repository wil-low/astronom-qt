#include "forms/MainForm.h"
#include "utils/SettingsManager.h"
#include <QApplication>
#include <QSettings>
//#include <QCleanlooksStyle>

int main(int argc,char *argv[])
{
	// Make application
	QApplication app(argc, argv);
	//app.setStyle(new QCleanlooksStyle);
	QCoreApplication::setApplicationName("Astronom");
	QCoreApplication::setOrganizationName("S&W Axis");
	QSettings::setDefaultFormat(QSettings::IniFormat);
	SettingsManager::get_mutable_instance().init();
	MainForm form;
	form.showMaximized();
	// Run the application
	return app.exec();
}
