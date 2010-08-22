#include "GlyphForm.h"
#include "ui_GlyphForm.h"

GlyphForm::GlyphForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlyphForm)
{
    ui->setupUi(this);
	ui->tableWidget->setFont(QFont("Astronom", 16));
	ui->tableWidget->setRowCount(16);
	ui->tableWidget->setColumnCount(16);
	for (int r = 0; r < 16; ++r)
		ui->tableWidget->setRowHeight(r, 34);
	for (int c = 0; c < 16; ++c)
		ui->tableWidget->setColumnWidth(c, 34);
	for (int r = 0; r < 16; ++r) {
		for (int c = 0; c < 16; ++c) {
			QString s;
			s.sprintf("%c", r * 16 + c);
			QTableWidgetItem *item = new QTableWidgetItem(s);
			item->setTextAlignment(Qt::AlignCenter);
			ui->tableWidget->setItem(r, c, item);
		}
	}
}

GlyphForm::~GlyphForm()
{
    delete ui;
}
