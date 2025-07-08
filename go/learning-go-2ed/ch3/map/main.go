package main

import "fmt"

func theMaps() {
	var nilMap map[string]int
	// it's not possible to write to nilMap. It will cause a panic.
	// nilMap["a"] = 1
	// however, reading the key from map is possible, but the value is always going to be the zero value of the map value type.
	fmt.Println(nilMap["a"])

	// empty map, however, can be written to.
	veryCoolMap := map[string]int{}
	veryCoolMap["a"] = 1
	veryCoolMap["s"] = 1
	veryCoolMap["u"] = 1
	fmt.Println(veryCoolMap["a"])
	fmt.Println(veryCoolMap)

	// here's non-empty map
	myMap := map[string]int{
		"a": 1,
		"s": 1,
		"u": 1,
	}
	fmt.Println(myMap["a"])
	fmt.Println(myMap)
}

func makeMap() {
	ages := make(map[int][]string, 10)
	// maps created with make still have a length of 0, and they can grow past the initial size.
	fmt.Println("len(ages):", len(ages))
}

func main() {
	// theMaps()
	makeMap()
}
