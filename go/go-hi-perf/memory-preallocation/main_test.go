package main

import (
	"testing"
)

// func BenchmarkAppendWithoutPreallocation(b *testing.B) {
// 	for b.Loop() {
// 		var s []int
// 		for i := 0; i < 1000000; i++ {
// 			s = append(s, i)
// 		}
// 	}
// }

func BenchmarkAppendWithPreallocation(b *testing.B) {
	c := 1000000
	var s []int = make([]int, 0, c)
	b.ResetTimer()
	for b.Loop() {
		s = s[:0]
		for i := 0; i < c; i++ {
			s = append(s, i)
			// fmt.Println(cap(s))
		}
	}
}

func BenchmarkAppendWithPreallocationNoBoundChecks(b *testing.B) {
	c := 1000000
	var s []int = make([]int, c)
	b.ResetTimer()
	for b.Loop() {
		for i := 0; i < c; i++ {
			s[i] = i
		}
	}
}
