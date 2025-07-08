package main

import "fmt"

func main() {
	var i int = 20
	// btw, this does not work since im assigning a int type to float variable
	// var f float64 = i
	// but, this works since it's an untyped literal and it will choose the type that the variable holds into
	var f float64 = 20

	// but anyway, here's the solution
	var fCorrect float64 = float64(i)

	fmt.Printf("%d\t%f\t%f\n", i, f, fCorrect)
}
