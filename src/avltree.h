#ifndef AVLTREE_H
#define AVLTREE_H

#include "treeview.h"
#include "treenode.h"

class AVLTree : public QObject
{
    Q_OBJECT

private:
    static const int MIN_NODE_DISTANCE = 100;
    static const int LEVEL_HEIGHT = 100;
    TreeNode *root;
    TreeView *view;
    void Insert(TreeNode * &node, TreeNode *parent, int x);
    void Delete(TreeNode * &node, int x);
    bool Find(TreeNode *node, int x);
    void Clear(TreeNode *node);
    void InOrder(TreeNode *node, QSequentialAnimationGroup *group);
    void PreOrder(TreeNode *node, QSequentialAnimationGroup *group);
    void PostOrder(TreeNode *node, QSequentialAnimationGroup *group);
    void CalcNodePos(TreeNode *node, int depth, QVector<qreal> &leftmost);
    void ApplyNodePos(TreeNode *node, int depth, qreal deltaX, QVector<qreal> &leftmost);
    void AnimNode();
    void AnimNode(TreeNode *node, int depth);

public:
    AVLTree();
    ~AVLTree();

    TreeView* getView();
    int max(int x,int y);
    int height(TreeNode * &node);
    void LL(TreeNode * &k2);
    void LR(TreeNode * &k2);
    void RR(TreeNode * &k2);
    void RL(TreeNode * &k2);
    void Insert(int x);
    void Delete(int x);
    void Find(int x);

public slots:
    void PreOrder();
    void InOrder();
    void PostOrder();
    void LevelOrder();
    void Clear();
};

#endif // AVLTREE_H
