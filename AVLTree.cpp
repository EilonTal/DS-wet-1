#include "AVLTree.h"
template<class T>
AVLTree<T>::AVLTree(T& data):
    : data(data), first(this), hight(1)
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
    }
    else
    {
        return_value = right_tree->insertElement();
    }
    return return_value;
}

template<class T>
int AVLTree<T>::getLeftHight()
{
    if (left_tree == nullptr)
    {
        return 0;
    }
    return left_tree.calculateHight();
}

template<class T>
int AVLTree<T>::getRightHight()
{
    if (right_tree == nullptr)
    {
        return 0;
    }
    return right_tree.calculateHight();
}

template<class T>
int AVLTree<T>::calculateHight()
{
    return 1+getRightHight()+getLeftHight();
}

template<class T>
int AVLTree<T>::calculateBalance() 
{
    return getLeftHight()-getRightHight();
}

template<class T>
void AVLTree<T>::doRoll() 
{
    hight = calculateHight();
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
    hight = calculateHight();
    balance = calculateBalance();   
}
template<class T>
void AVLTree<T>::LL()
{
    std::shared_ptr<AVLTree> temp = this;
    
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

template<class T>
template<class S>
std::shared_ptr<S> AVLTree<T>::getBestElements(int num_of_elements);
