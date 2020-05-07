#include "fontset.h"
#include "ui_fontset.h"

FontSet::FontSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FontSet)
{
    ui->setupUi(this);
    setWindowTitle("字体设置");
    setWindowModified(false);
    font.setVisible(true);
}

FontSet::~FontSet()
{
    delete ui;
}
