#ifndef SBAT_PADDING_H
#define SBAT_PADDING_H

#include <SFML/Graphics.hpp>

namespace sbat
{
	struct Padding
	{
		Padding()
			:
			left(0),
			down(0),
			right(0),
			top(0)
		{

		}

		Padding(int a_top, int a_down , int a_left , int a_right)
			:
			left(a_left),
			down(a_down),
			right(a_right),
			top(a_top)
		{

		}
		int left, right, top, down;
	};
}

#endif // SBAT_PADDING_H
