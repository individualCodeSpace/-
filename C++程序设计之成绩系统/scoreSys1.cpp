#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include<sstream>
#include <iomanip> 
#include <regex>
using namespace std;

struct Student {
	string name;
	string id;
	vector<int> scores;
};

std::vector<Student> students;

// 初始化students变量，从cj.txt文件读取数据
void initializeStudentsFromFile(string filename) {
	std::ifstream infile(filename);
	if (!infile) {
		std::cerr << "Error: Unable to open file!" << std::endl;
		return;
	}

	std::string line;
	std::getline(infile, line); // 跳过表头

	while (std::getline(infile, line)) {

		int score;

		std::regex pattern("\\t\\t"); // 匹配一个或多个连续的空格&&制表符

		std::string result = std::regex_replace(line, pattern, "  -1  ");

		std::regex pattern1("\\s"); // 匹配一个或多个连续的空格&&制表符


		std::istringstream ss(result);
		Student student;
		//// 假设学号和姓名的宽度分别为10和20
		ss >> student.id >> student.name;

		if (student.id != "-1")
		{
			//假设每个成绩的宽度为5
			for (int i = 0; i < 4; ++i) {

				//cout << line << endl;

				ss >> std::setw(5);
				if (ss >> score)
				{
					student.scores.push_back(score);
				}
				else
				{
					student.scores.push_back(-1); // 假设-1代表空白成绩
					ss.clear(); // 清除错误状态
				}

			}

			students.push_back(student);

		}

	}

	infile.close();
}
//初始界面
void displayMenu() {
	cout << "学生成绩管理系统" << endl;
	cout << "*******************************************************" << endl;
	cout << "1. 学生成绩显示" << endl;
	cout << "2. 学生成绩查询" << endl;
	cout << "3. 学生成绩添加" << endl;
	cout << "4. 学生成绩修改" << endl;
	cout << "5. 学生成绩删除" << endl;
	cout << "6. 统计学生成绩" << endl;
	cout << "7. 退出系统" << endl;
	cout << "请选择功能编号（1-7）：";
}
// 要求一：通过姓名或者学号查询students数组里的课程成绩信息
void queryScoreByNameOrId() {
	string input;
	cout << "请输入姓名或学号进行查询：";
	cin >> input;

	bool found = false;
	for (const auto& student : students)
	{
		if (student.name == input || student.id == input) {
			cout << "姓名：" << student.name << "\t学号：" << student.id << endl;
			cout << "各科成绩：";
			for (const auto& score : student.scores) {
				cout << score << " ";
			}
			cout << endl;
			found = true;
			break;
		}
	}

	if (!found) {
		cout << "未找到匹配的学生信息！" << endl;
	}
}
//要求2:成绩录入，分为单条录入和通过文件批量导入，若学生信息不在students数组,则新增，若存在则修改
void addScore() {
	bool exitLoop = false;
	int choice;
	do {
		cout << "学生成绩管理系统" << endl;
		cout << "*******************************************************" << endl;
		cout << "1. 单条信息录入" << endl;
		cout << "2. 按文件批量导入" << endl;
		cout << "3. 返回上一级目录" << endl;
		cout << "请选择功能编号：";
		cin >> choice;

		switch (choice) {
		case 1: {
			Student student;
			cout << "请输入学生姓名：";
			cin >> student.name;
			cout << "请输入学生学号：";
			cin >> student.id;

			cout << "请输入各科成绩（用空格分隔）：";
			for (int i = 0; i < 3; ++i) {
				int score;
				cin >> score;
				student.scores.push_back(score);
			}

			bool found = false;
			for (auto& s : students) {
				if (s.name == student.name && s.id == student.id) {
					s = student; // 更新学生成绩信息
					found = true;
					break;
				}
			}

			if (!found) {
				students.push_back(student); // 新增学生成绩信息
			}

			cout << "成绩录入成功！" << endl;
			break;
		}
		case 2: {
			initializeStudentsFromFile("cj.txt");
			initializeStudentsFromFile("tjxx.txt");

			
			
			cout << "批量导入成功！" << endl;
			break;
		}
		case 3:
			cout << "返回上一级目录" << endl;
			exitLoop = true; // 设置退出循环的条件
			break;
		default:
			cout << "无效的选择，请重新输入！" << endl;
			break;
		}
	} while (!exitLoop);
}

//要求3:选1时以数据表的格式显示出cj.txt文件里的成绩数据
void showGradesData() {
	//ifstream infile("cj.txt");
	//if (!infile) {
	//	cerr << "Error: Unable to open file!" << endl;
	//	return;
	//}
	//Student student;
	//while (infile >> student.id >> student.name) {
	//	for (int i = 0; i < 3; ++i) {
	//		int score;
	//		if (!(infile >> score)) {
	//			break; // 如果读取成绩失败，则跳出内部循环
	//		}
	//		student.scores.push_back(score);
	//	}

	//	students.push_back(student);
	//}
	//students.erase(students.end() - 1);
	//infile.close();

	// 打印表头
	cout << "学号\t姓名\t计算机\t数学\t英语\t政治" << endl;

	// 打印数据
	for (const auto& student : students) {
		cout << student.id << "\t" << student.name << "\t";
		for (const auto& score : student.scores) {
			cout << score << "\t";
		}
		cout << endl;
	}
}

