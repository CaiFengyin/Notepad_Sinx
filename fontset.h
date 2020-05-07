#ifndef FONTSET_H
#define FONTSET_H

#include <QWidget>
#include <QFontDialog>
namespace Ui {
class FontSet;
}

class FontSet : public QWidget
{
    Q_OBJECT

public:
    explicit FontSet(QWidget *parent = nullptr);
    ~FontSet();

private:
    Ui::FontSet *ui;
    QFontDialog font;
};

#endif // FONTSET_H
