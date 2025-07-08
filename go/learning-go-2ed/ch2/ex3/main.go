package main

import "fmt"

func main() {
	var b byte = 255
	var smallI int32 = 2147483647
	var bigI uint64 = 18_446_744_073_709_551_615
	fmt.Println(b, smallI, bigI)
	// overflows!
	fmt.Println(b+1, smallI+1, bigI+1)
	//
	// however, these won't even compile
	// are they calculated at compile time?
	// i wonder which part of the go compiler that does this calculation
	// var bE byte = 255 + 1
	// var smallIE int32 = 2147483647 + 1
	// var bigIE uint64 = 18_446_744_073_709_551_615 + 1
}
