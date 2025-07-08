package main

import (
	"io"
	"os"
	"testing"

	"golang.org/x/exp/mmap"
)

/* BEGIN mmap */

func BenchmarkReadWithCopy(b *testing.B) {
	f, err := os.Open("testdata/file.bin")
	if err != nil {
		b.Fatalf("failed to open file: %v", err)
	}
	defer f.Close()

	fStat, fStatErr := f.Stat()
	if fStatErr != nil {
		b.Fatalf("failed to stat file: %v", fStatErr)
	}

	buf := make([]byte, fStat.Size())
	for b.Loop() {
		_, err := f.ReadAt(buf, 0)
		if err != nil && err != io.EOF {
			b.Fatal(err)
		}
	}
}

func BenchmarkReadWithMmap(b *testing.B) {
	r, err := mmap.Open("testdata/file.bin")
	if err != nil {
		b.Fatalf("failed to mmap file: %v", err)
	}
	defer r.Close()

	buf := make([]byte, r.Len())
	for b.Loop() {
		_, err := r.ReadAt(buf, 0)
		if err != nil && err != io.EOF {
			b.Fatal(err)
		}
	}
}

/* END mmap */

// ------------------------

/* BEGIN copy vs slicing */

func BenchmarkCopy(b *testing.B) {
	data := make([]byte, 64*1024)
	for b.Loop() {
		buf := make([]byte, len(data))
		copy(buf, data)
	}
}

func BenchmarkSlice(b *testing.B) {
	data := make([]byte, 64*1024)
	for b.Loop() {
		_ = data[:]
	}
}
