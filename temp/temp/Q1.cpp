/*#include<iostream>
#include<string>
#include<vector>
using namespace std;

class DrawYellow
{
public:
	void draw()
	{
		cout << "yellow" << endl;
	}
};

class DrawRed
{
public:
	void draw()
	{
		cout << "red" << endl;
	}
};

class geometricobject
{
public:
	virtual void draw() = 0;
};

template<class Color>
class geometric :public geometricobject
{
public:
	void draw()
	{
		Color color;
		color.draw();
	}
	
};

void main()
{
	vector<geometricobject*>drawincolor;

	drawincolor.push_back(new geometric<DrawRed>);
	drawincolor.push_back(new geometric < DrawYellow>);

	for (auto x : drawincolor)
		x->draw();
}*/

#include<iostream>
#include<string>

using namespace std;

template <class T_type>
void print(const T_type &i) {
	cout << i << endl;
}

int main() {
	print(1);
	print(2.345f);
	print("Hello World");

	return 0;
}
