// Bjarne Stroustrup 7/20/2009
// Chapter 4 Exercise 3

#include "std_lib_facilities.h"	
// note that different compilers/SDEs keep header files in different places
// so that you may have to use "../std_lib_facilities.h" or "../../std_lib_facilities.h"
// the ../ notation means "look one directly/folder up from the current directory/folder"

/*
	Immediately, we are faced with the question "when do we stop reading in distance values?
	My choice here is "whenever we find a 0 or a negative distance"

	I decided to compute the sum of the distances, the smallest distance, and the largest distance
	as we read along. I could have waited until every value had been read and then go through the
	read values (now stored in the vector dist).
*/

int main()
try
{
	vector<double> dist;

	double sum = 0;	// accumulate total distance in sum
	double min = 0;	// smallest distance
	double max = 0; // latgest distance

	cout<< "please enter a whitespace-separated sequence of doubles (representing distances) : ";
	double val = 0;
	while (cin>>val) {	// read distance
		if (val<=0) {
			if (dist.size() == 0) error("no distances");
			cout << "total distance " << sum << '\n';
			cout << " smallest distance " << min << '\n';
			cout << "greatest distance " << max << '\n';
			cout << "mean distance " << sum/dist.size() << '\n';
			keep_window_open("~");	// For some Windows(tm) setups
			return 0;	// exit
		}
		dist.push_back(val);	// store the value

		// update the "running" values:
		sum += val;
		if (val<min) min = val;
		if (max<val) max = val;
	}
	if (dist.size() == 0) error("no distances");
	cout << "total distance " << sum << '\n';
	cout << " smallest distance " << min << '\n';
	cout << "greatest distance " << max << '\n';
	cout << "mean distance " << sum/dist.size() << '\n';
	keep_window_open("~");	// For some Windows(tm) setups
}
catch (runtime_error e) {	// this code is to produce error messages; it will be described in Chapter 5
	cout << e.what() << '\n';
	keep_window_open("~");	// For some Windows(tm) setups
}
catch (...) {	// this code is to produce error messages; it will be described in Chapter 5
	cout << "exiting\n";
	keep_window_open("~");	// For some Windows(tm) setups
}

/*
	Note the test for "no distances entered". Forgetting the case of "no input" is a common error.

	Why are the min and max correctly computed? 

	Is the mean correctly computed?

	what reason might I have had for computing sum, max, and mean as we read along? Could the code
	have been cleaner if I had postponed computation until after the last read?

	Why did I repeat the output statements? Replicating code is tedious and error-prone. Can you see
	a way of removing that replication?
*/

