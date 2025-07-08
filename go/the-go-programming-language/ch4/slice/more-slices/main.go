package main

import "fmt"

func remove(slice []int, i int) []int {
	copy(slice[i:], slice[i+1:])
	return slice[:len(slice)-1]
}

func removeUnordered(slice []int, i int) []int {
	slice[i] = slice[len(slice)-1]
	return slice[:len(slice)-1]
}

func main() {
	s := []int{5, 6, 7, 8, 9}
	s2 := make([]int, len(s))
	copy(s2, s)
	fmt.Println(remove(s, 2)) // "[5 6 8 9]"

	fmt.Println(removeUnordered(s2, 2)) // "[5 6 9 8]"
}
