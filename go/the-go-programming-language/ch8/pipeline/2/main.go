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
			// spin loop after naturals is closed because it will receive a never-ending stream of zeroes
			x := <-naturals
			squares <- x * x
		}
	}()

	for {
		fmt.Println(<-squares)
	}
}
