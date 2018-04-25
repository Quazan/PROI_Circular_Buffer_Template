#include <algorithm>
#include "buffer.h"
using namespace std;

void funkcja(string i)
{
	cout<<i<<" ";
}

int main()
{
	string s;
	Buffer<string> one;
	Buffer<string> two;
	Buffer<int> tester;
	Buffer<int> pomoc;
	int error = 0;
	int z = 1;
	int t;

	while(z != 0)
	{
		printf("SANDBOX\n\n");

		printf("[1] Dodaj element do pierwszego bufora\n");
		printf("[2] Dodaj element do drugiego bufora\n");
		printf("[3] Wypisz pierwszy bufor\n");
		printf("[4] Wypisz drugi bufor\n");
		printf("[5] Zsumuj bufory (dodaj drugi do pierwszego)\n");
		printf("[6] Wypisz element z pierwszego buforu\n");
		printf("[7] wypisz element z drugiego buforu\n");
		printf("[8] Wyczysc bufor pierwszy\n");
		printf("[9] Wyczysc bufor drugi\n");
		printf("[10] Sprawdz czy bufory są takie same\n");
		printf("[11] Wypisz rozmiary obu buforow\n");
		printf("[12] Wypisz oba bufory (for_each)\n\n");

		printf("TESTY JEDNOSTKOWE\n\n");

		printf("[13] Test metody wpisania\n");
		printf("[14] Test metody wypisania\n");
		printf("[15] Test metody usuwania\n");
		printf("[16] Test metody porownywania buforow\n");
		printf("[17] Test metody sumowania buforow\n\n");


		printf("[0] Zakoncz\n\n");

		
		cin>>z;
		if(z < 0 || z > 17)
		{
			printf("BLAD WPROWADZANIA DANYCH\n");
			continue;
		}

		getline(cin, s);

		if(s.size() != 0) 
		{
			printf("BLAD WPROWADZENIA DANYCH\n");
			printf("\n\n");
			continue;
		} 

		switch(z)
		{
			case 1:
				printf("Wpisz ilosc elementow, nastepnie wypisz je po spacji\n");
				cin>>one;
				cout<<one.get_error();
				break;

			case 2:
				printf("Wpisz ilosc elementow, nastepnie wypisz je po spacji\n");
				cin>>two;
				cout<<two.get_error();
				break;

			case 3:
				cout<<one;
				break;

			case 4:
				cout<<two;
				break;

			case 5:
				one += two;
				cout<<one.get_error();
				break;

			case 6:
				cout<<one.pop()<<endl;	
				break;

			case 7:
				cout<<two.pop()<<endl;
				break;

			case 8:
				one.clear();
				break;

			case 9:
				two.clear();
				break;

			case 10:
				if(one == two)
				{
					printf("Sa takie same\n");
				}
				else
				{
					printf("Sa rozne\n");
				}
				break;
			
			case 11:
				cout<<"Bufor pierwszy: "<<one.count()<<endl;
				cout<<"Bufor drugi: "<<two.count()<<endl;
				break;

			case 12:
				printf("Bufor pierwszy:\n");
				for_each(one.begin(), one.end(),funkcja);
				printf("\n");
				printf("Bufor drugi:\n");
				for_each(two.begin(), two.end(),funkcja);
				printf("\n");
				break;

			case 13:
				for(int i = 3; i <= 7; i++)
				{
					pomoc+=i;
				}

				tester += 1;
				tester.push(2);
				tester += 3;
				tester.push(4);
				tester.push(5);
				tester += 6;
				tester.push(7);

				if(tester == pomoc)
				{
					printf("Test poprawny\n");
				}

				tester.clear();
				pomoc.clear();

				break;

			case 14:

				tester.pop();
				if(tester != pomoc)
				{
					error++;
				}

				tester.push(1);
				tester.pop();

				if(tester != pomoc)
				{
					error++;
				}

				for(int i = 1; i <= 6; i++)
				{
					tester.push(i);
				}

				for(int i = 1; i <= 6; i++)
				{
					tester.pop();
				}

				if(tester != pomoc)
				{
					error++;
				}

				if(error != 0)
				{
					printf("Test niepoprawny\n");
				} 
				else
				{
					printf("Test poprawny\n");
				}
				tester.clear();
				error = 0;
				break;

			case 15:
				tester.clear();
				if(tester != pomoc)
				{
					error++;
				}

				tester += 1;
				tester.clear();

				if(tester != pomoc)
				{
					error++;
				}

				for(int i = 1; i <= 6; i++)
				{
					tester += i;
				}
				tester.clear();

				if(tester != pomoc)
				{
					error++;
				}
				if(error != 0)
				{
					printf("Test niepoprawny\n");
				} 
				else
				{
					printf("Test poprawny\n");
				}
				tester.clear();
				error = 0;
				break;

			case 16:

				if(tester != pomoc)
				{
					error++;
				}

				for(int i = 1; i <= 5; i++)
				{
					tester += i;
				}

				if(tester == pomoc)
				{
					error++;
				}

				tester.pop();
				tester.pop();

				pomoc += 1;
				pomoc += 10000;

				if(tester == pomoc)
				{
					error++;
				}
				if(error != 0)
				{
					printf("Test niepoprawny\n");
				} 
				else
				{
					printf("Test poprawny\n");
				}
				tester.clear();
				pomoc.clear();
				error = 0;
				break;

			case 17:
				tester += pomoc;
				if(tester != pomoc)
				{
					error++;
				}
				tester += 1;
				tester += 2;
				pomoc += 3;
				pomoc += 4;
				pomoc += 5;
				pomoc += 6;
				tester += pomoc;
				pomoc.clear();
				for(int i = 2; i <= 6; i++)
				{
					pomoc += i;
				}
				if(tester != pomoc)
				{
					error++;
				}
				pomoc.clear();
				for(int i = 5; i >= 1; i--)
				{
					pomoc += i;
				}
				tester += pomoc;
				if(tester != pomoc)
				{
					error++;
				}
				if(error != 0)
				{
					printf("Test niepoprawny\n");
				} 
				else
				{
					printf("Test poprawny\n");
				}
				tester.clear();
				pomoc.clear();
				error = 0;
				break;
				
			case 0:
				return 0;
				break;
		}
		printf("\n\n");
	}
}