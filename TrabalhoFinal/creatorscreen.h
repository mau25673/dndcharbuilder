#ifndef CREATORSCREEN_H
#define CREATORSCREEN_H

#include <QWidget>

namespace Ui {
class creatorScreen;
}

class creatorScreen : public QWidget
{
    Q_OBJECT

public:
    explicit creatorScreen(QWidget *parent = nullptr);
    ~creatorScreen();

private:
    Ui::creatorScreen *ui;
};

#endif // CREATORSCREEN_H
