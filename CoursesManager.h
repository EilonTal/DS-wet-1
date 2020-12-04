#include "AVLTree.h"
#include "Course.h"

class CoursesManager
{
private:
    AVLTree<Course> courseTree;
    AVLTree<Class> viewedTree;
    StatusType ValidateInput(int courseId, int classId = 0,
    int numOfClasses = 0, int time = 1);
public:
    CoursesManager() = default;
    ~CoursesManager() = default;
    StatusType AddCourse(int course_id, int num_of_classes);
    StatusType RemoveCourse(int course_id);
    StatusType WatchClass(int course_id, int class_id, int time);
    StatusType TimeViewed(int course_id, int  class_id, int * TimeViewed);
    StatusType GetMostViewedClasses(int num_of_classes, int * courses, int * classes);
    void Quit();

    //forDebuge
    AVLTree<Course>* getCourseTree()
    {
        return &courseTree;
    }
    AVLTree<Class> *getViewedTree()
    {
        return &viewedTree;
    }
};

