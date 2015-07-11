Insight Data Engineering - Coding Challenge
===========================================================

## Challenge Summary

This challenge is to implement two features:

1. Calculate the total number of times each word has been tweeted.
2. Calculate the median number of *unique* words per tweet, and update this median as tweets come in. 

For example, suppose the following three tweets come in, one after the other

- is #bigdata finally the answer to end poverty? @lavanyarathnam http://ow.ly/o8gt3  #analytics  
- interview: xia wang, astrazeneca on #bigdata and the promise of effective healthcare #kdn http://ow.ly/ot2uj  
- big data is not just for big business. on how #bigdata is being deployed for small businesses: http://bddy.me/1bzukb3  @cxotodayalerts #smb  

The first feature would produce the following total count for each word:

	#analytics  				1
	#bigdata 					3
	#kdn 						1
	#smb 						1
	@cxotodayalerts 			1
	@lavanyarathnam 			1
	and 						1
	answer  					1
	astrazeneca 				1
	being 						1
	big 						2
	business. 					1 
	businesses: 				1
	data 						1
	deployed 					1
	effective 					1
	end 						1
	finally 					1
	for 						2
	healthcare 					1
	how 						1
	http://bddy.me/1bzukb3  	1
	http://ow.ly/o8gt3 	 		1
	http://ow.ly/ot2uj  		1
	interview: 					1
	is  						3
	just 						1
	not 						1
	of 							1
	on 							2
	poverty? 					1
	promise 					1
	small 						1
	the  						2
	to  						1
	wang,						1
	xia 						1

For the second feature, the number of unique words in each tweet is 11, 14, and 17 (since the words 'is', 'big', and 'for' appear twice in the third tweet).  This means that the set of unique words per tweet is {11} after the first tweet arrives, is {11, 14} after the second tweet arrives, and is {11, 14, 17} after all three tweets arrive.  Thus, the second feature would produce the following output:

	11
	12.5
	14

Recall that the median of a set with an even number of items is the mean of the two middle elements (e.g. the median of {11, 14} is 12.5). In this challenge we have made a few assumptions to make things simpler:

- Each tweet only contains lowercase letters, numbers, and ASCII characters like ':', '@', and '#'.
- A word is defined as anything separated by whitespace. 

Note that the output of the first feature is outputted in order, according to the [ASCII Code](http://www.ascii-code.com).   

## Details of Implementation

Normally, tweets can be obtained through Twitter's API in JSON format and the "payload" text is parsed, but you may assume that this has already been done and written to a file named 'tweets.txt' inside a directory named 'tweet_input'.  For simplicity, this file 'tweets.txt' will only contain lowercase letters, numbers, and ASCII characters (e.g. common punctuation and characters like '@', and '#').  Additionally, 'tweets.txt' will have the content of each tweet on a newline:

tweets.txt:

	Contents of first tweet  
	Contents of second tweet  
	Contents of third tweet  
	.
	.
	.
	Contents of last tweet  

My program outputs the results of this first feature to a text file named `ft1.txt` in a directory named `tweet_output`.  My submission outputs the results of my first feature in order, according to the [ASCII Code](http://www.ascii-code.com), as shown in the above example.  For simplicity, treat all punctuation as part of the word itself, so 'business.' would be counted as a different word than 'business' without the period.

Assume that each new line of the text file corresponds to a new tweet and design your program to handle a text file with a large number of tweets.  My program outputs the results of this second feature to a text file named `ft2.txt` in the `tweet_output` directory.

## Libraries

My code requires boost_1_58_0 to run
