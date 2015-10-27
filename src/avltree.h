#ifndef AVLTREE_H
#define AVLTREE_H

#include "treeview.h"
#include "treenode.h"
#include "treepath.h"

class AVLTree : public QObject
{
    Q_OBJECT

private:
    static const int MIN_NODE_DISTANCE = 100;
    static const int LEVEL_HEIGHT = 100;
    TreeNode *root;
    TreeView *view;
    void Insert(TreeNode * &node, TreeNode *parent, int x, QAnimationGroup *group);
    void Delete(TreeNode * &node, int x, QAnimationGroup *group);
    void Find(TreeNode *node, int x, QAnimationGroup *group);
    void Clear(TreeNode *node);
    void InOrder(TreeNode *node, QAnimationGroup *group);
    void PreOrder(TreeNode *node, QAnimationGroup *group);
    void PostOrder(TreeNode *node, QAnimationGroup *group);
    void CalcNodePos(TreeNode *node, int depth, QVector<qreal> &leftmost);
    void ApplyNodePos(TreeNode *node, int depth, qreal deltaX, QVector<qreal> &leftmost);
    QAbstractAnimation* getPosAnim();
    void getPosAnim(TreeNode *node, int depth, QAnimationGroup *group);
    QAbstractAnimation* getEdgeAnim();
    void getEdgeAnim(TreeNode *node, TreeNode *parent, QAnimationGroup *group);
    int Count(TreeNode *node);
    qreal ASL(TreeNode *node, int depth);

public:
    AVLTree();
    ~AVLTree();

    TreeView* getView();
    int max(int x,int y);
    int height(TreeNode * &node);
    void LL(TreeNode * &k2, QAnimationGroup *group);
    void LR(TreeNode * &k2, QAnimationGroup *group);
    void RR(TreeNode * &k2, QAnimationGroup *group);
    void RL(TreeNode * &k2, QAnimationGroup *group);
    void Insert(int x, bool showProgress);
    void Delete(int x, bool showProgress);
    void Find(int x, bool showProgress);
    int Count();
    qreal ASL();

public slots:
    void PreOrder();
    void InOrder();
    void PostOrder();
    void LevelOrder();
    void Clear();
};

#endif // AVLTREE_H
