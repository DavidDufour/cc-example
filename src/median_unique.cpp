#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

// returns a double representing the average of two doubles
double average(double a, double b)
{
	return (a+b)/2.0;
}

// counts the number of unique words in a tweet
int getUniqueWordCount(string tweet)
{
	// words in tweet are separated by white space
	char_separator<char> whiteSpace(" \t\v\f");

	// frequency of each word in all tweets (running count)
    map<string,int> reduce;

	// separate the words in a tweet by whitespace
	tokenizer<char_separator<char> > tokens(tweet, whiteSpace);
	
	// add to the count of each word in the frequency map
	for (tokenizer<char_separator<char> >::iterator it = tokens.begin(); it != tokens.end(); ++it)
		++reduce[*it];
	
	// return the number of unique words seen in the tweet
	return reduce.size();
}

// returns the new median given two heaps
template<typename ta, typename tb>
double findNewMedian(ta a, tb b, int uniqueWordCount, double median)
{
	if (a.size() == b.size())
	{
		// add the unique word count to the heap
		a.push(uniqueWordCount);

		// the new median is the top of that heap
		return a.top();
	}
	else if (a.size() < b.size())
	{
		// add the unique word count to the heap
		a.push(uniqueWordCount);

		// the new median is the average of the top of the two heaps
		return average( a.top(), b.top() );
	}
	else if (a.size() > b.size())
	{
		// move the old median to the other heap
		b.push(a.top());
		a.pop();

		// add the new median to the heap
		a.push(uniqueWordCount);

		// the new median is the average of the top of the two heaps
		return average( a.top(), b.top() );
	}
}

int main()
{
	// file with input tweets
	ifstream tweets("tweet_input/tweets.txt");

	// file with the results from the second feature
	ofstream results("tweet_output/ft2.txt");

	// string for storing tweet
	string tweet;

	// maximum heap of tweets containing less or equal unique words than the median
	priority_queue<int> maxheap;
	
	// minimum heap of tweets containing greater or equal unique words than the median
	priority_queue<int, vector<int>, greater<int> > minheap;	

	// current median from tweets seen so far
	double median;
	
	// reads the tweets in line by line
	while (getline(tweets, tweet))
    {		
		// get the number of unique words in the tweet
		int uniqueWordCount = getUniqueWordCount(tweet);

		// initialize median
		if (maxheap.size() == 0)
		{
			maxheap.push(uniqueWordCount);

			median = maxheap.top();
		}
		// new word count is the same as the median
		else if (uniqueWordCount == median)
		{
			// both heaps are the same size
			if(maxheap.size() == minheap.size())
			{
				// add the new word count to the heap of word counts less than or equal to the median
				maxheap.push(uniqueWordCount);

				// the median shouldn't change here
				median = maxheap.top();
			}
			// the heap representing the word counts less than or equal to the median is smaller than the heap representing the word counts greater than or equal to the median 
			else if (maxheap.size() < minheap.size())
			{
				// add the new word count to the heap of word counts less than or equal to the median
				maxheap.push(uniqueWordCount);
				
				// the heaps should be the same size now so an averaging of the median values is reguired
				median = average( maxheap.top(), minheap.top() );
			}
			// the heap representing the word counts greater than or equal to the median is smaller than the heap representing the word counts less than or equal to the median
			else
			{
				// add the new word count to the heap of word counts greater than or equal to the median
				minheap.push(uniqueWordCount);

				// the heaps should be the same size now so an averaging of the median values is reguired
				median = average( minheap.top(), maxheap.top() );
			}
		}
		// the new word count is less than the current median
		else if (uniqueWordCount < median)
		{	
			// add the new word count to the heap of word counts less than or equal to the median and rearrage the heaps as necessary
			median = findNewMedian(maxheap, minheap, uniqueWordCount, median);
		}
		// the new word count is greater than the current median
		else if (uniqueWordCount > median)
		{
			// add the new word count to the heap of word counts greater than or equal to the median and rearrage the heaps as necessary
			median = findNewMedian(minheap, maxheap, uniqueWordCount, median);
		}

		// output the current median unique number of words per tweet
		results << median << endl;
	}
}