//要求4:学生成绩修改，此功能有子目录，包含单条数据修改和读取txt文件批量修改两种形式，单条数据修改：通过输入学号或者
//Id找出students数组中的元素，然后提示输入正确批量修改：
void modifyScore() {
	string input;
	cout << "请输入要修改的学生姓名或学号：";
	cin >> input;

	bool found = false;
	for (auto& student : students) {
		if (student.name == input || student.id == input) {
			cout << "找到学生：" << student.name << " 学号：" << student.id <<"\n"<<"各科分数,计算机：" << student.scores[0] << "数学：" << student.scores[1] << "英语：" << student.scores[2] << "政治：" << student.scores[3] << endl;
			cout << "请输入要修改的信息：" << endl;
			cout << "1. 姓名" << endl;
			cout << "2. 学号" << endl;
			cout << "3. 各科成绩" << endl;
			int choice;
			cin >> choice;

			if (choice == 1) {
				cout << "请输入新的姓名：";
				cin >> student.name;
			}
			else if (choice == 2) {
				cout << "请输入新的学号：";
				cin >> student.id;
			}
			else if (choice == 3) {
				cout << "请输入新的各科成绩（用空格分隔）：";
				for (int i = 0; i < 4; ++i) {
					int score;
					cin >> score;
					student.scores[i] = score;
				}
			}
			else {
				cout << "无效的选项！" << endl;
			}

			cout << "学生信息修改成功！" << endl;
			found = true;
			break;
		}
	}

	if (!found) {
		cout << "未找到匹配的学生信息！" << endl;
	}
}

//数据删除
void deleteStudent() {
	string input;
	cout << "请输入要删除的学生姓名或学号：";
	cin >> input;

	auto it = students.begin();
	bool found = false;
	while (it != students.end()) {
		if ((*it).name == input || (*it).id == input) {
			it = students.erase(it); // 删除匹配的学生信息
			cout << "学生信息删除成功！" << endl;
			found = true;
		}
		else {
			++it;
		}
	}
	if (found == false) {
		cout << "查无此人！" << endl;
	}
}
//统计成绩
void generateTotalAndAverageScoreFile()
{
	ofstream outfile("xxcj.txt");
	if (!outfile) {
		cerr << "Error: Unable to create file!" << endl;
		return;
	}

	for (const auto& student : students) {
		int totalScore = 0;
		for (int score : student.scores) {
			if (score != -1){
				totalScore += score;
			}
			
		}
		double averageScore = static_cast<double>(totalScore) / student.scores.size();

		outfile << "姓名：" << student.name << "\t学号：" << student.id << "\t总成绩：" << totalScore << "\t平均成绩：" << averageScore << endl;
	}

	outfile.close();
	cout << "xxcj.txt 文件生成成功！" << endl;
}


void generateCourseScoreFile(const string& courseName) {
	ofstream outfile(courseName + "未及格名单.txt");
	if (!outfile) {
		cerr << "Error: Unable to create file!" << endl;
		return;
	}
	for (const auto& student : students) {
		for (int i = 0; i < student.scores.size(); ++i) {
			if (student.scores[i] < 60) {
				outfile << "姓名：" << student.name << "\t学号：" << student.id << "\t课程名：" << courseName << "\t成绩：" << student.scores[i] << endl;
				break; // 只需要记录不及格的一门课程
			}
		}
	}
	outfile.close();
	cout << courseName << ".txt 文件生成成功！" << endl;
}


void generateLog() {
	ofstream outfile("log.txt", ios::app);
	if (!outfile) {
		cerr << "Error: Unable to create file!" << endl;
		return;
	}
	for (const auto& student : students) {
		outfile << "姓名：" << student.name << "\t学号：" << student.id << "\t成绩：";
		for (int score : student.scores) {
			outfile << score << " ";
		}
		outfile << endl;
	}
	outfile.close();
	cout << "log.txt 文件生成成功！" << endl;
}
//将变量写入txt
void saveDataToFile() {
	ofstream outfile("cj.txt");
	if (!outfile) {
		cerr << "Error: Unable to open file!" << endl;
		return;
	}
	outfile << "学号\t姓名\t计算机\t数学\t英语\t政治" << endl;
	for (const auto& student : students) {
		outfile << student.id << "\t" << student.name << "\t";
		for (const auto& score : student.scores) {
			outfile << score << "\t";
		}
		outfile << endl;
	}
	outfile.close();
}
//主函数
int main() {
	initializeStudentsFromFile("cj.txt");
	int choice;
	do {
		displayMenu();
		cin >> choice;

		switch (choice) {
		case 1:
			showGradesData();
			break;
		case 2:
			queryScoreByNameOrId();
			break;
		case 3:
			addScore();
			break;
		case 4:
			modifyScore();
			break;
		case 5:
			deleteStudent();
			break;
		case 6:
			cout << "学生成绩管理系统" << endl;
			cout << "*******************************************************" << endl;
			cout << "学生成绩管理系统" << endl;
			cout << "1. 生成总成绩和平均成绩文件（xxcj.txt）" << endl;
			cout << "2. 生成不及格学生文件" << endl;
			cout << "3. 生成日志文件（log.txt）" << endl;
			int option;
			cin >> option;

			if (option == 1) {
				generateTotalAndAverageScoreFile();
			}
			else if (option == 2) {
				string courseName;
				cout << "请输入课程名（拼音）：";
				cin >> courseName;
				generateCourseScoreFile(courseName);
			}
			else if (option == 3) {
				generateLog();
			}
			else {
				cout << "无效的选项！" << endl;
			}
			break;
			// 其他功能实现略
		case 7:
			saveDataToFile();
			cout << "感谢使用，已退出程序！" << endl;
			break;
		default:
			cout << "无效的选择，请重新输入！" << endl;
			break;
		}
	} while (choice != 0);

	return 0;
}