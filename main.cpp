#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class User
{
private:
	string _name;
	string _login;
	string _pass;

public:
	User(string name, string login, string pass) : _name(name), _login(login), _pass(pass){}

	friend fstream& operator >> (fstream& is, User& obj);
	friend ostream& operator << (ostream& os, User& obj);
};

class Message
{
private:
	string _text;
	string _sender;
	string _receiver;

public:
	Message(string text, string sender, string receiver) : _text(text), _sender(sender), _receiver(receiver){}

	friend fstream& operator >> (fstream& is, Message& obj);
	friend ostream& operator << (ostream& os, Message& obj);
};

fstream& operator>>(fstream& is, User& obj)
{
	is >> obj._name;
	is >> obj._login;
	is >> obj._pass;
	return is;
}

ostream& operator<<(ostream& os, User& obj)
{
	os << obj._name;
	os << ' ';
	os << obj._login;
	os << ' ';
	os << obj._pass;

	return os;
}

fstream& operator>>(fstream& is, Message& obj)
{
	is >> obj._text;
	is >> obj._sender;
	is >> obj._receiver;

	return is;
}

ostream& operator<<(ostream& os, Message& obj)
{
	os << obj._text;
	os << ' ';
	os << obj._sender;
	os << ' ';
	os << obj._receiver;

	return os;
}

void demo_perms(fs::perms p)
{
	cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
		<< ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
		<< ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
		<< ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
		<< ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
		<< ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
		<< ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
		<< ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
		<< ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
		<< endl;
}

int main()
{
	setlocale(LC_ALL, "rus");

	fstream user_file = fstream("user.txt", ios::in | ios::app | ios::out);

	if (!user_file.is_open())
	{
		cout << "Не удалось открыть файл user.txt" << endl;
		return 1;
	}

	fs::permissions("user.txt", fs::perms::owner_all);

	fstream mess_file = fstream("message.txt", ios::in | ios::app | ios::out);

	if (!mess_file.is_open())
	{
		cout << "Не удалось открыть файл message.txt" << endl;
		return 1;
	}

	fs::permissions("message.txt", fs::perms::owner_all);

	while (true)
	{

		cout << "Select file user(u) message(m). To exit the program, select q" << endl; //Выберете  файл user(u) message(m). Для выхода из программы выберете q
		char file;

		string userFile, nameVal, loginVal, passVal, messFile, textVal, senderVal, receiverVal;

		cin >> file;
		if (file == 'q') break;

		switch (file)
		{
		case 'u':

			if (user_file)
			{
				//Запишем данные в файл
				cout << "File user.txt:" << endl;

				cout << "Name: "; //Введите имя
				cin >> nameVal;

				cout << "Login: "; //Введите логин
				cin >> loginVal;

				cout << "Password: "; //Введите пароль
				cin >> passVal;

				User obj = User(nameVal, loginVal, passVal);

				user_file << obj << endl;

				// Чтобы считать данные из файла, надо установить позицию для чтения в начало файла
				user_file.seekg(0, ios_base::beg);

				cout << "File contents user.txt" << endl; //Содержимое файла user.txt

				// Считываем данные из файла
				while (!user_file.eof())
					if (user_file >> userFile)
						cout << userFile << endl;
			}
			else
			{
				cout << "Could not open the file user.txt" << endl; ///Не удалось открыть файл user.txt
				return 0;
			}
			break;
		case 'm':

			if (mess_file)
			{
				//Запишем данные в файл
				cout << "File message.txt:" << endl; //Файл message.txt
				cout << "Messages: "; ///Сообщения
				cin >> textVal;
				
				cout << "Sender: "; ///Отправитель
				cin >> senderVal;
				
				cout << "Receiver: "; ///Получатель
				cin >> receiverVal;

				Message obj = Message(textVal, senderVal, receiverVal);

				mess_file << obj;

				// Чтобы считать данные из файла, надо установить позицию для чтения в начало файла
				mess_file.seekg(0, ios_base::beg);

				cout << "File contents message.txt" << endl; ///Содержимое файла message.txt

				// Считываем данные из файла
				while (!mess_file.eof())
					if (mess_file >> messFile)
						cout << messFile << endl;
			}
			else
			{
				cout << "Could not open the file message.txt" << endl; ///Не удалось открыть файл message.txt
				return 0;
			}
			break;

		default:
			cout << "Selected a nonexistent file!!!" << endl; ///Выбрали несуществующий файл!!!
			break;
		}
	}

	user_file.close();
	mess_file.close();
	return 0;
}



