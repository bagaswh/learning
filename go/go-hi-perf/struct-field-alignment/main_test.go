package main

import (
	"sync"
	"testing"
)

/* BEGIN alignment */

type PoorlyAligned struct {
	flag  bool
	count int64
	id    byte
}

type WellAligned struct {
	count int64
	flag  bool
	id    byte
}

/*
	▶ go test -v -bench=. -benchmem ./struct-field-alignment/*.go
	goos: linux
	goarch: amd64
	cpu: 13th Gen Intel(R) Core(TM) i5-13500
	BenchmarkPoorlyAligned
	BenchmarkPoorlyAligned-20             33          34315760 ns/op        240001674 B/op         1 allocs/op
	BenchmarkWellAligned
	BenchmarkWellAligned-20               54          20924682 ns/op        160006146 B/op         1 allocs/op
	PASS
	ok      command-line-arguments  2.274s
*/

/*
	Why is it slower? Higher B/op is definitely expected with poorly aligned struct. But why is it also slower?

	Could be due to zeroing cost. Zeroing 24 bytes takes longer than 16 bytes.

	But this is the insights of ChatGPT. Take it with a grain of salt.

	# Larger footprint → fewer elements per cache line
	On your 64-byte cache lines, a 16-byte struct fits exactly 4 elements.
	A 24-byte struct only fits 2 elements (with 16 bytes unused). That means:

	- More cache lines must be loaded to touch the same number of elements.

	- Your inner loop (items[j].count = ...) thrashes more cache lines, increasing L1/L2 miss rates.

	- TLB (translation lookaside buffer) pressure goes up because you cover more pages for the same count.

	# Zeroing overhead vs. streaming stores
	Go’s make([]T, N) zeroes the backing memory, and zeroing 240 MB (10 M × 24 bytes)
	indeed takes longer than 160 MB (10 M × 16 bytes).
	But once zeroed, your hot loop is doing a streaming write to each element’s count field.
	The CPU can overlap zeroing (during allocation) and your writes,
	plus use wide stores—so the relative penalty of the extra zeroing is usually
	much smaller than the cache‐miss penalty.

	# Struct alignment and write‐combine buffers
	Misaligned or sparsely packed fields can’t always use the CPU’s write‐combine
	buffers as efficiently. Well-packed data lets the CPU coalesce writes into
	fewer large memory transactions, whereas poorly packed data can lead to more, smaller transactions.

*/

func BenchmarkPoorlyAligned(b *testing.B) {
	for b.Loop() {
		var items = make([]PoorlyAligned, 10_000_000)
		for j := range items {
			items[j].count = int64(j)
		}
	}
}

func BenchmarkWellAligned(b *testing.B) {
	for b.Loop() {
		var items = make([]WellAligned, 10_000_000)
		for j := range items {
			items[j].count = int64(j)
		}
	}
}

/* END alignment */

// --------------------

/* BEGIN false sharing */

/*

	In addition to memory layout efficiency, struct alignment also plays a crucial role in concurrent systems.
	When multiple goroutines access different fields of the same struct that reside on the same CPU cache line,
	they may suffer from false sharing—where changes to one field cause invalidations in the other,
	even if logically unrelated.

	On modern CPUs, a typical cache line is 64 bytes wide. When a struct is accessed in memory,
	the CPU loads the entire cache line that contains it, not just the specific field.
	This means that two unrelated fields within the same 64-byte block will both reside
	in the same line—even if they are used independently by separate goroutines.
	If one goroutine writes to its field, the cache line becomes invalidated and must
	be reloaded on the other core, leading to degraded performance due to false sharing.

*/

type SharedCounterBad struct {
	a int64
	b int64
}

type SharedCounterGood struct {
	a int64
	_ [56]byte // Padding to prevent a and b from sharing a cache line
	b int64
}

func BenchmarkFalseSharing(b *testing.B) {
	var c SharedCounterBad // (1)
	var wg sync.WaitGroup

	for b.Loop() {
		wg.Add(2)
		go func() {
			for i := 0; i < 1_000_000; i++ {
				c.a++
			}
			wg.Done()
		}()
		go func() {
			for i := 0; i < 1_000_000; i++ {
				c.b++
			}
			wg.Done()
		}()
		wg.Wait()
	}
}

func BenchmarkNoFalseSharing(b *testing.B) {
	var c SharedCounterGood
	var wg sync.WaitGroup

	for b.Loop() {
		wg.Add(2)
		go func() {
			for i := 0; i < 1_000_000; i++ {
				c.a++
			}
			wg.Done()
		}()
		go func() {
			for i := 0; i < 1_000_000; i++ {
				c.b++
			}
			wg.Done()
		}()
		wg.Wait()
	}
}

/* END false sharing */
