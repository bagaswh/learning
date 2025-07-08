package main

import "fmt"

func UpdateSlice(s []string, str string) {
	str = s[len(s)-1]
}

func GrowSlice(s []string, str string) []string {
	s = append(s, str)
	return s
}

func main() {
	s1 := []string{"a", "b", "c"}
	str := "hamlo"
	fmt.Println("before UpdateSlice", s1, str)
	UpdateSlice(s1, str)
	fmt.Println("after UpdateSlice", s1, str)

	fmt.Println("before GrowSlice", s1, str)
	s1 = GrowSlice(s1, str)
	fmt.Println("after GrowSlice", s1, str)
}
