#include "CoursesManager.h"
#include <iostream>
#define COUNT 10

// Function to print binary tree in 2D  
// It does reverse inorder traversal
template <class T>  
void print2DUtil(AVLTree<T> *root, int space)  
{  
    // Base case  
    if (root == nullptr)  
        return;  
  
    // Increase distance between levels  
    space += COUNT;  
  
    // Process right child first  
    print2DUtil(root->getRightTree(), space);  
  
    // Print current node after space  
    // count  
    std::cout<<std::endl;  
    for (int i = COUNT; i < space; i++)  
        std::cout<<" ";  
    std::cout<<root->getData()<< std::endl;  
  
    // Process left child  
    print2DUtil(root->getLeftTree(), space);  
}  
  
// Wrapper over print2DUtil()
template <class T>
void print2D(AVLTree<T> *root)
{  
    // Pass initial space count as 0  
    std::cout<<"___________print tree:___________"<<std::endl;
    print2DUtil(root, 0);
    std::cout << "\n___________end tree:___________\n" << std::endl;
}  

template<class T>
void printBT(const std::string &prefix, AVLTree<T> *node, bool isLeft)
{
    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "'--");

        // print the value of the node
        std::cout <<node->getData() << std::endl;

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "│   " : "    "), node->getLeftTree(), true);
        printBT(prefix + (isLeft ? "│   " : "    "), node->getRightTree(), false);
    }
}
template <class T>
void printBTA(AVLTree<T> *node)
{
    printBT("", node, false);
    std::cout<<"\nfirst:"<<node->getFirst()<<std::endl;
    std::cout <<"_"<< std::endl;
}
int main() 
{
 /*   AVLTree<int> tree;
    int a1 = 11, a2 = 14, a3 = 13, a4 = 12;
    tree.insertElement(a1);
    tree.insertElement(a2);
    tree.insertElement(a3);
    tree.insertElement(a4);
    tree.deleteElement(a1);
    tree.deleteElement(a3); */

    CoursesManager cm;
    cm.AddCourse(11, 3);
    cm.AddCourse(14, 4);
    cm.AddCourse(13, 2);
    cm.AddCourse(12, 2);
    cm.WatchClass(12, 0, 7);
    cm.WatchClass(11, 0, 3);
    cm.WatchClass(14, 3, 8);
    cm.WatchClass(12, 1, 5);
    cm.WatchClass(13, 1, 6);
    print2D(cm.getViewedTree()->getTree());
    int num_to_print = 3;
    int *courses = new int[num_to_print], *classes = new int[num_to_print];
    cm.GetMostViewedClasses(num_to_print, courses, classes);
    std::cout << "print most" << std::endl;
    for (int i = 0; i < num_to_print; i++)
    {
        std::cout<<courses[i]<<": "<<classes[i]<<std::endl;
    }
    print2D(cm.getCourseTree()->getTree());
    print2D(cm.getViewedTree()->getTree());
    cm.RemoveCourse(11);
    cm.RemoveCourse(13);
    print2D(cm.getCourseTree()->getTree());
    print2D(cm.getViewedTree()->getTree());
    delete[] courses;
    delete[] classes;
    num_to_print = 3;
    courses = new int[num_to_print];
    classes = new int[num_to_print];
    cm.GetMostViewedClasses(num_to_print, courses, classes);
    std::cout << "print most" << std::endl;
    for (int i = 0; i < num_to_print; i++)
    {
        std::cout << courses[i] << ": " << classes[i] << std::endl;
    }
    delete[] courses;
    delete[] classes;
}