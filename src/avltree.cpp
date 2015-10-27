#include "avltree.h"

AVLTree::AVLTree()
{
    root = NULL;
    view = new TreeView();
}

AVLTree::~AVLTree()
{
    delete view;
}

TreeView *AVLTree::getView()
{
    return view;
}

int AVLTree::max(int x, int y)
{
    return x > y ? x : y;
}

void AVLTree::Insert(TreeNode * &node, TreeNode *parent, int x, QAnimationGroup *group)
{
    if (group && parent)
        group->addAnimation(parent->getTurnRedAnim());
    if (node == NULL)
    {
        QParallelAnimationGroup *anim = new QParallelAnimationGroup;
        node = new TreeNode();
        view->addItem(node);
        node->data = x;
        node->setPos(parent ? parent->pos() : QPointF(0, 0));
        anim->addAnimation(node->getFadeInAnim());
        if (group)
        {
            anim->addAnimation(node->setParent(parent));
            anim->addAnimation(getPosAnim());
            group->addAnimation(anim);
            if (parent)
                group->addAnimation(parent->getTurnBlackAnim());
        }
        else
        {
            anim->start(QAbstractAnimation::DeleteWhenStopped);
        }
        return;
    }
    TreePath *path;
    if (group && parent)
    {
        path = new TreePath(parent, node, view);
        group->addAnimation(path->getToSonAnim());
    }
    if (node->data > x)
    {
        Insert(node->Lson, node, x, group);
        if (group && parent)
            group->addAnimation(path->getToParentAnim());
        if (2 == height(node->Lson) - height(node->Rson))
        {
            if (x < node->Lson->data)
                LL(node, group);
            else
                LR(node, group);
        }
    }
    else if (node->data < x)
    {
        Insert(node->Rson, node, x, group);
        if (group && parent)
            group->addAnimation(path->getToParentAnim());
        if (2 == height(node->Rson) - height(node->Lson))
        {
            if (x > node->Rson->data)
                RR(node, group);
            else
                RL(node, group);
        }
    }
    else if (group && parent)
        group->addAnimation(path->getToParentAnim());
    if (group && parent)
        group->addAnimation(parent->getTurnBlackAnim());
    node->h = max(height(node->Lson), height(node->Rson)) + 1;
}

