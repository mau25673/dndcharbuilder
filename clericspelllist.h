#ifndef CLERICSPELLLIST_H
#define CLERICSPELLLIST_H
#include <QWidget>
#include <vector>
#include <string>

using namespace std;

namespace Ui {
class clericSpellList;
}

class clericSpellList : public QWidget
{
    Q_OBJECT

public:
    explicit clericSpellList(QWidget *parent = nullptr);
    ~clericSpellList();

private:
    Ui::clericSpellList *ui;
    vector<vector<string>> Spells;
};

#endif // CLERICSPELLLIST_H
