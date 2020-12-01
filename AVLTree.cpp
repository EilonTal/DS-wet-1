#include "AVLTree.h"
template<class T>
AVLTree<T>::AVLTree(T& data):
: data(data), first(this), height(1), father(nullptr)
{
}

template<class T>
StatusType AVLTree<T>::insertElement(T &element)
{
    StatusType return_value = SUCCESS;
    if (data == element)
    {
        return FAILURE;
    }
    if (data < element)
    {
        return_value = insertToLeft(element);
    }
    else
    {
        return_value = insertToRight(element);
    }
    doRoll();
    return return_value
}

template<class T>
StatusType AVLTree<T>::insertToLeft(T& element)
{
    StatusType return_value = SUCCESS;
    if (left_tree == nullptr)
    {
        left_tree = std::shared_ptr<AVLTree>(AVLTree(element));
        left_tree->father = this;
    }
    else
    {
        return_value = left_tree->insertElement();
    }
    return return_value;
}

template<class T>
StatusType AVLTree<T>::insertToRight(T& element)
{
    StatusType return_value = SUCCESS;
    if (right_tree == nullptr)
    {
        right_tree = std::shared_ptr<AVLTree>(AVLTree(element));
        right_tree->father = this;

    }
    else
    {
        return_value = right_tree->insertElement();
    }
    return return_value;
}

template<class T>
int AVLTree<T>::getLeftHeight()
{
    if (left_tree == nullptr)
    {
        return 0;
    }
    return left_tree.calculateHeight();
}

template<class T>
int AVLTree<T>::getRightHeight()
{
    if (right_tree == nullptr)
    {
        return 0;
    }
    return right_tree.calculateHeight();
}

template<class T>
int AVLTree<T>::calculateHeight()
{
    return 1 + std::max(getRightHeight(), getLeftHeight());
}

template<class T>
int AVLTree<T>::calculateBalance()
{
    return getLeftHeight()-getRightHeight();
}

template<class T>
void AVLTree<T>::doRoll()
{
    height = calculateHeight();
    balance = calculateBalance();
    if (balance > 1)
    {
        if (left_tree->balance >= 0)
        {
            LL();
        }
        LR();
    }
    else if(balance < -1)
    {
        if(right_tree->balance <= 0)
        {
            RR();
        }
        RL();
    }
    height = calculateHeight();
    balance = calculateBalance();
}

template<class T>
void AVLTree<T>::LL()
{
    std::shared_ptr<AVLTree> AR_temp = this->left_tree->right_tree;

    // changing A to be root
    this = this->left_tree;

    // changing A right son to be B
    this->right_tree = this->father;
    this->right_tree->father = this;
    this->father = nullptr;

    // rolling previous right son of A to be left son of B
    this->right_tree->left_tree = AR_temp;
    this->right_tree->left_tree->father = this->right_tree;

    //update height and balance
    this->right_tree->height = this->right_tree->calculateHeight();
    this->right_tree->balance = this->right_tree->calculateBalance();
    height = calculateHeight();
    balance = calculateBalance();
}

template<class T>
void AVLTree<T>::RR()
{
    std::shared_ptr<AVLTree> BL_temp = this->right_tree->left_tree;

    // changing A to be root
    this = this->right_tree;

    // changing A left son to be B
    this->left_tree = this->father;
    this->left_tree->father = this;
    this->father = nullptr;

    // rolling previous left son of A to be left son of B
    this->left_tree->right_tree = BL_temp;
    this->left_tree->right_tree->father = this->left_tree;

    //update height and balance
    this->right_tree->height = this->right_tree->calculateHeight();
    this->right_tree->balance = this->right_tree->calculateBalance();
    height = calculateHeight();
    balance = calculateBalance();
}

template<class T>
void AVLTree<T>::LR()
{
    std::shared_ptr<AVLTree> A_temp = this->right_tree->left_tree;
    this->left_tree->RR();
    A_temp->father = this;
    this->LL();
}

template<class T>
void AVLTree<T>::RL()
{
    std::shared_ptr<AVLTree> A_temp = this->right_tree->left_tree;
    this->right_tree->LL();
    A_temp->father = this;
    this->RR();
}

template<class T>
template<class Id>
StatusType AVLTree<T>::deleteElement(Id &id)
{
    std::shared_ptr<AVLTree> v = getElementPointer(id);

}
template<class T>
StatusType AVLTree<T>::deleteThisElement(std::shared_ptr<AVLTree> v)
{
    if (isLeaf)
    {
        if (father->left_tree == v)
        {

        }
    }
}

bool AVLTree::isLeaf()
{
    return right_tree == nullptr && left_tree == nullptr;
}

bool AVLTree::isRoot()
{
    return father == nullptr;
}

template<class T>
std::shared_ptr<AVLTree<T>> AVLtree::getLeftTree()
{
    return left_tree;
}

template<class T>
std::shared_ptr<AVLTree<T>> AVLtree::getRightTree()
{
    return right_tree;
}

template<class T>
std::shared_ptr<AVLTree<T>> AVLtree::getFather()
{
    return father;
}

template<class T>
std::shared_ptr<AVLTree<T>> AVLtree::getFirst()
{
    return first;
}

template<class T>
template<class S>
std::shared_ptr<S> AVLTree<T>::getBestElements(int num_of_elements);
