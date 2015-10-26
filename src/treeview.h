#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QWidget>
#include <QtWidgets>
#include "treenode.h"
#include "treeedge.h"

class TreeNode;

class TreeEdge;

class TreeView : public QGraphicsView
{
    Q_OBJECT

    Q_PROPERTY(QRectF sceneRect READ sceneRect WRITE setSceneRect)

public:
    TreeView();
    void resizeEvent(QResizeEvent *event);
    void addNode(TreeNode *node);
    void addEdge(TreeEdge *edge);
    void setSceneRect(QRectF rect);

private:
    QGraphicsScene *mScene;
    QPropertyAnimation *zoomAnim;

private slots:
    void resize();
};

#endif // TREEVIEW_H
