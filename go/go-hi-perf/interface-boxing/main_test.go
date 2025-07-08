package perf

import "testing"

/*
# How to Avoid Interface Boxing

	- Use pointers when assigning to interfaces.
	  If the method set requires a pointer receiver or the value is large,
	  explicitly pass a pointer to avoid repeated copying and heap allocation.

	  	```go
		for i := range tasks {
			result = append(result, &tasks[i]) // Avoids boxing copies
		}
		```

	- Avoid interfaces in hot paths. If the concrete type is known and stable,

	- Avoid interface indirection entirely—especially in compute-intensive or allocation-sensitive functions.

	- Use type-specific containers. Instead of []interface{},
	  prefer generic slices or typed collections where feasible.
   	  This preserves static typing and reduces unnecessary allocations.

	- Benchmark and inspect with pprof.
	  Use go test -bench and pprof to observe where allocations occur. If the allocation site is in runtime.convT2E (convert T to interface), you're likely boxing.

*/

// interface-start

type Worker interface {
	Work()
}

type LargeJob struct {
	payload [4096]byte
}

func (LargeJob) Work() {}

// interface-end

// bench-slice-start
func BenchmarkBoxedLargeSlice(b *testing.B) {
	jobs := make([]Worker, 0, 1000)
	for b.Loop() {
		jobs = jobs[:0]
		for j := 0; j < 1000; j++ {
			var job LargeJob
			jobs = append(jobs, job)
		}
	}
}

func BenchmarkPointerLargeSlice(b *testing.B) {
	jobs := make([]Worker, 0, 1000)
	for b.Loop() {
		jobs := jobs[:0]
		for j := 0; j < 1000; j++ {
			job := &LargeJob{}
			jobs = append(jobs, job)
		}
	}
}

// bench-slice-end

// bench-call-start
var sink Worker

func call(w Worker) {
	sink = w
}

func BenchmarkCallWithValue(b *testing.B) {
	for b.Loop() {
		var j LargeJob
		call(j)
	}
}

func BenchmarkCallWithPointer(b *testing.B) {
	for b.Loop() {
		j := &LargeJob{}
		call(j)
	}
}

// bench-call-end
