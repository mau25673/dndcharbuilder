#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "character.h"
#include "species.h"
#include "background.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QWidget>
#include <QComboBox>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Character myCharacter;
    QComboBox *classComboBox;
    int tempLevel, tempStr, tempDex, tempCon, tempWis, tempInte, tempCha;
    Ui::MainWindow *ui;
    QStackedWidget *stack;
    QWidget *createHomePage();
    QWidget *createLevelAndNameSelectionPage();
    QWidget *createClassSelectionPage();
    QWidget *createSubClassSelectionPage();
    QWidget *createBackgroundSelectionPage();
    QWidget *createSpeciesSelectionPage();
    QWidget *createAbilityScoresSelectionPage();
    QWidget *createLoadPage();

    vector<characterClass*> classes;
    vector<Background> backgrounds;
    vector<Species> species;
    vector<subClass*> subClassesFighter;
    vector<subClass*> subClassesRogue;
    vector<subClass*> subClassesWizard;
    vector<subClass*> subClassesCleric;

private slots:
    void goToHomePage();
    void goToLevelAndNameSelection();
    void goToClassSelection();
    void goToSubClassSelection();
    void goToBackgroundSelection();
    void goToSpeciesSelection();
    void goToAbilityScoresSelection();
    void goToLoadCharacter();
};
#endif // MAINWINDOW_H
