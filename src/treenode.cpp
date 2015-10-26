#include "treenode.h"

TreeNode::TreeNode() : QGraphicsItem()
{
    mOpacityAnim = new QPropertyAnimation(this, "opacity");
    mOpacityAnim->setEasingCurve(QEasingCurve::OutExpo);
    mOpacityAnim->setStartValue(0);
    mOpacityAnim->setEndValue(1);
    mOpacityAnim->setDuration(1000);
    mOpacityAnim->start();
    mPosAnim = new QPropertyAnimation(this, "pos");
    mPosAnim->setEasingCurve(QEasingCurve::OutElastic);
    mPosAnim->setDuration(1000);
    mPopAnim = new QPropertyAnimation(this, "scale");
    mPopAnim->setEasingCurve(QEasingCurve::OutExpo);
    mPopAnim->setKeyValueAt(0, 1);
    mPopAnim->setKeyValueAt(0.5, 1.5);
    mPopAnim->setKeyValueAt(1, 1);
    mPopAnim->setDuration(1000);
    h = 0;
    data = 0;
    parent = Lson = Rson = NULL;
    rawX = 0;
}

TreeNode::~TreeNode()
{
    delete mOpacityAnim;
}

void TreeNode::fadeOut()
{
    emit fadeOuting();
    mOpacityAnim->stop();
    mOpacityAnim->setEasingCurve(QEasingCurve::OutCurve);
    mOpacityAnim->setStartValue(opacity());
    mOpacityAnim->setEndValue(0);
    mOpacityAnim->start();
    connect(mOpacityAnim, SIGNAL(finished()), SLOT(deleteLater()));
}

void TreeNode::moveTo(QPointF p)
{
    mPosAnim->stop();
    mPosAnim->setEndValue(p);
    mPosAnim->start();
}

void TreeNode::pop()
{
    mPopAnim->stop();
    mPopAnim->start();
}

QPropertyAnimation* TreeNode::getPopAnim()
{
    QPropertyAnimation *popAnim = new QPropertyAnimation(this, "scale");
    popAnim->setEasingCurve(QEasingCurve::OutCurve);
    popAnim->setKeyValueAt(0, 1);
    popAnim->setKeyValueAt(0.5, 1.5);
    popAnim->setKeyValueAt(1, 1);
    popAnim->setDuration(400);
    return popAnim;
}

void TreeNode::setParent(TreeNode *node, TreeView *view)
{
    if (node == parent) return;
    if (parent != NULL) parentEdge->fadeOut();
    parent = node;
    if (node)
    {
        parentEdge = new TreeEdge(node, this);
        view->addEdge(parentEdge);
    }
    else
    {
        parentEdge = NULL;
    }
}

QRectF TreeNode::boundingRect() const
{
    return QRectF(-NODE_RADIUS, -NODE_RADIUS, NODE_RADIUS * 2, NODE_RADIUS * 2);
}

void TreeNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(Qt::white));
    painter->drawEllipse(QPointF(0, 0), NODE_RADIUS, NODE_RADIUS);
    painter->setPen(Qt::black);
    painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(data));
}

void TreeNode::setPos(QPointF center)
{
    QGraphicsItem::setPos(center);
    emit posChanged();
}