void AVLTree::Delete(TreeNode * &node, int x, QAnimationGroup *group)
{
    if (node == NULL)
        return;
    if (group&& node->parent)
        group->addAnimation(node->parent->getTurnRedAnim());
    TreePath *path;
    if (group && node->parent)
    {
        path = new TreePath(node->parent, node, view);
        group->addAnimation(path->getToSonAnim());
    }
    TreeNode* parent = node->parent;
    if (x < node->data)
    {
        //如果x小于节点的值,就继续在节点的左子树中删除x
        Delete(node->Lson, x, group);
        if (group && node->parent)
            group->addAnimation(path->getToParentAnim());
        if (2 == height(node->Rson) - height(node->Lson))
        {
            if (node->Rson->Lson != NULL &&
                (height(node->Rson->Lson)>height(node->Rson->Rson)))
                RL(node, group);
            else
                RR(node, group);
        }

    }
    else if (x > node->data)
    {
        Delete(node->Rson, x, group);//如果x大于节点的值,就继续在节点的右子树中删除x
        if (group && node->parent)
            group->addAnimation(path->getToParentAnim());
        if (2 == height(node->Lson) - height(node->Rson))
        {
            if (node->Lson->Rson != NULL &&
                (height(node->Lson->Rson)>height(node->Lson->Lson)))
                LR(node, group);
            else
                LL(node, group);
        }

    }
    else//如果相等,此节点就是要删除的节点
    {
        if (group)
            group->addAnimation(node->getPopAnim());
        else
            node->getPopAnim()->start(QAbstractAnimation::DeleteWhenStopped);
        if (node->Lson && node->Rson)//此节点有两个儿子
        {
            TreeNode* temp = node->Rson;//temp指向节点的右儿子
            while (temp->Lson != NULL) temp = temp->Lson;//找到右子树中值最小的节点
            //把右子树中最小节点的值赋值给本节点
            if (group)
                group->addAnimation(node->getValueAnim(temp->data));
            else
                node->data = temp->data;
            //node->freq = temp->freq;
            Delete(node->Rson, temp->data, group);//删除右子树中最小值的节点
            if (group && node->parent)
                group->addAnimation(path->getToParentAnim());
            if (2 == height(node->Lson) - height(node->Rson))
            {
                if (node->Lson->Rson != NULL &&
                    (height(node->Lson->Rson)>height(node->Lson->Lson)))
                    LR(node, group);
                else
                    LL(node, group);
            }
        }
        else//此节点有1个或0个儿子
        {
            TreeNode* temp = node;
            TreeNode* parent = node->parent;
            if (group && node->parent)
                group->addAnimation(path->getToParentAnim());
            if (node->Lson == NULL)//有右儿子或者没有儿子
                node = node->Rson;
            else if (node->Rson == NULL)//有左儿子
                node = node->Lson;
            if (group)
            {
                QParallelAnimationGroup *anim = new QParallelAnimationGroup;
                anim->addAnimation(temp->getFadeOutAnim());
                if (node)
                    anim->addAnimation(node->setParent(parent));
                group->addAnimation(anim);
            }
            else
            {
                temp->getFadeOutAnim()->start(QAbstractAnimation::DeleteWhenStopped);
                if (node)
                    node->setParent(parent)->start(QAbstractAnimation::DeleteWhenStopped);
            }
            if (group)
                group->addAnimation(getPosAnim());
        }
    }
    if (group && parent)
        group->addAnimation(parent->getTurnBlackAnim());
    if (node == NULL)
        return;
    node->h = max(height(node->Lson), height(node->Rson)) + 1;
    return;
}

