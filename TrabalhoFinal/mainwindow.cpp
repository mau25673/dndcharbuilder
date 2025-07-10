#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "background.h"
#include "species.h"
#include "wizardspelllist.h"
#include "clericspelllist.h"
#include "creatorScreen.h"
#include <iostream>
#include <cstdio>
#include <QScrollArea>
#include <algorithm>
#include <fstream>
#include <string>
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
#include <sstream>
#include <QLineEdit>
#include <QDebug>
#include <QInputDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stack = new QStackedWidget;
    QMenuBar *menuBar = new QMenuBar(this);
    this->setMenuBar(menuBar);

    QMenu *spellsMenu = new QMenu("Spells", this);
    menuBar->addMenu(spellsMenu);
    QAction *wizardSpells = new QAction("Wizard Spell List", this);
    spellsMenu->addAction(wizardSpells);
    QAction *clericSpells = new QAction("Cleric Spell List", this);
    spellsMenu->addAction(clericSpells);

    QMenu *aboutMenu = new QMenu("About", this);
    menuBar->addMenu(aboutMenu);
    QAction *creatorScreenCreate = new QAction("Creator", this);
    aboutMenu->addAction(creatorScreenCreate);
    QAction *returnHome = new QAction("Return", this);
    aboutMenu->addAction(returnHome);

    connect(wizardSpells, &QAction::triggered,this, [=](){
        qDebug() << "Abrindo janela Wizard Spell List.";
        wizardSpellList *wizardSpellListWindow = new wizardSpellList();
        wizardSpellListWindow->setWindowTitle("Wizard Spell List");
        wizardSpellListWindow->resize(500, 300);
        wizardSpellListWindow->setAttribute(Qt::WA_DeleteOnClose);
        wizardSpellListWindow->show();
    });

    connect(clericSpells, &QAction::triggered,this, [=](){
        qDebug() << "Abrindo janela Cleric Spell List.";
        clericSpellList *clericSpellListWindow = new clericSpellList();
        clericSpellListWindow->setWindowTitle("Cleric Spell List");
        clericSpellListWindow->resize(500, 300);
        clericSpellListWindow->setAttribute(Qt::WA_DeleteOnClose);
        clericSpellListWindow->show();
    });

    connect(creatorScreenCreate, &QAction::triggered,this, [=](){
        qDebug() << "Abrindo janela Creator Screen.";
        creatorScreen *creatorScreenWindow = new creatorScreen();
        creatorScreenWindow->setWindowTitle("Creator");
        creatorScreenWindow->resize(500, 300);
        creatorScreenWindow->setAttribute(Qt::WA_DeleteOnClose);
        creatorScreenWindow->show();
    });

    connect(returnHome, &QAction::triggered, this, &MainWindow::goToHomePage);

    QWidget *homePage = createHomePage();
    QWidget *levelAndNamePage = createLevelAndNameSelectionPage();
    QWidget *classSelectionPage = createClassSelectionPage();
    QWidget *subClassSelectionPage = createSubClassSelectionPage();
    QWidget *backgroundSelectionPage = createBackgroundSelectionPage();
    QWidget *speciesSelectionPage = createSpeciesSelectionPage();
    QWidget *abilityScoresSelectionPage = createAbilityScoresSelectionPage();


    stack->addWidget(homePage);
    stack->addWidget(levelAndNamePage);
    stack->addWidget(classSelectionPage);
    stack->addWidget(subClassSelectionPage);
    stack->addWidget(backgroundSelectionPage);
    stack->addWidget(speciesSelectionPage);
    stack->addWidget(abilityScoresSelectionPage);


    setCentralWidget(stack);
    resize(600, 400);
}

QWidget *MainWindow::createHomePage(){
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    layout->addStretch();

    QLabel *title = new QLabel("Character Builder for Dungeons and Dragons 5th Edition"); //titulo
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold;");

    QPushButton *New = new QPushButton("New Character"); //botoes
    QPushButton *load = new QPushButton("Load Character");
    QPushButton *Delete = new QPushButton("Delete Character");

    New->setFixedSize(200, 40);
    load->setFixedSize(200, 40);
    Delete->setFixedSize(200, 40);

    QVBoxLayout *buttonLayout = new QVBoxLayout; //alinhamento dos botoes
    buttonLayout->setAlignment(Qt::AlignHCenter);
    buttonLayout->addWidget(New);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(load);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(Delete);

    layout->addWidget(title); //alinhamento da pagina
    layout->addSpacing(40);
    layout->addLayout(buttonLayout);
    layout->addStretch();

    page->setLayout(layout);

    connect(New, &QPushButton::clicked, this, &MainWindow::goToLevelAndNameSelection);
    connect(load, &QPushButton::clicked, this, [=] () {
        myCharacter = Character();
        QString loadCharacter = QInputDialog::getText(this, "Character Loading", "Character Name:");
        string loadCharacterStr = loadCharacter.toStdString();
        replace(loadCharacterStr.begin(), loadCharacterStr.end(), ' ', '_');
        loadCharacter = QString::fromStdString(loadCharacterStr);
        stringstream stream;
        stream << loadCharacter.toStdString() << ".txt";
        ifstream fileReader(stream.str());
        if(fileReader.is_open()){
            string charName, charClassName, charSubClassName, charSpeciesName, charBackgroundName, charLevelStr, charStrStr, charDexStr, charConStr, charIntStr, charWisStr, charChaStr;
            int charLevel, charStr, charDex, charCon, charInt, charWis, charCha;

            getline(fileReader,charName,'|');
            qDebug() << charName;
            getline(fileReader,charClassName,'|');
            qDebug() << charClassName;
            getline(fileReader,charSubClassName,'|');
            qDebug() << charSubClassName;
            getline(fileReader,charBackgroundName,'|');
            qDebug() << charBackgroundName;
            getline(fileReader,charSpeciesName,'|');
            qDebug() << charSpeciesName;
            getline(fileReader,charLevelStr, '|');
            charLevel = stoi(charLevelStr);
            qDebug() << charLevel;
            getline(fileReader,charStrStr, '|');
            charStr = stoi(charStrStr);
            qDebug() << charStr;
            getline(fileReader,charDexStr, '|');
            charDex = stoi(charDexStr);
            qDebug() << charDex;
            getline(fileReader,charConStr, '|');
            charCon = stoi(charConStr);
            qDebug() << charCon;
            getline(fileReader,charIntStr, '|');
            charInt = stoi(charIntStr);
            qDebug() << charInt;
            getline(fileReader,charWisStr, '|');
            charWis = stoi(charWisStr);
            qDebug() << charWis;
            getline(fileReader,charChaStr, '|');
            charCha = stoi(charChaStr);
            qDebug() << charCha;

            myCharacter.SetName(charName);
            for (auto myCharacterClass : classes){
                if (charClassName == myCharacterClass->getName()){
                    myCharacter.SetCharacterClass(*myCharacterClass);
                    break;
                }
            }
            for (auto subClassI : subClassesFighter){
                if (charSubClassName == subClassI->GetName()){
                    myCharacter.SetCharacterSubClass(*subClassI);
                    break;
                }
            }
            for (auto subClassI : subClassesRogue){
                if (charSubClassName == subClassI->GetName()){
                    myCharacter.SetCharacterSubClass(*subClassI);
                    break;
                }
            }
            for (auto subClassI : subClassesWizard){
                if (charSubClassName == subClassI->GetName()){
                    myCharacter.SetCharacterSubClass(*subClassI);
                    break;
                }
            }
            for (auto subClassI : subClassesCleric){
                if (charSubClassName == subClassI->GetName()){
                    myCharacter.SetCharacterSubClass(*subClassI);
                    break;
                }
            }
            for (auto background : backgrounds){
                if (charBackgroundName == background.getName()){
                    myCharacter.SetBackground(background);
                    break;
                }
            }
            for (auto specie : species){
                if (charSpeciesName == specie.GetName()){
                    myCharacter.SetSpecies(specie);
                }
            }
            myCharacter.SetLevel(charLevel);
            myCharacter.SetScore(charStr, charDex, charCon, charInt, charWis, charCha);
            QWidget *loadPage = createLoadPage();
            stack->addWidget(loadPage);
            stack->setCurrentWidget(loadPage);
        }
        else{
            QMessageBox::warning(this, "Invalid Character", "No character with this name found. Check grammar and spaces.");
        }
        fileReader.close();
    });
    connect(Delete, &QPushButton::clicked, this, [=] () {
        QString deleteCharacter = QInputDialog::getText(this, "Character Deletion", "Character Name:");
        string deleteCharacterStr = deleteCharacter.toStdString();
        replace(deleteCharacterStr.begin(), deleteCharacterStr.end(), ' ', '_');
        deleteCharacter = QString::fromStdString(deleteCharacterStr);
        stringstream stream;
        stream << deleteCharacter.toStdString() << ".txt";
        int deletionStatus = remove(stream.str().c_str());
        if (deletionStatus != 0) {
            QMessageBox::warning(this, "Invalid Character", "No character with this name found. Check grammar and spaces.");;
        }
    });
    return page;
}

QWidget *MainWindow::createLevelAndNameSelectionPage(){
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *firstStep = new QLabel("1. Decide Your Name and Level");
    firstStep->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    firstStep->setStyleSheet("font-size: 18px; font-weight: bold;");
    firstStep->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    QLabel *nameLabel = new QLabel("Character Name:");
    nameLabel->setAlignment(Qt::AlignLeft);
    nameLabel->setStyleSheet("font-size: 14px;");
    nameLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    QLineEdit *nameEdit = new QLineEdit("");
    nameEdit->setFixedWidth(300);

    QLabel *levelLabel = new QLabel("Character Level:");
    levelLabel->setAlignment(Qt::AlignLeft);
    levelLabel->setStyleSheet("font-size: 14px;");
    levelLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    QLineEdit *levelEdit = new QLineEdit("");
    QIntValidator *validator = new QIntValidator(1, 20, this);
    levelEdit->setValidator(validator);
    levelEdit->setFixedWidth(40);

    QPushButton *next = new QPushButton("Next");
    next->setFixedSize(200, 40);

    layout->addWidget(firstStep);
    layout->addWidget(nameLabel);
    layout->addWidget(nameEdit);
    layout->addWidget(levelLabel);
    layout->addWidget(levelEdit);
    layout->addWidget(next, 0, Qt::AlignRight);

    page->setLayout(layout);

    connect(next, &QPushButton::clicked, this, [=](){
        if((nameEdit->text().trimmed().toStdString().empty()) || ((levelEdit->text().trimmed().toInt()) <= 0 || (levelEdit->text().trimmed().toInt()) > 20) || levelEdit->text().trimmed().toStdString().empty()){
            if(nameEdit->text().trimmed().toStdString().empty()){
                QMessageBox::warning(this, "Invalid Name", "Please enter a character name.");
                return;
            }
            if(levelEdit->text().toStdString().empty()){
                QMessageBox::warning(this, "Invalid Level", "Please enter a valid level (1 to 20).");
                return;
            }
            if((levelEdit->text().toInt()) <= 0 || (levelEdit->text().toInt()) > 20){
                QMessageBox::warning(this, "Invalid Level", "Please enter a valid level (1 to 20).");
                return;
            }
        }
        else{
            string characterNameTreated = nameEdit->text().toStdString();
            replace(characterNameTreated.begin(), characterNameTreated.end(), ' ', '_');
            myCharacter.SetName(characterNameTreated);
            myCharacter.SetLevel(levelEdit->text().toInt());
            this->goToClassSelection();
        }
    });

    return page;
}

