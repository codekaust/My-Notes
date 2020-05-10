# Heap & Heap Sort

## How to represent a binary tree in an array?

Array must preserve the value of all nodes and the relations ships. We can just fill the array in depth first search manner (level by level) while leaving empty spaces for null nodes.

Consequences:
1. If the binary tree is **complete** -> Array will have no blank spaces. (A binary tree is **complete** if it is a **full** binary tree till max_height-1 and nodes are filled from left to right on the last level.).
2. Let max-height = h -> Length of array required is (2^h -1).
3. Relationship: Let a node x at position i of array (*indexing must from 1*)
	- Left Child: *(2\*i)*
	- Right Child: *(2\* + 1)*
	- Parent: *floor(i/2)*

NOTE: *Height* of a **complete binary tree** is *log(n)* [base 2 (of course)] [n=number of nodes].

## Max and Min Heap

Max Heap: A complete binary tree with every node having value greater than (or equal to) all its descendents.

Same for min heap (less than or equal to).