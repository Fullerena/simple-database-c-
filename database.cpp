#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <array>
#include <deque>
#define string std::string
#define cout std::cout
#define cin std::cin
#define ws std::ws
#define setw std::setw
#define left std::left
#define fstream std::fstream
#define deque std::deque

void func(std::array<deque<string>, 3> &deck)
{
	string d;
	int count = 0;
	cout << "Selamat datang di Database yang simpel ini.";
	cout << "\nSeluruh Data di simpan di file\n=====================\n";
	cout << "1. masukkan data\n2. akses data berdasarkan kolom dan indeks\n";
	cout << "3. hapus data\n4. lihat keseluruhan data\n";
	cout << "5. kosongkan terminal\n";
	cout << "6. Selesai\n=====================\n";
	cout << "pilih salah satu[1-6]\n";
	char action;
	string col[3] = {"nama", "umur", "ciri"};
	cin >> action;
	while (true)
	{
		if (action == '6')
		{
			break;
		}
		count = 0;
		switch (action)
		{
		case '1':
		{
			cout << "Masukkan nama: ";
			ws(cin);
			getline(cin, d);
			deck[0].emplace_back(d);

			cout << "Masukkan umur: ";
			ws(cin);
			getline(cin, d);
			deck[1].emplace_back(d);

			cout << "Masukkan ciri: ";
			getline(cin, d);
			deck[2].emplace_back(d);

			cin >> action;
			break;
		}
		case '2':
		{
			int choice, index;
			cout << "pilih kolom(nama, umur, ciri)\n";
			cin >> d;
			while (true)
			{
				if (d == "nama")
				{
					choice = 0;
					break;
				}
				if (d == "umur")
				{
					choice = 1;
					break;
				}
				if (d == "ciri")
				{
					choice = 2;
					break;
				}
				else
				{
					cout << "??\n";
					cin >> d;
				}
			}

			cout << "pilih indeks (dimulai dari satu)\n";
			while(!(cin>>index)){
				cout << "not found \n(ketik karakter apapun jika belum memasukkan data)\n";
				cin.clear();
				cin.ignore();
			}
			while (index > deck[choice].size() or index <= 0)
			{
				if(index==0){
					break;
				}
				cout << "not found \n(ketik karakter apapun jika belum memasukkan data)\n";
				cin >> index;
				cin.clear();
				cin.ignore();
			}
			if(index!=0){
				cout << deck[choice].at(index-1) << '\n';
			}
			
			cin >> action;
			break;
		}
		case '3':
		{
			int var;
			cout << "pilih indeks yang ingin dihapus\n(dimulai dari 1)\n";

			while (!(cin >> var))
			{
				cout << "eits tidak bisa\n(jika belum memasukkan data apapun \nketik 0)\n";
				cin.clear();
				cin.ignore();
			}
			while (var > deck[0].size() or var <= 0)
			{
				if (var == 0)
				{
					break;
				}
				cout << "eits tidak bisa\n(jika belum memasukkan data apapun \nketik karakter apapun)\n";
				cin >> var;
				cin.clear();
				cin.ignore();
			}
			if (var != 0)
			{
				deck[0].erase(deck[0].begin() + var - 1);
				deck[1].erase(deck[1].begin() + var - 1);
				deck[2].erase(deck[2].begin() + var - 1);
			}
			cin >> action;
			break;
		}
		case '4':
		{
			cout << left << setw(25) << " nama" << left << setw(10) << " umur"
				 << " ciri\n";
			for (int i = 0; i < 43; ++i)
				cout << "=";

			cout << "\n";
			count = 0;
			for (int i = 0; i < deck[0].size(); ++i)
			{
				cout << (i + 1) << '.' << left << setw(25) << deck[0][i] << left << setw(10) << deck[1][i] << left << setw(20) << deck[2][i] << '\n';
			}
			cin >> action;
			break;
		}
		case '5':
			cout << "\033c";
			cout << "Selamat datang di Database yang simpel ini.";
			cout << "\nSeluruh Data di simpan di file\n=====================\n";
			cout << "1. masukkan data\n2. akses data berdasarkan kolom dan indeks\n";
			cout << "3. hapus data\n4. lihat keseluruhan data\n";
			cout << "5. kosongkan terminal\n";
			cout << "6. Selesai\n=====================\n";
			cout << "pilih salah satu[1-5]\n";
			cin >> action;
			break;
		default:
		{
			cout << "pilih angka [1-6]\n";
			cin >> action;
			break;
		}
		}
	}
}
int main()
{
	using std::chrono::system_clock;
	system_clock::time_point today = system_clock::now();
	std::time_t tt = system_clock::to_time_t(today);

	char h;
	std::array<deque<string>, 3> deck;
	func(deck);

	cout << "\napakah data akan disimpan di dalam file?\n(y|n)\n";
	cout << "\ncatatan: data yang disimpan tidak bisa diubah\n";
	cin >> h;
	if (h == 'y' or h == 'Y')
	{
		fstream datafile;

		//you can change this path
		datafile.open("./untitled.txt", fstream::in | fstream::out | fstream::app);

		if (datafile.is_open())
		{
			datafile << "\n";
			datafile << ctime(&tt);
			for (int i = 0; i < deck[0].size(); ++i)
			{
				datafile << (i + 1) << '.' << left << setw(25) << deck[0][i] << left << setw(10) << deck[1][i] << left << setw(20) << deck[2][i] << '\n';
			}
		}
		datafile.close();
	}
	return 0;
}