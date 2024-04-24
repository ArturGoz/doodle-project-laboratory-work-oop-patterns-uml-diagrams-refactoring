#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;
mutex mt;

class regression {
	//змінні які використовуються для обчислення алгоритму
	float coeff, constTerm, sum_xy, sum_x, sum_y, sum_x_square, sum_y_square, test_number;
public:

	regression()
	{
		coeff = 0;
		constTerm = 0;
		sum_y = 0;
		sum_y_square = 0;
		sum_x_square = 0;
		sum_x = 0;
		sum_xy = 0;
		// задаю число, для працювання з тестами.
		test_number = 5;
	}
	//обчислення кофіцієнту
	void calculateCoefficient(int N)
	{
		float numerator;

			numerator = (N * sum_xy - sum_x * sum_y);
		float denominator = (N * sum_x_square - sum_x * sum_x);
		coeff = numerator / denominator;
	}
	//обчислення константи
	void calculateConstantTerm(int N)
	{
		
		float numerator;

			numerator = (sum_y * sum_x_square - sum_x * sum_xy);
			//cout << "Potok = " << this_thread::get_id() << endl;

		float denominator
			= (N * sum_x_square - sum_x * sum_x);
		constTerm = numerator / denominator;
	}

	// вивід нашого графіку(нашого обчисленого алгоритму)
	void PrintBestFittingLine(int N)
	{
		if (coeff == 0 && constTerm == 0) {

				calculateCoefficient(N);
				calculateConstantTerm(N);

		}
		cout << "The best fitting line is y = "
			<< coeff << "x + " << constTerm << endl;
	}
	//функція за допомогою якої користувач буде вводити числа, та відразу ці числа будуть перевірятись на раціональні числа
	
	void takeInput(int n)
	{
		int j = n / 2 + (n%2);
		int e = 0;
		thread t1([&]() { 
			
			for (int i = 0; i < j; i++) {
				cout << "Enter data:" << endl;

				float xi;

				float yi;

				string xii;
				string yii;

				mt.lock();

				cout << "x[" << e << "] = ";
				cin >> xii;
				xi = check_rational(xii);
				cout << " float: " << xi << endl;
				cout << "y[" << e << "] = ";
				cin >> yii;

				yi = check_rational(yii);
				cout << " float: " << yi << endl;

				mt.unlock();

				sum_xy += xi * yi;
				sum_x += xi;
				sum_y += yi;
				sum_x_square += xi * xi;
				sum_y_square += yi * yi;
				++e;
			}

			});
		thread t2([&]() {
		for (int i = j; i < n; i++) {
			cout << "Enter data:" << endl;

			float xi;

			float yi;

			string xii;
			string yii;

			mt.lock();

			cout << "x[" << e << "] = ";
			cin >> xii;
			xi = check_rational(xii);
			cout << " float: " << xi << endl;
			cout << "y[" << e << "] = ";
			cin >> yii;

			yi = check_rational(yii);
			cout << " float: " << yi << endl;

			mt.unlock();

			sum_xy += xi * yi;
			sum_x += xi;
			sum_y += yi;
			sum_x_square += xi * xi;
			sum_y_square += yi * yi;
			++e;

		}
			});
		t1.join();
		t2.join();
	}
	
	//перевірка на раціональні числа
	float check_rational(string input) {
		stringstream ss(input);
		float result = 0;

		if (input.find('/') != string::npos) {
			// Ввід у форматі "a/b"
			int numerator, denominator;
			char slash;
			if (ss >> numerator >> slash >> denominator && slash == '/' && denominator != 0) {
				result = static_cast<float>(numerator) / denominator;
			}
			else {
				cout << "incorrect, try another" << endl;
				string input2;
				cin >> input2;
				result = check_rational(input2);
			}
		}
		else {
			// Ввід у форматі "a" або "a.0"
			float floatValue;
			ss.clear(); // Скидаємо флаги помилок потоку
			ss.seekg(0); // Переносимо позицію читання на початок потоку

			if (ss >> floatValue && ss.eof()) {
				result = floatValue;
			}
			else {
				cout << "incorrect" << endl;
				string input2;
				cout << "Input another number" << endl;
				cin >> input2;
				result = check_rational(input2);
			}
		}
		return result;

	}

