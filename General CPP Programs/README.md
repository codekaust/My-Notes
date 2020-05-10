1. String functions: (char buffer[16] = {0}, string str;)
	- isalnum(char c), isalpha(char c), isdigit(char c), tolower(char c)
	- strlen(buffer) //does according to at which index it finds '\0' (as basically buffer is just char*)
	- cin>>buffer; //NOT PREFERRED: Can five stack-smashing-detected error.
	- cin.get(buffer, 10) //when you want to read 10 chars 
		-//clear input buffer otherwise cin.get wont wait for another input
    	`while ((getchar()) != '\n');`
	- cin>>str; //get word
	- getline(cin, str);
	- char* abc = (char * )(str.c_str()); // str.c_str() = const char*
	- convert b/w stirng and integer
		- string to integer
			- https://www.geeksforgeeks.org/converting-strings-numbers-cc/
		- integer to string
			- to_string(int)

2. Algorithm (#include<algorithm>) Functions: 
	- sort(a.begin(), a.end())
	- min(a,b), max(a,b)

3. Imp headers to knw:
	// #include<bits/stdc++.h> (GAWD)

	// #include<iostream>
	// #include<vector>
	// #include<stack>
	// #include<queue>
	// #include<map>
	// #include<unordered_map>
	// #include<string>
	// #include<string.h>
	// #include <list>
	// #include<algorithm>

4. Data Structure and Methods
	1. **Priority Queue**:
		- `#include <queue>`
		- Get pq.pop() in ASCENDING ORDER:
			- `std::priority_queue<int, std::vector<int>, std::greater<int> > q2;`
		- DESCENDING ORDER
			- `std::priority_queue<int> q;` OR `std::priority_queue<int, std::vector<int>, std::less<int> > q2;` 
		- In place of using vector<int> as container, you may use dequeue<int>
		- Possible that you make your priority queue of some type for which greater than funtion is not defined. So you can do the following (example a vector<int> is prioritised according to size):
			- For ASCENDING ORDER, we passes `std::greater<type>` which returns if first parameter is bigger. So, we will define our own lambda:
				`auto cmp = [](vector<int> left, vector<int> right) { return (left.size()) > (right.size()); };`
			- FOR DESCENDING, do similar with sign `<`
			- One more way:
			Example:

			```cpp
			#include <functional>
			#include <queue>
			#include <vector>
			#include <iostream>
			 
			template<typename T> void print_queue(T& q) {
			    while(!q.empty()) {
			        std::cout << q.top() << " ";
			        q.pop();
			    }
			    std::cout << '\n';
			}

			template<typename T> void print_queue_2(T& q) {
			    while(!q.empty()) {
			        std::cout << q.top().size() << " ";
			        q.pop();
			    }
			    std::cout << '\n';
			}

			struct CompareVec { 
			    bool operator()(std::vector<int> left, std::vector<int> right) 
			    { 
			        return left.size() > right.size(); 
			    } 
			}; 
			 
			int main() {
			    std::priority_queue<int> q;
			 
			    for(int n : {1,8,5,6,3,4,0,9,7,2})
			        q.push(n);
			 
			    print_queue(q);
			 
			    std::priority_queue<int, std::vector<int>, std::greater<int> > q2;
			 
			    for(int n : {1,8,5,6,3,4,0,9,7,2})
			        q2.push(n);
			 
			    print_queue(q2);
			 
			     // Using lambda to compare elements.
			    auto cmp = [](std::vector<int> left, std::vector<int> right) { return (left.size()) > (right.size()); };
			    
			    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, decltype(cmp)> q3(cmp);
			 
			    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, CompareVec> q4;

			    for(int n : {1,8,5,6,3,4,0,9,7,2}){
			        q3.push(std::vector<int>(n));
			        q4.push(std::vector<int>(n));
			    }

			    print_queue_2(q3);
			    
			    print_queue_2(q4);
			}
			```

			Output:
			```
			9 8 7 6 5 4 3 2 1 0 
			0 1 2 3 4 5 6 7 8 9 
			0 1 2 3 4 5 6 7 8 9 
			0 1 2 3 4 5 6 7 8 9 
			```
