package main

import "testing"

var appendOps []int = []int{10, 1, 1, 1, 1, 50, 25, 100}

func BenchmarkAppendInt(b *testing.B) {
	lastInt := 0
	for i := 0; i < b.N; i++ {
		for op := range appendOps {
			slice1 := make([]int, op, op)
			for j := 1; j <= op; j++ {
				slice1[j-1] = j + lastInt
			}
			_ = appendInt([]int{}, slice1...)
			lastInt += op
		}
	}
}
