#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <iomanip>
#include "./system.h"
using namespace std;

/**
 * @brief 等待回车输入
 * @param prompt 提示语
*/
void wait_for_enter(const char* prompt)
{
	cout << endl << prompt << ",请按回车键继续";
	while (getchar() != '\n')
		;
	cout << endl << endl;
}

/**
 * @brief 初始化系统
 * @param tj 同济大学选课系统
*/
void InitSystem(EduSystem& tj)
{
	char FileDir[128];
	system("mode con: cols=83 lines=30");
	ifstream File;
	cout << endl << endl << endl << endl;
	cout << "\t\t\t欢迎登录同济大学学生信息管理系统!" << endl;
	cout << endl << endl << endl << endl << endl << endl;

	while (true) {
		cout << "\t\t[请输入学生名单路径导入学生名单]" << endl;
		cout << "\t\t请在此处键入:";
		cin >> FileDir;
		File.open(FileDir, ios::in);
		if (File.is_open())
			break;
		else
			cout << "\t\t文件打开失败, 请重试!" << endl;
	}
	tj.InitStudentList(File);
	cout << "\t\t共成功插入学生" << tj.GetStudentNum() << "个!" << endl << endl;
	File.close();

	while (true) {
		cout << "\t\t[请输入课程名单路径导入课程名单]" << endl;
		cout << "\t\t请在此处键入:";
		cin >> FileDir;
		File.open(FileDir, ios::in);
		if (File.is_open())
			break;
		else
			cout << "\t\t文件打开失败, 请重试!" << endl;
	}
	tj.InitCourseList(File);
	cout << "\t\t共成功插入课程" << tj.GetCourseNum() << "个!" << endl;

	getchar();
	wait_for_enter("\t\t初始化名单完毕");
}

/**
 * @brief 可视化菜单界面
 * @return 选择的菜单项
*/
int Menu()
{
	system("mode con: cols=83 lines=30");
	cout << endl << endl << endl << endl;
	cout << "\t\t\t\t同济大学选课系统" << endl;

	cout << endl << endl;
	cout << "\t\t\t\t    菜单选择" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl;
	cout << "\t|\t1\t|\t2\t|\t3\t|\t4\t|" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << "\t|   新增学生\t|    新增课程\t|    删除学生\t|    删除课程\t|" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl;
	cout << "\t|\t5\t|\t6\t|\t7\t|\t0\t|" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << "\t|   查询学生\t|    查询课程\t|    课程注册\t|    退出系统\t|" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl << endl << endl;
	cout << "\t\t\t     [请按对应数字选择功能]" << endl;
	cout << "\t\t\t\t\t";
	while (char ch = _getch())
		if (ch >= '0' && ch <= '7')
			return ch - '0';
	return 0;
}

