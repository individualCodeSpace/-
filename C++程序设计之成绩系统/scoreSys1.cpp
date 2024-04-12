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

// ��ʼ��students��������cj.txt�ļ���ȡ����
void initializeStudentsFromFile(string filename) {
	std::ifstream infile(filename);
	if (!infile) {
		std::cerr << "Error: Unable to open file!" << std::endl;
		return;
	}

	std::string line;
	std::getline(infile, line); // ������ͷ

	while (std::getline(infile, line)) {

		int score;

		std::regex pattern("\\t\\t"); // ƥ��һ�����������Ŀո�&&�Ʊ��

		std::string result = std::regex_replace(line, pattern, "  -1  ");

		std::regex pattern1("\\s"); // ƥ��һ�����������Ŀո�&&�Ʊ��


		std::istringstream ss(result);
		Student student;
		//// ����ѧ�ź������Ŀ�ȷֱ�Ϊ10��20
		ss >> student.id >> student.name;

		if (student.id != "-1")
		{
			//����ÿ���ɼ��Ŀ��Ϊ5
			for (int i = 0; i < 4; ++i) {

				//cout << line << endl;

				ss >> std::setw(5);
				if (ss >> score)
				{
					student.scores.push_back(score);
				}
				else
				{
					student.scores.push_back(-1); // ����-1����հ׳ɼ�
					ss.clear(); // �������״̬
				}

			}

			students.push_back(student);

		}

	}

	infile.close();
}
//��ʼ����
void displayMenu() {
	cout << "ѧ���ɼ�����ϵͳ" << endl;
	cout << "*******************************************************" << endl;
	cout << "1. ѧ���ɼ���ʾ" << endl;
	cout << "2. ѧ���ɼ���ѯ" << endl;
	cout << "3. ѧ���ɼ����" << endl;
	cout << "4. ѧ���ɼ��޸�" << endl;
	cout << "5. ѧ���ɼ�ɾ��" << endl;
	cout << "6. ͳ��ѧ���ɼ�" << endl;
	cout << "7. �˳�ϵͳ" << endl;
	cout << "��ѡ���ܱ�ţ�1-7����";
}
// Ҫ��һ��ͨ����������ѧ�Ų�ѯstudents������Ŀγ̳ɼ���Ϣ
void queryScoreByNameOrId() {
	string input;
	cout << "������������ѧ�Ž��в�ѯ��";
	cin >> input;

	bool found = false;
	for (const auto& student : students)
	{
		if (student.name == input || student.id == input) {
			cout << "������" << student.name << "\tѧ�ţ�" << student.id << endl;
			cout << "���Ƴɼ���";
			for (const auto& score : student.scores) {
				cout << score << " ";
			}
			cout << endl;
			found = true;
			break;
		}
	}

	if (!found) {
		cout << "δ�ҵ�ƥ���ѧ����Ϣ��" << endl;
	}
}
//Ҫ��2:�ɼ�¼�룬��Ϊ����¼���ͨ���ļ��������룬��ѧ����Ϣ����students����,�����������������޸�
void addScore() {
	bool exitLoop = false;
	int choice;
	do {
		cout << "ѧ���ɼ�����ϵͳ" << endl;
		cout << "*******************************************************" << endl;
		cout << "1. ������Ϣ¼��" << endl;
		cout << "2. ���ļ���������" << endl;
		cout << "3. ������һ��Ŀ¼" << endl;
		cout << "��ѡ���ܱ�ţ�";
		cin >> choice;

		switch (choice) {
		case 1: {
			Student student;
			cout << "������ѧ��������";
			cin >> student.name;
			cout << "������ѧ��ѧ�ţ�";
			cin >> student.id;

			cout << "��������Ƴɼ����ÿո�ָ�����";
			for (int i = 0; i < 3; ++i) {
				int score;
				cin >> score;
				student.scores.push_back(score);
			}

			bool found = false;
			for (auto& s : students) {
				if (s.name == student.name && s.id == student.id) {
					s = student; // ����ѧ���ɼ���Ϣ
					found = true;
					break;
				}
			}

			if (!found) {
				students.push_back(student); // ����ѧ���ɼ���Ϣ
			}

			cout << "�ɼ�¼��ɹ���" << endl;
			break;
		}
		case 2: {
			initializeStudentsFromFile("cj.txt");
			initializeStudentsFromFile("tjxx.txt");

			
			
			cout << "��������ɹ���" << endl;
			break;
		}
		case 3:
			cout << "������һ��Ŀ¼" << endl;
			exitLoop = true; // �����˳�ѭ��������
			break;
		default:
			cout << "��Ч��ѡ�����������룡" << endl;
			break;
		}
	} while (!exitLoop);
}

//Ҫ��3:ѡ1ʱ�����ݱ�ĸ�ʽ��ʾ��cj.txt�ļ���ĳɼ�����
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
	//			break; // �����ȡ�ɼ�ʧ�ܣ��������ڲ�ѭ��
	//		}
	//		student.scores.push_back(score);
	//	}

	//	students.push_back(student);
	//}
	//students.erase(students.end() - 1);
	//infile.close();

	// ��ӡ��ͷ
	cout << "ѧ��\t����\t�����\t��ѧ\tӢ��\t����" << endl;

	// ��ӡ����
	for (const auto& student : students) {
		cout << student.id << "\t" << student.name << "\t";
		for (const auto& score : student.scores) {
			cout << score << "\t";
		}
		cout << endl;
	}
}