	// тест для перевірки раціональних чисел
	void Test1()
	{
		float test1 = check_rational("15.123");
		cout << "our input: " << 15.123 << " result " << test1 << endl;
		float test2 = check_rational("3/4");
		cout << "our input: " << "3/4" << " result " << test2 << endl;
		float test3 = check_rational("111");
		cout << "our input: " << 111 << " result " << test3 << endl;
		float test4 = check_rational("-4/5");
		cout << "our input: " << "-4/5" << " result " << test4 << endl;
		float test5 = check_rational("-4");
		cout << "our input: " << -4 << " result " << test5 << endl;
		float test6 = check_rational("-15.33");
		cout << "our input: " << "-15.33" << " result " << test6 << endl;
		float test7 = check_rational("-15.123asdasd33");
		cout << "our input: " << "-15.123asdasd33" << " result " << test7 << endl;
		float test8 = check_rational("1+5i");
		cout << "our input: " << "-1+5i" << " result " << test8 << endl;
	}
	
	// тест вводу даних
	void Test2()
	{
		float x[3] = { 0 };
		float y[3] = { 0 };
		x[0] = 0, x[1] = 0.5, x[2] = -1, y[0] = 1, y[1] = 2, y[2] = -1;
		for (int i = 0; i < 3; i++) {
			float xi = x[i];
			cout << " xi= " << xi << endl;
			float yi = y[i];
			cout << " yi= " << yi << endl;
			sum_xy += xi * yi;
			sum_x += xi;
			sum_y += yi;
			sum_x_square += xi * xi;
			sum_y_square += yi * yi;

		}
		PrintBestFittingLine(3);
	}
	
	// тест вводу даних з сайту
	void TestFromSite()
	{
		int size = 6;
		float x[6] = { 0 };
		float y[6] = { 0 };
		x[0] = 43, x[1] = 21, y[0] = 99, y[1] = 65;
		x[2] = 25, x[3] = 42, y[2] = 79, y[3] = 75;
		x[4] = 57, x[5] = 59, y[4] = 87, y[5] = 81;

			for (int i = 0; i < size; i++) {
			
				float xi = x[i];
				cout << " xi= " << xi << endl;
				float yi = y[i];
				cout << " yi= " << yi << endl;
				
				sum_xy += xi * yi;
				sum_x += xi;
				sum_y += yi;
				sum_x_square += xi * xi;
				sum_y_square += yi * yi;

			}

		cout << sum_y_square << endl;
		cout << sum_x_square << endl;
		cout << sum_x << endl;
		cout << sum_y << endl;
		cout << sum_xy << endl;
		PrintBestFittingLine(6);
	}
	


	//перевірка на ефективність використання 2 потоків для обчислення алгоритму
	void TestForEffeciencyWith2()
	{
	//	std::mutex mtx;
		auto start_time = chrono::high_resolution_clock::now();
		mt.lock();
		int size = 5000;
		float x[5000] = { 0 };
		float y[5000] = { 0 };
		for (int i = 0; i < size; ++i)
		{
			x[i] = i;
			y[i] = i + test_number;
		}

		int j = size / 2;
		mt.unlock();



		std::thread t1([&] {

			for (int i = 0; i < j; i++) {
				float xi = x[i];
				float yi = y[i];

				mt.lock();
				sum_xy += xi * yi;
				sum_x += xi;
				sum_y += yi;
				sum_x_square += xi * xi;
				sum_y_square += yi * yi;
				mt.unlock();
			}
			});

			std::thread t2([&] {
		for (int i = j; i < size; i++) {
			float xi = x[i];
			float yi = y[i];

			mt.lock();
			sum_xy += xi * yi;
			sum_x += xi;
			sum_y += yi;
			sum_x_square += xi * xi;
			sum_y_square += yi * yi;
			mt.unlock();
		}
			});



		t1.join();
		t2.join();

		cout << sum_y_square << endl;
		cout << sum_x_square << endl;
		cout << sum_x << endl;
		cout << sum_y << endl;
		cout << sum_xy << endl;
		PrintBestFittingLine(5000);

		auto end_time = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		// Вивід часу виконання в мікросекундах
		cout << "time with 2 threads: " << duration.count() << " microseconds" << endl;
	}

