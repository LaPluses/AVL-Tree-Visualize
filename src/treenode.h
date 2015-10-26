#ifndef TREENODE_H
#define TREENODE_H

#include <QWidget>
#include <QtWidgets>
#include "treeedge.h"
#include "treeview.h"

class TreeEdge;

class TreeView;

class TreeNode : public QObject, public QGraphicsItem
{
    Q_OBJECT

    Q_PROPERTY(QPointF pos READ pos WRITE setPos NOTIFY posChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(qreal scale READ scale WRITE setScale)

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
    void fadeOut();
    void moveTo(QPointF p);
    void pop();
    QPropertyAnimation* getPopAnim();
    void setParent(TreeNode *node, TreeView *view);

signals:
    void posChanged();
    void fadeOuting();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPropertyAnimation *mOpacityAnim;
    QPropertyAnimation *mPosAnim;
    QPropertyAnimation *mPopAnim;
};

#endif // TREENODE_H
