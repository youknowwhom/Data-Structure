#pragma once
#include <iostream>
#include <sstream>
#include <cstring>
#include "./hashtable.hpp"
#define HashLength 19997
#define NO_STUDENT 10
#define NO_COURSE 11
#define ALREADY_REGISTER 12
using namespace std;

struct CourseInfo;	//先做不完整的声明

/* 学生信息 */
struct StudentInfo {
	long long ID;						//学号
	char name[32];						//姓名
	char major[64];						//专业
	char gender;						//性别 F/M
	SqList<long long> courses;			//选课(存课号)
	/* 用于查找学生信息 学号匹配即可 */
	bool operator==(const StudentInfo& that) const
	{
		return ID == that.ID;
	}
};

/* 课程信息 */
struct CourseInfo {
	long long ID;						//课号
	char name[32];						//课名
	float credit;						//学分
	char venue[64];						//上课地点
	SqList<long long> students;			//所选学生(存学号)
	/* 用于查找课程信息 课号匹配即可 */
	bool operator==(const CourseInfo& that) const
	{
		return ID == that.ID;
	}
};

/* 选课系统 */
class EduSystem {
	Hashtable<StudentInfo> StudentList;		//学生列表
	Hashtable<CourseInfo> CourseList;		//课程列表
	int StudentNum, CourseNum;				//学生、课程数量
public:
	//获取学生数量
	int GetStudentNum();		
	//获取课程数量
	int GetCourseNum();			
	//初始化学生列表
	Status InitStudentList(istream& in);
	//初始化课程列表
	Status InitCourseList(istream& in);	
	//插入学生信息
	Status InsertStudent(const StudentInfo& e);		
	//插入课程信息
	Status InsertCourse(const CourseInfo& e);
	//删除学生信息
	Status DeleteStudent(StudentInfo& e);	
	//删除课程信息
	Status DeleteCourse(CourseInfo& e);			
	//查询学生信息
	Status SearchStudent(StudentInfo& e, ostringstream& out);	
	//查询课程信息
	Status SearchCourse(CourseInfo& e, ostringstream& out);			
	//注册课程
	Status Register(CourseInfo& ec, StudentInfo& es);				
};

