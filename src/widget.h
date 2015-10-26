#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "treeview.h"
#include "treenode.h"
#include "treeedge.h"
#include "avltree.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void treeInsert();
    void treeDelete();
    void treeFind();

private:
    QLineEdit *insertEdit;
    QLineEdit *deleteEdit;
    QLineEdit *findEdit;
    QPushButton *insertButton;
    QPushButton *deleteButton;
    QPushButton *findButton;
    QPushButton *preOrderButton;
    QPushButton *inOrderButton;
    QPushButton *postOrderButton;
    QPushButton *levelOrderButton;
    QPushButton *clearButton;
    AVLTree *tree;
};

#endif // WIDGET_H
