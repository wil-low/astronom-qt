#include "GlyphForm.h"
#include "ui_GlyphForm.h"

GlyphForm::GlyphForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GlyphForm)
{
    ui->setupUi(this);
	ui->tblGlyphs->setFont(QFont("Astronom", 16));
	ui->tblGlyphs->setRowCount(16);
	ui->tblGlyphs->setColumnCount(16);
	for (int r = 0; r < 16; ++r)
		ui->tblGlyphs->setRowHeight(r, 34);
	for (int c = 0; c < 16; ++c)
		ui->tblGlyphs->setColumnWidth(c, 34);
	for (int r = 0; r < 16; ++r) {
		for (int c = 0; c < 16; ++c) {
			QString s;
			s.sprintf("%c", r * 16 + c);
			QTableWidgetItem *item = new QTableWidgetItem(s);
			item->setTextAlignment(Qt::AlignCenter);
			ui->tblGlyphs->setItem(r, c, item);
		}
	}
}

GlyphForm::~GlyphForm()
{
    delete ui;
}

void GlyphForm::on_tblGlyphs_cellClicked(int row, int column)
{
	QString s;
	int cellNumber = 16 * row + column;
	s.sprintf("0x%X (%d)", cellNumber, cellNumber);
	ui->lblCharCode->setText(s);
}
