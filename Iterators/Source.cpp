#include <iostream>
#include <vector>
#include <forward_list>
#include <iterator>
#include "T15funcs.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <numeric>
#include "helperfunctions.h"

class Element
{
public:
	Element(int a, int b, int c)
		:
		id(a),
		x(b),
		y(c)
	{}
	void Print() const
	{
		std::cout << "id: " << id << " | x: " << x << " | y: " << y << std::endl;
	}
	int GetY() const
	{
		return y;
	}
	const bool operator<(Element& rhs) const
	{
		return id < rhs.id;
	}
//	const bool operator>(Element& rhs) const
//	{
//		return id > rhs.id;
//	}
	class YLess
	{
	public:
		bool operator()( const Element& lhs, const Element& rhs ) const
		{
			return lhs.y < rhs.y;
		}
	};
	class DescId
	{
	public:
		bool operator()(const Element& lhs, const Element& rhs) const
		{
			return lhs.id > rhs.id;
		}
	};
private:
	int id;
	int x;
	int y;
};
void T15stuff()
{
	std::vector<int> vi = { 0,    1,    2,    3,    4,     5,    6 };

	std::vector<float> vf = { 0.1f, 1.2f, 2.2f, 3.1f, 44.3f, 5.0f, 6.6f };
	//std::string str = "hello";

	//std::forward_list<int> li = { 1,2,3 };

	printI(vi.data(), vi.data() + vi.size());
	//print(vi.begin(),vi.end());
	//print(vf.begin(),vf.end());
	//print(str.cbegin(),str.cend());

	//print(li.begin(),li.end());
	/*for (auto i = vi.begin(), e = vi.end(); i != e; )
	{
		if (*i % 2 == 0)
		{
			i = vi.erase(i);
		}
		else
		{
			++i;
		}
	}*/
	std::vector<float> vfsum;
	//sum(vi.begin(), vi.end(), vf.begin(), std::ostream_iterator<float>(std::cout, ", "));
	sum(vi.begin(), vi.end(), vf.begin(), std::back_inserter(vfsum));

	printX(vfsum.data(), vfsum.data() + vfsum.size());

	/*
	for ( std::vector<int>::iterator L = vi.begin(); L != vi.end(); ++L)
	{
		std::cout << *L << " ";
	}

	int a[] = { 1,2,3,4,5 };
	printI(std::begin(a), std::end(a));
	*/
}
void Print(std::vector<Element>& evec)
{
	for (Element& e : evec)
	{
		e.Print();
	}
	std::cout << "-------------------------" << std::endl;
}
void T16stuff()
{
	std::vector<Element> elementen = { {1,2,2},{4,2,12},{3,0,1},{0,0,0}, {99,4,11} };

	class ThresholdTestY
	{
	public:
		ThresholdTestY(int thresh)
			:
			thresh(thresh)
		{}
		bool operator()(const Element& elem) const
		{
			return elem.GetY() > thresh;
		}
	private:
		int thresh;
	};

	ThresholdTestY testTh(3);
	bool res;
	res = testTh({ 1,1,1 });
	res = testTh({ 1,1,4 });

	Print(elementen);

	std::sort(elementen.begin(), elementen.end(), Element::YLess{});
	Print(elementen);

	std::sort(elementen.begin(), elementen.end());
	Print(elementen);

	std::sort(elementen.begin(), elementen.end(), Element::DescId{});
	Print(elementen);

	//const auto new_end = std::remove_if(elementen.begin(), elementen.end(), ThresholdTestY(3));
	//USE LAMBDA FUNCTION INSTEAD
	auto mylamb = [](const Element& elem)->bool
	{
		return elem.GetY() > 10;
	};
	auto mylambIter = [](const auto iter)->bool
	{
		return iter->GetY() == 1;
	};
	bool test = mylamb(elementen.front());
	test = mylamb(*(elementen.begin() + 1));
	test = mylambIter(elementen.begin() + 2);


	int thresh = 3;
	const auto new_end = std::remove_if(elementen.begin(), elementen.end(),
		[thresh](const Element& elem)
		{
			return elem.GetY() > thresh;
		}
	);
	elementen.erase(new_end, elementen.end());

	Print(elementen);

	//std::vector<int> vec{9, 8,1,6,1,4,3,2,1,0};
	//std::sort(vec.begin(), vec.end(), std::greater<int>());

}

