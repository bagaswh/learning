package main

import (
	"fmt"
	"time"
)

func main() {
	naturals := make(chan int)
	squares := make(chan int)

	go func() {
		defer close(naturals)
		for i := 0; i <= 10; i++ {
			naturals <- i
			i++
			time.Sleep(time.Millisecond * 376)
		}
	}()

	go func() {
		defer close(squares)
		for x := range naturals {
			squares <- x * x
		}
	}()

	for sq := range squares {
		fmt.Println(sq)
	}
}