void AVLTree::Find(TreeNode *node, int x, QAnimationGroup *group)
{
    if (node == NULL) return;
    TreePath *path;
    if (node->parent && group)
    {
        path = new TreePath(node->parent, node, view);
        group->addAnimation(path->getToSonAnim());
    }
    if (group)
        group->addAnimation(node->getTurnRedAnim());
    if (node->data == x)
    {
        if (group)
            group->addAnimation(node->getPopAnim());
        else
            node->getPopAnim()->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else if (node->data > x)
        Find(node->Lson, x, group);
    else
        Find(node->Rson, x, group);
    if (group)
        group->addAnimation(node->getTurnBlackAnim());
    if (node->parent && group)
    {
        group->addAnimation(path->getToParentAnim());
    }
}

void AVLTree::Clear(TreeNode *node)
{
    if (node == NULL) return;
    Clear(node->Lson);
    Clear(node->Rson);
    node->getFadeOutAnim()->start(QAbstractAnimation::DeleteWhenStopped);
}

int AVLTree::height(TreeNode * &node)
{
    if (node != NULL) return node->h;
    else return -1;
}

void AVLTree::LL(TreeNode * &k2, QAnimationGroup *group)
{
    qDebug() << "LL";
    TreeNode *k1;
    k1 = k2->Lson;
    k2->Lson = k1->Rson;
    k1->Rson = k2;
    k2->h = max(height(k2->Lson), height(k2->Rson)) + 1;
    k1->h = max(height(k1->Lson), k2->h) + 1;
    k2 = k1;
    if (group)
    {
        QParallelAnimationGroup *anim = new QParallelAnimationGroup;
        anim->addAnimation(k1->setParent(k1->Rson->parent));
        anim->addAnimation(k1->Rson->setParent(k1));
        if (k1->Rson->Lson) anim->addAnimation(k1->Rson->Lson->setParent(k1->Rson));
        group->addAnimation(anim);
        group->addAnimation(getPosAnim());
    }
}

void AVLTree::RR(TreeNode * &k2, QAnimationGroup *group)
{
    qDebug() << "RR";
    TreeNode *k1;
    k1 = k2->Rson;
    k2->Rson = k1->Lson;
    k1->Lson = k2;
    k1->h = max(height(k1->Lson), height(k1->Rson)) + 1;
    k2->h = max(height(k2->Lson), height(k2->Rson)) + 1;
    k2 = k1;
    if (group)
    {
        QParallelAnimationGroup *anim = new QParallelAnimationGroup;
        anim->addAnimation(k1->setParent(k1->Lson->parent));
        anim->addAnimation(k1->Lson->setParent(k1));
        if (k1->Lson->Rson) anim->addAnimation(k1->Lson->Rson->setParent(k1->Lson));
        group->addAnimation(anim);
        group->addAnimation(getPosAnim());
    }
}

void AVLTree::LR(TreeNode * &k2, QAnimationGroup *group)
{
    qDebug() << "LR";
    RR(k2->Lson, group);
    LL(k2, group);
}

void AVLTree::RL(TreeNode * &k2, QAnimationGroup *group)
{
    qDebug() << "RL";
    LL(k2->Rson, group);
    RR(k2, group);
}

void AVLTree::Insert(int x, bool showProgress)
{
    if (showProgress)
    {
        QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
        Insert(root, NULL, x, group);
        group->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else
    {
        Insert(root, NULL, x, NULL);
        getPosAnim()->start(QAbstractAnimation::DeleteWhenStopped);
        getEdgeAnim()->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void AVLTree::Delete(int x, bool showProgress)
{
    if (showProgress)
    {
        QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
        Delete(root, x, group);
        group->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else
    {
        Delete(root, x, NULL);
        getPosAnim()->start(QAbstractAnimation::DeleteWhenStopped);
        getEdgeAnim()->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void AVLTree::Find(int x, bool showProgress)
{
    if (showProgress)
    {
        QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
        Find(root, x, group);
        group->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else
    {
        Find(root, x, NULL);
    }
}

int AVLTree::Count()
{
    return Count(root);
}

qreal AVLTree::ASL()
{
    return ASL(root, 0) / Count();
}

void AVLTree::Clear()
{
    Clear(root);
    root = NULL;
}

void AVLTree::InOrder()
{
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
    InOrder(root, group);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void AVLTree::PreOrder()
{
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
    PreOrder(root, group);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void AVLTree::PostOrder()
{
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
    PostOrder(root, group);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void AVLTree::LevelOrder()
{
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
    QQueue<TreeNode*> q;
    q.push_back(root);
    while (!q.empty())
    {
        TreeNode *node = q.front();
        q.pop_front();
        if (node == NULL) continue;
        group->addAnimation(node->getPopAnim());
        q.push_back(node->Lson);
        q.push_back(node->Rson);
    }
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void AVLTree::PreOrder(TreeNode * node, QAnimationGroup *group)
{
    if (node == NULL) return;
    group->addAnimation(node->getTurnRedAnim());
    group->addAnimation(node->getPopAnim());
    TreePath *path = new TreePath(node, node->Lson, view);
    group->addAnimation(path->getToSonAnim());
    PreOrder(node->Lson, group);
    group->addAnimation(path->getToParentAnim());
    path = new TreePath(node, node->Rson, view);
    group->addAnimation(path->getToSonAnim());
    PreOrder(node->Rson, group);
    group->addAnimation(path->getToParentAnim());
    group->addAnimation(node->getTurnBlackAnim());
}

void AVLTree::InOrder(TreeNode * node, QAnimationGroup *group)
{
    if (node == NULL) return;
    group->addAnimation(node->getTurnRedAnim());
    TreePath *path = new TreePath(node, node->Lson, view);
    group->addAnimation(path->getToSonAnim());
    PreOrder(node->Lson, group);
    group->addAnimation(path->getToParentAnim());
    group->addAnimation(node->getPopAnim());
    path = new TreePath(node, node->Rson, view);
    group->addAnimation(path->getToSonAnim());
    PreOrder(node->Rson, group);
    group->addAnimation(path->getToParentAnim());
    group->addAnimation(node->getTurnBlackAnim());
}

void AVLTree::PostOrder(TreeNode *node, QAnimationGroup *group)
{
    if (node == NULL) return;
    group->addAnimation(node->getTurnRedAnim());
    TreePath *path = new TreePath(node, node->Lson, view);
    group->addAnimation(path->getToSonAnim());
    PreOrder(node->Lson, group);
    group->addAnimation(path->getToParentAnim());
    path = new TreePath(node, node->Rson, view);
    group->addAnimation(path->getToSonAnim());
    PreOrder(node->Rson, group);
    group->addAnimation(path->getToParentAnim());
    group->addAnimation(node->getPopAnim());
    group->addAnimation(node->getTurnBlackAnim());
}

void AVLTree::CalcNodePos(TreeNode *node, int depth, QVector<qreal> &leftmost)
{
    if (node == NULL) return;
    if (leftmost.size() < depth + 1) leftmost.append(0);
    CalcNodePos(node->Lson, depth + 1, leftmost);
    CalcNodePos(node->Rson, depth + 1, leftmost);
    if (node->Lson && node->Rson)
    {
        node->rawX = (node->Lson->rawX + node->Rson->rawX) / 2;
    }
    else if (node->Lson)
    {
        node->rawX = node->Lson->rawX + MIN_NODE_DISTANCE / 2;
    }
    else if (node->Rson)
    {
        node->rawX = node->Rson->rawX - MIN_NODE_DISTANCE / 2;
    }
    else
    {
        node->rawX = 0;
    }
    qreal deltaX = qMax(leftmost[depth] + MIN_NODE_DISTANCE - node->rawX, 0.0);
    if (deltaX > 0) ApplyNodePos(node, depth, deltaX, leftmost);
    leftmost[depth] = node->rawX;
}

void AVLTree::ApplyNodePos(TreeNode *node, int depth, qreal deltaX, QVector<qreal> &leftmost)
{
    if (node == NULL) return;
    node->rawX += deltaX;
    leftmost[depth] = node->rawX;
    ApplyNodePos(node->Lson, depth + 1, deltaX, leftmost);
    ApplyNodePos(node->Rson, depth + 1, deltaX, leftmost);
}

QAbstractAnimation* AVLTree::getPosAnim()
{
    QParallelAnimationGroup* group = new QParallelAnimationGroup();
    QVector<qreal> leftmost;
    CalcNodePos(root, 0, leftmost);
    getPosAnim(root, 0, group);
    return group;
}

void AVLTree::getEdgeAnim(TreeNode *node, TreeNode *parent, QAnimationGroup *group)
{
    if (node == NULL) return;
    group->addAnimation(node->setParent(parent));
    getEdgeAnim(node->Lson, node, group);
    getEdgeAnim(node->Rson, node, group);
}

int AVLTree::Count(TreeNode *node)
{
    if (node == NULL) return 0;
    return Count(node->Lson) + Count(node->Rson) + 1;
}

qreal AVLTree::ASL(TreeNode *node, int depth)
{
    if (node == NULL) return 0;
    return ASL(node->Lson, depth + 1) + ASL(node->Rson, depth + 1) + depth + 1;
}

void AVLTree::getPosAnim(TreeNode *node, int depth, QAnimationGroup *group)
{
    if (node == NULL) return;
    group->addAnimation(node->getMoveAnim(QPointF(node->rawX - root->rawX, depth * LEVEL_HEIGHT)));
    getPosAnim(node->Lson, depth + 1, group);
    getPosAnim(node->Rson, depth + 1, group);
}

QAbstractAnimation *AVLTree::getEdgeAnim()
{
    QParallelAnimationGroup* group = new QParallelAnimationGroup();
    getEdgeAnim(root, NULL, group);
    return group;
}