// you may not modify this
struct Pube
{
	int num;
	std::string str;
	bool operator<(const Pube& rhs) const
	{
		return num < rhs.num;
	}
	operator int() const
	{
		return num;
	}
};

// write your remove_erase_if template function here!
// Method 1
/*
template<class T, typename L>
void remove_erase_if(T& vec, L lambda)
{
	for (auto iter_runner = vec.begin(); iter_runner != vec.end(); )
	{
		if (lambda(*iter_runner))
		{
			iter_runner = vec.erase(iter_runner);
		}
		else
		{
			++iter_runner;
		}
	}
}
*/
// Method 3 (CHILI METHOD)
template<class T, typename L>
void remove_erase_if(T& container, L predicate)
{
	const auto new_end = std::remove_if(container.begin(), container.end(), predicate);
	container.erase(new_end, container.end());
}
// write your custom insertion operator here!
std::ostream& operator<<(std::ostream& os, const Pube& p)
{
	os << p.num << ", " << p.str ;
	return os;
}


void Homework()
{
	////////////////////////////////////////////////////////////////////////////
	//     !! HOMEWORK !!
	// use the C++ <algorithms> as extensively as you can for these problems!

	// materiel (do not modify!)
	const std::vector<Pube> numbers = {
		{ 0,"zero" },
		{ 9,"nine" },
		{ 7,"seven" },
		{ 2,"two" },
		{ 8,"eight" },
		{ 3,"three" },
		{ 4,"four" },
		{ 1,"one" },
		{ 6,"six" },
		{ 5,"five" }
	};
	const std::vector<Pube> memes = {
		{ 3,"dat boi" },
		{ 1,"yaaaas" },
		{ 3,"soviet russia" },
		{ 1,"damn daniel" },
		{ 1,"hipster ariel" },
		{ 3,"harambe" },
		{ 2,"doge" },
		{ 3,"cash me outside" },
		{ 2,"henlo" },
		{ 3,"kappa" }
	};
	const std::string nambies = "eight one six eight three three eight five four two nine six nine";
	const std::string numpies = { 6, 6, 5, 0, 6, 1, 8, 6 };
	
	// Problem 1:
	// create a vector that contains 4 copies of each of the elements of memes
	// sort it first by number descending (score from 3 to 1) and then name ascending
	// output sorted meme list w/ score and name using custom insertion operator
	std::cout << "<< Sort Memes >>" << std::endl;
	{
		// STEP 1. Create vector with 4x elements of memes
		/*// Method 1
		std::vector<Pube> sortedMemes(4 * memes.size());// , { 0,"" });
		int offset = memes.size();
		auto insert2 = sortedMemes.begin();
		for (auto in1 = memes.begin(), end1 = memes.end(); in1 != end1; ++in1, ++insert2)
		{
			for (int i=0;i<4;i++) *(insert2 + i*offset) = *in1;
		}
		*/
		/*// Method 2
		std::vector<Pube> sortedMemes(4 * memes.size());// , { 0,"" });
		for (int i = 0; i < 4; i++)
		{
			int offset = i * memes.size();
			std::copy(memes.begin(), memes.end(), sortedMemes.begin()+offset);
		}
		*/
		/*// Method 3
		std::vector<Pube> sortedMemes(4 * memes.size());// , { 0,"" });
		for (size_t offset = 0; offset < sortedMemes.size(); offset+=memes.size())
		{
			std::copy(memes.begin(), memes.end(), sortedMemes.begin() + offset);
		}
		*/
		// Method 4 (Chili's solution)
		auto sortedMemes = memes;
		for (int i = 0; i < 3; i++)
		{
			sortedMemes.insert(sortedMemes.end(), memes.begin(), memes.end());
		}

		// STEP 2. Sort - 1st sorting run
		// Method 1: Sort Major (by number descending) - use reverse iterators
		/*
		std::sort(sortedMemes.rbegin(), sortedMemes.rend());
		*/
		// Method 2: Sort Major (by number descending) - use Lambda function
		/*
		std::sort(sortedMemes.begin(), sortedMemes.end(),
				[](Pube& lhs, Pube& rhs) {return lhs.num > rhs.num; }
			);
		*/
		// Method 3: Sort Major (by number descending) - define own custom functor in the Pube class
		/*
		std::sort(sortedMemes.begin(), sortedMemes.end(), Pube::Sort1{} );
		*/
		// Method 4: Sort Major (by number descending) - define functor in situ
		/*
		class Sort1
		{
		public:
			bool operator()(const Pube& lhs, const Pube& rhs) const
			{
				return lhs.num > rhs.num;
			}
		};
		std::sort(sortedMemes.begin(), sortedMemes.end(), Sort1{});
		*/
		// Method 5 (CHILI METHOD): Sort Minor (by meme string name ascenting)
		std::sort(sortedMemes.begin(), sortedMemes.end(), [](const Pube& lhs, const Pube& rhs)
			{
				return lhs.str < rhs.str;
			});

		// STEP 3. Sort - 2nd sorting run
		// Method 1: Sort Minor (by meme string name ascenting)
		/*
		auto lambSort2 = [] (Pube& lhs, Pube& rhs)
		{
			return lhs.str < rhs.str;
		};
		//auto end1 = std::find_end(sortedMemes.begin(), sortedMemes.end(), sortedMemes.begin(), sortedMemes.begin()+1 );
		//auto begin2 = std::find_if(sortedMemes.begin(), sortedMemes.end(), [](const Pube& p)->bool {return (int(p) != 3); });
		//std::sort(sortedMemes.begin(), begin2, Pube::Sort2{});
		//std::sort(sortedMemes.begin(), end1+1, Pube::Sort2{});
		auto iter_runner = sortedMemes.begin();
		while (iter_runner != sortedMemes.end())
		{
			auto end1 = std::find_end(iter_runner, sortedMemes.end(), iter_runner, iter_runner + 1);
			std::sort(iter_runner, end1 + 1, lambSort2);
			iter_runner = end1+1;
		}
		*/
		// Method 2 (CHILI METHOD): Sort Major (by number descending)
		std::stable_sort(sortedMemes.begin(), sortedMemes.end(), [](const Pube& lhs, const Pube& rhs)
			{
				return lhs.num > rhs.num;
			});

		// STEP 4: Write to the console
		// Method 1
		/*
		for (Pube& p : sortedMemes)
		{
			std::cout << p << std::endl;
		}
		*/
		// Method 2 (CHILI METHOD)
		std::copy(sortedMemes.begin(), sortedMemes.end(), std::ostream_iterator<Pube>(std::cout, "\n"));
	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 2:
	// output nambies as string of digits without spaces
	// (can be done in single statement!)
	std::cout << "<< Number Words to Digits >>" << std::endl;
	{
		// code goes here
		// Method 1: extract nambies strings using stream operations
		/*
		std::string str = "";
		std::istringstream stream(nambies);
		std::ostringstream out;
		while (stream >> str)
		{
			auto begin = std::find_if(numbers.begin(), numbers.end(), [str](const Pube& p)->bool {return (p.str == str); });
			out << begin->num;
		}
		str = out.str();
		std::cout << str << std::endl;
		*/
		// Method 2 (CHILI METHOD)
		
		std::istringstream stream(nambies);
		//std::vector<std::string> tokens{ std::istream_iterator<std::string>(stream >> std::skipws),{} };

		std::transform(
			// this works (with helper function in header file):
			//std::istream_iterator<std::string>(lvalue(std::istringstream(nambies))),
			std::istream_iterator<std::string>(stream),
			std::istream_iterator<std::string>(),
			std::ostream_iterator<int>(std::cout),
			[&numbers](std::string str)->int
			{
				auto p = std::find_if(numbers.begin(), numbers.end(), [str](const Pube& p)->bool {return (p.str == str); });
				return p->num;
			}
		);
		
	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 3:
	// output numpies as a string of words separated by spaces
	// don't use std::find_if or other searches
	std::cout << "<< Digits to Number Words >>" << std::endl;
	{
		// code goes here
		// Method 1
		/*
		// STEP 1: sort the vector "number"
		std::vector<Pube> numbers2 = numbers;
		std::sort(numbers2.begin(), numbers2.end());
		// STEP 2: match digits with numbers by indexing "number" with the tentative digit
		std::istringstream stream(numpies);
		char i;
		while (stream >> i)
		{
			std::cout << numbers2[i].str << " ";
		}
		*/
		// Method 2 (CHILI METHOD)
		
		auto sorted = numbers;
		std::sort(sorted.begin(), sorted.end());
		std::transform(numpies.begin(), numpies.end(), std::ostream_iterator<std::string>(std::cout, " "),
			[&sorted](char ch) 
			{
				return sorted[ch].str;
			}
		);
		std::cout << std::endl;
	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 4:
	// find the product of all numbers in nambies
	// and output of course
		
	std::cout << "<< Product >>" << std::endl;
		
	{
		// code goes here
		/*
		// Method 1
		std::istringstream stream(nambies);
		std::vector<std::string> numberTokens{ std::istream_iterator<std::string>(stream >> std::skipws),{} };
		int product = 1;
		for (const std::string& s : numberTokens)
		{
			int num = std::find_if(numbers.begin(), numbers.end(), [&s](const Pube& p)->bool { return p.str == s; })->num;
			product *= num;
		}
		std::cout << product << std::endl;
		*/
		//Method 2 (CHILI METHOD)
		std::vector<int> nums;
		std::istringstream stream(nambies);
		std::transform(
			std::istream_iterator<std::string>(stream),
			std::istream_iterator<std::string>(),
			std::back_inserter(nums),
			[&numbers](std::string str)
			{
				auto p = std::find_if(numbers.begin(), numbers.end(), [str](const Pube& p)->bool {return (p.str == str); });
				return p->num;
			}
		);
		/*
		int product = 1;
		for (int n : nums)
		{
			product *= n;
		}
		*/
		//int product = std::accumulate(nums.begin(), nums.end(), 1, [](int cum, int n) {return cum * n; });
		int product = std::accumulate(nums.begin(), nums.end(), 1, std::multiplies<int>() );

		std::cout << product << std::endl;
	}
	
	
	std::cout << "============================================" << std::endl << std::endl;


	// Problem 5:
	// find sums of corresponding nums in numbers and memes
	// output as comma separated list
	std::cout << "<< Parallel Sum >>" << std::endl;
	{
		// code goes here
		// Method 1
		/*
		std::transform(numbers.begin(), numbers.end(), memes.begin(), 
			std::ostream_iterator<int>(std::cout, ","), 
			[](const Pube& n, const Pube& m)->int {return n.num + m.num; }
		);
		*/
		// Method 2 (CHILI METHOD)
		std::transform(numbers.begin(), numbers.end(), memes.begin(),
			std::ostream_iterator<int>(std::cout, ","), std::plus<int>{}
		);

		std::cout << std::endl;
		
	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 6:
	// write a template function (not here, above int main())
	// that will remove elements from vector based on unary predicate
	// the following code should not be modified
	std::cout << "<< Top Memes >>" << std::endl;
	{
		// copy to get non-const vector
		auto maymays = memes;
		// remove all memes with score below 3
		remove_erase_if(maymays, [](const Pube& p) { return p.num < 3; });
		// output results
		std::copy(maymays.begin(), maymays.end(), std::ostream_iterator<Pube>(std::cout, "\n"));
	}
	std::cout << "============================================" << std::endl << std::endl;
}

int increment(int x) { return x + 1; }
void ExperimentWithFunctors()
{
	int arr[] = { 1,2,3,4,5 };
	int n = sizeof(arr) / sizeof(arr[0]);

	//apply function reference
	std::transform( arr, &arr[n], arr, increment );
	//apply a lambda function
	std::transform( arr, &arr[n], arr, [](int& x)->int {return x -5 ; });

	class increment
	{
	public:
		increment()
			:
			x(10)
		{}
		increment(int x)
			:
			x(x)
		{}
		int operator()(int in)
		{
			return in + x;
		}
	private:
		int x;

	};
	
	//different applications of functors
	std::transform( arr, &arr[n], arr, increment(+10) );
	increment obj(100);
	std::transform(arr, &arr[n], arr, obj);
	std::transform(arr, &arr[n], arr, increment()  );
	PerformTransform(arr, &arr[n], increment(1000) );
}

int main()
{
	//ExperimentWithFunctors();
	Homework();


	std::cin.get();
	return 0;
}	