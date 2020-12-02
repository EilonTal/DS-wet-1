#include <memory>
#include <algorithm>
#include "library.h"
template<class T>
class AVLTree
{
private:
    std::shared_ptr<AVLTree> left_tree;
    std::shared_ptr<AVLTree> right_tree;
    std::shared_ptr<AVLTree> father;
    std::shared_ptr<AVLTree> first, root;
    int height;
    int balance;

    /*
    * return the height of the left tree
    * if has no left return 0
    */
    int getLeftHeight();
    /*
    * return the height of the right tree
    * if has no right return 0
    */
    int getRightHeight();
    /*
    * return the height of the tree (H(left)+H(right)+1)
    */
    int calculateHeight();
    /*
    * return the balance of the tree (H(left)-H(right))
    */
    int calculateBalance();
    //?
    bool isLeaf();
    bool isRoot();

    std::shared_ptr<AVLTree> getFather();
    StatusType setFather(std::shared_ptr<AVLTree>  element);
    std::shared_ptr<AVLTree> getFirst();
    //?
    template<class Id>
    std::shared_ptr<AVLTree> getElementPointer(Id &data);
    void setFather(T& data);
    /*
    * get the T element to insert
    * insert it to the left tree
    * if there is no such left tree create new tree element of it and insert it
    * return FAILURE if element alredy exists
    *       else return SECCESS
    */
    StatusType insertToLeft(T& element);
    /*
    * get the T element to insert
    * insert it to the right tree
    * if there is no such right tree create new tree element of it and insert it
    * return FAILURE if element alredy exists
    *       else return SECCESS
    */
    StatusType insertToRight(T& element);

    std::shared_ptr<AVLTree> calculateFirst();
    std::shared_ptr<AVLTree> getNextInorder();
    void switchPlaces(std::shared_ptr<AVLTree> v);

    StatusType deleteThisElement(std::shared_ptr<AVLTree> v);
    void LL();
    void LR();
    void RL();
    void RR();
    /*
    * check which roll to do acording to avl algoritem
    */
    void doRoll();

public:
    AVLTree(T& element);
    ~AVLTree() = default;
    AVLTree(AVLTree& tree_to_copy) = default;
    AVLTree& operator=(AVLTree& element) = default;
    /*
    * get the T element to insert
    * insert it to the tree according to T order
    * return FAILURE if element alredy exists
    *       else return SECCESS
    */
    StatusType insertElement(T &element);
    template<class Id>
    StatusType deleteElement(Id &data);
    template<class Id>
    StatusType getElement(Id &data);
    template<class S>
    std::shared_ptr<S> getBestElements(int num_of_elements);
    std::shared_ptr<AVLTree> getPointer();
    std::shared_ptr<AVLTree> getLeftTree();
    std::shared_ptr<AVLTree> getRightTree();
    T data;
};

template <class T>
AVLTree<T>::AVLTree(T &element)
        : data(element), height(1), root(this), first(this), balance(0), father(nullptr), left_tree(nullptr), right_tree(nullptr)
{
}



template <class T>
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
    return return_value;
}

template <class T>
StatusType AVLTree<T>::insertToLeft(T &element)
{
    StatusType return_value = SUCCESS;
    if (left_tree == nullptr)
    {
        AVLTree t(element);
        left_tree = std::shared_ptr<AVLTree>(&t);
        left_tree->father = std::shared_ptr<AVLTree>(this);
    }
    else
    {
        return_value = left_tree->insertElement(element);
    }
    return return_value;
}

template <class T>
StatusType AVLTree<T>::insertToRight(T &element)
{
    StatusType return_value = SUCCESS;
    if (right_tree == nullptr)
    {
        AVLTree t(element);
        right_tree = std::shared_ptr<AVLTree>(&t);
        right_tree->father = std::shared_ptr<AVLTree>(this);
    }
    else
    {
        return_value = right_tree->insertElement(element);
    }
    return return_value;
}

