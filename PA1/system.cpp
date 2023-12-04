#define _CRT_SECURE_NO_WARNINGS
#include "./system.h"
/**
 * @brief 计算在哈希表中对应下标
 * @param e 计算的元素
 * @return 下标值
*/
static int GetIndex(const CourseInfo& e)
{
	return e.ID % HashLength;
}

/**
 * @brief 计算在哈希表中对应下标
 * @param e 计算的元素
 * @return 下标值
*/
static int GetIndex(const StudentInfo& e)
{
	return e.ID % HashLength;
}

/**
 * @brief 取系统学生数量
 * @return 学生数量
*/
int EduSystem::GetStudentNum()
{
	return StudentNum;
}

/**
 * @brief 取系统课程数量
 * @return 课程数量
*/
int EduSystem::GetCourseNum()
{
	return CourseNum;
}

/**
 * @brief 初始化学生名单
 * @param in 输入流
 * @return 初始化状态
*/
Status EduSystem::InitStudentList(istream& in)
{
	StudentNum = 0;
	while (in.peek() != EOF) {
		StudentInfo tmp;
		char temp[20];
		in >> tmp.ID >> tmp.name >> temp >> tmp.major;
		if (strcmp(temp, "男") == 0)
			tmp.gender = 'M';
		else if (strcmp(temp, "女") == 0)
			tmp.gender = 'F';
		StudentList.TableInsert(tmp, &GetIndex);
		StudentNum++;
		in.get();
	}
	return OK;
}

/**
 * @brief 初始化课程名单
 * @param in 输入流
 * @return 初始化状态
*/
Status EduSystem::InitCourseList(istream& in)
{
	CourseNum = 0;
	while (in.peek() != EOF) {
		CourseInfo tmp;
		in >> tmp.ID >> tmp.name >> tmp.credit >> tmp.venue;
		CourseList.TableInsert(tmp, &GetIndex);
		CourseNum++;
		in.get();
	}
	return OK;
}


/**
 * @brief 插入新学生信息
 * @param e 学生信息
 * @return 插入状态
*/
Status EduSystem::InsertStudent(const StudentInfo& e)
{
	if (StudentList.IsInTable(e, &GetIndex))
		return ERROR;			//学号重复
	return StudentList.TableInsert(e, &GetIndex);
}

/**
 * @brief 插入新课程信息
 * @param e 课程信息
 * @return 插入状态
*/
Status EduSystem::InsertCourse(const CourseInfo& e)
{
	if (CourseList.IsInTable(e, &GetIndex))
		return ERROR;			//课号重复
	return CourseList.TableInsert(e, &GetIndex);
}


/**
 * @brief 删除学生信息
 * @param e 删除的学生信息
 * @return 删除状态
*/
Status EduSystem::DeleteStudent(StudentInfo& e)
{
	return StudentList.TableDelete(e, &GetIndex);
}


/**
 * @brief 删除课程信息
 * @param e 删除的课程信息
 * @return 删除状态
*/
Status EduSystem::DeleteCourse(CourseInfo& e)
{
	return CourseList.TableDelete(e, &GetIndex);
}


/**
 * @brief 查找学生信息
 * @param e 学生信息(传入时通过学号查找, 传出时用于打印信息)
 * @param out 输出流
 * @return 查找状态
*/
Status EduSystem::SearchStudent(StudentInfo& e, ostringstream& out)
{
	if (!StudentList.IsInTable(e, &GetIndex))
		return ERROR;
	else {
		StudentList.TableSearch(e, &GetIndex);
		for (int i = 1; i <= e.courses.ListLength(); i++) {
			CourseInfo c;
			//找到对应的课号
			e.courses.GetElem(i, c.ID);
			//找具体信息
			int pst = CourseList.TableSearch(c, &GetIndex);
			//可能已选的课程被删除了
			if (pst == OK) {
				out << "\t\t[课号]" << c.ID << "\t[课名]" << c.name << "\t[学分]" << c.credit << endl;
			}
		}
	}
	return OK;
}


/**
 * @brief 查找课程信息
 * @param e 课程信息(传入时通过课号查找, 传出时用于打印信息)
 * @param out 输出流
 * @return 查找状态
*/
Status EduSystem::SearchCourse(CourseInfo& e, ostringstream& out)
{
	if (!CourseList.IsInTable(e, &GetIndex))
		return ERROR;
	else {
		CourseList.TableSearch(e, &GetIndex);
		for (int i = 1; i <= e.students.ListLength(); i++) {
			StudentInfo s;
			//找到对应的课号
			e.students.GetElem(i, s.ID);
			//找具体信息
			int pst = StudentList.TableSearch(s, &GetIndex);
			//可能已选的课程被删除了
			if (pst == OK) {
				out << "\t\t[学号]" << s.ID << "\t[姓名]" << s.name << "\t[性别]" << (s.gender == 'M' ? "男" : "女") << "\t[专业]" << s.major << endl;
			}
		}
	}

	return OK;
}


/**
 * @brief 学生注册新课程
 * @param ec 学生信息
 * @param es 课程信息
 * @return 注册状态
*/
Status EduSystem::Register(CourseInfo& ec, StudentInfo& es)
{
	StudentInfo * studentp;
	CourseInfo * coursep;
	int ret1, ret2;
	ret1 = StudentList.LocateElem(es, studentp, &GetIndex);
	ret2 = CourseList.LocateElem(ec, coursep, &GetIndex);
	if (ret1 == ERROR)
		return NO_STUDENT;
	if (ret2 == ERROR)
		return NO_COURSE;
	if (studentp->courses.IsInList(coursep->ID))
		return ALREADY_REGISTER;
	studentp->courses.ListInsert(1, coursep->ID);
	coursep->students.ListInsert(1, studentp->ID);
	return OK;
}
