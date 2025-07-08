package main

import (
	"fmt"
)

func sliceFromThings() {
	arr1 := [...]string{1: "January", 2: "February", 3: "March", 4: "April", 5: "May", 6: "June", 7: "July", 8: "August", 9: "September", 10: "October", 11: "November", 12: "December"}
	fmt.Println("arr1", arr1, len(arr1))

	// slice operator s[i:j], where 0<=i<=j<=cap(s) can refer to either array, pointer of array, or another slice
	// the resulting slice has j-i elements
	// this means that the j is exclusive, i is inclusive
	sliceArr1 := arr1[2:8]
	pointerArr1 := &arr1
	slicePointerArr1 := pointerArr1[5:6]
	sliceSliceArr1 := sliceArr1[1:3]

	fmt.Println(sliceArr1, cap(sliceArr1))
	fmt.Println(pointerArr1)
	fmt.Println(slicePointerArr1)
	fmt.Println(sliceSliceArr1, cap(slicePointerArr1))
}

func reverse(s []int) {
	for i, j := 0, len(s)-1; i < j; i, j = i+1, j-1 {
		s[i], s[j] = s[j], s[i]
	}
}

func rotate(s []int, n int) {
	reverse(s[:n])
	fmt.Println(s)
	reverse(s[n:])
	fmt.Println(s)
	reverse(s)
	fmt.Println(s)
}

func sliceAsMapKey() {
	// trying to understand page 86 to 87 of The Go Programming Language book

	// this is not possible
	// slice is not comparable, thus cannot be used as a map key
	// m := make(map[[]int]string)

	// this, however, is possible since array is comparable
	// thus, we can use it as a map key
	// m := make(map[[1]int]string)
}

func main() {
	// sliceFromThings()
	rotate([]int{1, 2, 3, 4}, 2)
}
