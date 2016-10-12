#include<iostream>
#include<string>

template<class T_TYPE>
class Vector2D
{
public:
	T_TYPE x, y;
	Vector2D(const T_TYPE &input_x,const T_TYPE &input_y)
		:x(input_x),y(input_y)
	{}
};

int main()
{
	Vector2D<int> intvector(1, 2);
	Vector2D<float>floatvector(1.2f, 3.5f);
	Vector2D<double>doublevector(2.512, 3.161);
}