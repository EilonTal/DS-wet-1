#include <memory>
class Class
{
private:
    int time;
    int courseId;
    int classId;
public:
    Class(int coursId, int classId, int time = 0);
    ~Class() = default;
    Class(Class& c);
    Class& operator=(Class& c);
    bool operator<(Class& c);
    bool operator>(Class& c);
    bool operator==(Class& c);
    int getTime();
    int getCourseId();
    int getClassId();
    int addTime(int time);
};