	//перевірка на ефективність використання 3 потоків для обчислення алгоритму
	void TestForEffeciencyWith3()
	{
		//std::mutex mtx;
		auto start_time = chrono::high_resolution_clock::now();
		mt.lock();
		int size = 5000;
		float x[5000] = { 0 };
		float y[5000] = { 0 };
		for (int i = 0; i < size; ++i)
		{
			x[i] = i;
			y[i] = i + test_number;
		}

		int j = size / 3;
		int j2 = 2 * j;
		mt.unlock();

		std::thread t1([&] {
			for (int i = 0; i < j; i++) {
				float xi = x[i];
				float yi = y[i];

				mt.lock();
				sum_xy += xi * yi;
				sum_x += xi;
				sum_y += yi;
				sum_x_square += xi * xi;
				sum_y_square += yi * yi;
				mt.unlock();
			}
			});

		std::thread t2([&] {
			for (int i = j; i < j2; i++) {
				float xi = x[i];
				float yi = y[i];

				mt.lock();
				sum_xy += xi * yi;
				sum_x += xi;
				sum_y += yi;
				sum_x_square += xi * xi;
				sum_y_square += yi * yi;
				mt.unlock();
			}
			});

		std::thread t3([&] {
			for (int i = j2; i < size; i++) {
				float xi = x[i];
				float yi = y[i];

				mt.lock();
				sum_xy += xi * yi;
				sum_x += xi;
				sum_y += yi;
				sum_x_square += xi * xi;
				sum_y_square += yi * yi;
				mt.unlock();
			}
			});

		t1.join();
		t2.join();
		t3.join();

		cout << sum_y_square << endl;
		cout << sum_x_square << endl;
		cout << sum_x << endl;
		cout << sum_y << endl;
		cout << sum_xy << endl;
		PrintBestFittingLine(5000);

		auto end_time = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		// Вивід часу виконання в мікросекундах
		cout << "time with 3 threads: " << duration.count() << " microseconds" << endl;
	}

	//перевірка на ефективність використання без потоків для обчислення алгоритму
	void TestForEffeciencyWithout()
	{
		

		auto start_time = chrono::high_resolution_clock::now();

		int size = 5000;
		float x[5000] = { 0 };
		float y[5000] = { 0 };
		for (int i = 0; i < size; ++i)
		{
			x[i] = i;
			y[i] = i + test_number;
		}


		int j = size / 2;

		
		for (int i = 0; i < j; i++) {

			float xi = x[i];
			float yi = y[i];

			sum_xy += xi * yi;
			sum_x += xi;
			sum_y += yi;
			sum_x_square += xi * xi;
			sum_y_square += yi * yi;

		}
		

		for (int i = j; i < size; i++) {

			float xi = x[i];
			float yi = y[i];

			sum_xy += xi * yi;
			sum_x += xi;
			sum_y += yi;
			sum_x_square += xi * xi;
			sum_y_square += yi * yi;

		}
		
		cout << sum_y_square << endl;
		cout << sum_x_square << endl;
		cout << sum_x << endl;
		cout << sum_y << endl;
		cout << sum_xy << endl;
		PrintBestFittingLine(5000);

		auto end_time = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		// Вивід часу виконання в мікросекундах
		cout << "time : " << duration.count() << " microseconds" << endl;
	}
};

int main()
{
	char input;
	cout << "input t for unit test or input i to input own points// e -> to check threads efficiency" << endl;
	cin >> input;
	//input = 't';


	regression reg;

	switch (input)
	{
	case 't':
		cout << " test1 " << endl;
		reg.Test1();
		cout << " test2 " << endl;
		reg = regression();
		reg.Test2();
		cout << " test3 " << endl;
		reg = regression();
		reg.TestFromSite();
		break;

	case 'e':
		reg = regression();
		reg.TestForEffeciencyWith2();
		reg = regression();
		reg.TestForEffeciencyWith3();
		reg = regression();
		reg.TestForEffeciencyWithout();

		break;

	case 'i':
		reg = regression();
		int n;
		cout << "How many data points? ";
		cin >> n;
		reg.takeInput(n);
		reg.PrintBestFittingLine(n);
		break;

	default:
		std::cout << "Unknown choice" << std::endl;
		break;

	}


	return 0;
}