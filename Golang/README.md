Following are my notes from "A Tour of Go".

# Basics of Golang

## Packages, Imports & Exported Names

Consider the program:
```golang
package main

import (
	"fmt"
	"math"
)

func main() {
	fmt.Println(math.Pi)
	fmt.Println(math.Sqrt(25))
}
```

Every Go program is made up of **packages**, and starts running in package `main`.
Imports are parenthesized under one/many **import statement**. Package name also serve as the last element of import path for that package.
eg: Above import could also be written as:
```golang
import("fmt")
import("math")
```

In Go, a name is **Exported** if it begins with a capital letter. (eg. `Pi`, `Sqrt` in above program)
When importing a package, you can refer only to its exported names. Any "unexported" names are not accessible from outside the package (like access control staments in java).

## Functions
Consider the program:
```golang
package main

import "fmt"

func addAndMultiply(x int, y int) (int, int) {
	return x+y, x*y
}

func main() {
	fmt.Println(addAndMultiply(42, 13))
}
```

Output: `55 546`

Note:
1. Type of any variable, return type of functions are written to right.
2. When two or more **consecutive** named function parameters share a type, you can omit the type from all but the last. eg: `func add(x, y int)`.
3. Function may have **multiple return results** as in above example program.

**Named return values**: The return values of any function can be named which will allow usage of *naked* `return` statement.
eg: In previous program, the function can be written as below and its naked `return` will be same as `return x+y, x*y`
```golang
func addAndMultiply(x int, y int) (a int, m int) {
	a = x+y
	m = x*y
	return
}
```

Though even after defining named returns, you can use `return a, m`. Naked return is not preffered in long functions for better readability.