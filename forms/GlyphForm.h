#ifndef GLYPHFORM_H
#define GLYPHFORM_H

#include <QDialog>

namespace Ui {
    class GlyphForm;
}

class GlyphForm : public QDialog
{
    Q_OBJECT

public:
    explicit GlyphForm(QWidget *parent = 0);
    ~GlyphForm();

private:
    Ui::GlyphForm *ui;

private slots:
	void on_tblGlyphs_cellClicked(int row, int column);
};

#endif // GLYPHFORM_H
