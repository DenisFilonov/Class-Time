#include"Time.h"

int main()
{
	setlocale(NULL, "");

	//=============================CLASS=CHECK===============
	/*int choice = 0;
	cout << "\n1) Установить 12 часовой формат \"am\"";
	cout << "\n2) Установить 12 часовой формат \"pm\"";
	cout << "\n3) Установить 24 часовой формат \"utc\"";
	cout << "\n0) Выйти из меню установки.\nВыбор: ";
	cin >> choice;

	Time a, b(23, 00, 00), c(11, 00, 00, "pm");
	a.setFormat(choice);
	b.setFormat(choice);

	cout << "\na = " << a.getFormat();
	cout << "\nb = " << b.getFormat();
	cout << "\nc = " << c.getFormat();


	a.showTime();
	b.showTime();
	c.showTime();

	cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << (b >= c ? "\nВерно\n" : "\nНе верно\n");
	cout << (b == c ? "\nВерно\n" : "\nНе верно\n");
	cout << (b <= c ? "\nВерно\n" : "\nНе верно\n");
	cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

	int value = 5;

	a += value;
	a.showTime();
	b -= value;
	b.showTime();
	cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	Time f = c + value;
	c.showTime();
	f.showTime();

	Time d = b - value;
	b.showTime();
	d.showTime();*/



	return 0;
}