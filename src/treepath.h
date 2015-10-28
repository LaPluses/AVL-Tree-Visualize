#ifndef TREEPATH_H
#define TREEPATH_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "treenode.h"
#include "speedcontroller.h"

class TreeNode;

class TreePath : public QObject, public QGraphicsItem
{
    Q_OBJECT

    Q_PROPERTY(qreal step READ step WRITE setStep)

public:
    TreePath(TreeNode *node, TreeNode *son, TreeView *view);
    QAbstractAnimation* getToSonAnim();
    QAbstractAnimation* getToParentAnim();
    qreal step();
    void setStep(qreal step);

private:
    TreeNode *mNode;
    TreeNode *mSon;
    qreal mStep;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TREEPATH_H