template <class T>
int AVLTree<T>::getLeftHeight()
{
    if (left_tree == nullptr)
    {
        return 0;
    }
    return left_tree->calculateHeight();
}

template <class T>
int AVLTree<T>::getRightHeight()
{
    if (right_tree == nullptr)
    {
        return 0;
    }
    return right_tree->calculateHeight();
}

template <class T>
int AVLTree<T>::calculateHeight()
{
    return 1 + std::max(getRightHeight(), getLeftHeight());
}

template <class T>
int AVLTree<T>::calculateBalance()
{
    return getLeftHeight() - getRightHeight();
}

template <class T>
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
    else if (balance < -1)
    {
        if (right_tree->balance <= 0)
        {
            RR();
        }
        RL();
    }
    height = calculateHeight();
    balance = calculateBalance();
}

template <class T>
void AVLTree<T>::LL()
{
    std::shared_ptr<AVLTree> AR_temp = this->left_tree->right_tree;

    // changing A to be root
    this = &(*left_tree);

    // changing A right son to be B
    this->right_tree = this->father;
    this->right_tree->father = std::shared_ptr<AVLTree>(this);
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

template <class T>
void AVLTree<T>::RR()
{
    std::shared_ptr<AVLTree> BL_temp = this->right_tree->left_tree;

    // changing A to be root
    this = right_tree.get();

    // changing A left son to be B
    this->left_tree = this->father;
    this->left_tree->father = std::shared_ptr<AVLTree>(this);
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

template <class T>
void AVLTree<T>::LR()
{
    std::shared_ptr<AVLTree> A_temp = this->right_tree->left_tree;
    this->left_tree->RR();
    A_temp->father = std::shared_ptr<AVLTree>(this);
    this->LL();
}

template <class T>
void AVLTree<T>::RL()
{
    std::shared_ptr<AVLTree> A_temp = this->right_tree->left_tree;
    this->right_tree->LL();
    A_temp->father = std::shared_ptr<AVLTree>(this);
    this->RR();
}

template <class T>
template <class Id>
StatusType AVLTree<T>::deleteElement(Id &id)
{
    std::shared_ptr<AVLTree> v = getElementPointer(id);
    deleteThisElement(v);
    calculateFirst();
}

template <class T>
StatusType AVLTree<T>::deleteThisElement(std::shared_ptr<AVLTree> v)
{
    if (right_tree != nullptr && left_tree != nullptr)
    {
        switchPlaces(getNextInorder());
    }
    else
    {
        std::shared_ptr<AVLTree> to_father;
        if (isLeaf)
        {
            to_father = nullptr;
        }
        else if (left_tree == nullptr)
        {
            to_father = right_tree;
            right_tree->father = father;
        }
        else
        {
            to_father = left_tree;
            left_tree->father = father;
        }
        if (father == nullptr)
        {
            root = to_father;
        }
        else
        {
            if (father->left_tree == v)
            {
                father->left_tree = to_father;
            }
            else
            {
                father->right_tree = to_father;
            }
        }
    }
    return SUCCESS;
}

template <class T>
void AVLTree<T>::switchPlaces(std::shared_ptr<AVLTree> v)
{
    T tmp = v.data;
    v.data = data;
    data = tmp;
}

template <class T>
bool AVLTree<T>::isLeaf()
{
    return right_tree == nullptr && left_tree == nullptr;
}

template <class T>
bool AVLTree<T>::isRoot()
{
    return father == nullptr;
}

template <class T>
std::shared_ptr<AVLTree<T>> AVLTree<T>::getLeftTree()
{
    return left_tree;
}

template <class T>
std::shared_ptr<AVLTree<T>> AVLTree<T>::getRightTree()
{
    return right_tree;
}

template <class T>
std::shared_ptr<AVLTree<T>> AVLTree<T>::getFather()
{
    return father;
}

template <class T>
std::shared_ptr<AVLTree<T>> AVLTree<T>::getFirst()
{
    return first;
}

//template<class T>
//template<class S>
//std::shared_ptr<S> AVLTree<T>::getBestElements(int num_of_elements);