QWidget *MainWindow::createClassSelectionPage(){
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    //implementação fighter
    vector<tuple<int,string,string>> fighterFeatures;
    vector<int> fighterFeatureLevels = {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 17, 18, 19, 20};
    vector<string> fighterFeatureNames = {"Fighting Style", "Second Wind", "Action Surge", "Martial Archetype",
    "Ability Score Improvement", "Extra Attack", "Ability Score Improvement", "Martial Archetype feature",
    "Ability Score Improvement", "Indomitable", "Martial Archetype feature", "Extra Attack (2)",
    "Ability Score Improvement", " Indomitable (two uses)", "Ability Score Improvement", "Martial Archetype feature",
    "Ability Score Improvement", "Action Surge (two uses)", "Indomitable (three uses)", "Martial Archetype feature",
    "Ability Score Improvement", "Extra Attack (3)"};
    vector<string> fighterFeatureDescriptions = {"You adopt a particular style of fighting as your specialty. Choose one of the following options. You can't take the same Fighting Style option more than once, even if you get to choose again.\n\nArchery\nYou gain a +2 bonus to attack rolls you make with ranged weapons.\n\nDefense\nWhile you are wearing armor, you gain a +1 bonus to AC.\n\nDueling\nWhen you are wielding a melee weapon in one hand and no other weapons, you gain a +2 bonus to damage rolls with that weapon.\n\nGreat Weapon Fighting\nWhen you roll a 1 or 2 on a damage die for an attack you make with a melee weapon that you are wielding with two hands, you can reroll the die and must use the new roll, even if the new roll is a 1 or a 2. The weapon must have the two-handed or versatile property for you to gain this benefit.\n\nProtection\nWhen a creature you can see attacks a target other than you that is within 5 feet of you, you can use your reaction to impose disadvantage on the attack roll. You must be wielding a shield.\n\nTwo-Weapon Fighting\nWhen you engage in two-weapon fighting, you can add your ability modifier to the damage of the second attack.",
    "You have a limited well of stamina that you can draw on to protect yourself from harm.\nOn your turn, you can use a bonus action to regain hit points equal to 1d10 + your fighter level.\nOnce you use this feature, you must finish a short or long rest before you can use it again.",
    "Starting at 2nd level, you can push yourself beyond your normal limits for a moment. On your turn, you can take one additional action.\nOnce you use this feature, you must finish a short or long rest before you can use it again. Starting at 17th level, you can use it twice before a rest, but only once on the same turn.",
    "At 3rd level, you choose an archetype from the list available that you strive to emulate in your combat styles and techniques. The archetype you choose grants you features at 3rd level and again at 7th, 10th, 15th, and 18th level.",
    "When you reach 4th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "Beginning at 5th level, you can attack twice, instead of once, whenever you take the Attack action on your turn.\nThe number of attacks increases to three when you reach 11th level in this class and to four when you reach 20th level in this class.",
    "When you reach 6th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "At 7th level, you gain a feature granted by your Martial Archetype.",
    "When you reach 8th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "Beginning at 9th level, you can reroll a saving throw that you fail. If you do so, you must use the new roll, and you can't use this feature again until you finish a long rest.\nYou can use this feature twice between long rests starting at 13th level and three times between long rests starting at 17th level.",
    "At 10th level, you gain a feature granted by your Martial Archetype.",
    "At 11th level, you can attack three times whenever you take the Attack action on your turn.",
    "When you reach 12th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "At 13th level, you can use Indomitable twice between long rests.",
    "When you reach 14th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "At 15th level, you gain a feature granted by your Martial Archetype.",
    "When you reach 16th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "At 17th level, you can use Action Surge twice before a rest, but only once on the same turn.",
    "At 17th level, you can use Indomitable three times between long rests.",
    "At 18th level, you gain a feature granted by your Martial Archetype.",
    "When you reach 19th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "At 20th level, you can attack four times whenever you take the Attack action on your turn."};
    for (size_t i = 0; i < fighterFeatureNames.size(); i++) {
        fighterFeatures.push_back(make_tuple(fighterFeatureLevels.at(i),fighterFeatureNames.at(i),fighterFeatureDescriptions.at(i)));
    }
    this->classes.push_back(new fighterClass("Fighter",fighterFeatures));

    //implementação rogue
    vector<tuple<int, string, string>> rogueFeatures;
    vector<int> rogueFeatureLevels = {1, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    vector<string> rogueFeatureNames = {"Expertise", "Sneak Attack", "Thieves' Cant", "Cunning Action", "Roguish Archetype",
    "Ability Score Improvement", "Uncanny Dodge", "Expertise", "Evasion", "Ability Score Improvement", "Roguish Archetype feature",
    "Ability Score Improvement", "Reliable Talent", "Ability Score Improvement", "Roguish Archetype feature", "Blindsense",
    "Slippery Mind", "Ability Score Improvement", "Roguish Archetype feature", "Elusive", "Ability Score Improvement",
    "Stroke of Luck"};
    vector<string> rogueFeatureDescriptions = {"At 1st level, choose two of your skill proficiencies, or one of your skill proficiencies and your proficiency with thieves' tools. Your proficiency bonus is doubled for any ability check you make that uses either of the chosen proficiencies.\nAt 6th level, you can choose two more of your proficiencies (in skills or with thieves' tools) to gain this benefit.",
    "Beginning at 1st level, you know how to strike subtly and exploit a foe's distraction. Once per turn, you can deal an extra 1d6 damage to one creature you hit with an attack if you have advantage on the attack roll. The attack must use a finesse or a ranged weapon.\nYou don't need advantage on the attack roll if another enemy of the target is within 5 feet of it, that enemy isn't incapacitated, and you don't have disadvantage on the attack roll.\nThe amount of the extra damage increases as you gain levels in this class, with each odd level increasing the damage by 1d6.",
    "During your rogue training you learned thieves' cant, a secret mix of dialect, jargon, and code that allows you to hide messages in seemingly normal conversation. Only another creature that knows thieves' cant understands such messages. It takes four times longer to convey such a message than it does to speak the same idea plainly.\nIn addition, you understand a set of secret signs and symbols used to convey short, simple messages, such as whether an area is dangerous or the territory of a thieves' guild, whether loot is nearby, or whether the people in an area are easy marks or will provide a safe house for thieves on the run.",
    "Starting at 2nd level, your quick thinking and agility allow you to move and act quickly. You can take a bonus action on each of your turns in combat. This action can be used only to take the Dash, Disengage, or Hide action.",
    "At 3rd level, you choose an archetype that you emulate in the exercise of your rogue abilities from the list of available archetypes. Your archetype choice grants you features at 3rd level and then again at 9th, 13th, and 17th level.",
    "When you reach 4th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "Starting at 5th level, when an attacker that you can see hits you with an attack, you can use your reaction to halve the attack's damage against you.",
    "At 6th level, you can choose two more of your proficiencies (in skills or with thieves' tools) to gain the benefit of Expertise.",
    "Beginning at 7th level, you can nimbly dodge out of the way of certain area effects, such as a red dragon's fiery breath or an ice storm spell. When you are subjected to an effect that allows you to make a Dexterity saving throw to take only half damage, you instead take no damage if you succeed on the saving throw, and only half damage if you fail.",
    "When you reach 8th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "At 9th level, you gain a feature granted by your Roguish Archetype.",
    "When you reach 10th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "By 11th level, you have refined your chosen skills until they approach perfection. Whenever you make an ability check that lets you add your proficiency bonus, you can treat a d20 roll of 9 or lower as a 10.",
    "When you reach 12th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "At 13th level, you gain a feature granted by your Roguish Archetype.",
    "Starting at 14th level, if you are able to hear, you are aware of the location of any hidden or invisible creature within 10 feet of you.",
    "By 15th level, you have acquired greater mental strength. You gain proficiency in Wisdom saving throws.",
    "When you reach 16th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "At 17th level, you gain a feature granted by your Roguish Archetype.",
    "Beginning at 18th level, you are so evasive that attackers rarely gain the upper hand against you. No attack roll has advantage against you while you aren't incapacitated.",
    "When you reach 19th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "At 20th level, you have an uncanny knack for succeeding when you need to. If your attack misses a target within range, you can turn the miss into a hit. Alternatively, if you fail an ability check, you can treat the d20 roll as a 20.\nOnce you use this feature, you can't use it again until you finish a short or long rest."};
    for (size_t i = 0; i < rogueFeatureNames.size(); i++) {
        rogueFeatures.push_back(make_tuple(rogueFeatureLevels.at(i),rogueFeatureNames.at(i),rogueFeatureDescriptions.at(i)));
    }
    this->classes.push_back(new rogueClass("Rogue",rogueFeatures));

    //implementação clérigo
    vector<tuple<int, string, string>> clericFeatures;
    vector<int> clericFeatureLevels = {1, 1, 2, 2, 4, 5, 6, 6, 8, 8, 8, 10, 11, 12, 14, 16, 17, 17, 18, 19, 20};
    vector<string> clericFeatureNames = {"Spellcasting", "Divine Domain", "Channel Divinity", "Divine Domain feature",
    "Ability Score Improvement", "Destroy Undead (CR 1/2)", "Channel Divinity", "Divine Domain feature",
    "Ability Score Improvement", "Destroy Undead (CR 1)", "Divine Domain feature", "Divine Intervention",
    "Destroy Undead (CR 2)", "Ability Score Improvement", "Destroy Undead (CR 3)", "Ability Score Improvement",
    "Destroy Undead (CR 4)", "Divine Domain feature", "Channel Divinity", "Ability Score Improvement",
    "Divine Intervention Improvement"};
    vector<string> clericFeatureDescriptions = {"As a conduit for divine power, you can cast cleric spells. See chapter 10 for the general rules of spellcasting and chapter 11 for a selection of cleric spells.\n\nCantrips\nAt 1st level, you know three cantrips of your choice from the cleric spell list. You learn additional cleric cantrips of your choice at higher levels, as shown in the Cantrips Known column of the Cleric table.\n\nPreparing and Casting Spells\nThe Cleric table shows how many spell slots you have to cast your cleric spells of 1st level and higher. To cast one of these spells, you must expend a slot of the spell's level or higher. You regain all expended spell slots when you finish a long rest.\n\nYou prepare the list of cleric spells that are available for you to cast, choosing from the cleric spell list. When you do so, choose a number of cleric spells equal to your Wisdom modifier + your cleric level (minimum of one spell). The spells must be of a level for which you have spell slots.\n\nFor example, if you are a 3rd-level cleric, you have four 1st-level and two 2nd-level spell slots. With a Wisdom of 16, your list of prepared spells can include six spells of 1st or 2nd level, in any combination. If you prepare the 1st-level spell cure wounds, you can cast it using a 1st-level or 2nd-level slot. Casting the spell doesn't remove it from your list of prepared spells.\n\nYou can change your list of prepared spells when you finish a long rest. Preparing a new list of cleric spells requires time spent in prayer and meditation: at least 1 minute per spell level for each spell on your list.\n\nSpellcasting Ability\nWisdom is your spellcasting ability for your cleric spells. The power of your spells comes from your devotion to your deity. You use your Wisdom whenever a cleric spell refers to your spellcasting ability. In addition, you use your Wisdom modifier when setting the saving throw DC for a cleric spell you cast and when making an attack roll with one.\n\nSpell save DC = 8 + Wisdom modifier + Proficiency Bonus\nSpell attack modifier = Wisdom modifier + Proficiency Bonus\nRitual Casting\nYou can cast a cleric spell as a ritual if that spell has the ritual tag and you have the spell prepared.\n\nSpellcasting Focus\nYou can use a holy symbol as a spellcasting focus for your cleric spells.",
    "Choose one domain related to your deity from the list of available domains. Each domain is detailed in their own feature, and each one provides examples of gods associated with it. Your choice grants you domain spells and other features when you choose it at 1st level. It also grants you additional ways to use Channel Divinity when you gain that feature at 2nd level, and additional benefits at 6th, 8th, and 17th levels.\n\nDomain Spells\nEach domain has a list of spells—its domain spells—that you gain at the cleric levels noted in the domain description. Once you gain a domain spell, you always have it prepared, and it doesn't count against the number of spells you can prepare each day.\n\nIf you have a domain spell that doesn't appear on the cleric spell list, the spell is nonetheless a cleric spell for you.",
    "At 2nd level, you gain the ability to channel divine energy directly from your deity, using that energy to fuel magical effects. You start with two such effects: Turn Undead and an effect determined by your domain. Some domains grant you additional effects as you advance in levels, as noted in the domain description.\n\nWhen you use your Channel Divinity, you choose which effect to create. You must then finish a short or long rest to use your Channel Divinity again.\n\nSome Channel Divinity effects require saving throws. When you use such an effect from this class, the DC equals your cleric spell save DC.\n\nBeginning at 6th level, you can use your Channel Divinity twice between rests, and beginning at 18th level, you can use it three times between rests. When you finish a short or long rest, you regain your expended uses.\n\nChannel Divinity: Turn Undead\nAs an action, you present your holy symbol and speak a prayer censuring the undead. Each undead that can see or hear you within 30 feet of you must make a Wisdom saving throw. If the creature fails its saving throw, it is turned for 1 minute or until it takes any damage.\n\nA turned creature must spend its turns trying to move as far away from you as it can, and it can't willingly move to a space within 30 feet of you. It also can't take reactions. For its action, it can use only the Dash action or try to escape from an effect that prevents it from moving. If there's nowhere to move, the creature can use the Dodge action.",
    "At 2nd level, you gain a feature from your Divine Domain.",
    "When you reach 4th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\n\nIf your DM allows the use of feats, you may instead take a feat.",
    "Starting at 5th level, when an undead of CR 1/2 or lower fails its saving throw against your Turn Undead feature, the creature is instantly destroyed.",
    "Beginning at 6th level, you can use your Channel Divinity twice between rests.",
    "At 6th level, you gain a feature from your Divine Domain.",
    "When you reach 8th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "Starting at 8th level, when an undead of CR 1 or lower fails its saving throw against your Turn Undead feature, the creature is instantly destroyed.",
    "At 8th level, you gain a feature from your Divine Domain.",
    "Beginning at 10th level, you can call on your deity to intervene on your behalf when your need is great.\n\nImploring your deity's aid requires you to use your action. Describe the assistance you seek, and roll percentile dice. If you roll a number equal to or lower than your cleric level, your deity intervenes. The DM chooses the nature of the intervention; the effect of any cleric spell or cleric domain spell would be appropriate. If your deity intervenes, you can't use this feature again for 7 days. Otherwise, you can use it again after you finish a long rest.\n\nAt 20th level, your call for intervention succeeds automatically, no roll required.",
    "Starting at 11th level, when an undead of CR 2 or lower fails its saving throw against your Turn Undead feature, the creature is instantly destroyed.",
    "When you reach 12th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "Starting at 14th level, when an undead of CR 3 or lower fails its saving throw against your Turn Undead feature, the creature is instantly destroyed.",
    "When you reach 16th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "Starting at 17th level, when an undead of CR 4 or lower fails its saving throw against your Turn Undead feature, the creature is instantly destroyed.",
    "At 17th level, you gain a feature from your Divine Domain.",
    "Beginning at 18th level, you can use your Channel Divinity three times between rests.",
    "When you reach 19th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\nIf your DM allows the use of feats, you may instead take a feat.",
    "At 20th level, your call for intervention succeeds automatically, no roll required."};
    for (size_t i = 0; i < clericFeatureNames.size(); i++) {
        clericFeatures.push_back(make_tuple(clericFeatureLevels.at(i),clericFeatureNames.at(i),clericFeatureDescriptions.at(i)));
    }
    this->classes.push_back(new clericClass("Cleric",clericFeatures));

    //implementação wizard
    vector<tuple<int,string,string>> wizardFeatures;
    vector<int> wizardFeatureLevels = {1,1,2,4,6,8,10,12,14,16,18,19,20};
    vector<string> wizardFeatureNames = {"Spellcasting", "Arcane Recovery", "Arcane Tradition", "Ability Score Improvement",
    "Arcane Tradition", "Ability Score Improvement", "Arcane Tradition", "Ability Score Improvement","Arcane Tradition", "Ability Score Improvement",
    "Spell Mastery", "Ability Score Improvement", "Signature Spells"};
    vector<string> wizardFeatureDescriptions = {"Cantrips\nAt 1st level, you know three cantrips of your choice from the wizard spell list. You learn additional wizard cantrips of your choice at higher levels, as shown in the Cantrips Known column of the Wizard table.\n\nSpellbook\nAt 1st level, you have a spellbook containing six 1st-level wizard spells of your choice. Your spellbook is the repository of the wizard spells you know, except your cantrips, which are fixed in your mind.\n\nPreparing and Casting Spells\nThe Wizard table shows how many spell slots you have to cast your wizard spells of 1st level and higher. To cast one of these spells, you must expend a slot of the spell's level or higher. You regain all expended spell slots when you finish a long rest.\n\nYou prepare the list of wizard spells that are available for you to cast. To do so, choose a number of wizard spells from your spellbook equal to your Intelligence modifier + your wizard level (minimum of one spell). The spells must be of a level for which you have spell slots.\n\nFor example, if you're a 3rd-level wizard, you have four 1st-level and two 2nd-level spell slots. With an Intelligence of 16, your list of prepared spells can include six spells of 1st or 2nd level, in any combination, chosen from your spellbook. If you prepare the 1st-level spell magic missile, you can cast it using a 1st-level or a 2nd-level slot. Casting the spell doesn't remove it from your list of prepared spells.\n\nYou can change your list of prepared spells when you finish a long rest. Preparing a new list of wizard spells requires time spent studying your spellbook and memorizing the incantations and gestures you must make to cast the spell: at least 1 minute per spell level for each spell on your list.\n\nSpellcasting Ability\nIntelligence is your spellcasting ability for your wizard spells, since you learn your wizard spells through dedicated study and memorization. You use your Intelligence whenever a spell refers to your spellcasting ability. In addition, you use your Intelligence modifier when setting the saving throw DC for a wizard spell you cast and when making an attack roll with one.\n\nSpell save DC = 8 + Intelligence modifier + Proficiency Bonus\nSpell attack modifier = Intelligence modifier + Proficiency Bonus\nRitual Casting\nYou can cast a wizard spell as a ritual if that spell has the ritual tag and you have the spell in your spellbook. You don't need to have the spell prepared.\n\nSpellcasting Focus\nYou can use an arcane focus as a spellcasting focus for your wizard spells.\n\nLearning Spells of 1st Level and Higher\nEach time you gain a wizard level, you can add two wizard spells of your choice to your spellbook. Each of these spells must be of a level for which you have spell slots, as shown on the Wizard table. On your adventures, you might find other spells that you can add to your spellbook (see 'Your Spellbook').\n\nYour Spellbook\nThe spells that you add to your spellbook as you gain levels reflect the arcane research you conduct on your own, as well as intellectual breakthroughs you have had about the nature of the multiverse. You might find other spells during your adventures. You could discover a spell recorded on a scroll in an evil wizard's chest, for example, or in a dusty tome in an ancient library.\n\nA spellbook doesn't contain cantrips.\n\nCopying a Spell into the Book. When you find a wizard spell of 1st level or higher, you can add it to your spellbook if it is of a spell level you can prepare and if you can spare the time to decipher and copy it.\n\nCopying a spell into your spellbook involves reproducing the basic form of the spell, then deciphering the unique system of notation used by the wizard who wrote it. You must practice the spell until you understand the sounds or gestures required, then transcribe it into your spellbook using your own notation.\n\nFor each level of the spell, the process takes 2 hours and costs 50 gp. The cost represents material components you expend as you experiment with the spell to master it, as well as the fine inks you need to record it. Once you have spent this time and money, you can prepare the spell just like your other spells.\n\nReplacing the Book. You can copy a spell from your own spellbook into another book—for example, if you want to make a backup copy of your spellbook. This is just like copying a new spell into your spellbook, but faster and easier, since you understand your own notation and already know how to cast the spell. You need spend only 1 hour and 10 gp for each level of the copied spell.\n\nIf you lose your spellbook, you can use the same procedure to transcribe the spells that you have prepared into a new spellbook. Filling out the remainder of your spellbook requires you to find new spells to do so, as normal. For this reason, many wizards keep backup spellbooks in a safe place.\n\nThe Book's Appearance. Your spellbook is a unique compilation of spells, with its own decorative flourishes and margin notes. It might be a plain, functional leather volume that you received as a gift from your master, a finely bound gilt-edged tome you found in an ancient library, or even a loose collection of notes scrounged together after you lost your previous spellbook in a mishap.",
    "You have learned to regain some of your magical energy by studying your spellbook. Once per day when you finish a short rest, you can choose expended spell slots to recover. The spell slots can have a combined level that is equal to or less than half your wizard level (rounded up), and none of the slots can be 6th level or higher.\n\nFor example, if you're a 4th-level wizard, you can recover up to two levels worth of spell slots. You can recover either a 2nd-level spell slot or two 1st-level spell slots.",
    "When you reach 2nd level, you choose an arcane tradition from the list of available traditions, shaping your practice of magic. Your choice grants you features at 2nd level and again at 6th, 10th, and 14th level.",
    "When you reach 4th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\n\nIf your DM allows the use of feats, you may instead take a feat.",
    "At 6th level, you gain a feature granted by your Arcane Tradition.",
    "When you reach 8th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\n\nIf your DM allows the use of feats, you may instead take a feat.",
    "At 10th level, you gain a feature granted by your Arcane Tradition.",
    "When you reach 12th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\n\nIf your DM allows the use of feats, you may instead take a feat.",
    "At 14th level, you gain a feature granted by your Arcane Tradition.",
    "When you reach 16th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\n\nIf your DM allows the use of feats, you may instead take a feat.",
    "At 18th level, you have achieved such mastery over certain spells that you can cast them at will. Choose a 1st-level wizard spell and a 2nd-level wizard spell that are in your spellbook. You can cast those spells at their lowest level without expending a spell slot when you have them prepared. If you want to cast either spell at a higher level, you must expend a spell slot as normal.\n\nBy spending 8 hours in study, you can exchange one or both of the spells you chose for different spells of the same levels.",
    "When you reach 19th level, you can increase one ability score of your choice by 2, or you can increase two ability scores of your choice by 1. As normal, you can't increase an ability score above 20 using this feature.\n\nIf your DM allows the use of feats, you may instead take a feat.",
    "When you reach 20th level, you gain mastery over two powerful spells and can cast them with little effort. Choose two 3rd-level wizard spells in your spellbook as your signature spells. You always have these spells prepared, they don't count against the number of spells you have prepared, and you can cast each of them once at 3rd level without expending a spell slot. When you do so, you can't do so again until you finish a short or long rest.\n\nIf you want to cast either spell at a higher level, you must expend a spell slot as normal."};
    for (size_t i = 0; i < wizardFeatureNames.size(); i++) {
        wizardFeatures.push_back(make_tuple(wizardFeatureLevels.at(i),wizardFeatureNames.at(i),wizardFeatureDescriptions.at(i)));
    }
    this->classes.push_back(new wizardClass("Wizard",wizardFeatures));


    QListWidget *list = new QListWidget;
    QTextBrowser *desc = new QTextBrowser;

    QPushButton *next = new QPushButton("Next");
    next->setFixedSize(200, 40);
    next->setVisible(false);

    for (auto& charClass : classes) {
        list->addItem(QString::fromStdString(charClass->getName()));
    }
    connect(list, &QListWidget::itemSelectionChanged, this, [=]() {
        QListWidgetItem *currentItem = list->currentItem();
        if (!currentItem) return;

        QString name = currentItem->text();
        for (const auto &charClass : classes) {
            if (QString::fromStdString(charClass->getName()) == name) {
                stringstream stream;
                for (size_t i = 0; i < charClass->getFeatures().size(); i++){
                    stream << "Level " << charClass->getFeatureLevel(i) << ": " << charClass->getFeatureName(i) << endl << charClass->getFeatureDescription(i) << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl;
                }
                QString fullText = QString::fromStdString(stream.str());
                desc->setText(fullText);

                this->myCharacter.SetCharacterClass(*charClass);
                next->setVisible(true);
                qDebug() << "Classe selecionada:" << QString::fromStdString(myCharacter.GetCharacterClass().getName());
                qDebug() << "Level: " << myCharacter.GetLevel();
                break;
            }
        }
    });

    QLabel *secondStep = new QLabel("2. Choose Your Class:");
    secondStep->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    secondStep->setStyleSheet("font-size: 18px; font-weight: bold;");
    secondStep->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    layout->addWidget(secondStep);
    layout->addWidget(list, 1);
    layout->addWidget(desc, 3);
    layout->addWidget(next, 0, Qt::AlignRight);
    page->setLayout(layout);

    connect(next, &QPushButton::clicked, this, [=] (){
        if ((myCharacter.GetLevel() >= 3) && (myCharacter.GetCharacterClass().getName() == "Fighter" || myCharacter.GetCharacterClass().getName() == "Rogue"))
            this->goToSubClassSelection();
        else if ((myCharacter.GetLevel() >= 2) && (myCharacter.GetCharacterClass().getName() == "Wizard"))
            this->goToSubClassSelection();
        else if (myCharacter.GetCharacterClass().getName() == "Cleric")
            this->goToSubClassSelection();
        else
            this->goToBackgroundSelection();
    });

    return page;
}

QWidget *MainWindow::createSubClassSelectionPage(){
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    //implementação subclasses fighter
    vector<int> championFeatureLevels = {3, 7, 10, 15, 18};
    vector<string> championFeatureNames = {"Improved Critical", "Remarkable Athlete", "Additional Fighting Style",
    "Superior Critical", "Survivor"};
    vector<string> championFeatureDescriptions = {"Beginning when you choose this archetype at 3rd level, your weapon attacks score a critical hit on a roll of 19 or 20.",
    "Starting at 7th level, you can add half your proficiency bonus (round up) to any Strength, Dexterity, or Constitution check you make that doesn't already use your proficiency bonus.\nIn addition, when you make a running long jump, the distance you can cover increases by a number of feet equal to your Strength modifier.",
    "At 10th level, you can choose a second option from the Fighting Style class feature.",
    "Starting at 15th level, your weapon attacks score a critical hit on a roll of 18-20.",
    "At 18th level, you attain the pinnacle of resilience in battle. At the start of each of your turns, you regain hit points equal to 5 + your Constitution modifier if you have no more than half of your hit points left. You don't gain this benefit if you have 0 hit points."};
    vector<tuple<int,string,string>> championFeatures;
    for (size_t i = 0; i < championFeatureNames.size(); i++) {
       championFeatures.push_back(make_tuple(championFeatureLevels.at(i),championFeatureNames.at(i),championFeatureDescriptions.at(i)));
    }
    this->subClassesFighter.push_back(new Champion("Champion", championFeatures));
    vector<int> battleMasterFeatureLevels = {3, 3, 3, 7, 7, 7, 10, 10, 15, 15, 15, 18};
    vector<string> battleMasterFeatureNames = {"Student of War", "Combat Superiority", "Maneuvers", "Additional Maneuvers",
    "Additional Superiority Die", "Know Your Enemy", "Additional Maneuvers", "Improved Combat Superiority (d10)", "Additional Maneuvers",
    "Additional Superiority Die", "Relentless", "Improved Combat Superiority (d12)"};
    vector<string> battleMasterFeatureDescriptions = {"At 3rd level, you gain proficiency with one type of artisan's tools of your choice.",
    "When you choose this archetype at 3rd level, you learn maneuvers that are fueled by special dice called superiority dice.\n\nManeuvers. You learn three maneuvers of your choice, which are listed under 'Maneuvers' below. Many maneuvers enhance an attack in some way. You can use only one maneuver per attack.\n\nYou learn two additional maneuvers of your choice at 7th, 10th, and 15th level. Each time you learn new maneuvers, you can also replace one maneuver you know with a different one.\n\nSuperiority Dice. You have four superiority dice, which are d8s. A superiority die is expended when you use it. You regain all of your expended superiority dice when you finish a short or long rest.\n\nYou gain another superiority die at 7th level and one more at 15th level.\n\nSaving Throws. Some of your maneuvers require your target to make a saving throw to resist the maneuver's effects. The saving throw DC is calculated as follows:\n\nManeuver save DC = 8 + Strength or Dexterity modifier (your choice) + Proficiency Bonus",
    "The maneuvers are presented in alphabetical order.\n\nCommander's Strike. When you take the Attack action on your turn, you can forgo one of your attacks and use a bonus action to direct one of your companions to strike. When you do so, choose a friendly creature who can see or hear you and expend one superiority die. That creature can immediately use its reaction to make one weapon attack, adding the superiority die to the attack's damage roll.\n\nDisarming Attack. When you hit a creature with a weapon attack, you can expend one superiority die to attempt to disarm the target, forcing it to drop one item of your choice that it's holding. You add the superiority die to the attack's damage roll, and the target must make a Strength saving throw. On a failed save, it drops the object you choose. The object lands at its feet.\n\nDistracting Strike. When you hit a creature with a weapon attack, you can expend one superiority die to distract the creature, giving your allies an opening. You add the superiority die to the attack's damage roll. The next attack roll against the target by an attacker other than you has advantage if the attack is made before the start of your next turn.\n\nEvasive Footwork. When you move, you can expend one superiority die, rolling the die and adding the number rolled to your AC until you stop moving.\n\nFeinting Attack. You can expend one superiority die and use a bonus action on your turn to feint, choosing one creature within 5 feet of you as your target. You have advantage on your next attack roll against that creature this turn. If that attack hits, add the superiority die to the attack's damage roll.\n\nGoading Attack. When you hit a creature with a weapon attack, you can expend one superiority die to attempt to goad the target into attacking you. You add the superiority die to the attack's damage roll, and the target must make a Wisdom saving throw. On a failed save, the target has disadvantage on all attack rolls against targets other than you until the end of your next turn.\n\nLunging Attack. When you make a melee weapon attack on your turn, you can expend one superiority die to increase your reach for that attack by 5 feet. If you hit, you add the superiority die to the attack's damage roll.\n\nManeuvering Attack. When you hit a creature with a weapon attack, you can expend one superiority die to maneuver one of your comrades into a more advantageous position. You add the superiority die to the attack's damage roll, and you choose a friendly creature who can see or hear you. That creature can use its reaction to move up to half its speed without provoking opportunity attacks from the target of your attack.\n\nMenacing Attack. When you hit a creature with a weapon attack, you can expend one superiority die to attempt to frighten the target. You add the superiority die to the attack's damage roll, and the target must make a Wisdom saving throw. On a failed save, it is frightened of you until the end of your next turn.\n\nParry. When another creature damages you with a melee attack, you can use your reaction and expend one superiority die to reduce the damage by the number you roll on your superiority die + your Dexterity modifier.\n\nPrecision Attack. When you make a weapon attack roll against a creature, you can expend one superiority die to add it to the roll. You can use this maneuver before or after making the attack roll, but before any effects of the attack are applied.\n\nPushing Attack. When you hit a creature with a weapon attack, you can expend one superiority die to attempt to drive the target back. You add the superiority die to the attack's damage roll, and if the target is Large or smaller, it must make a Strength saving throw. On a failed save, you push the target up to 15 feet away from you.\n\nRally. On your turn, you can use a bonus action and expend one superiority die to bolster the resolve of one of your companions. When you do so, choose a friendly creature who can see or hear you. That creature gains temporary hit points equal to the superiority die roll + your Charisma modifier.\n\nRiposte. When a creature misses you with a melee attack, you can use your reaction and expend one superiority die to make a melee weapon attack against the creature. If you hit, you add the superiority die to the attack's damage roll.\n\nSweeping Attack. When you hit a creature with a melee weapon attack, you can expend one superiority die to attempt to damage another creature with the same attack. Choose another creature within 5 feet of the original target and within your reach. If the original attack roll would hit the second creature, it takes damage equal to the number you roll on your superiority die. The damage is of the same type dealt by the original attack.\n\nTrip Attack. When you hit a creature with a weapon attack, you can expend one superiority die to attempt to knock the target down. You add the superiority die to the attack's damage roll, and if the target is Large or smaller, it must make a Strength saving throw. On a failed save, you knock the target prone.","At 7th level, you learn two additional maneuvers of your choice.","You gain another superiority die at 7th level.","If you spend at least 1 minute observing or interacting with another creature outside combat, you can learn certain information about its capabilities compared to your own. The DM tells you if the creature is your equal, superior, or inferior in regard to two of the following characteristics of your choice:\n\n*Strength score\n*Dexterity score\n*Constitution score\n*Armor Class\n*Current hit points\n*Total class levels (if any)\n*Fighter class levels (if any)", "At 10th level, you learn two additional maneuvers of your choice.", "At 10th level, your superiority dice turn into d10s.", "At 15th level, you learn two additional maneuvers of your choice.", "You gain another superiority die at 15th level.", "Starting at 15th level, when you roll initiative and have no superiority dice remaining, you regain 1 superiority die.", "At 18th level, your superiority dice turn into d12s."};
    vector<tuple<int,string,string>> battleMasterFeatures;
    for (size_t i = 0; i < battleMasterFeatureNames.size(); i++) {
        battleMasterFeatures.push_back(make_tuple(battleMasterFeatureLevels.at(i),battleMasterFeatureNames.at(i),battleMasterFeatureDescriptions.at(i)));
    }
    this->subClassesFighter.push_back(new BattleMaster("Battle Master", battleMasterFeatures));

    //implementação subclasses rogue
    vector<int> assassinFeatureLevels = {3, 3, 9, 13, 17};
    vector<string> assassinFeatureNames = {"Assassinate", "Bonus Proficiencies", "Infiltration Expertise", "Impostor", "Death Strike"};
    vector<string> assassinFeatureDescriptions = {"Starting at 3rd level, you are at your deadliest when you get the drop on your enemies. You have advantage on attack rolls against any creature that hasn't taken a turn in the combat yet. In addition, any hit you score against a creature that is surprised is a critical hit.", "When you choose this archetype at 3rd level, you gain proficiency with the disguise kit and the poisoner's kit.", "Starting at 9th level, you can unfailingly create false identities for yourself. You must spend seven days and 25 gp to establish the history, profession, and affiliations for an identity. You can't establish an identity that belongs to someone else. For example, you might acquire appropriate clothing, letters of introduction, and official-looking certification to establish yourself as a member of a trading house from a remote city so you can insinuate yourself into the company of other wealthy merchants.\n\nThereafter, if you adopt the new identity as a disguise, other creatures believe you to be that person until given an obvious reason not to.", "At 13th level, you gain the ability to unerringly mimic another person's speech, writing, and behavior. You must spend at least three hours studying these three components of the person's behavior, listening to speech, examining handwriting, and observing mannerism.\n\nYour ruse is indiscernible to the casual observer. If a wary creature suspects something is amiss, you have advantage on any Charisma (Deception) check you make to avoid detection.", "Starting at 17th level, you become a master of instant death. When you attack and hit a creature that is surprised, it must make a Constitution saving throw (DC 8 + your Dexterity modifier + your proficiency bonus). On a failed save, double the damage of your attack against the creature."};
    vector<tuple<int,string,string>> assassinFeatures;
    for (size_t i = 0; i < assassinFeatureNames.size(); i++) {
        assassinFeatures.push_back(make_tuple(assassinFeatureLevels.at(i),assassinFeatureNames.at(i),assassinFeatureDescriptions.at(i)));
    }
    this->subClassesRogue.push_back(new Assassin("Assassin", assassinFeatures));
    vector<int> thiefFeatureLevels = {3, 3, 9, 13, 17};
    vector<string> thiefFeatureNames = {"Fast Hands", "Second-Story Work", "Supreme Sneak", "Use Magic Device", "Thief's Reflexes"};
    vector<string> thiefFeatureDescriptions = {"Starting at 3rd level, you can use the bonus action granted by your Cunning Action to make a Dexterity (Sleight of Hand) check, use your thieves' tools to disarm a trap or open a lock, or take the Use an Object action.", "When you choose this archetype at 3rd level, you gain the ability to climb faster than normal; climbing no longer costs you extra movement.\n\nIn addition, when you make a running jump, the distance you cover increases by a number of feet equal to your Dexterity modifier.", "Starting at 9th level, you have advantage on a Dexterity (Stealth) check if you move no more than half your speed on the same turn.", "By 13th level, you have learned enough about the workings of magic that you can improvise the use of items even when they are not intended for you. You ignore all class, race, and level requirements on the use of magic items.", "When you reach 17th level, you have become adept at laying ambushes and quickly escaping danger. You can take two turns during the first round of any combat. You take your first turn at your normal initiative and your second turn at your initiative minus 10. You can't use this feature when you are surprised."};
    vector<tuple<int,string,string>> thiefFeatures;
    for (size_t i = 0; i < thiefFeatureNames.size(); i++) {
        thiefFeatures.push_back(make_tuple(thiefFeatureLevels.at(i),thiefFeatureNames.at(i),thiefFeatureDescriptions.at(i)));
    }
    this->subClassesRogue.push_back(new Thief("Thief", thiefFeatures));

    //implementação subclasses wizard
    vector<int> transmutationFeatureLevels = {2, 2, 6, 10, 14};
    vector<string> transmutationFeatureNames = {"Transmutation Savant", "Minor Alchemy", "Transmuter's Stone", "Shapechanger", "Master Transmuter"};
    vector<string> transmutationFeatureDescriptions = {"Beginning when you select this school at 2nd level, the gold and time you must spend to copy a transmutation spell into your spellbook is halved.", "Starting at 2nd level when you select this school, you can temporarily alter the physical properties of one nonmagical object, changing it from one substance into another. You perform a special alchemical procedure on one object composed entirely of wood, stone (but not a gemstone), iron, copper, or silver, transforming it into a different one of those materials. For each 10 minutes you spend performing the procedure, you can transform up to 1 cubic foot of material. After 1 hour, or until you lose your concentration (as if you were concentrating on a spell), the material reverts to its original substance.", "Starting at 6th level, you can spend 8 hours creating a transmuter's stone that stores transmutation magic. You can benefit from the stone yourself or give it to another creature. A creature gains a benefit of your choice as long as the stone is in the creature's possession. When you create the stone, choose the benefit from the following options:\n\n*Darkvision out to a range of 60 feet, as described in chapter 8.\n*An increase to speed of 10 feet while the creature is unencumbered.\n*Proficiency in Constitution saving throws.\n*Resistance to acid, cold, fire, lightning, or thunder damage (your choice whenever you choose this benefit).\nEach time you cast a transmutation spell of 1st level or higher, you can change the effect of your stone if the stone is on your person.\nIf you create a new transmuter's stone, the previous one ceases to function.", "At 10th level, you add the polymorph spell to your spellbook, if it is not there already. You can cast polymorph without expending a spell slot. When you do so, you can target only yourself and transform into a beast whose challenge rating is 1 or lower.\n\nOnce you cast polymorph in this way, you can't do so again until you finish a short or long rest, though you can still cast it normally using an available spell slot.", "Starting at 14th level, you can use your action to consume the reserve of transmutation magic stored within your transmuter's stone in a single burst. When you do so, choose one of the following effects. Your transmuter's stone is destroyed and can't be remade until you finish a long rest.\n\nMajor Transformation. You can transmute one nonmagical object—no larger than a 5-foot cube—into another nonmagical object of similar size and mass and of equal or lesser value. You must spend 10 minutes handling the object to transform it.\n\nPanacea. You remove all curses, diseases, and poisons affecting a creature that you touch with the transmuter's stone. The creature also regains all its hit points.\n\nRestore Life. You cast the raise dead spell on a creature you touch with the transmuter's stone, without expending a spell slot or needing to have the spell in your spellbook.\n\nRestore Youth. You touch the transmuter's stone to a willing creature, and that creature's apparent age is reduced by 3d10 years, to a minimum of 13 years. This effect doesn't extend the creature's lifespan."};
    vector<tuple<int,string,string>> transmutationFeatures;
    for (size_t i = 0; i < transmutationFeatureNames.size(); i++) {
        transmutationFeatures.push_back(make_tuple(transmutationFeatureLevels.at(i),transmutationFeatureNames.at(i),transmutationFeatureDescriptions.at(i)));
    }
    this->subClassesWizard.push_back(new Transmutation("Transmutation School", transmutationFeatures));
    vector<int> abjurationFeatureLevels = {2, 2, 6, 10, 14};
    vector<string> abjurationFeatureNames = {"Abjuration Savant", "Arcane Ward", "Projected Ward", "Improved Abjuration", "Spell Resistance"};
    vector<string> abjurationFeatureDescriptions = {"Beginning when you select this school at 2nd level, the gold and time you must spend to copy an abjuration spell into your spellbook is halved.", "Starting at 2nd level, you can weave magic around yourself for protection. When you cast an abjuration spell of 1st level or higher, you can simultaneously use a strand of the spell's magic to create a magical ward on yourself that lasts until you finish a long rest. The ward has a hit point maximum equal to twice your wizard level + your Intelligence modifier. Whenever you take damage, the ward takes the damage instead. If this damage reduces the ward to 0 hit points, you take any remaining damage.\n\nWhile the ward has 0 hit points, it can't absorb damage, but its magic remains. Whenever you cast an abjuration spell of 1st level or higher, the ward regains a number of hit points equal to twice the level of the spell.\n\nOnce you create the ward, you can't create it again until you finish a long rest.", "Starting at 6th level, when a creature that you can see within 30 feet of you takes damage, you can use your reaction to cause your Arcane Ward to absorb that damage. If this damage reduces the ward to 0 hit points, the warded creature takes any remaining damage.", "Beginning at 10th level, when you cast an abjuration spell that requires you to make an ability check as a part of casting that spell (as in counterspell and dispel magic), you add your proficiency bonus to that ability check.", "Starting at 14th level, you have advantage on saving throws against spells.\nFurthermore, you have resistance against the damage of spells."};
    vector<tuple<int,string,string>> abjurationFeatures;
    for (size_t i = 0; i < abjurationFeatureNames.size(); i++) {
        abjurationFeatures.push_back(make_tuple(abjurationFeatureLevels.at(i),abjurationFeatureNames.at(i),abjurationFeatureDescriptions.at(i)));
    }
    this->subClassesWizard.push_back(new Abjuration("Abjuration School", abjurationFeatures));

    //implementação subclasses cleric
    vector<int> lifeFeatureLevels = {1, 1, 2, 6, 8, 17};
    vector<string> lifeFeatureNames = {"Bonus Proficiency", "Disciple of Life", "Channel Divinity: Preserve Life", "Blessed Healer", "Divine Strike", "Supreme Healing"};
    vector<string> lifeFeatureDescriptions = {"When you choose this domain at 1st level, you gain proficiency with heavy armor.", "Also starting at 1st level, your healing spells are more effective. Whenever you use a spell of 1st level or higher to restore hit points to a creature, the creature regains additional hit points equal to 2 + the spell's level.\n\nAt each indicated cleric level, you add the listed spells to your spells prepared.\nLife Domain Spells\nCleric Level\nSpells\n1st	bless, cure wounds\n3rd	lesser restoration, spiritual weapon\n5th beacon of hope, revivify\n7th	death ward, guardian of faith\n9th	mass cure wounds, raise dead", "Starting at 2nd level, you can use your Channel Divinity to heal the badly injured.\nAs an action, you present your holy symbol and evoke healing energy that can restore a number of hit points equal to five times your cleric level. Choose any creatures within 30 feet of you, and divide those hit points among them. This feature can restore a creature to no more than half of its hit point maximum. You can't use this feature on an undead or a construct.", "Beginning at 6th level, the healing spells you cast on others heal you as well. When you cast a spell of 1st level or higher that restores hit points to a creature other than you, you regain hit points equal to 2 + the spell's level.", "At 8th level, you gain the ability to infuse your weapon strikes with divine energy. Once on each of your turns when you hit a creature with a weapon attack, you can cause the attack to deal an extra 1d8 radiant damage to the target. When you reach 14th level, the extra damage increases to 2d8.", "Starting at 17th level, when you would normally roll one or more dice to restore hit points with a spell, you instead use the highest number possible for each die. For example, instead of restoring 2d6 hit points to a creature, you restore 12."};
    vector<tuple<int,string,string>> lifeFeatures;
    for (size_t i = 0; i < lifeFeatureNames.size(); i++) {
        lifeFeatures.push_back(make_tuple(lifeFeatureLevels.at(i),lifeFeatureNames.at(i),lifeFeatureDescriptions.at(i)));
    }
    this->subClassesCleric.push_back(new Life("Life Domain", lifeFeatures));
    vector<int> lightFeatureLevels = {1, 1, 2, 6, 8, 17};
    vector<string> lightFeatureNames = {"Bonus Cantrip", "Warding Flare", "Channel Divinity: Radiance of the Dawn", "Improved Flare", "Potent Spellcasting", "Corona of Light"};
    vector<string> lightFeatureDescriptions = {"When you choose this domain at 1st level, you gain the light cantrip if you don't already know it. This cantrip doesn't count against the number of cleric cantrips you know.", "Also at 1st level, you can interpose divine light between yourself and an attacking enemy. When you are attacked by a creature within 30 feet of you that you can see, you can use your reaction to impose disadvantage on the attack roll, causing light to flare before the attacker before it hits or misses. An attacker that can't be blinded is immune to this feature.\n\nYou can use this feature a number of times equal to your Wisdom modifier (a minimum of once). You regain all expended uses when you finish a long rest.\n\nAt each indicated cleric level, you add the listed spells to your spells prepared.\n\nLight Domain Spells\nCleric Level	\nSpells\n1st	burning hands, faerie fire\n3rd	flaming sphere, scorching ray\n5th	daylight, fireball\n7th	guardian of faith, wall of fire\n9th	flame strike, scrying", "Starting at 2nd level, you can use your Channel Divinity to harness sunlight, banishing darkness and dealing radiant damage to your foes.\n\nAs an action, you present your holy symbol, and any magical darkness within 30 feet of you is dispelled. Additionally, each hostile creature within 30 feet of you must make a Constitution saving throw. A creature takes radiant damage equal to 2d10 + your cleric level on a failed saving throw, and half as much damage on a successful one. A creature that has total cover from you is not affected.", "Starting at 6th level, you can also use your Warding Flare feature when a creature that you can see within 30 feet of you attacks a creature other than you.", "Starting at 8th level, you add your Wisdom modifier to the damage you deal with any cleric cantrip.", "Starting at 17th level, you can use your action to activate an aura of sunlight that lasts for 1 minute or until you dismiss it using another action. You emit bright light in a 60-foot radius and dim light 30 feet beyond that. Your enemies in the bright light have disadvantage on saving throws against any spell that deals fire or radiant damage."};
    vector<tuple<int,string,string>> lightFeatures;
    for (size_t i = 0; i < lightFeatureNames.size(); i++) {
        lightFeatures.push_back(make_tuple(lightFeatureLevels.at(i),lightFeatureNames.at(i),lightFeatureDescriptions.at(i)));
    }
    this->subClassesCleric.push_back(new Light("Light Domain", lightFeatures));

    QPushButton *refreshList = new QPushButton("Update");
    refreshList->setFixedSize(200, 40);

    QPushButton *next = new QPushButton("Next");
    next->setFixedSize(200, 40);
    next->setVisible(false);

    QListWidget *list = new QListWidget;
    QTextBrowser *desc = new QTextBrowser;
    connect(refreshList, &QPushButton::clicked, this, [=](){
        if(myCharacter.GetCharacterClass().getName() == "Fighter"){
            list->clear();
            for (auto& subclass : subClassesFighter) {
                list->addItem(QString::fromStdString(subclass->GetName()));
            }
            connect(list, &QListWidget::itemSelectionChanged, this, [=]() {
                QListWidgetItem *currentItem = list->currentItem();
                if (!currentItem) return;

                QString name = currentItem->text();
                for (const auto &subclass : subClassesFighter) {
                    if (QString::fromStdString(subclass->GetName()) == name) {
                        stringstream stream;
                        for (size_t i = 0; i < subclass->getFeatures().size(); i++){
                            stream << "Level " << subclass->getFeatureLevel(i) << ": " << subclass->getFeatureName(i) << endl << subclass->getFeatureDescription(i) << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl;
                        }
                        QString fullText = QString::fromStdString(stream.str());
                        desc->setText(fullText);

                        this->myCharacter.SetCharacterSubClass(*subclass);
                        next->setVisible(true);
                        qDebug() << "Subclasse selecionada:" << QString::fromStdString(myCharacter.GetCharacterSubClass().GetName());
                        qDebug() << "Level: " << myCharacter.GetLevel();
                        break;
                    }
                }
            });
        }
        else if(myCharacter.GetCharacterClass().getName() == "Rogue"){
            list->clear();
            for (auto& subclass : subClassesRogue) {
                list->addItem(QString::fromStdString(subclass->GetName()));
            }
            connect(list, &QListWidget::itemSelectionChanged, this, [=]() {
                QListWidgetItem *currentItem = list->currentItem();
                if (!currentItem) return;

                QString name = currentItem->text();
                for (const auto &subclass : subClassesRogue) {
                    if (QString::fromStdString(subclass->GetName()) == name) {
                        stringstream stream;
                        for (size_t i = 0; i < subclass->getFeatures().size(); i++){
                            stream << "Level " << subclass->getFeatureLevel(i) << ": " << subclass->getFeatureName(i) << endl << subclass->getFeatureDescription(i) << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl;
                        }
                        QString fullText = QString::fromStdString(stream.str());
                        desc->setText(fullText);

                        this->myCharacter.SetCharacterSubClass(*subclass);
                        next->setVisible(true);
                        qDebug() << "Subclasse selecionada:" << QString::fromStdString(myCharacter.GetCharacterSubClass().GetName());
                        qDebug() << "Level: " << myCharacter.GetLevel();
                        break;
                    }
                }
            });
        }
        else if(myCharacter.GetCharacterClass().getName() == "Wizard"){
            list->clear();
            for (auto& subclass : subClassesWizard) {
                list->addItem(QString::fromStdString(subclass->GetName()));
            }
            connect(list, &QListWidget::itemSelectionChanged, this, [=]() {
                QListWidgetItem *currentItem = list->currentItem();
                if (!currentItem) return;

                QString name = currentItem->text();
                for (const auto &subclass : subClassesWizard) {
                    if (QString::fromStdString(subclass->GetName()) == name) {
                        stringstream stream;
                        for (size_t i = 0; i < subclass->getFeatures().size(); i++){
                            stream << "Level " << subclass->getFeatureLevel(i) << ": " << subclass->getFeatureName(i) << endl << subclass->getFeatureDescription(i) << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl;
                        }
                        QString fullText = QString::fromStdString(stream.str());
                        desc->setText(fullText);

                        this->myCharacter.SetCharacterSubClass(*subclass);
                        next->setVisible(true);
                        qDebug() << "Subclasse selecionada:" << QString::fromStdString(myCharacter.GetCharacterSubClass().GetName());
                        qDebug() << "Level: " << myCharacter.GetLevel();
                        break;
                    }
                }
            });
        }
        else if(myCharacter.GetCharacterClass().getName() == "Cleric"){
            list->clear();
            for (auto& subclass : subClassesCleric) {
                list->addItem(QString::fromStdString(subclass->GetName()));
            }
            connect(list, &QListWidget::itemSelectionChanged, this, [=]() {
                QListWidgetItem *currentItem = list->currentItem();
                if (!currentItem) return;

                QString name = currentItem->text();
                for (const auto &subclass : subClassesCleric) {
                    if (QString::fromStdString(subclass->GetName()) == name) {
                        stringstream stream;
                        for (size_t i = 0; i < subclass->getFeatures().size(); i++){
                            stream << "Level " << subclass->getFeatureLevel(i) << ": " << subclass->getFeatureName(i) << endl << subclass->getFeatureDescription(i) << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl;
                        }
                        QString fullText = QString::fromStdString(stream.str());
                        desc->setText(fullText);

                        this->myCharacter.SetCharacterSubClass(*subclass);
                        next->setVisible(true);
                        qDebug() << "Subclasse selecionada:" << QString::fromStdString(myCharacter.GetCharacterSubClass().GetName());
                        qDebug() << "Level: " << myCharacter.GetLevel();
                        break;
                    }
                }
            });
        }
    });
    QLabel *secondandahalfStep = new QLabel("2.5. Choose Your Subclass:");
    secondandahalfStep->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    secondandahalfStep->setStyleSheet("font-size: 18px; font-weight: bold;");
    secondandahalfStep->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    layout->addWidget(secondandahalfStep);
    layout->addWidget(list, 1);
    layout->addWidget(desc, 3);
    layout->addWidget(refreshList,0, Qt::AlignLeft);
    layout->addWidget(next, 0, Qt::AlignRight);
    page->setLayout(layout);

    connect(next, &QPushButton::clicked, this, &MainWindow::goToBackgroundSelection);

    return page;
}

QWidget *MainWindow::createBackgroundSelectionPage(){
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    backgrounds.push_back(Background("Acolyte", "You have spent your life in the service of a temple to a specific god or pantheon of gods. You act as an intermediary between the realm of the holy and the mortal world, performing sacred rites and offering sacrifices in order to conduct worshipers into the presence of the divine. You are not necessarily a cleric—performing sacred rites is not the same thing as channeling divine power.", "Feature: Shelter of the Faithful\nAs an acolyte, you command the respect of those who share your faith, and you can perform the religious ceremonies of your deity. You and your adventuring companions can expect to receive free healing and care at a temple, shrine, or other established presence of your faith, though you must provide any material components needed for spells. Those who share your religion will support you (but only you) at a modest lifestyle. You might also have ties to a specific temple dedicated to your chosen deity or pantheon, and you have a residence there. This could be the temple where you used to serve, if you remain on good terms with it, or a temple where you have found a new home. While near your temple, you can call upon the priests for assistance, provided the assistance you ask for is not hazardous and you remain in good standing with your temple."));
    backgrounds.push_back(Background("Charlatan", "You have always had a way with people. You know what makes them tick, you can tease out their hearts' desires after a few minutes of conversation, and with a few leading questions you can read like they were children's books. It's a useful talent, and one that you're perfectly willing to use for your advantage.\nYou know what people want and you deliver, or rather, you promise to deliver. Common sense should steer people away from things that sound too good to be true, but common sense seems to be in short supply when you're around. The bottle of pink-colored liquid will surely cure that unseemly rash, this ointment–nothing more than a bit of fat with a sprinkle of silver dust–can restore youth and vigor, and there's a bridge in the city that just happens to be for sale. These marvels sound implausible, but you can make them sound like the real deal.", "Feature: False Identity\nYou have created a second identity that includes documentation, established acquaintances, and disguises that allow you to assume that persona. Additionally, you can forge documents including official papers and personal letters, as long as you have seen an example of the kind of document or the handwriting you are trying to copy."));
    backgrounds.push_back(Background("Criminal", "You are an experienced criminal with a history of breaking the law. You have spent a lot of time among other criminals and still have contacts within the criminal underworld. You're far closer than most people to the world of murder, theft, and violence that pervades the underbelly of civilization, and you have survived up to this point by flouting the rules and regulations of society.", "Feature: Criminal Contact\nYou have a reliable and trustworthy contact who acts as your liaison to a network of other criminals. You know how to get messages to and from your contact, even over great distances; specifically, you know the local messengers, corrupt caravan masters, and seedy sailors who can deliver messages for you."));
    backgrounds.push_back(Background("Folk Hero", "You come from a humble social rank, but you are destined for so much more. Already the people of your home village regard you as their champion, and your destiny calls you to stand against the tyrants and monsters that threaten the common folk everywhere.", "Feature: Rustic Hospitality\nSince you come from the ranks of the common folk, you fit in among them with ease. You can find a place to hide, rest, or recuperate among other commoners, unless you have shown yourself to be a danger to them. They will shield you from the law or anyone else searching for you, though they will not risk their lives for you."));
    backgrounds.push_back(Background("Guild Artisan", "You are a member of an artisan's guild, skilled in a particular field and closely associated with other artisans. You are a well-established part of the mercantile world, freed by talent and wealth from the constraints of a feudal social order. You learned your skills as an apprentice to a master artisan, under the sponsorship of your guild, until you became a master in your own right.", "Feature: Guild Membership\nAs an established and respected member of a guild, you can rely on certain benefits that membership provides. Your fellow guild members will provide you with lodging and food if necessary, and pay for your funeral if needed. In some cities and towns, a guildhall offers a central place to meet other members of your profession, which can be a good place to meet potential patrons, allies, or hirelings.\nGuilds often wield tremendous political power. If you are accused of a crime, your guild will support you if a good case can be made for your innocence or the crime is justifiable. You can also gain access to powerful political figures through the guild, if you are a member in good standing. Such connections might require the donation of money or magic items to the guild's coffers.\nYou must pay dues of 5 gp per month to the guild. If you miss payments, you must make up back dues to remain in the guild's good graces."));
    backgrounds.push_back(Background("Noble", "You understand wealth, power, and privilege. You carry a noble title, and your family owns land, collects taxes, and wields significant political influence. You might be a pampered aristocrat unfamiliar with work or discomfort, a former merchant just elevated to the nobility, or a disinherited scoundrel with a disproportionate sense of entitlement. Or you could be an honest, hard-working landowner who cares deeply about the people who live and work on your land, keenly aware of your responsibility to them.\nWork with your DM to come up with an appropriate title and determine how much authority that title carries. A noble title doesn't stand on its own—it's connected to an entire family, and whatever title you hold, you will pass it down to your own children. Not only do you need to determine your noble title, but you should also work with the DM to describe your family and their influence on you.", "Feature: Position of Privilege\nThanks to your noble birth, people are inclined to think the best of you. You are welcome in high society, and people assume you have the right to be wherever you are. The common folk make every effort to accommodate you and avoid your displeasure, and other people of high birth treat you as a member of the same social sphere. You can secure an audience with a local noble if you need to."));
    backgrounds.push_back(Background("Sage", "You spent years learning the lore of the multiverse. You scoured manuscripts, studied scrolls, and listened to the greatest experts on the subjects that interest you. Your efforts have made you a master in your fields of study.", "Feature: Researcher\nWhen you attempt to learn or recall a piece of lore, if you do not know that information, you often know where and from whom you can obtain it. Usually, this information comes from a library, scriptorium, university, or a sage or other learned person or creature. Your DM might rule that the knowledge you seek is secreted away in an almost inaccessible place, or that it simply cannot be found. Unearthing the deepest secrets of the multiverse can require an adventure or even a whole campaign."));
    backgrounds.push_back(Background("Soldier", "War has been your life for as long as you care to remember. You trained as a youth, studied the use of weapons and armor, learned basic survival techniques, including how to stay alive on the battlefield. You might have been part of a standing national army or a mercenary company, or perhaps a member of a local militia who rose to prominence during a recent war.\nWhen you choose this background, work with your DM to determine which military organization you were a part of, how far through its ranks you progressed, and what kind of experiences you had during your military career. Was it a standing army, a town guard, or a village militia? Or it might have been a noble's or merchant's private army, or a mercenary company.", "Feature: Military Rank\nYou have a military rank from your career as a soldier. Soldiers loyal to your former military organization still recognize your authority and influence, and they defer to you if they are of a lower rank. You can invoke your rank to exert influence over other soldiers and requisition simple equipment or horses for temporary use. You can also usually gain access to friendly military encampments and fortresses where your rank is recognized."));

    QListWidget *list = new QListWidget;
    QTextBrowser *desc = new QTextBrowser;

    QPushButton *next = new QPushButton("Next");
    next->setFixedSize(200, 40);
    next->setVisible(false);
    list->clear();

    for (auto& background : backgrounds) {
        list->addItem(QString::fromStdString(background.getName()));
    }

    connect(list, &QListWidget::itemSelectionChanged, this, [=]() {
        QListWidgetItem *currentItem = list->currentItem();
        if (!currentItem) return;

        QString name = currentItem->text();
        for (const auto &background : backgrounds) {
            if (QString::fromStdString(background.getName()) == name) {
                QString fullText = QString::fromStdString(background.getDescription() + "\n\n" + background.getFeature());
                desc->setText(fullText);

                this->myCharacter.SetBackground(background);
                next->setVisible(true);
                qDebug() << "Background selecionado:" << QString::fromStdString(myCharacter.GetBackground().getName());
                break;
            }
        }
    });
    QLabel *thirdStep = new QLabel("3. Choose Your Background:");
    thirdStep->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    thirdStep->setStyleSheet("font-size: 18px; font-weight: bold;");
    thirdStep->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    layout->addWidget(thirdStep);
    layout->addWidget(list, 1);
    layout->addWidget(desc, 3);
    layout->addWidget(next, 0, Qt::AlignRight);
    page->setLayout(layout);

    connect(next, &QPushButton::clicked, this, &MainWindow::goToSpeciesSelection);

    return page;
}

QWidget *MainWindow::createSpeciesSelectionPage(){
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    vector<string> speciesNames = {"Human", "Elf", "Dwarf", "Halfling", "Tiefling", "Half-Orc", "Gnome"};
    vector<string> speciesFeatures = {"Ability Scores: Strength +1; Dexterity +1; Constitution +1; Intelligence +1; Wisdom +1; Charisma +1\nCreature Type: Humanoid\nSize: Medium\nSpeed: 30 feet\n\nAge. Humans reach adulthood in their late teens and live less than a century.\n\nSize. Humans vary widely in height and build, from barely 5 feet to well over 6 feet tall. Regardless of your position in that range, your size is Medium.\n\nLanguages. You can speak, read, and write Common and one extra language of your choice. Humans typically learn the languages of other peoples they deal with, including obscure dialects. They are fond of sprinkling their speech with words borrowed from other tongues: Orc curses, Elvish musical expressions, Dwarvish military phrases, and so on.",
    "Ability Scores: Dexterity +2\nCreature Type: Humanoid\nSize: Medium\nSpeed: 30 feet\n\nAge. Although elves reach physical maturity at about the same age as humans, the elven understanding of adulthood goes beyond physical growth to encompass worldly experience. An elf typically claims adulthood and an adult name around the age of 100 and can live to be 750 years old.\n\nSize. Elves range from under 5 to over 6 feet tall and have slender builds. Your size is Medium.\n\nDarkvision. Accustomed to twilit forests and the night sky, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can't discern color in darkness, only shades of gray.\n\nKeen Senses. You have proficiency in the Perception skill.\n\nFey Ancestry. You have advantage on saving throws against being charmed, and magic can't put you to sleep.\n\nTrance. Elves don't need to sleep. Instead, they meditate deeply, remaining semiconscious, for 4 hours a day. (The Common word for such meditation is 'trance.') While meditating, you can dream after a fashion; such dreams are actually mental exercises that have become reflexive through years of practice. After resting in this way, you gain the same benefit that a human does from 8 hours of sleep.\n\nIf you meditate during a long rest, you finish the rest after only 4 hours. You otherwise obey all the rules for a long rest; only the duration is changed.\n\nLanguages. You can speak, read, and write Common and Elvish. Elvish is fluid, with subtle intonations and intricate grammar. Elven literature is rich and varied, and their songs and poems are famous among other races. Many bards learn their language so they can add Elvish ballads to their repertoires.",
    "Ability Scores: Constitution +2\nCreature Type: Humanoid\nSize: Medium\nSpeed: 25 feet\n\nAge. Dwarves mature at the same rate as humans, but they're considered young until they reach the age of 50. On average, they live about 350 years.\n\nSize. Dwarves stand between 4 and 5 feet tall and average about 150 pounds. Your size is Medium.\n\nSpeed. Your speed is not reduced by wearing heavy armor.\n\nDarkvision. Accustomed to life underground, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can't discern color in darkness, only shades of gray.\n\nDwarven Resilience. You have advantage on saving throws against poison, and you have resistance against poison damage.\n\nDwarven Combat Training. You have proficiency with the battleaxe, handaxe, light hammer, and warhammer.\n\nTool Proficiency. You gain proficiency with the artisan's tools of your choice: Smith's tools, brewer's supplies, or mason's tools.\n\nStonecunning. Whenever you make an Intelligence (History) check related to the origin of stonework, you are considered proficient in the History skill and add double your proficiency bonus to the check, instead of your normal proficiency bonus.\n\nLanguages. You can speak, read, and write Common and Dwarvish. Dwarvish is full of hard consonants and guttural sounds, and those characteristics spill over into whatever other language a dwarf might speak.",
    "Ability Scores: Dexterity +2\nCreature Type: Humanoid\nSize: Small\nSpeed: 25 feet\n\nAge. A halfling reaches adulthood at the age of 20 and generally lives into the middle of his or her second century.\n\nSize. Halflings average about 3 feet tall and weigh about 40 pounds. Your size is Small.\n\nLucky. When you roll a 1 on an attack roll, ability check, or saving throw, you can reroll the die and must use the new roll.\n\nBrave. You have advantage on saving throws against being frightened.\n\nHalfling Nimbleness. You can move through the space of any creature that is of a size larger than yours.\n\nLanguages. You can speak, read, and write Common and Halfling. The Halfling language isn't secret, but halflings are loath to share it with others. They write very little, so they don't have a rich body of literature. Their oral tradition, however, is very strong. Almost all halflings speak Common to converse with the people in whose lands they dwell or through which they are traveling.",
    "Ability Scores: Charisma +2; Intelligence +1\nCreature Type: Humanoid\nSize: Medium\nSpeed: 30 feet\n\nAge. Tieflings mature at the same rate as humans but live a few years longer.\n\nSize. Tieflings are about the same size and build as humans. Your size is Medium.\n\nDarkvision. Thanks to your infernal heritage, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can't discern color in darkness, only shades of gray.\n\nHellish Resistance. You have resistance to fire damage.\n\nInfernal Legacy. You know the thaumaturgy cantrip. Once you reach 3rd level, you can cast the hellish rebuke spell as a 2nd-level spell with this trait; you regain the ability to cast it when you finish a long rest. Once you reach 5th level, you can also cast the darkness spell once per day with this trait; you regain the ability to cast it when you finish a long rest. Charisma is your spellcasting ability for these spells.\n\nLanguages. You can speak, read, and write Common and Infernal.",
    "Ability Scores: Strength +2; Constitution +1\nCreature Type: Humanoid\nSize: Medium\nSpeed: 30 feet\n\nAge. Half-orcs mature a little faster than humans, reaching adulthood around age 14. They age noticeably faster and rarely live longer than 75 years.\n\nSize. Half-orcs are somewhat larger and bulkier than humans, and they range from 5 to well over 6 feet tall. Your size is Medium.\n\nDarkvision. Thanks to your orc blood, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can't discern color in darkness, only shades of gray.\n\nMenacing. You gain proficiency in the Intimidation skill.\n\nRelentless Endurance. When you are reduced to 0 hit points but not killed outright, you can drop to 1 hit point instead. You can't use this feature again until you finish a long rest.\n\nSavage Attacks. When you score a critical hit with a melee weapon attack, you can roll one of the weapon's damage dice one additional time and add it to the extra damage of the critical hit.\n\nLanguages. You can speak, read, and write Common and Orc. Orc is a harsh, grating language with hard consonants. It has no script of its own but is written in the Dwarvish script.",
    "Ability Scores: Intelligence +2\nCreature Type: Humanoid\nSize: Small\nSpeed: 25 feet\n\nTraits\nAge. Gnomes mature at the same rate humans do, and most are expected to settle down into an adult life by around age 40. They can live 350 to almost 500 years.\n\nSize. Gnomes are between 3 and 4 feet tall and average about 40 pounds. Your size is Small.\n\nDarkvision. Accustomed to life underground, you have superior vision in dark and dim conditions. You can see in dim light within 60 feet of you as if it were bright light, and in darkness as if it were dim light. You can't discern color in darkness, only shades of gray.\n\nGnome Cunning. You have advantage on all Intelligence, Wisdom, and Charisma saving throws against magic.\n\nLanguages. You can speak, read, and write Common and Gnomish. The Gnomish language, which uses the Dwarvish script, is renowned for its technical treatises and its catalogs of knowledge about the natural world."};
    vector<vector<pair<string,int>>> speciesAbilityScores;
    vector<pair<string,int>> humanAbilityScores = {make_pair("Strength", 1), make_pair("Dexterity", 1), make_pair("Constitution", 1), make_pair("Wisdom", 1), make_pair("Intelligence", 1), make_pair("Charisma", 1)};
    speciesAbilityScores.push_back(humanAbilityScores);
    vector<pair<string,int>> elfAbilityScores = {make_pair("Dexterity", 2)};
    speciesAbilityScores.push_back(elfAbilityScores);
    vector<pair<string,int>> dwarfAbilityScores = {make_pair("Constitution", 2)};
    speciesAbilityScores.push_back(dwarfAbilityScores);
    vector<pair<string,int>> halflingAbilityScores = {make_pair("Dexterity", 2)};
    speciesAbilityScores.push_back(halflingAbilityScores);
    vector<pair<string,int>> tieflingAbilityScores = {make_pair("Charisma", 2), make_pair("Intelligence", 1)};
    speciesAbilityScores.push_back(tieflingAbilityScores);
    vector<pair<string,int>> half_orcAbilityScores = {make_pair("Strength", 2), make_pair("Constitution", 1)};
    speciesAbilityScores.push_back(half_orcAbilityScores);
    vector<pair<string,int>> gnomeAbilityScores = {make_pair("Intelligence", 2)};
    speciesAbilityScores.push_back(gnomeAbilityScores);
    for (size_t i = 0; i < speciesNames.size(); ++i) {
        Species specie(speciesNames[i], speciesFeatures[i], speciesAbilityScores[i]);
        species.push_back(specie);
    }

    QListWidget *list = new QListWidget;
    QTextBrowser *desc = new QTextBrowser;

    QPushButton *next = new QPushButton("Next");
    next->setFixedSize(200, 40);
    next->setVisible(false);
    list->clear();
    for (auto& species : species) {
        list->addItem(QString::fromStdString(species.GetName()));
    }

    connect(list, &QListWidget::itemSelectionChanged, this, [=]() {
        QListWidgetItem *currentItem = list->currentItem();
        if (!currentItem) return;

        QString name = currentItem->text();
        for (const auto &species : species) {
            if (QString::fromStdString(species.GetName()) == name) {
                QString fullText = QString::fromStdString(species.GetFeatures());
                desc->setText(fullText);

                this->myCharacter.SetSpecies(species);
                next->setVisible(true);
                qDebug() << "Espécie selecionada:" << QString::fromStdString(myCharacter.GetSpecies().GetName());
                qDebug() << "Ability score: " << QString::fromStdString(myCharacter.GetSpecies().GetAbilityScores().at(0).first) << "Bonus: " << (myCharacter.GetSpecies().GetAbilityScores().at(0).second);
                break;
            }
        }
    });

    QLabel *fourthStep = new QLabel("4. Choose Your Species:");
    fourthStep->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    fourthStep->setStyleSheet("font-size: 18px; font-weight: bold;");
    fourthStep->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    layout->addWidget(fourthStep);
    layout->addWidget(list, 1);
    layout->addWidget(desc, 3);
    layout->addWidget(next, 0, Qt::AlignRight);

    page->setLayout(layout);

    connect(next, &QPushButton::clicked, this, &MainWindow::goToAbilityScoresSelection);

    return page;
}

QWidget *MainWindow::createAbilityScoresSelectionPage(){
    QWidget *page = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    QIntValidator *validator = new QIntValidator(1, 20);

    QVBoxLayout *strLayout = new QVBoxLayout;
    QLabel *strLabel = new QLabel("Strength");
    QLineEdit *strEdit = new QLineEdit;
    strEdit->setValidator(validator);
    QLabel *strMod = new QLabel;
    connect(strEdit, &QLineEdit::textChanged, [=](const QString &text) {
        bool ok;
        int value = text.toInt(&ok);
        if (ok) {
            int mod = (value - 10) / 2;
            QString sign = (mod >= 0) ? "+" : "";
            strMod->setText(sign + QString::number(mod));
        } else {
            strMod->setText("Invalid input");
        }
    });
    strEdit->setMaximumSize(80, 20);
    strLabel->setMaximumSize(80, 20);
    strMod->setMaximumSize(80, 20);
    strLayout->addWidget(strLabel);
    strLayout->addWidget(strEdit);
    strLayout->addWidget(strMod);

    QVBoxLayout *dexLayout = new QVBoxLayout;
    QLabel *dexLabel = new QLabel("Dexterity");
    QLineEdit *dexEdit = new QLineEdit;
    dexEdit->setValidator(validator);
    QLabel *dexMod = new QLabel;
    connect(dexEdit, &QLineEdit::textChanged, [=](const QString &text) {
        bool ok;
        int value = text.toInt(&ok);
        if (ok) {
            int mod = (value - 10) / 2;
            QString sign = (mod >= 0) ? "+" : "";
            dexMod->setText(sign + QString::number(mod));
        } else {
            dexMod->setText("Invalid input");
        }
    });
    dexEdit->setMaximumSize(80, 20);
    dexLabel->setMaximumSize(80, 20);
    dexMod->setMaximumSize(80, 20);
    dexLayout->addWidget(dexLabel);
    dexLayout->addWidget(dexEdit);
    dexLayout->addWidget(dexMod);

    QVBoxLayout *conLayout = new QVBoxLayout;
    QLabel *conLabel = new QLabel("Constitution");
    QLineEdit *conEdit = new QLineEdit;
    conEdit->setValidator(validator);
    QLabel *conMod = new QLabel;
    connect(conEdit, &QLineEdit::textChanged, [=](const QString &text) {
        bool ok;
        int value = text.toInt(&ok);
        if (ok) {
            int mod = (value - 10) / 2;
            QString sign = (mod >= 0) ? "+" : "";
            conMod->setText(sign + QString::number(mod));
        } else {
            conMod->setText("Invalid input");
        }
    });
    conEdit->setMaximumSize(80, 20);
    conLabel->setMaximumSize(80, 20);
    conMod->setMaximumSize(80, 20);
    conLayout->addWidget(conLabel);
    conLayout->addWidget(conEdit);
    conLayout->addWidget(conMod);

    QVBoxLayout *wisLayout = new QVBoxLayout;
    QLabel *wisLabel = new QLabel("Wisdom");
    QLineEdit *wisEdit = new QLineEdit;
    wisEdit->setValidator(validator);
    QLabel *wisMod = new QLabel;
    connect(wisEdit, &QLineEdit::textChanged, [=](const QString &text) {
        bool ok;
        int value = text.toInt(&ok);
        if (ok) {
            int mod = (value - 10) / 2;
            QString sign = (mod >= 0) ? "+" : "";
            wisMod->setText(sign + QString::number(mod));
        } else {
            wisMod->setText("Invalid input");
        }
    });
    wisEdit->setMaximumSize(80, 20);
    wisLabel->setMaximumSize(80, 20);
    wisMod->setMaximumSize(80, 20);
    wisLayout->addWidget(wisLabel);
    wisLayout->addWidget(wisEdit);
    wisLayout->addWidget(wisMod);

    QVBoxLayout *intLayout = new QVBoxLayout;
    QLabel *intLabel = new QLabel("Intelligence");
    QLineEdit *intEdit = new QLineEdit;
    intEdit->setValidator(validator);
    QLabel *intMod = new QLabel;
    connect(intEdit, &QLineEdit::textChanged, [=](const QString &text) {
        bool ok;
        int value = text.toInt(&ok);
        if (ok) {
            int mod = (value - 10) / 2;
            QString sign = (mod >= 0) ? "+" : "";
            intMod->setText(sign + QString::number(mod));
        } else {
            intMod->setText("Invalid input");
        }
    });
    intEdit->setMaximumSize(80, 20);
    intLabel->setMaximumSize(80, 20);
    intMod->setMaximumSize(80, 20);
    intLayout->addWidget(intLabel);
    intLayout->addWidget(intEdit);
    intLayout->addWidget(intMod);

    QVBoxLayout *chaLayout = new QVBoxLayout;
    QLabel *chaLabel = new QLabel("Charisma");
    QLineEdit *chaEdit = new QLineEdit;
    chaEdit->setValidator(validator);
    QLabel *chaMod = new QLabel;
    connect(chaEdit, &QLineEdit::textChanged, [=](const QString &text) {
        bool ok;
        int value = text.toInt(&ok);
        if (ok) {
            int mod = (value - 10) / 2;
            QString sign = (mod >= 0) ? "+" : "";
            chaMod->setText(sign + QString::number(mod));
        } else {
            chaMod->setText("Invalid input");
        }
    });
    chaEdit->setMaximumSize(80, 20);
    chaLabel->setMaximumSize(80, 20);
    chaMod->setMaximumSize(80, 20);
    chaLayout->addWidget(chaLabel);
    chaLayout->addWidget(chaEdit);
    chaLayout->addWidget(chaMod);

    QLabel *fifthStep = new QLabel("5. Decide Your Ability Scores");
    fifthStep->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    fifthStep->setStyleSheet("font-size: 18px; font-weight: bold;");
    fifthStep->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    QLabel *speciesScores = new QLabel;
    QPushButton *showBonus = new QPushButton("Show Species Bonus");
    showBonus->setFixedSize(400, 40);
    connect(showBonus, &QPushButton::clicked, this, [=](){
        stringstream stream;
        for (size_t i = 0; i < myCharacter.GetSpecies().GetAbilityScores().size() ; i++) {
            stream << (myCharacter.GetSpecies().GetAbilityScores().at(i).first) << ": +" << (myCharacter.GetSpecies().GetAbilityScores().at(i).second) << endl;
        }
        speciesScores->setText(QString::fromStdString(stream.str()));
    });

    QPushButton *next = new QPushButton("Next");
    next->setFixedSize(400, 40);

    QVBoxLayout *textLayout = new QVBoxLayout;
    textLayout->addWidget(fifthStep);
    textLayout->addWidget(speciesScores);
    textLayout->addWidget(showBonus);
    textLayout->addWidget(next);

    connect(next, &QPushButton::clicked, this, [=] (){
        if ((strMod->text() == "Invalid input" || strMod->text() == "") || (dexMod->text() == "Invalid input" || dexMod->text() == "") || (conMod->text() == "Invalid input" || conMod->text() == "") || (wisMod->text() == "Invalid input" || wisMod->text() == "") || (intMod->text() == "Invalid input" || intMod->text() == "") || (chaMod->text() == "Invalid input" || chaMod->text() == "")){
            QMessageBox::warning(this, "Invalid scores", "Please enter a valid score.");
            return;
        }
        else{
            myCharacter.SetScore(strEdit->text().toInt(), dexEdit->text().toInt(), conEdit->text().toInt(), wisEdit->text().toInt(), intEdit->text().toInt(), chaEdit->text().toInt());
            QMessageBox charCreated;
            charCreated.setWindowTitle("Character created");
            charCreated.setText("Character created succesfully!");
            charCreated.setIcon(QMessageBox::NoIcon);
            charCreated.exec();

            stringstream stream;
            stream << myCharacter.GetName() << ".txt";
            ofstream fileWriter(stream.str());
            if(fileWriter.is_open()){
                fileWriter << myCharacter.GetName() << "|" << myCharacter.GetCharacterClass().getName() << "|" << myCharacter.GetCharacterSubClass().GetName() << "|" << myCharacter.GetBackground().getName() << "|" << myCharacter.GetSpecies().GetName() << "|" << myCharacter.GetLevel() << "|" << myCharacter.GetScore();
            }
            else{
                QMessageBox::warning(this, "Error", "Saving process failed.");
                return;
            }
            fileWriter.close();
            MainWindow::goToHomePage();
        }
    });
    layout->addLayout(textLayout);
    layout->addLayout(strLayout);
    layout->addLayout(dexLayout);
    layout->addLayout(conLayout);
    layout->addLayout(wisLayout);
    layout->addLayout(intLayout);
    layout->addLayout(chaLayout);
    page->setLayout(layout);
    return page;
}

QWidget *MainWindow::createLoadPage(){
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(8);

    QHBoxLayout *headerLayout = new QHBoxLayout;
    headerLayout->setSpacing(10);

    QGridLayout *infoGrid = new QGridLayout;
    infoGrid->setHorizontalSpacing(15);
    infoGrid->setVerticalSpacing(5);

    QString name = QString::fromStdString(myCharacter.GetName()).replace('_', ' ');
    QLabel *charLevel = new QLabel(QString("Level:\n%1").arg(myCharacter.GetLevel()));
    charLevel->setStyleSheet("font-size: 24px; margin: 0;");
    charLevel->setAlignment(Qt::AlignCenter);
    QString HP = (myCharacter.GetCharacterClass().getName() == "Fighter") ? QString("Hit Points:\n%1").arg((10+get<2>(myCharacter.GetScoreRaw().at(2)))+((myCharacter.GetLevel()-1)*(get<2>(myCharacter.GetScoreRaw().at(2))))+((myCharacter.GetLevel()-1)*6)) : QString("Hit Points:\n%1").arg((8+get<2>(myCharacter.GetScoreRaw().at(2)))+((myCharacter.GetLevel()-1)*(get<2>(myCharacter.GetScoreRaw().at(2))))+((myCharacter.GetLevel()-1)*5));
    QLabel *charHP = new QLabel(HP);
    charHP->setStyleSheet("font-size: 24px; margin: 0;");
    charHP->setAlignment(Qt::AlignCenter);
    headerLayout->addWidget(charLevel, 0, Qt::AlignLeft);
    headerLayout->addWidget(charHP, 0, Qt::AlignLeft);
    infoGrid->addWidget(new QLabel("Name: " + name), 0, 0);
    infoGrid->addWidget(new QLabel("Class: " + QString::fromStdString(myCharacter.GetCharacterClass().getName())), 0, 1);
    infoGrid->addWidget(new QLabel("Sub-class: " + QString::fromStdString(myCharacter.GetCharacterSubClass().GetName())), 0, 2);
    infoGrid->addWidget(new QLabel("Species: " + QString::fromStdString(myCharacter.GetSpecies().GetName())), 1, 0);
    infoGrid->addWidget(new QLabel("Background: " + QString::fromStdString(myCharacter.GetBackground().getName())), 1, 1);

    headerLayout->addLayout(infoGrid);
    layout->addLayout(headerLayout);

    QFrame *divider = new QFrame;
    divider->setFrameShape(QFrame::HLine);
    divider->setFrameShadow(QFrame::Sunken);
    layout->addWidget(divider);

    QGridLayout *scoreGrid = new QGridLayout;
    scoreGrid->setHorizontalSpacing(10);
    scoreGrid->setVerticalSpacing(5);
    QString labelStyleScore = "QLabel {""text-align: center;""margin: 2px;""padding: 5px;""border: 1px solid #aaa;""border-radius: 4px;""}";

    for (int i = 0; i < 6; i++) {
        auto scoreData = myCharacter.GetScoreRaw().at(i);
        QString name = QString::fromStdString(get<0>(scoreData));
        QString value = QString::number(get<1>(scoreData));
        QString modifier = (get<2>(scoreData) >= 0) ? QString("+%1").arg(get<2>(scoreData)) : QString::number(get<2>(scoreData));

        QLabel *scoreLabel = new QLabel(QString("<center><b>%1</b><br>%2<br>%3</center>").arg(name).arg(value).arg(modifier));

        scoreLabel->setStyleSheet(labelStyleScore);
        scoreLabel->setAlignment(Qt::AlignCenter);

        scoreGrid->addWidget(scoreLabel, i / 3, i % 3);
    }
    layout->addLayout(scoreGrid);

    //SCROLL AREA INTEIRA
    QScrollArea *scrollAreaFeatures = new QScrollArea;
    scrollAreaFeatures->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollAreaFeatures->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    QWidget *scrollAreaFeaturesContent = new QWidget;
    QVBoxLayout *scrollAreaFeaturesContentLayout = new QVBoxLayout(scrollAreaFeaturesContent);
    scrollAreaFeaturesContentLayout->setContentsMargins(5, 5, 5, 5);
    scrollAreaFeaturesContentLayout->setSpacing(8);
    //CLASS FEATURES
    QLabel *classFeatureTitle = new QLabel("Class Features: ");
    classFeatureTitle->setStyleSheet("font-size: 18px; font-weight: bold;");
    scrollAreaFeaturesContentLayout->addWidget(classFeatureTitle);
    for (size_t i = 0; i < myCharacter.GetCharacterClass().getFeatures().size(); i++){
        if(get<0>(myCharacter.GetCharacterClass().getFeatures().at(i)) <= myCharacter.GetLevel()){
            stringstream stream;
            stream << "Level " << get<0>(myCharacter.GetCharacterClass().getFeatures().at(i)) << ": " << get<1>(myCharacter.GetCharacterClass().getFeatures().at(i)) << endl << get<2>(myCharacter.GetCharacterClass().getFeatures().at(i)) << endl << "-----------------------------------------------------------------------------------------------------------------------------";
            QLabel *featureLabel = new QLabel(QString::fromStdString(stream.str()));
            featureLabel->setWordWrap(true);
            featureLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
            scrollAreaFeaturesContentLayout->addWidget(featureLabel);
        }
    }
    //SUBCLASS FEATURES
    QLabel *subClassFeatureTitle = new QLabel("Sub-class Features: ");
    subClassFeatureTitle->setStyleSheet("font-size: 18px; font-weight: bold;");
    scrollAreaFeaturesContentLayout->addWidget(subClassFeatureTitle);
    for (size_t i = 0; i < myCharacter.GetCharacterSubClass().getFeatures().size(); i++){
        if((myCharacter.GetCharacterSubClass().getFeatureLevel(i)) <= myCharacter.GetLevel()){
            stringstream stream;
            stream << "Level " << myCharacter.GetCharacterSubClass().getFeatureLevel(i) << ": " << myCharacter.GetCharacterSubClass().getFeatureName(i) << endl << myCharacter.GetCharacterSubClass().getFeatureDescription(i) << endl << "-----------------------------------------------------------------------------------------------------------------------------";
            QLabel *featureLabel = new QLabel(QString::fromStdString(stream.str()));
            featureLabel->setWordWrap(true);
            featureLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
            scrollAreaFeaturesContentLayout->addWidget(featureLabel);
        }
    }
    //BACKGROUND FEATURES
    QLabel *backgroundFeatureTitle = new QLabel("Background: ");
    backgroundFeatureTitle->setStyleSheet("font-size: 18px; font-weight: bold;");
    scrollAreaFeaturesContentLayout->addWidget(backgroundFeatureTitle);
    stringstream stream;
    stream << myCharacter.GetBackground().getName() << endl << myCharacter.GetBackground().getDescription() << endl << myCharacter.GetBackground().getFeature();
    QLabel *featureLabel = new QLabel(QString::fromStdString(stream.str()));
    featureLabel->setWordWrap(true);
    featureLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    scrollAreaFeaturesContentLayout->addWidget(featureLabel);
    //SPECIES FEATURES
    QLabel *speciesFeatureTitle = new QLabel("Species: ");
    speciesFeatureTitle->setStyleSheet("font-size: 18px; font-weight: bold;");
    scrollAreaFeaturesContentLayout->addWidget(speciesFeatureTitle);
    stream.clear();
    stream.str("");
    stream << myCharacter.GetSpecies().GetName() << endl << myCharacter.GetSpecies().GetFeatures();
    featureLabel = new QLabel(QString::fromStdString(stream.str()));
    featureLabel->setWordWrap(true);
    featureLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    scrollAreaFeaturesContentLayout->addWidget(featureLabel);
    //ADICIONA O WIDGET
    scrollAreaFeatures->setWidget(scrollAreaFeaturesContent);
    layout->addWidget(scrollAreaFeatures);
    layout->addStretch();


    return page;
}

void MainWindow::goToHomePage(){
    stack->setCurrentIndex(0);
}

void MainWindow::goToLevelAndNameSelection(){
    stack->setCurrentIndex(1);
}

void MainWindow::goToClassSelection(){
    stack->setCurrentIndex(2);
}

void MainWindow::goToSubClassSelection(){
    stack->setCurrentIndex(3);
}

void MainWindow::goToBackgroundSelection(){
    stack->setCurrentIndex(4);
}

void MainWindow::goToSpeciesSelection(){
    stack->setCurrentIndex(5);
}

void MainWindow::goToAbilityScoresSelection(){
    stack->setCurrentIndex(6);
}

void MainWindow::goToLoadCharacter(){
    stack->setCurrentIndex(7);
}

MainWindow::~MainWindow()
{
    for (auto c : classes) {
        delete c;
    }
    for (auto sc : subClassesFighter) {
        delete sc;
    }
    for (auto sc : subClassesRogue) {
        delete sc;
    }
    for (auto sc : subClassesCleric) {
        delete sc;
    }
    for (auto sc : subClassesWizard) {
        delete sc;
    }
    delete ui;
}
