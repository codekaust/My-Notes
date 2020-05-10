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

2. Imp headers to knw:
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