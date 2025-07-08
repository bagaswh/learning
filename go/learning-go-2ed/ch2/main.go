package main

import (
	"fmt"
	"reflect"
	"runtime"
	"time"
)

func literals() {
	// integers
	base10 := 10
	base16 := 0x10
	base2 := 0b10
	base8 := 0o10
	// do not use this
	base8DoNotUse := 010
	fmt.Println(base10, base16, base2, base8, base8DoNotUse)

	// underscores in numbers
	base10Underscores := 10_000
	base16Underscores := 0x10_000
	base2Underscores := 0b10_000
	base8Underscores := 0o10_000
	posixPermissions := 0o755
	fmt.Println(base10Underscores, base16Underscores, base2Underscores, base8Underscores, posixPermissions)

	// floats
	floatWithExponent := 3.14e+2
	floatWithNegativeExponent := 3.14e-2
	floatHexadecimal := 0x12.34p5
	floatWithunderScore := 3.14_15
	fmt.Println(floatWithExponent, floatWithNegativeExponent, floatHexadecimal, floatWithunderScore)

	// runes
	rune1 := 'a'
	rune2 := '🐶'
	runeOctal := '\141'
	rune8BitHexadecimal := '\x61'
	rune16BitHexadecimal := '\u0061'
	rune32BitHexadecimal := '\U00000061'
	fmt.Println(rune1, rune2, runeOctal, rune8BitHexadecimal, rune16BitHexadecimal, rune32BitHexadecimal)

	// strings
	interpretedString := "Hello,\nWorld\tFrom\n\"Go\"\\The best language of all time"
	rawString := `Hello,
World	From
"Go"\The best language of all time`
	fmt.Println(interpretedString, rawString)

}

func numericTypes() {
	// division
	divInt := 10 / 3                     // will result in int
	divWrappedInFloat := float64(10 / 3) // this will not preserve digits after the decimal point
	divFloat := float64(10) / float64(3) // this, will preserve digits after the decimal point
	divFloatInt := 10 / 3.0
	fmt.Printf("divInt: %d\ndivWrappedInFloat: %f\ndivFloat: %f\ndivFloatInt: %f\n", divInt, divWrappedInFloat, divFloat, divFloatInt)

	// // floats
	// positiveInfinity := 1.0 / 0
	// negativeInfinity := -1.0 / 0
	// nan := 0.0 / 0
	// fmt.Println(positiveInfinity, negativeInfinity, nan)
}

func acceptsNumeric(v any) {

}

// constants are calculated at compile time
const c_pi float64 = 3.14

var pi = 3.14

//	unused constants do not throw compile errors
//
// they are simply not included in the binary
var unusedConst = 10

func main() {
	fmt.Println(reflect.TypeOf(c_pi))

	// literals()
	// numericTypes()

	// some humongous numbers
	// apparently it's a compile-time error to have a number that is too big for any integer type to hold
	// even with untyped literal
	acceptsNumeric(int64(8911812010109288381))

	// it's idiomatic to write var x byte instead of x := byte(0)
	var x byte = 0
	acceptsNumeric(x)

	// sl1 := make([]int, 0, 11)
	// const sl1Cap = cap(sl1)

	// unused variables
	xU := 10
	xU = 20
	// as long as the variable is read once,
	fmt.Println(xU)
	// then this is fine, compiles just fine even there's another assignment
	xU = 100

	// _⠀ := 10

	for {
		var m runtime.MemStats
		runtime.ReadMemStats(&m)
		// For info on each, see: https://golang.org/pkg/runtime/#MemStats
		fmt.Printf("Alloc = %v MiB", bToMb(m.Alloc))
		fmt.Printf("\tTotalAlloc = %v MiB", bToMb(m.TotalAlloc))
		fmt.Printf("\tSys = %v MiB", bToMb(m.Sys))
		fmt.Printf("\tNumGC = %v\n", m.NumGC)

		time.Sleep(1 * time.Second)
	}
}

func bToMb(b uint64) uint64 {
	return b / 1024 / 1024
}
