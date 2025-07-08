package main

import (
	"crypto/sha256"
	"fmt"
)

func main() {
	a := sha256.Sum256([]byte("xZZ"))
	b := sha256.Sum256([]byte("ytZZzz"))
	fmt.Println(diffCount(a, b))
}

func diffCount(a, b [32]byte) (int, []int) {
	diffs := make([]int, 0, 0)
	for i, aEl := range a {
		if aEl != b[i] {
			diffs = append(diffs, i)
		}
	}
	return len(diffs), diffs
}
