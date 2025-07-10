#include "creatorscreen.h"
#include "ui_creatorscreen.h"
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
creatorScreen::creatorScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::creatorScreen)
{
    ui->setupUi(this);
    QVBoxLayout *layout = new QVBoxLayout;
    setWindowIcon(QIcon(":/icons/icons/dnd-icon.png"));
    QPixmap original(":/icons/creatorphoto.png");
    QPixmap reduced = original.scaled(500, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QLabel *image = new QLabel(this);
    image->setPixmap(reduced);
    image->setAlignment(Qt::AlignCenter);

    QLabel *nameAndRegNumber = new QLabel("Maurício Melo Filho\n24206544");
    nameAndRegNumber->setAlignment(Qt::AlignCenter);
    nameAndRegNumber->setStyleSheet("font-size: 18px; font-weight: bold;");

    nameAndRegNumber->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    layout->addWidget(image);
    layout->addWidget(nameAndRegNumber);
    setLayout(layout);
}

creatorScreen::~creatorScreen()
{
    delete ui;
}
