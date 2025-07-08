package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

func main() {
	filenames := 10
	sizes := make(chan int64)
	var wg sync.WaitGroup
	for range filenames {
		wg.Add(1)
		go func() {
			defer wg.Done()
			time.Sleep(250 * time.Millisecond)
			sizes <- rand.Int63n(5000)
		}()
	}
	// it has to be concurrent
	// otherwise, wg.Wait() will never finish because no one is consuming sizes channel
	// unless we make the channel buffered with as much capacity as filenames
	go func() {
		wg.Wait()
		close(sizes)
	}()
	var total int64
	for size := range sizes {
		total += size
	}
	fmt.Println(total)
}
