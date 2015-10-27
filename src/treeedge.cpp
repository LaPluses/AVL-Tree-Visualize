#include "treeedge.h"

TreeEdge::TreeEdge(TreeNode* A, TreeNode* B) : mA(A), mB(B)
{
    connect(A, SIGNAL(destroyed(QObject*)), SLOT(deleteLater()));
    connect(B, SIGNAL(destroyed(QObject*)), SLOT(deleteLater()));
    setZValue(-2);
    setOpacity(0);
}

TreeEdge::~TreeEdge()
{
}

QAbstractAnimation *TreeEdge::getFadeInAnim()
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "opacity");
    anim->setEasingCurve(QEasingCurve::OutExpo);
    anim->setStartValue(0);
    anim->setEndValue(1);
    anim->setDuration(500);
    return anim;
}

QAbstractAnimation *TreeEdge::getFadeOutAnim()
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "opacity");
    anim->setEasingCurve(QEasingCurve::OutExpo);
    anim->setStartValue(1);
    anim->setEndValue(0);
    anim->setDuration(500);
    connect(anim, SIGNAL(finished()), SLOT(deleteLater()));
    return anim;
}

QRectF TreeEdge::boundingRect() const
{
    return QRectF(0, 0, 0, 0);
}

void TreeEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QLineF line(mA->pos(), mB->pos());
    if (line.length() <= TreeNode::NODE_RADIUS * (mA->scale() + mB->scale()))
    {
        return;
    }
    line.setP1(QPointF(line.x1() + line.unitVector().dx() * TreeNode::NODE_RADIUS * mA->scale(),
                       line.y1() + line.unitVector().dy() * TreeNode::NODE_RADIUS * mA->scale()));
    line.setP2(QPointF(line.x2() - line.unitVector().dx() * TreeNode::NODE_RADIUS * mB->scale(),
                       line.y2() - line.unitVector().dy() * TreeNode::NODE_RADIUS * mB->scale()));
    painter->drawLine(line);
}
