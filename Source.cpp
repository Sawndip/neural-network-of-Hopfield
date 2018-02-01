//@author Vladislav Navrosiuk

//@author стандартные библиотеки языка С++
#include <iostream>
#include<iomanip> 
#include <vector>
#include <random>
#include <conio.h>
//@author http://arma.sourceforge.net
//C++ linear algebra library
#include <armadillo>
#include <fstream>

using namespace std;
using namespace arma;

bool ifEq(fmat Y1, fmat Y2);
void funAct(fmat &Y);
int iteration = 0;

fmat signMatrix(fmat& mt) {
	fmat res(mt.n_rows, mt.n_cols);
	for (int i = 0; i < mt.n_rows; i++)
		for (int j = 0; j < mt.n_cols; j++)
			res(i, j) = (mt(i, j) < 0) ? -1 : 1;
	return res;
}

fmat parseToDigits(string str) {
	fmat result(1, 64);
	int id = 0;
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == '-') {
			result(0, id) = (-1);
			id++;
		}
		if (str[i] == '*') {
			result(0, id) = (1);
			id++;
		}
	}
	return result;
}

void printOut(fmat str) {
	int id = 0;
	for (int i = 0; i < str.size(); ++i) {

		if (id == 8) {
			cout << "\n";
			id = 0;
		}id++;
		//str[i] = (int)str[i];
		if (str[i] < 0) {
			cout << "- ";
		}
		if (str[i] > 0) {
			cout << "* ";
		}
		//cout << str[i];
	}
	cout << endl;
}

fmat W(64, 64, fill::zeros), X(1, 64), Y(1, 64);
fmat Wi(64, 64, fill::zeros);
fmat Wold(64, 64, fill::zeros);
fmat Woldold(64, 64, fill::zeros);
fmat Woldoldo(64, 1, fill::zeros);


void createW(fmat* numbers, int count) {
	//W = W + (X.t()*X);
	double FACTOR = 0.8; // 0.7..0.9
	double E = 0.00003;
	int width = numbers[0].n_cols;
	int height = numbers[0].n_rows;
	int pixels = width*height;
	int N = pixels + 1;
	W = fmat(pixels, pixels,fill::zeros);
	bool isRun = true;
	do {
		for (int indexImage = 0; indexImage < count; indexImage++) {
			fmat Xi = numbers[indexImage];
		
			
			//reshape(Xi, width*height, 1);
			Xi.reshape(64, 1);
			

			//cout << (Xi - W * Xi) * Xi.t();
			fmat deltaW = ((FACTOR / N) * (Xi - W * Xi) * Xi.t());
			W = W + deltaW;
		
			

			
 		

			//gthtjghtltk chfdytybt
		}

		isRun = false;

		Wold = Wi;
		Wi = W;
		iteration++;	
		system("cls");
			cout <<"ITeration:"<< iteration;
			

		//cout << iteration;
		//_getch();6

			if (approx_equal(Wi,Wold,"absdiff", 0.0001) )
			{
				cout <<endl<< "Matrix weight is relax";
				_getch();
				system("cls");
				isRun = true;
				break;
			}

	//	std::cout << change << std::endl;
	} while (true);
	system("cls");

	//_getch();
	Y.reshape(64, 1);
	fmat q = W*Y;
	funAct(q);

}
void init() {
	int c;
	vector<string> fileNames;
	cout << "Enter koll of files ";
	cin >> c;
	for (int i = 0; i < c; i++) {
		cout << "Enter " << i + 1 << " filename without .txt\n";
		string qwer;
		cin >> qwer;
		string str;
		str.append(qwer);
		str.append(".txt");
		//str.a
		fileNames.push_back(str);
	}

	fmat* numbers = new fmat[c];
	
	

	for (int i = 0; i < fileNames.size(); i++) {
		ifstream f(fileNames[i]);
		if (!f) {
			cout << "File reading error";
			system("pause");
			return;
		}
		string someLetter;
		string n;
		while (getline(f, n))
		{
			someLetter.append(n);
		};
		f.close();
		numbers[i] = parseToDigits(someLetter);
		//printOut(numbers[i]);
		//createW(parseToDigits(someLetter));
	}
	
	ifstream f1("t2.txt");
	string qwerq, letterForRaspozn;
	while (getline(f1, qwerq))
	{
		letterForRaspozn.append(qwerq);
	};
	f1.close();
	Y = parseToDigits(letterForRaspozn);

	createW(numbers, c);
}


void funAct(fmat &Y) {
	for (int i = 0; i < Y.n_rows; i++) {
		for (int j = 0; j < Y.n_cols; j++)
		{
			Y(i, j) = tanh(Y(i, j));
		}
	}
}
//при каких условиях состояние релаксации

bool ifEq(fmat Y1, fmat Y2) {
	if (Y1.n_cols != Y2.n_cols || Y1.n_rows != Y2.n_rows)
		return false;
	for (int i = 0; i < Y1.n_rows; i++) {
		for (int j = 0; j < Y1.n_cols; j++)
		{
			if (Y1(i, j) != Y2(i, j)) {
				return false;
			}
		}
	}
	return true;
}

bool ifEq(fmat Y1, fmat Y2, fmat Y3) {
	for (int i = 0; i < Y1.n_rows; i++) {
		for (int j = 0; j < Y1.n_cols; j++)
		{
			if (Y1(i, j) != Y2(i, j)|| Y1(i, j) != Y3(i, j)) {
				return false;
			}
		}
	}
	return true;
}


int main(int argc, char** argv) {
	setlocale(LC_ALL, "Russian");
		init();
		int iter = 0;
	fmat Y_new(1, 64, fill::zeros);
	fmat Y_old(1, 64, fill::zeros);
	system("cls");
	cout << "Input\n";
	printOut(Y);
	Y.reshape(64, 1);
	_getch();
	do {

		fmat q = W*Y;
		funAct(q);
		system("cls");
		//printOut(q);
		//
		
		//_getch();
		iter++;
		cout << "Iteration:" <<iter;
		
		
		if ((approx_equal(q, Y, "absdiff", 0.0001) || approx_equal(q, Y_old, "absdiff", 0.0001))
			
			
			) {
			system("cls");
			printOut(q);
			cout <<
				"Iteration:" << iter;
			break;
		}
		Y_old = Y;
		Y = q;
		//cout << iteration

	} while (true);

	
//	cout << iteration;
	
	system("pause");

}