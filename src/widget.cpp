#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    insertEdit = new QLineEdit;
    deleteEdit = new QLineEdit;
    findEdit = new QLineEdit;
    insertEdit->setValidator(new QIntValidator());
    deleteEdit->setValidator(new QIntValidator());
    findEdit->setValidator(new QIntValidator());
    insertButton = new QPushButton(tr("Insert"));
    deleteButton = new QPushButton(tr("Delete"));
    findButton = new QPushButton(tr("Find"));
    preOrderButton = new QPushButton(tr("Pre-order"));
    inOrderButton = new QPushButton(tr("In-order"));
    postOrderButton = new QPushButton(tr("Post-order"));
    levelOrderButton = new QPushButton(tr("Level-order"));
    clearButton = new QPushButton(tr("Clear"));
    showProgressCheckBox = new QCheckBox(tr("Show Progress"));
    countLabel = new QLabel(tr("N = 0"));
    countLabel->setAlignment(Qt::AlignCenter);
    aslLabel = new QLabel(tr("ASL = 0"));
    aslLabel->setAlignment(Qt::AlignCenter);
    speedLabel = new QLabel(tr("Speed"));
    speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setMinimum(1);
    speedSlider->setMaximum(5);
    speedSlider->setValue(3);
    speedSlider->setTickPosition(QSlider::TicksBelow);
    speedSlider->setTickInterval(1);
    connect(speedSlider, SIGNAL(sliderMoved(int)), SpeedController::getInstance(), SLOT(setSpeed(int)));
    tree = new AVLTree;
    connect(insertEdit, SIGNAL(returnPressed()), insertButton, SLOT(click()));
    connect(deleteEdit, SIGNAL(returnPressed()), deleteButton, SLOT(click()));
    connect(findEdit, SIGNAL(returnPressed()), findButton, SLOT(click()));
    connect(insertButton, SIGNAL(clicked(bool)), SLOT(treeInsert()));
    connect(deleteButton, SIGNAL(clicked(bool)), SLOT(treeDelete()));
    connect(findButton, SIGNAL(clicked(bool)), SLOT(treeFind()));
    connect(preOrderButton, SIGNAL(clicked(bool)), tree, SLOT(PreOrder()));
    connect(inOrderButton, SIGNAL(clicked(bool)), tree, SLOT(InOrder()));
    connect(postOrderButton, SIGNAL(clicked(bool)), tree, SLOT(PostOrder()));
    connect(levelOrderButton, SIGNAL(clicked(bool)), tree, SLOT(LevelOrder()));
    connect(clearButton, SIGNAL(clicked(bool)), tree, SLOT(Clear()));
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setRowStretch(15, 1);
    mainLayout->addWidget(tree->getView(), 0, 0, 16, 1);
    mainLayout->addWidget(insertEdit, 0, 1, 1, 2);
    mainLayout->addWidget(insertButton, 1, 1, 1, 2);
    mainLayout->addWidget(deleteEdit, 2, 1, 1, 2);
    mainLayout->addWidget(deleteButton, 3, 1, 1, 2);
    mainLayout->addWidget(findEdit, 4, 1, 1, 2);
    mainLayout->addWidget(findButton, 5, 1, 1, 2);
    mainLayout->addWidget(preOrderButton, 6, 1, 1, 2);
    mainLayout->addWidget(inOrderButton, 7, 1, 1, 2);
    mainLayout->addWidget(postOrderButton, 8, 1, 1, 2);
    mainLayout->addWidget(levelOrderButton, 9, 1, 1, 2);
    mainLayout->addWidget(clearButton, 10, 1, 1, 2);
    mainLayout->addWidget(showProgressCheckBox, 11, 1, 1, 2);
    mainLayout->addWidget(countLabel, 12, 1, 1, 2);
    mainLayout->addWidget(aslLabel, 13, 1, 1, 2);
    mainLayout->addWidget(speedLabel, 14, 1);
    mainLayout->addWidget(speedSlider, 14, 2);
    setLayout(mainLayout);
    setWindowTitle(tr("AVL Tree Visualize"));
    setMinimumSize(800, 500);
}

Widget::~Widget()
{
    delete tree;
}

void Widget::treeInsert()
{
    qDebug() << "Insert" << insertEdit->text().toInt();
    tree->Insert(insertEdit->text().toInt(), showProgressCheckBox->isChecked());
    insertEdit->clear();
    insertEdit->setFocus();
    countLabel->setText("N = " + QString::number(tree->Count()));
    aslLabel->setText("ASL = " + QString::number(tree->ASL()));
}

void Widget::treeDelete()
{
    qDebug() << "Delete" << deleteEdit->text().toInt();
    tree->Delete(deleteEdit->text().toInt(), showProgressCheckBox->isChecked());
    deleteEdit->clear();
    deleteEdit->setFocus();
    countLabel->setText("N = " + QString::number(tree->Count()));
    aslLabel->setText("ASL = " + QString::number(tree->ASL()));
}

void Widget::treeFind()
{
    qDebug() << "Find" << findEdit->text().toInt();
    tree->Find(findEdit->text().toInt(), showProgressCheckBox->isChecked());
    findEdit->clear();
    findEdit->setFocus();
}
