package main

import "fmt"

// remember that constants are just giving name to literals
// this means we can assign this untyped constant to any variable type that supports the value
// we can assign this to int and float64, at the very least
const value = 10

var vi int = value
var vf float64 = value

func main() {
	fmt.Println(vi, vf)
}
