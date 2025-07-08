package main

import "testing"

func Benchmark_preallocatedAndPredeclared(b *testing.B) {
	preallocatedAndPredeclared()
}

func Benchmark_predeclared(b *testing.B) {
	predeclared()
}
