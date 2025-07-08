package main

import (
	"fmt"
	"math"
)

func main() {
	for x := 0; x < 8; x++ {
		fmt.Printf("x = %d eA = %8.3f\n", x, math.Exp(float64(x)))
	}

	const Avogadro = 6.02214129e23
	const Planck = 6.62606957e-34
	fmt.Printf("%g %f\n", Avogadro, Avogadro)

	const longDecimals = math.MaxFloat64
	fmt.Printf("%g\n", longDecimals)

	fmt.Printf("%g %[1]f %[1]e", 3.8912347382912813987)
}