//Ҫ��4:ѧ���ɼ��޸ģ��˹�������Ŀ¼���������������޸ĺͶ�ȡtxt�ļ������޸�������ʽ�����������޸ģ�ͨ������ѧ�Ż���
//Id�ҳ�students�����е�Ԫ�أ�Ȼ����ʾ������ȷ�����޸ģ�
void modifyScore() {
	string input;
	cout << "������Ҫ�޸ĵ�ѧ��������ѧ�ţ�";
	cin >> input;

	bool found = false;
	for (auto& student : students) {
		if (student.name == input || student.id == input) {
			cout << "�ҵ�ѧ����" << student.name << " ѧ�ţ�" << student.id <<"\n"<<"���Ʒ���,�������" << student.scores[0] << "��ѧ��" << student.scores[1] << "Ӣ�" << student.scores[2] << "���Σ�" << student.scores[3] << endl;
			cout << "������Ҫ�޸ĵ���Ϣ��" << endl;
			cout << "1. ����" << endl;
			cout << "2. ѧ��" << endl;
			cout << "3. ���Ƴɼ�" << endl;
			int choice;
			cin >> choice;

			if (choice == 1) {
				cout << "�������µ�������";
				cin >> student.name;
			}
			else if (choice == 2) {
				cout << "�������µ�ѧ�ţ�";
				cin >> student.id;
			}
			else if (choice == 3) {
				cout << "�������µĸ��Ƴɼ����ÿո�ָ�����";
				for (int i = 0; i < 4; ++i) {
					int score;
					cin >> score;
					student.scores[i] = score;
				}
			}
			else {
				cout << "��Ч��ѡ�" << endl;
			}

			cout << "ѧ����Ϣ�޸ĳɹ���" << endl;
			found = true;
			break;
		}
	}

	if (!found) {
		cout << "δ�ҵ�ƥ���ѧ����Ϣ��" << endl;
	}
}

//����ɾ��
void deleteStudent() {
	string input;
	cout << "������Ҫɾ����ѧ��������ѧ�ţ�";
	cin >> input;

	auto it = students.begin();
	bool found = false;
	while (it != students.end()) {
		if ((*it).name == input || (*it).id == input) {
			it = students.erase(it); // ɾ��ƥ���ѧ����Ϣ
			cout << "ѧ����Ϣɾ���ɹ���" << endl;
			found = true;
		}
		else {
			++it;
		}
	}
	if (found == false) {
		cout << "���޴��ˣ�" << endl;
	}
}
//ͳ�Ƴɼ�
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

		outfile << "������" << student.name << "\tѧ�ţ�" << student.id << "\t�ܳɼ���" << totalScore << "\tƽ���ɼ���" << averageScore << endl;
	}

	outfile.close();
	cout << "xxcj.txt �ļ����ɳɹ���" << endl;
}


void generateCourseScoreFile(const string& courseName) {
	ofstream outfile(courseName + "δ��������.txt");
	if (!outfile) {
		cerr << "Error: Unable to create file!" << endl;
		return;
	}
	for (const auto& student : students) {
		for (int i = 0; i < student.scores.size(); ++i) {
			if (student.scores[i] < 60) {
				outfile << "������" << student.name << "\tѧ�ţ�" << student.id << "\t�γ�����" << courseName << "\t�ɼ���" << student.scores[i] << endl;
				break; // ֻ��Ҫ��¼�������һ�ſγ�
			}
		}
	}
	outfile.close();
	cout << courseName << ".txt �ļ����ɳɹ���" << endl;
}


void generateLog() {
	ofstream outfile("log.txt", ios::app);
	if (!outfile) {
		cerr << "Error: Unable to create file!" << endl;
		return;
	}
	for (const auto& student : students) {
		outfile << "������" << student.name << "\tѧ�ţ�" << student.id << "\t�ɼ���";
		for (int score : student.scores) {
			outfile << score << " ";
		}
		outfile << endl;
	}
	outfile.close();
	cout << "log.txt �ļ����ɳɹ���" << endl;
}
//������д��txt
void saveDataToFile() {
	ofstream outfile("cj.txt");
	if (!outfile) {
		cerr << "Error: Unable to open file!" << endl;
		return;
	}
	outfile << "ѧ��\t����\t�����\t��ѧ\tӢ��\t����" << endl;
	for (const auto& student : students) {
		outfile << student.id << "\t" << student.name << "\t";
		for (const auto& score : student.scores) {
			outfile << score << "\t";
		}
		outfile << endl;
	}
	outfile.close();
}
//������
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
			cout << "ѧ���ɼ�����ϵͳ" << endl;
			cout << "*******************************************************" << endl;
			cout << "ѧ���ɼ�����ϵͳ" << endl;
			cout << "1. �����ܳɼ���ƽ���ɼ��ļ���xxcj.txt��" << endl;
			cout << "2. ���ɲ�����ѧ���ļ�" << endl;
			cout << "3. ������־�ļ���log.txt��" << endl;
			int option;
			cin >> option;

			if (option == 1) {
				generateTotalAndAverageScoreFile();
			}
			else if (option == 2) {
				string courseName;
				cout << "������γ�����ƴ������";
				cin >> courseName;
				generateCourseScoreFile(courseName);
			}
			else if (option == 3) {
				generateLog();
			}
			else {
				cout << "��Ч��ѡ�" << endl;
			}
			break;
			// ��������ʵ����
		case 7:
			saveDataToFile();
			cout << "��лʹ�ã����˳�����" << endl;
			break;
		default:
			cout << "��Ч��ѡ�����������룡" << endl;
			break;
		}
	} while (choice != 0);

	return 0;
}