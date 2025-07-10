#ifndef WIZARDSPELLLIST_H
#define WIZARDSPELLLIST_H
#include <QWidget>
#include <vector>
#include <string>

using namespace std;

#include <QWidget>

namespace Ui {
class wizardSpellList;
}

class wizardSpellList : public QWidget
{
    Q_OBJECT

public:
    explicit wizardSpellList(QWidget *parent = nullptr);
    ~wizardSpellList();

private:
    Ui::wizardSpellList *ui;
    vector<vector<string>> Spells;
};

#endif // WIZARDSPELLLIST_H
