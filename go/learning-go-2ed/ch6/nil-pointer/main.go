package main

import "fmt"

func failedUpdate(g *int) {
	x := 10
	// this does not change the pointer to reference x, no it does not
	// you have to dereference the pointer if you want to change what g holds
	g = &x
}

func main() {
	var f *int
	failedUpdate(f)
	fmt.Println(f)
}
