#ifndef TREENODE_H
#define TREENODE_H

#include <QWidget>
#include <QtWidgets>
#include "treeedge.h"
#include "treeview.h"
#include "speedcontroller.h"

class TreeEdge;

class TreeView;

class TreeNode : public QObject, public QGraphicsItem
{
    Q_OBJECT

    Q_PROPERTY(QPointF pos READ pos WRITE setPos NOTIFY posChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
    Q_PROPERTY(int redValue READ redValue WRITE setRedValue)
    Q_PROPERTY(int value READ value WRITE setValue)

public:
    static const int NODE_RADIUS = 20;
    int data;
    TreeEdge *parentEdge;
    TreeNode *parent;
    TreeNode *Lson;
    TreeNode *Rson;
    int h;
    qreal rawX;
    TreeNode();
    ~TreeNode();
    void setPos(QPointF center);
    void moveTo(QPointF p);
    int value();
    void setValue(int value);
    QAbstractAnimation* getPopAnim();
    QAbstractAnimation* getValueAnim(int value);
    QAbstractAnimation* getTurnRedAnim();
    QAbstractAnimation* getTurnBlackAnim();
    QAbstractAnimation* getMoveAnim(QPointF p);
    QAbstractAnimation* getFadeInAnim();
    QAbstractAnimation* getFadeOutAnim();
    QAbstractAnimation* setParent(TreeNode *node);
    int redValue();
    void setRedValue(int redValue);

signals:
    void posChanged();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int mRedValue;
};

#endif // TREENODE_H
