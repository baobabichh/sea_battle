#ifndef SBAT_COMPORABLE_H
#define SBAT_COMPORABLE_H



namespace sbat
{
	template <typename T>
	class Comparable
	{
	public:

		
		//NEED TO BE OVERLOADED  < and ==
		


		//AUTO
		bool operator<=( const  T& right)const
		{
			if (*this < right || *this == right)
				return 1;
			return 0;
		}
		bool operator>( const  T& right)const
		{
			if (!(*this < right) && !(*this == right))
				return 1;
			return 0;
		}
		bool operator>=( const  T& right)const
		{
			if (!(*this < right) && !(*this == right) || *this == right)
				return 1;
			return 0;
		}
		bool operator!=( const  T& right)const
		{
			if (!(*this == right))
				return 1;
			return 0;
		}

	};
}



#endif // !SBAT_COMPORABLE_H