int main()
{
	EduSystem TongjiEdu;
	InitSystem(TongjiEdu);
	int ret;
	while (ret = Menu())
	{
		StudentInfo tmps;
		CourseInfo tmpc;
		ostringstream out;
		switch (ret) {
			case 1:
				system("cls");
				char tmpt[20];
				cout << "\n\t\t\t\t[新增学生信息]" << endl;
				cout << endl << endl << endl << endl;
				while (true) {
					cout << "\t\t请输入学生学号:";
					cin >> tmps.ID;
					if (cin.good())
						break;
					cin.clear();
					cin.ignore(65536, '\n');
				}
				cout << "\n\t\t请输入学生姓名:";
				cin >> tmps.name;
				while (true) {
					cout << "\n\t\t请输入学生性别:";
					cin >> tmpt;
					if (strcmp(tmpt, "男") == 0) {
						tmps.gender = 'M';
						break;
					}
					else if (strcmp(tmpt, "女") == 0) {
						tmps.gender = 'F';
						break;
					}
					cout << "\t\t性别必须为 男 / 女!" << endl;
				}
				cout << "\n\t\t请输入学生专业:";
				cin >> tmps.major;
				if (TongjiEdu.InsertStudent(tmps) == ERROR) {
					getchar();
					wait_for_enter("\n\n\t\t该学号已经有学生");
				}
				else {
					getchar();
					wait_for_enter("\n\n\t\t学生信息录入完毕");
				}
				break;
			case 2:
				system("cls");
				cout << "\n\t\t\t\t[新增课程信息]" << endl;
				cout << endl << endl << endl << endl;
				while (true) {
					cout << "\t\t请输入课程课号:";
					cin >> tmpc.ID;
					if (cin.good())
						break;
					cin.clear();
					cin.ignore(65536, '\n');
				}
				cout << "\n\t\t请输入课程课名:";
				cin >> tmpc.name;
				cout << "\n\t\t请输入课程学分:";
				cin >> tmpc.credit;
				cout << "\n\t\t请输入上课地点:";
				cin >> tmpc.venue;
				if (TongjiEdu.InsertCourse(tmpc) == ERROR) {
					getchar();
					wait_for_enter("\n\n\t\t该课号已经有课程");
				}
				else {
					getchar();
					wait_for_enter("\n\n\t\t课程信息录入完毕");
				}
				break;
			case 3:
				system("cls");
				cout << "\n\t\t\t\t[删除学生信息]" << endl;
				cout << endl << endl << endl << endl;
				while (true) {
					cout << "\t\t请输入学生学号:";
					cin >> tmps.ID;
					if (cin.good())
						break;
					cin.clear();
					cin.ignore(65536, '\n');
				}
				if (TongjiEdu.DeleteStudent(tmps) == ERROR)
					cout << "\t\t不存在该学生!!!" << endl;
				else
					cout << "\t\t\n\t\t[学号]" << tmps.ID << "\n\t\t[姓名]" << tmps.name << "\n\t\t[性别]" << (tmps.gender == 'M' ? "男" : "女") << "\n\t\t[专业]" << tmps.major << "\n\t\t已成功删除" << endl;
				getchar();
				wait_for_enter("\n\n\t\t功能执行结束");
				break;
			case 4:
				system("cls");
				cout << "\n\t\t\t\t[删除课程信息]" << endl;
				cout << endl << endl << endl << endl;
				while (true) {
					cout << "\t\t请输入课程课号:";
					cin >> tmpc.ID;
					if (cin.good())
						break;
					cin.clear();
					cin.ignore(65536, '\n');
				}
				if (TongjiEdu.DeleteCourse(tmpc) == ERROR)
					cout << "\t\t不存在该课程!!!" << endl;
				else
					cout << "\t\t\n\t\t[课号]" << tmpc.ID << "\n\t\t[课名]" << tmpc.name << "\n\t\t[学分]" << tmpc.credit << "\n\t\t[地点]" << tmpc.venue << "\n\t\t已成功删除" << endl;
				getchar();
				wait_for_enter("\n\n\t\t功能执行结束");
				break;
			case 5:
				system("cls");
				cout << "\n\t\t\t\t[查询学生信息]" << endl;
				cout << endl << endl << endl << endl;
				while (true) {
					cout << "\t\t请输入学生学号:";
					cin >> tmps.ID;
					if (cin.good())
						break;
					cin.clear();
					cin.ignore(65536, '\n');
				}
				if (TongjiEdu.SearchStudent(tmps, out) == ERROR)
					cout << "\t\t不存在该学生!!!" << endl;
				else
					cout << "\t\t该学生的信息是:\n\t\t[学号]" << tmps.ID << "\n\t\t[姓名]" << tmps.name << "\n\t\t[性别]" << (tmps.gender == 'M' ? "男" : "女") << "\n\t\t[专业]" << tmps.major << endl;
				cout << "\n\t\t注册的课程如下:\n" << out.str();
				getchar();
				wait_for_enter("\n\n\t\t功能执行结束");
				break;
			case 6:
				system("cls");
				cout << "\n\t\t\t\t[查询课程信息]" << endl;
				cout << endl << endl << endl << endl;
				while (true) {
					cout << "\t\t请输入课程课号:";
					cin >> tmpc.ID;
					cout << tmpc.ID << endl;
					if (cin.good())
						break;
					cin.clear();
					cin.ignore(65536, '\n');
				}
				if (TongjiEdu.SearchCourse(tmpc, out) == ERROR)
					cout << "\t\t不存在该课程!!!" << endl;
				else
					cout << "\t\t该课程的信息是:\n\t\t[课号]" << tmpc.ID << "\n\t\t[课名]" << tmpc.name << "\n\t\t[学分]" << tmpc.credit << "\n\t\t[地点]" << tmpc.venue << endl;
				cout << "\n\t\t注册的学生如下:\n" << out.str();
				getchar();
				wait_for_enter("\n\n\t\t功能执行结束");
				break;
			case 7:
				system("cls");
				cout << "\n\t\t\t\t[学生注册课程]" << endl;
				cout << endl << endl << endl << endl;
				while (true) {
					cout << "\t\t请输入学生学号:";
					cin >> tmps.ID;
					if (cin.good())
						break;
					cin.clear();
					cin.ignore(65536, '\n');
				}
				cout << endl << endl << endl << endl;
				while (true) {
					cout << "\t\t请输入课程课号:";
					cin >> tmpc.ID;
					if (cin.good())
						break;
					cin.clear();
					cin.ignore(65536, '\n');
				}
				int ret = TongjiEdu.Register(tmpc, tmps);
				if (ret == NO_STUDENT)
					cout << "\n\n\t\t学生不存在!" << endl;
				else if (ret == NO_COURSE)
					cout << "\n\n\t\t课程不存在!" << endl;
				else if (ret == ALREADY_REGISTER)
					cout << "\n\n\t\t该学生已注册过该课程" << endl;
				else
					cout << "\n\n\t\t课程注册成功" << endl;
				getchar();
				wait_for_enter("\n\n\t\t功能执行结束");
				break;
		}
	}

	return 0;
}