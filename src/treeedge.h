#ifndef TREEEDGE_H
#define TREEEDGE_H

#include <QWidget>
#include <QtWidgets>
#include "treenode.h"

class TreeNode;

class TreeEdge : public QObject, public QGraphicsItem
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    TreeEdge(TreeNode* A, TreeNode* B);
    ~TreeEdge();
    QAbstractAnimation* getFadeInAnim();
    QAbstractAnimation* getFadeOutAnim();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    TreeNode* mA;
    TreeNode* mB;
};

#endif // TREEEDGE_H
