#include "treenode.h"

TreeNode::TreeNode() : QGraphicsItem()
{
    mPopAnim = new QPropertyAnimation(this, "scale");
    mPopAnim->setEasingCurve(QEasingCurve::OutExpo);
    mPopAnim->setKeyValueAt(0, 1);
    mPopAnim->setKeyValueAt(0.5, 2);
    mPopAnim->setKeyValueAt(1, 1);
    mPopAnim->setDuration(1000);
    setOpacity(0);
    h = 0;
    data = 0;
    parent = Lson = Rson = NULL;
    rawX = 0;
    mRedValue = 0;
}

TreeNode::~TreeNode()
{
}

void TreeNode::pop()
{
    mPopAnim->stop();
    mPopAnim->start();
}

int TreeNode::value()
{
    return data;
}

void TreeNode::setValue(int value)
{
    data = value;
}

QAbstractAnimation* TreeNode::getPopAnim()
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "scale");
    anim->setEasingCurve(QEasingCurve::OutCurve);
    anim->setKeyValueAt(0, 1);
    anim->setKeyValueAt(0.5, 2);
    anim->setKeyValueAt(1, 1);
    anim->setDuration(400);
    return anim;
}

QAbstractAnimation *TreeNode::getValueAnim(int value)
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "value");
    anim->setEndValue(value);
    anim->setDuration(0);
    return anim;
}

QAbstractAnimation *TreeNode::getTurnRedAnim()
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "redValue");
    anim->setStartValue(0);
    anim->setEndValue(255);
    anim->setDuration(200);
    return anim;
}

QAbstractAnimation *TreeNode::getTurnBlackAnim()
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "redValue");
    anim->setStartValue(255);
    anim->setEndValue(0);
    anim->setDuration(200);
    return anim;
}

QAbstractAnimation *TreeNode::getMoveAnim(QPointF p)
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "pos");
    anim->setEasingCurve(QEasingCurve::OutElastic);
    anim->setDuration(500);
    anim->setEndValue(p);
    return anim;
}

QAbstractAnimation *TreeNode::getFadeInAnim()
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "opacity");
    anim->setEasingCurve(QEasingCurve::OutExpo);
    anim->setStartValue(0);
    anim->setEndValue(1);
    anim->setDuration(500);
    return anim;
}

QAbstractAnimation *TreeNode::getFadeOutAnim()
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "opacity");
    anim->setEasingCurve(QEasingCurve::OutCurve);
    anim->setStartValue(1);
    anim->setEndValue(0);
    anim->setDuration(1000);
    connect(anim, SIGNAL(finished()), SLOT(deleteLater()));
    if (parent)
    {
        QParallelAnimationGroup *group = new QParallelAnimationGroup;
        group->addAnimation(setParent(NULL));
        group->addAnimation(anim);
        return group;
    }
    else
        return anim;
}

QAbstractAnimation *TreeNode::setParent(TreeNode *node)
{
    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    if (node == parent) return group;
    if (parent != NULL) group->addAnimation(parentEdge->getFadeOutAnim());
    parent = node;
    if (node)
    {
        parentEdge = new TreeEdge(node, this);
        scene()->addItem(parentEdge);
        group->addAnimation(parentEdge->getFadeInAnim());
    }
    else
    {
        parentEdge = NULL;
    }
    return group;
}

int TreeNode::redValue()
{
    return mRedValue;
}

void TreeNode::setRedValue(int redValue)
{
    mRedValue = redValue;
    scene()->update();
}

QRectF TreeNode::boundingRect() const
{
    return QRectF(-NODE_RADIUS / scale(), -NODE_RADIUS / scale(), NODE_RADIUS / scale() * 2, NODE_RADIUS / scale() * 2);
}

void TreeNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setColor(QColor(mRedValue, 0, 0));
    pen.setWidthF(mRedValue / 255.0 + 1);
    painter->setPen(pen);
    painter->setBrush(QBrush(Qt::white));
    painter->drawEllipse(QPointF(0, 0), NODE_RADIUS, NODE_RADIUS);
    painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(data));
}

void TreeNode::setPos(QPointF center)
{
    QGraphicsItem::setPos(center);
    emit posChanged();
}
