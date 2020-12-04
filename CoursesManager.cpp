#include "CoursesManager.h"

StatusType CoursesManager::ValidateInput(int course_id, int class_id, int num_of_classes, int time)
{
    if (course_id <= 0 || class_id < 0 || num_of_classes < 0 || time <= 0)
    {
        return INVALID_INPUT;
    }
    return SUCCESS;
}

StatusType CoursesManager::AddCourse(int course_id, int num_of_classes)
{
    if (ValidateInput(course_id, 0, num_of_classes) != SUCCESS)
    {
        return INVALID_INPUT;
    }
    Course c(course_id, num_of_classes);
    if (courseTree.insertElement(c) != SUCCESS)
    {
        return FAILURE;
    }
    return SUCCESS;
}


StatusType CoursesManager::RemoveCourse(int course_id)
{
    if (ValidateInput(course_id) == INVALID_INPUT)
    {
        return INVALID_INPUT;
    }
    Course* course_ptr = courseTree.getElement(course_id);
    if (course_ptr == nullptr)
    {
        return FAILURE;
    }
    for (int i = 0; i < course_ptr->getNumOfClasses(); i++)
    {
        Class *c = course_ptr->getClass(i);
        if (c != nullptr)
        {
            if (viewedTree.deleteElement(*c) != SUCCESS)
            {
                return FAILURE;
            }
        }
    }
    return courseTree.deleteElement(course_id);
}

StatusType CoursesManager::WatchClass(int course_id, int class_id, int time)
{
    if (ValidateInput(course_id, class_id, 0, time) != SUCCESS)
    {
        return INVALID_INPUT;
    }
    Course* course_of_class_ptr = courseTree.getElement(course_id);
    if (course_of_class_ptr == nullptr)
    {
        return FAILURE;
    }
    if (course_of_class_ptr->getNumOfClasses() < class_id + 1)
    {
        return INVALID_INPUT;
    }
    Class tmp_c (course_id, class_id, time);
    Class *class_in_viewed_ptr = viewedTree.getElement(tmp_c);
    if (class_in_viewed_ptr != nullptr)
    {
        Class class_in_viewed = *class_in_viewed_ptr;
        class_in_viewed.addTime(time);
    }
    // class not in viewed tree so it needs to be added
    else
    {
        Class c (course_id, class_id, time);
        // if all classes are used - probably will never happen
        // because it is checked before
        if (course_of_class_ptr->addClass(c) != SUCCESS)
        {
            return FAILURE;
        }
        if (viewedTree.insertElement(c) != SUCCESS)
        {
            return FAILURE;
        }
    }
    return SUCCESS;
}

StatusType CoursesManager::TimeViewed(int course_id, int class_id, int *TimeViewed)
{
    if (ValidateInput(course_id, class_id) == INVALID_INPUT)
    {
        return INVALID_INPUT;
    }
    Course *course_ptr = courseTree.getElement(course_id);
    if (course_ptr == nullptr)
    {
        return FAILURE;
    }
    if (course_ptr->getNumOfClasses() < class_id+1)
    {
        return INVALID_INPUT;
    }
    Class *c = course_ptr->getClass(class_id);
    if (c == nullptr)
    {
        *TimeViewed = 0;
    }
    else
    {
        *TimeViewed = c->getTime();
    }
    return SUCCESS;
}

StatusType CoursesManager::GetMostViewedClasses(int num_of_classes, int *courses, int *classes)
{
    if (num_of_classes <= 0)
    {
        return INVALID_INPUT;
    }
    int counter_of_classes = 0;
    Class *arr_classes = viewedTree.getBestElements(num_of_classes, counter_of_classes);
    for (int i = 0; i < counter_of_classes; i++)
    {
        classes[i] = arr_classes[i].getClassId();
        courses[i] = arr_classes[i].getCourseId();
    }
    if (num_of_classes == counter_of_classes)
    {
        return SUCCESS;
    }
    int num_of_left_classes = num_of_classes - counter_of_classes;
    int counter_of_courses = 0;
    Course *arr_courses = courseTree.getBestElements(num_of_classes, counter_of_courses);
    for (int i = 0; i < counter_of_courses && counter_of_classes != num_of_classes; i++)
    {
        for (int j = 0; arr_courses[i] > j && counter_of_classes != num_of_classes; j++)
        {
            if (arr_courses[i].getClass(j) == nullptr)
            {
                classes[counter_of_classes] = arr_courses[i].getClass(j)->getClassId();
                courses[counter_of_classes] = arr_courses[i].getCourseId();
                counter_of_classes++;
            }
        }
    }
    if (counter_of_classes != num_of_classes)
    {
        return FAILURE;
    }
    return SUCCESS;
}
