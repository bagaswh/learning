package main

import (
	"context"
	"time"
)

func countTo(ctx context.Context, max int) <-chan int {
	c := make(chan int)
	go func() {
		defer close(c)
		for i := 1; i <= max; i++ {
			select {
			case <-ctx.Done():
				println("goroutine", i, "canceled")
			case c <- i:
				println("goroutine", i)
			default:
				println("goroutine", i, "blocked")
			}
		}
	}()
	return c
}

func main() {
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()
	for i := range countTo(ctx, 10) {
		if i > 5 {
			break
		}
		println(i)
	}
	time.Sleep(10 * time.Second)
}
