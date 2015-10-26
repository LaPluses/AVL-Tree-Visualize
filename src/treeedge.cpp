#include "treeedge.h"

TreeEdge::TreeEdge(TreeNode* A, TreeNode* B) : mA(A), mB(B)
{
    connect(A, SIGNAL(destroyed(QObject*)), SLOT(deleteLater()));
    connect(B, SIGNAL(destroyed(QObject*)), SLOT(deleteLater()));
    connect(A, SIGNAL(fadeOuting()), SLOT(fadeOut()));
    connect(B, SIGNAL(fadeOuting()), SLOT(fadeOut()));
    setZValue(-1);
    mOpacityAnim = new QPropertyAnimation(this, "opacity");
    mOpacityAnim->setEasingCurve(QEasingCurve::OutExpo);
    mOpacityAnim->setStartValue(0);
    mOpacityAnim->setEndValue(1);
    mOpacityAnim->setDuration(1000);
    mOpacityAnim->start();
}

TreeEdge::~TreeEdge()
{
    delete mOpacityAnim;
}

void TreeEdge::fadeOut()
{
    mOpacityAnim->stop();
    mOpacityAnim->setEasingCurve(QEasingCurve::OutExpo);
    mOpacityAnim->setStartValue(opacity());
    mOpacityAnim->setEndValue(0);
    mOpacityAnim->start();
    connect(mOpacityAnim, SIGNAL(finished()), SLOT(deleteLater()));
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
