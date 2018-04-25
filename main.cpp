#include <algorithm>
#include "buffer.h"
using namespace std;

void funkcja(int i)
{
	cout<<i<<endl;
}

int main()
{
	Buffer<int> bufor;
	bufor.push(45);
	bufor.push(65);
	bufor.push(69);
	Buffer<int> bufor_2(bufor);
	cout<<bufor<<endl<<bufor_2;
	if(bufor != bufor_2)
	{
		printf("DZIALA\n");
	}
	else
	{
		printf("niedziala\n");
	}
	//bufor.clear();
	//cout<<bufor_2<<endl;
	//bufor_2.push(111);
	//bufor_2.push(123);
	//bufor_2.push(321);
	/*bufor+=bufor_2;
	//printf("chuj\n");
	bufor+=1;
	cout<<bufor;
	




//	Buffer<string> bufor_3;
	cin>>bufor;
	cout<<bufor;


*/
	for_each(bufor.begin(), bufor.end(),funkcja);

	cout<<bufor;
	bufor.clear();

	for_each(bufor.begin(), bufor.end(),funkcja);

}