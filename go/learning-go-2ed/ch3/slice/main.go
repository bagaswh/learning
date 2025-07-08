package main

import "fmt"

func slices() {
	// the nil slice
	var s []int
	fmt.Println(s == nil)

}

func appendToSubslice() {
	sliceA := []int{1, 2, 3, 4, 5, 6}
	sliceA = append(sliceA, 7)
	fmt.Println("appended to sliceA")
	fmt.Println(sliceA)
	fmt.Println("cap sliceA", cap(sliceA))

	subsliceA := sliceA[1:2]
	fmt.Println("subsliceA", subsliceA)
	// it should be the end of the backing array
	fmt.Println("cap subsliceA", cap(subsliceA))
	subsliceA = append(subsliceA, 8)
	fmt.Println("appended to subslice")
	fmt.Println(sliceA)
	fmt.Println(subsliceA)

}

func evenMoreConfusingSlices() {
	x := make([]string, 0, 5)
	x = append(x, "a", "b", "c", "d")
	// x is now []string{"a", "b", "c", "d"}
	fmt.Println("x:", x)

	y := x[:2]
	// y is []string{"a", "b"}
	fmt.Println("y:", y)

	z := x[2:]
	// z is []string{"c", "d"}
	fmt.Println("z:", z)

	// cap(x) = 5, len(x) = 4
	// cap(y) = 5, len(y) = 2
	// cap(z) = 3, len(z) = 2
	fmt.Println(cap(x), cap(y), cap(z))
	fmt.Println(len(x), len(y), len(z))

	y = append(y, "i", "j", "k")
	// y is now []string{"a", "b", "i", "j", "k"}
	// x is now []string{"a", "b", "i", "j"}, since the len of x is 4
	fmt.Println("y after append:", y)
	fmt.Println("x after append:", x)

	x = append(x, "x")
	// x is now []string{"a", "b", "i", "j" "x"}
	// y is also now []string{"a", "b", "i", "j" "x"}
	fmt.Println("y after append:", y)
	fmt.Println("x after append:", x)

	z = append(z, "y")
	// z is now []string{"i", "j", "y"}
	// x is now []string{"a", "b", "i", "j" "y"}
	// y is now []string{"a", "b", "i", "j", "y"}
	fmt.Println("z after append:", z)
	fmt.Println("y after append:", y)
	fmt.Println("x after append:", x)

	fmt.Println("x:", x)
	fmt.Println("y:", y)
	fmt.Println("z:", z)
}

func fullSliceExpression() {
	x := make([]string, 0, 5)
	x = append(x, "a", "b", "c", "d")
	y := x[:2:2]
	// cap will be 2-0=2
	fmt.Println("cap(y)", cap(y))
	z := x[2:4:4]
	// cap will be 4-2=2
	fmt.Println("cap(z)", cap(z))

	// appending to either y and z will not change the contents of x
	// instead, since the cap is insufficient, a new backing array will be created that's unconnected to x
	y = append(y, "i", "j", "k")
	z = append(z, "l", "m", "n")

	fmt.Println("x:", x)
	fmt.Println("y:", y)
	fmt.Println("z:", z)
}

func copySlice() {
	x := []int{1, 2, 3, 4, 5, 6}
	y := make([]int, 3)
	// copying min(len(y), len(x)) elements from x to y
	copy(y, x)
	// y is now [1, 2, 3]
	fmt.Println("y:", y)

	// copy a subslice
	z := make([]int, 10)
	copy(z, x[2:4])
	// z is now [3, 4, 0 ... 0]
	fmt.Println("z:", z)

	x2 := []int{99, 999, 9999, 99999, 999999}
	copy(z[len(z)-5:], x2[2:4])
	fmt.Println("z:", z)

	arr1 := [...]int{42, 420, 24, 41, 39, 611}
	// because copy sees the length and not the capacity, it won't overwrite the contents of z past [2:5]
	// even arr1 is longer than z[2:5]
	// also, you can make a slice out of array by using the slice expression
	copy(z[2:5], arr1[:])
	fmt.Println(z)
}

func convertSliceToArray() {
	xSlice := []int{1, 2, 3, 4, 5, 6}
	xArray := [4]int(xSlice)
	fmt.Println(xArray)

	// will panic
	// xArray2's length can be bigger than the length of xSlice
	// xArray2 := [7]int(xSlice)
	// fmt.Println(xArray2)

	// convert slice into a pointer to an array
	// the memory is not shared
	xArrayPtr := (*[4]int)(xSlice)
	fmt.Println(xArrayPtr)
	xSlice[0] = 10
	fmt.Println(xArrayPtr)
}

func whyIStillDontUnderstandSlice() {
	// when we make a slice with length non zero, the elements up to the length are set to zero values
	sliceA := make([]int, 5)
	fmt.Println(sliceA)

	// when we make a slice with length zero, and capacity non-zero, what's gonna happen
	sliceB := make([]int, 0, 5)
	fmt.Println(sliceB)

}

func main() {
	// slices()
	// appendToSubslice()
	// evenMoreConfusingSlices()
	// fullSliceExpression()
	// copySlice()
	// convertSliceToArray()
	whyIStillDontUnderstandSlice()
}
