package perf

import (
	"sync"
	"testing"
)

type Data struct {
	// allocate large enough slice to be able to see benefit of pooling
	// otherwise, sync's Get(), Put(), type assertions, and sync.Pool internal bookkeeping overheads
	// might outweight any memory allocation prevention benefit
	Values [65 * 1024]int
}

func BenchmarkWithoutPooling(b *testing.B) {
	for b.Loop() {
		data := &Data{}
		data.Values[0] = 42
	}
}

var dataPool = sync.Pool{
	New: func() any {
		return &Data{}
	},
}

func BenchmarkWithPooling(b *testing.B) {
	for b.Loop() {
		obj := dataPool.Get().(*Data)
		obj.Values[0] = 42
		dataPool.Put(obj)
	}
}
