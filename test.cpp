#include "CoursesManager.h"
#include <iostream>

void printBT(const std::string &prefix, AVLTree<int>* node, bool isLeft)
{
    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "'--");

        // print the value of the node
        std::cout << node->getData() << std::endl;

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "|  " : "    "), node->getLeftTree(), true);
        printBT(prefix + (isLeft ? "|   " : "    "), node->getRightTree(), false);
    }
}

void printBTA(AVLTree<int>* node)
{
    printBT("", node, false);
    std::cout<<"first:"<<node->getFirst()<<std::endl;
    std::cout <<"_"<< std::endl;
}
int main() {
    int a = 5;
    int b = 3;
    int c = 4;
    int d = 8;
    int e = 9;
    int f = 10;
    AVLTree<int> tree;
    tree.insertElement(b);
    tree.insertElement(a);
    tree.insertElement(c);
    printBTA(tree.getTree());
    tree.insertElement(d);
    printBTA(tree.getTree());
    tree.insertElement(e);
    printBTA(tree.getTree());
    tree.insertElement(f);
    printBTA(tree.getTree());
    tree.deleteElement(c);
    printBTA(tree.getTree());
    int tmp = 0;
    int *arr = tree.getBestElements(3, tmp);
    std::cout<<"arr is:"<<std::endl;
    for (int i =0; i<3 ;i++)
    {
        std::cout<<arr[i]<<std::endl;
    }
}