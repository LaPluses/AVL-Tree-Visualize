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

void TreeView::addItem(QGraphicsItem *item)
{
    mScene->addItem(item);
}

void TreeView::setSceneRect(QRectF rect)
{
    QGraphicsView::setSceneRect(rect);
    fitInView(rect, Qt::KeepAspectRatio);
}

void TreeView::resize()
{
    zoomAnim->stop();
    zoomAnim->setEndValue(mScene->itemsBoundingRect().adjusted(-25, -25, 25, 25));
    zoomAnim->start();
}

