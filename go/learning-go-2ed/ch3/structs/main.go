package main

import "fmt"

func structComparisons() {
	// structs can be defined in any blocks

	// same struct type
	type person struct {
		name string
		age  int
	}
	p1 := person{"John", 20}
	p2 := person{"John", 20}
	p3 := person{"Obamna", 65}
	// p1 == p2 is true
	// p1 == p3 is false
	fmt.Println(p1 == p2, p1 == p3)

	// different struct type
	type person2 struct {
		name string
		age  int
	}
	p2_1 := person2{"John", 20}
	p2_2 := person2{"Obamna", 65}
	// not possible because the struct type is different
	// fmt.Println(p1 == p2_1)
	// you need to convert the type so that the structs are the same
	fmt.Println(p1 == person(p2_1)) // true
	fmt.Println(p2 == person(p2_2)) // false

	// anonymous struct does not require type conversion to be compared
	panon_3 := struct {
		name string
		age  int
	}{"John", 20}
	fmt.Println(p1 == panon_3) // true

	// in any other case, you cannot convert two structs...
}

func main() {
	structComparisons()
}
