#include "wizardspelllist.h"
#include "ui_wizardspelllist.h"
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
#include <utility>
wizardSpellList::wizardSpellList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::wizardSpellList)
{
    ui->setupUi(this);
    QHBoxLayout *layout = new QHBoxLayout;
    setWindowIcon(QIcon(":/icons/icons/dnd-icon.png"));

    vector<string> wizardLevel1 = {
        "Alarm", "Burning Hands", "Charm Person", "Chromatic Orb", "Color Spray",
        "Comprehend Languages", "Detect Magic", "Disguise Self", "Expeditious Retreat",
        "False Life", "Feather Fall", "Find Familiar", "Fog Cloud", "Grease", "Identify",
        "Illusory Script", "Jump", "Longstrider", "Mage Armor", "Magic Missle",
        "Protection from Evil and Good", "Ray of Sickness", "Shield", "Silent Image",
        "Sleep", "Tasha's Hideous Laughter", "Tensor's Floating Disk", "Thunderwave",
        "Unseen Servant", "Witch Bolt"
    };
    this->Spells.push_back(wizardLevel1);

    vector<string> wizardLevel2 = {
        "Alter Self", "Arcane Lock", "Blindness/Deafness", "Blur", "Cloud of Daggers",
        "Continual Flame", "Crown of Madness", "Darkness", "Darkvision", "Detect Thoughts",
        "Enlarge/Reduce", "Gust of Wind", "Invisibility", "Knock", "Levitate",
        "Locate Object", "Magic Mouth", "Magic Weapon", "Melf's Acid Arrow",
        "Mirror Image", "Misty Step", "Nystul's Magic Aura", "Phantasmal Force",
        "Ray of Enfeeblement", "Rope Trick", "Scorching Ray", "See Invisibility",
        "Shatter", "Spider Climb", "Web"
    };
    this->Spells.push_back(wizardLevel2);

    vector<string> wizardLevel3 = {
        "Animate Dead", "Bestow Curse", "Blink", "Clairvoyance", "Counterspell",
        "Dispel Magic", "Fear", "Feign Death", "Fireball", "Fly", "Gaseous Form",
        "Glyph of Warding", "Haste", "Hunger of Hadar", "Hypnotic Pattern",
        "Leomund's Tiny Hut", "Lightning Bolt", "Magic Circle", "Major Image",
        "Phantom Steed", "Remove Curse", "Sending", "Sleet Storm", "Slow",
        "Stinking Cloud", "Tongues", "Vampiric Touch", "Water Breathing", "Water Walk"
    };
    this->Spells.push_back(wizardLevel3);

    vector<string> wizardLevel4 = {
        "Arcane Eye", "Banishment", "Blight", "Confusion", "Conjure Minor Elementals",
        "Control Water", "Divination", "Evard's Black Tentacles", "Fabricate",
        "Fire Shield", "Freedom of Movement", "Greater Invisibility",
        "Hallucinatory Terrain", "Ice Storm", "Leomund's Secret Chest", "Locate Creature",
        "Mordenkainen's Faithful Hound", "Mordenkainen's Private Sanctum",
        "Otiluke's Resilient Sphere", "Phantasmal Killer", "Polymorph", "Stone Shape",
        "Stoneskin", "Wall of Fire"
    };
    this->Spells.push_back(wizardLevel4);

    vector<string> wizardLevel5 = {
        "Animate Objects", "Cloudkill", "Cone of Cold", "Conjure Elemental",
        "Contact Other Plane", "Creation", "Dominate Person", "Dream", "Geas",
        "Hold Monster", "Legend Lore", "Mislead", "Modify Memory", "Passwall",
        "Planar Binding", "Raise Dead", "Rary's Telepathic Bond", "Scrying",
        "Seeming", "Telekinesis", "Teleportation Circle", "Wall of Force",
        "Wall of Stone"
    };
    this->Spells.push_back(wizardLevel5);

    vector<string> wizardLevel6 = {
        "Arcane Gate", "Chain Lightning", "Circle of Death", "Contingency",
        "Create Undead", "Disintegrate", "Drawmij's Instant Summons", "Eyebite",
        "Flesh to Stone", "Globe of Invulnerability", "Guards and Wards", "Magic Jar",
        "Mass Suggestion", "Move Earth", "Otiluke's Freezing Sphere",
        "Otto's Irresistible Dance", "Programmed Illusion", "Sunbeam", "True Seeing",
        "Wall of Ice"
    };
    this->Spells.push_back(wizardLevel6);

    vector<string> wizardLevel7 = {
        "Delayed Blast Fireball", "Etherealness", "Finger of Death", "Forcecage",
        "Mirage Arcane", "Mordenkainen's Magnificent Mansion", "Mordenkainen's Sword",
        "Plane Shift", "Prismatic Spray", "Project Image", "Reverse Gravity",
        "Sequester", "Simulacrum", "Symbol", "Teleport"
    };
    this->Spells.push_back(wizardLevel7);

    vector<string> wizardLevel8 = {
        "Antimagic Field", "Antipathy/Sympathy", "Clone", "Control Weather",
        "Demiplane", "Dominate Monster", "Earthquake", "Feeblemind", "Incendiary Cloud",
        "Maze", "Mind Blank", "Power Word Stun", "Sunburst", "Telepathy",
        "Trap the Soul", "Tsunami"
    };
    this->Spells.push_back(wizardLevel8);

    vector<string> wizardLevel9 = {
        "Astral Projection", "Foresight", "Gate", "Imprisonment", "Meteor Swarm",
        "Power Word Kill", "Prismatic Wall", "Shapechange", "Time Stop",
        "True Polymorph", "Weird", "Wish"
    };
    this->Spells.push_back(wizardLevel9);

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


wizardSpellList::~wizardSpellList()
{
    delete ui;
}
