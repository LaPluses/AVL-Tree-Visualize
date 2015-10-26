#include "treeview.h"

TreeView::TreeView() : QGraphicsView()
{
    mScene = new QGraphicsScene;
    setRenderHint(QPainter::Antialiasing);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(mScene);
    connect(mScene, SIGNAL(changed(QList<QRectF>)), SLOT(resize()));
    zoomAnim = new QPropertyAnimation(this, "sceneRect");
    zoomAnim->setDuration(500);
    zoomAnim->setEasingCurve(QEasingCurve::OutExpo);
}

void TreeView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    resize();
}

void TreeView::addNode(TreeNode *node)
{
    mScene->addItem(node);
}

void TreeView::addEdge(TreeEdge *edge)
{
    mScene->addItem(edge);
}

void TreeView::setSceneRect(QRectF rect)
{
    QGraphicsView::setSceneRect(rect);
    fitInView(rect, Qt::KeepAspectRatio);
}

void TreeView::resize()
{
    zoomAnim->stop();
    zoomAnim->setEndValue(mScene->itemsBoundingRect().adjusted(-10, -10, 10, 10));
    zoomAnim->start();
}

