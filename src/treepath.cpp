#include "treepath.h"

TreePath::TreePath(TreeNode *node, TreeNode *son, TreeView *view) : QGraphicsItem(), mNode(node), mSon(son)
{
    mStep = 0;
    setZValue(-1);
    view->addItem(this);
}

QAbstractAnimation *TreePath::getToSonAnim()
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "step");
    anim->setDuration(mSon ? SpeedController::getInstance()->speed() / 2 : 0);
    anim->setStartValue(0);
    anim->setEndValue(1);
    return anim;
}

QAbstractAnimation *TreePath::getToParentAnim()
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "step");
    anim->setDuration(mSon ? SpeedController::getInstance()->speed() / 2 : 0);
    anim->setStartValue(1);
    anim->setEndValue(0);
    connect(anim, SIGNAL(finished()), this, SLOT(deleteLater()));
    return anim;
}

qreal TreePath::step()
{
    return mStep;
}

void TreePath::setStep(qreal step)
{
    mStep = step;
    scene()->update();
}

QRectF TreePath::boundingRect() const
{
    return QRectF(0, 0, 0, 0);
}

void TreePath::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (mSon == NULL) return;
    QLineF line(mNode->pos(), mSon->pos());
    qreal length = line.length() - TreeNode::NODE_RADIUS * (mNode->scale() + mSon->scale());
    if (length <= 0)
    {
        return;
    }
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);
    line.setP1(QPointF(line.x1() + line.unitVector().dx() * TreeNode::NODE_RADIUS * mNode->scale(),
                       line.y1() + line.unitVector().dy() * TreeNode::NODE_RADIUS * mNode->scale()));
    line.setP2(QPointF(line.x2() - line.unitVector().dx() * (TreeNode::NODE_RADIUS * mSon->scale() + length * (1 - mStep)),
                       line.y2() - line.unitVector().dy() * (TreeNode::NODE_RADIUS * mSon->scale() + length * (1 - mStep))));
    painter->drawLine(line);
}
