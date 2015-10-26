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

void AVLTree::Insert(TreeNode * &node, TreeNode *parent, int x)
{
    if (node == NULL)
    {
        node = new TreeNode();
        view->addNode(node);
        node->data = x;
        node->setPos(parent ? parent->pos() : QPointF(0, 0));
        node->setParent(parent, view);
        return;
    }
    if (node->data > x)
    {
        Insert(node->Lson, node, x);
        if (2 == height(node->Lson) - height(node->Rson))
        {
            if (x < node->Lson->data)
                LL(node);
            else
                LR(node);
        }
    }
    else if (node->data < x)
    {
        Insert(node->Rson, node, x);
        if (2 == height(node->Rson) - height(node->Lson))
        {
            if (x > node->Rson->data)
                RR(node);
            else
                RL(node);
        }
    }
    node->h = max(height(node->Lson), height(node->Rson)) + 1;
}

void AVLTree::Delete(TreeNode * &node, int x)
{
    if (node == NULL) return;//没有找到值是x的节点
    if (x < node->data)
    {
        //如果x小于节点的值,就继续在节点的左子树中删除x
        Delete(node->Lson, x);
        if (2 == height(node->Rson) - height(node->Lson))
        {
            if (node->Rson->Lson != NULL &&
                (height(node->Rson->Lson)>height(node->Rson->Rson)))
                RL(node);
            else
                RR(node);
        }

    }
    else if (x > node->data)
    {
        Delete(node->Rson, x);//如果x大于节点的值,就继续在节点的右子树中删除x
        if (2 == height(node->Lson) - height(node->Rson))
        {
            if (node->Lson->Rson != NULL &&
                (height(node->Lson->Rson)>height(node->Lson->Lson)))
                LR(node);
            else
                LL(node);
        }

    }
    else//如果相等,此节点就是要删除的节点
    {
        node->pop();
        if (node->Lson&&node->Rson)//此节点有两个儿子
        {
            TreeNode* temp = node->Rson;//temp指向节点的右儿子
            while (temp->Lson != NULL) temp = temp->Lson;//找到右子树中值最小的节点
            //把右子树中最小节点的值赋值给本节点
            node->data = temp->data;
            //node->freq = temp->freq;
            Delete(node->Rson, temp->data);//删除右子树中最小值的节点
            if (2 == height(node->Lson) - height(node->Rson))
            {
                if (node->Lson->Rson != NULL &&
                    (height(node->Lson->Rson)>height(node->Lson->Lson)))
                    LR(node);
                else
                    LL(node);
            }
        }
        else//此节点有1个或0个儿子
        {
            TreeNode* temp = node;
            TreeNode* parent = node->parent;
            if (node->Lson == NULL)//有右儿子或者没有儿子
                node = node->Rson;
            else if (node->Rson == NULL)//有左儿子
                node = node->Lson;
            temp->fadeOut();
            if (node) node->setParent(parent, view);
        }
    }
    if (node == NULL) return;
    node->h = max(height(node->Lson), height(node->Rson)) + 1;
    return;
}

bool AVLTree::Find(TreeNode *node, int x)
{
    if (node == NULL) return false;
    if (node->data == x)
    {
        node->pop();
        return true;
    }
    if (Find(node->Lson, x) || Find(node->Rson, x)) return true;
    return false;
}

void AVLTree::Clear(TreeNode *node)
{
    if (node == NULL) return;
    Clear(node->Lson);
    Clear(node->Rson);
    node->fadeOut();
}

int AVLTree::height(TreeNode * &node)
{
    if (node != NULL) return node->h;
    else return -1;
}

void AVLTree::LL(TreeNode * &k2)
{
    TreeNode *k1;
    k1 = k2->Lson;
    k2->Lson = k1->Rson;
    k1->Rson = k2;
    k1->setParent(k2->parent, view);
    k2->setParent(k1, view);
    if (k2->Lson) k2->Lson->setParent(k2, view);
    k2->h = max(height(k2->Lson), height(k2->Rson)) + 1;
    k1->h = max(height(k1->Lson), k2->h) + 1;
    k2 = k1;
}

void AVLTree::RR(TreeNode * &k2)
{
    TreeNode *k1;
    k1 = k2->Rson;
    k2->Rson = k1->Lson;
    k1->Lson = k2;
    k1->setParent(k2->parent, view);
    k2->setParent(k1, view);
    if (k2->Rson) k2->Rson->setParent(k2, view);
    k1->h = max(height(k1->Lson), height(k1->Rson)) + 1;
    k2->h = max(height(k2->Lson), height(k2->Rson)) + 1;
    k2 = k1;
}

void AVLTree::LR(TreeNode * &k2)
{
    RR(k2->Lson);
    LL(k2);
}

void AVLTree::RL(TreeNode * &k2)
{
    LL(k2->Rson);
    RR(k2);
}

void AVLTree::Insert(int x)
{
    Insert(root, NULL, x);
    AnimNode();
}

void AVLTree::Delete(int x)
{
    Delete(root, x);
    AnimNode();
}

void AVLTree::Find(int x)
{
    Find(root, x);
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

void AVLTree::PreOrder(TreeNode * node, QSequentialAnimationGroup *group)
{
    if (node == NULL) return;
    group->addAnimation(node->getPopAnim());
    PreOrder(node->Lson, group);
    PreOrder(node->Rson, group);
}

void AVLTree::InOrder(TreeNode * node, QSequentialAnimationGroup *group)
{
    if (node == NULL) return;
    InOrder(node->Lson, group);
    group->addAnimation(node->getPopAnim());
    InOrder(node->Rson, group);
}

void AVLTree::PostOrder(TreeNode *node, QSequentialAnimationGroup *group)
{
    if (node == NULL)return;
    PostOrder(node->Lson, group);
    PostOrder(node->Rson, group);
    group->addAnimation(node->getPopAnim());
}

void AVLTree::AnimNode()
{
    QVector<qreal> leftmost;
    CalcNodePos(root, 0, leftmost);
    AnimNode(root, 0);
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

void AVLTree::AnimNode(TreeNode *node, int depth)
{
    if (node == NULL) return;
    node->moveTo(QPointF(node->rawX - root->rawX, depth * LEVEL_HEIGHT));
    AnimNode(node->Lson, depth + 1);
    AnimNode(node->Rson, depth + 1);
}
