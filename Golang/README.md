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
2. When two or more **consecutive** named function parameters share a type, you can omit the type from all but the last. eg: `func add(x, y int)`. Some function can have args sth like: `func add(x, y int, z bool)` also.
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

## Variables

### Declaration of Variables
This can be done in following ways:
1. Method 1: Declaration with zero initialisation
```golang
var a, b, c int
```
Note: <s>`var a, b, c int, d bool`</s> is wrong, i.e. all variables in one line must be of same type defined at the end. (Here *Go* will take `int` as the last word and throw an error "unexpected ,")
2. Method 2: Declaration with zero initialisation
If you want to define multiple kinds of variables, you can use multiple lines of point 1 or:
```golang
var(
	a, b int
	c bool
)
```
3. Method 3: Declaration with initialisation.
```golang
var a, b, c = 1, 2, true
```
Here, variables can be of different type.
4. Method 4: Declaration with initialisation.
```golang
a := 5
```

Here you don't need to use `var` keyword but this method can ber used only inside a function.

Notice in method 1, 2 above, the variables are auto initialised to a **ZERO VALUE** which is `0` for numeric types, `false` for the boolean, and `""` (empty string) for strings.

### Basic Types and Conversions
```
bool

string

int  int8  int16  int32  int64
uint uint8 uint16 uint32 uint64 uintptr

byte // alias for uint8

rune // alias for int32, represents a Unicode code point

float32 float64

complex64 complex128
```
By default int = intX for X bit system (X = 32 or 64). There exist **nothing like float**.

**Conversion:**
```golang
var f float32 = 5.5
var a int = int(f)
```

This won't work for string conversions. What works?
```golang
i, err := strconv.Atoi("-42")
s := strconv.Itoa(-42)

b, err := strconv.ParseBool("true")
f, err := strconv.ParseFloat("3.1415", 64)
i, err := strconv.ParseInt("-42", 10, 64)
u, err := strconv.ParseUint("42", 10, 64)
```

You can print type by: `fmt.Printf("a is of type %T", a)`

## Constants

Constants are declared like `const Truth = true`. They cannot be declared with `:=`, though the parenthesis format is valid.