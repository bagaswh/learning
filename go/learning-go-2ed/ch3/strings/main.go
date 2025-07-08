package main

import (
	"fmt"
)

func endianness() {
	// var c int = 1

}

func theByte() {
	var c byte = 'a'
	// same result
	fmt.Println(c == 97, c == 'a')

	// string slicing
	// var s string = "🌎"

	// the braille character '⡡' has this binary representation
	// var cL int32 = 0b00000000_0000000_0101000_01100001
	// the 🌎 has this binary representation
	var earth int32 = 0b00000001_11110011_00001110
	brailleC := "🌎"
	for c := range brailleC {
		fmt.Println(rune(c))
	}
	fmt.Println([]byte(brailleC[:]))
	// []byte(string) will convert to UTF-8 bytes
	fmt.Println([]byte(string(earth)))
	// []rune(string) will convert to runes which can be as long as 4 bytes
	fmt.Println([]byte(string(earth)))

	// var s string = "Hello 🌎"
	// var s2 string = s[4:7]
	// var s3 string = s[:5]
	// var s4 string = s[6:]
	// theWorldEmojiSum := sumBytes([]byte(s4))
	// fmt.Println(s2, s3, theWorldEmojiSum)

}

func runes() {
	// runes
	var s string = "Hello, 🌎"
	var bs []byte = []byte(s)
	var rs []rune = []rune(s)
	fmt.Println(bs)
	fmt.Println(rs)
}

func sumBytes(b []byte) int {
	sum := 0
	for _, v := range b {
		sum += int(v)
	}
	return sum
}

func main() {
	theByte()
	// runes()
}
