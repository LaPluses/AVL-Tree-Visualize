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
    mainLayout->setRowStretch(11, 1);
    mainLayout->addWidget(tree->getView(), 0, 0, 12, 1);
    mainLayout->addWidget(insertEdit, 0, 1);
    mainLayout->addWidget(insertButton, 1, 1);
    mainLayout->addWidget(deleteEdit, 2, 1);
    mainLayout->addWidget(deleteButton, 3, 1);
    mainLayout->addWidget(findEdit, 4, 1);
    mainLayout->addWidget(findButton, 5, 1);
    mainLayout->addWidget(preOrderButton, 6, 1);
    mainLayout->addWidget(inOrderButton, 7, 1);
    mainLayout->addWidget(postOrderButton, 8, 1);
    mainLayout->addWidget(levelOrderButton, 9, 1);
    mainLayout->addWidget(clearButton, 10, 1);
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
    tree->Insert(insertEdit->text().toInt());
    insertEdit->clear();
    insertEdit->setFocus();
}

void Widget::treeDelete()
{
    qDebug() << "Delete" << deleteEdit->text().toInt();
    tree->Delete(deleteEdit->text().toInt());
    deleteEdit->clear();
    deleteEdit->setFocus();
}

void Widget::treeFind()
{
    qDebug() << "Find" << findEdit->text().toInt();
    tree->Find(findEdit->text().toInt());
    findEdit->clear();
    findEdit->setFocus();
}
