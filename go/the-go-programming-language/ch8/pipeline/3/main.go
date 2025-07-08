package main

import (
	"fmt"
	"time"
)

func main() {
	naturals := make(chan int)
	squares := make(chan int)

	go func() {
		for i := 0; i <= 10; i++ {
			naturals <- i
			i++
			time.Sleep(time.Millisecond * 376)
		}
		close(naturals)
	}()

	go func() {
		for {
			x, ok := <-naturals
			if !ok {
				break
			}
			squares <- x * x
		}
		close(squares)
	}()

	for {
		// spin loop after squares is closed because it will receive a never-ending stream of zeroes
		fmt.Println(<-squares)
	}
}
