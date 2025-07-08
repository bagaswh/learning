package main

import (
	"fmt"
)

func appendInt(x []int, y ...int) []int {
	var z []int
	xlen := len(x)
	zlen := len(x) + len(y)
	xcap := cap(x)
	if zlen > xcap {
		zcap := 0
		if xcap > 256 {
			zcap = (xcap + 768) / 4
		}
		if zlen > zcap {
			zcap = zlen
		}
		// new backing array
		z = make([]int, zlen, zcap)
	} else {
		// extends the slice
		z = x[:zlen]
	}
	copy(z[xlen:], y)
	return z
}

func appendInt_book(x []int, y int) []int {
	var z []int
	zlen := len(x) + 1
	if zlen <= cap(x) {
		// There is room to grow. Extend the slice.
		z = x[:zlen]
	} else {
		// There is insufficient space. Allocate a new array.
		// Grow by doubling, for amortized linear complexity.
		zcap := zlen
		if zcap < 2*len(x) {
			zcap = 2 * len(x)
		}
		z = make([]int, zlen, zcap)
		copy(z, x) // a built-in function; see text
	}
	z[len(x)] = y
	return z
}

func main() {
	x1_Mult := make([]int, 0, 0)
	x1_Mult = append(x1_Mult, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
	fmt.Println(x1_Mult, cap(x1_Mult))

	x2_Mult := make([]int, 0, 0)
	x2_Mult = appendInt(x2_Mult, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
	fmt.Println(x2_Mult, cap(x2_Mult))

	// x1 := make([]int, 0, 1)
	// x1 = append(x1, 1)
	// x1 = append(x1, 2)
	// x1 = append(x1, 3)
	// fmt.Println(x1, cap(x1))

	// x2 := make([]int, 0, 1)
	// x2 = appendInt(x2, 1)
	// x2 = appendInt(x2, 2)
	// x2 = appendInt(x2, 3)
	// fmt.Println(x2, cap(x2))

	// x3 := make([]int, 0, 1)
	// x3 = appendInt_book(x3, 1)
	// x3 = appendInt_book(x3, 2)
	// x3 = appendInt_book(x3, 3)
	// fmt.Println(x3, cap(x3))

	// // 0 cap
	// x1_0cap := make([]int, 0, 0)
	// x1_0cap = append(x1_0cap, 1)
	// // fmt.Println("x1_0cap first append cap:", cap(x1_0cap))
	// x1_0cap = append(x1_0cap, 2)
	// x1_0cap = append(x1_0cap, 3)
	// fmt.Println(x1_0cap, cap(x1_0cap))

	// x2_0cap := make([]int, 0, 0)
	// x2_0cap = appendInt(x2_0cap, 1)
	// // fmt.Println("x2_0cap first append cap:", cap(x2_0cap))
	// x2_0cap = appendInt(x2_0cap, 2)
	// x2_0cap = appendInt(x2_0cap, 3)
	// fmt.Println(x2_0cap, cap(x2_0cap))

	// x3_0cap := make([]int, 0, 0)
	// x3_0cap = appendInt_book(x3_0cap, 1)
	// // fmt.Println("x3_0cap first append cap:", cap(x3_0cap))
	// x3_0cap = appendInt_book(x3_0cap, 2)
	// x3_0cap = appendInt_book(x3_0cap, 3)
	// fmt.Println(x3_0cap, cap(x3_0cap))

	// // nil slice
	// var x1_nil = []int{}
	// x1_nil = append(x1_nil, 1)
	// fmt.Println("x1_nil first append cap:", cap(x1_nil))
	// x1_nil = append(x1_nil, 2)
	// x1_nil = append(x1_nil, 3)
	// fmt.Println(x1_nil, cap(x1_nil))

	// var x2_nil = []int{}
	// x2_nil = appendInt(x2_nil, 1)
	// fmt.Println("x2_0cap first append cap:", cap(x2_nil))
	// x2_nil = appendInt(x2_nil, 2)
	// x2_nil = appendInt(x2_nil, 3)
	// fmt.Println(x2_nil, cap(x2_nil))

	// var x3_nil = []int{}
	// x3_nil = appendInt_book(x3_nil, 1)
	// fmt.Println("x3_nil first append cap:", cap(x3_nil))
	// x3_nil = appendInt_book(x3_nil, 2)
	// x3_nil = appendInt_book(x3_nil, 3)
	// fmt.Println(x3_nil, cap(x3_nil))
}
