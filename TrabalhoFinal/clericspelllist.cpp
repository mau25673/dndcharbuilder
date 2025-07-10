#include "clericspelllist.h"
#include "ui_clericspelllist.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QAction>
#include <QComboBox>
#include <QListWidget>
#include <QTextBrowser>
#include <QLineEdit>
#include <QDebug>
#include <vector>
#include <string>
clericSpellList::clericSpellList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::clericSpellList)
{
    ui->setupUi(this);
    QHBoxLayout *layout = new QHBoxLayout;
    setWindowIcon(QIcon(":/icons/icons/dnd-icon.png"));

    vector<string> clericSpellsLevel1 = {
        "Bane", "Bless", "Command", "Create or Destroy Water",
        "Cure Wounds", "Detect Evil and Good", "Detect Magic",
        "Detect Poison and Disease", "Guiding Bolt", "Inflict Wounds",
        "Protection from Evil and Good", "Purify Food and Drink",
        "Sanctuary", "Shield of Faith"
    };
    this->Spells.push_back(clericSpellsLevel1);

    vector<string> clericSpellsLevel2 = {
        "Aid", "Augury", "Calm Emotions", "Continual Flame",
        "Find Traps", "Gentle Repose", "Lesser Restoration",
        "Locate Object", "Prayer of Healing", "Protection of Poison",
        "Silence", "Spiritual Weapon", "Warding Bond", "Zone of Truth"
    };
    this->Spells.push_back(clericSpellsLevel2);

    vector<string> clericSpellsLevel3 = {
        "Animate Dead", "Beacon of Hope", "Bestow Curse",
        "Clairvoyance", "Create Food and Water", "Crusader's Mantle",
        "Daylight", "Dispel Magic", "Glyph of Warding", "Magic Circle",
        "Mass Healing Word", "Meld Into Stone", "Protection from Energy",
        "Remove Curse", "Revivify", "Sending", "Speak with Dead",
        "Spirit Guardians"
    };
    this->Spells.push_back(clericSpellsLevel3);

    vector<string> clericSpellsLevel4 = {
        "Aura of Life", "Aura of Purify", "Banishment",
        "Control Weather", "Death Ward", "Divination",
        "Freedom of Movement", "Guardian of Faith", "Locate Creature",
        "Stone Shape"
    };
    this->Spells.push_back(clericSpellsLevel4);

    vector<string> clericSpellsLevel5 = {
        "Commune", "Contagion", "Dispel Evil and Good",
        "Flame Strike", "Geas", "Greater Restoration",
        "Hallow", "Insect Plague", "Legend Lore", "Mass Cure Wounds",
        "Raise Dead"
    };
    this->Spells.push_back(clericSpellsLevel5);

    vector<string> clericSpellsLevel6 = {
        "Blade Barrier", "Create Undead", "Forbiddance",
        "Harm", "Heal", "Heroes' Feast", "Planar Ally", "Word of Recall"
    };
    this->Spells.push_back(clericSpellsLevel6);

    vector<string> clericSpellsLevel7 = {
        "Conjure Celestial", "Divine Word", "Etherealness",
        "Plane Shift", "Regenerate", "Resurrection"
    };
    this->Spells.push_back(clericSpellsLevel7);

    vector<string> clericSpellsLevel8 = {
        "Antimagic Field", "Antipathy/Sympathy",
        "Control Weather", "Earthquake", "Holy Aura"
    };
    this->Spells.push_back(clericSpellsLevel8);

    vector<string> clericSpellsLevel9 = {
        "Astral Projection", "Gate", "Mass Heal",
        "Power Word Heal", "True Resurrection"
    };
    this->Spells.push_back(clericSpellsLevel9);

    vector<string> spellLevels = {"1st Level", "2nd Level", "3rd Level", "4th Level", "5th Level", "6th Level", "7th Level", "8th Level", "9th Level"};

    QListWidget *list = new QListWidget;
    QTextBrowser *desc = new QTextBrowser;

    for (string &lvl : spellLevels) {
        list->addItem(QString::fromStdString(lvl));
    }

    connect(list, &QListWidget::itemSelectionChanged, this, [=]() {
        QListWidgetItem *currentItem = list->currentItem();
        if (!currentItem) return;

        QString name = currentItem->text();
        for (size_t i = 0; i < spellLevels.size(); ++i) {
            if (QString::fromStdString(spellLevels[i]) == name) {
                QString fullText;
                for (string &spell : Spells[i]) {
                    fullText += QString::fromStdString(spell) + "\n";
                }
                desc->setText(fullText);
                break;
            }
        }
    });

    layout->addWidget(list, 1);
    layout->addWidget(desc, 2);
    setLayout(layout);
}

clericSpellList::~clericSpellList()
{
    delete ui;
}
