package main

import (
	"fmt"
	"time"
)

func main() {
	naturals := make(chan int)
	squares := make(chan int)

	go counter(naturals)
	go square(naturals, squares)

	print(squares)
}

func counter(out chan<- int) {
	for i := 0; i <= 10; i++ {
		out <- i
		i++
		time.Sleep(time.Millisecond * 376)
	}
	// Since the close operation asserts that no more sends will occur on a channel, only the sending goroutine is in a position to call it,
	// and for this reason it is a compile time error to attempt to close a receive-only channel.
	close(out)
	fmt.Println("counter done")
}

func square(in <-chan int, out chan<- int) {
	for x := range in {
		out <- x * x
	}
	close(out)
	// compile-time error
	// close(in)
	fmt.Println("square done")
}

func print(in <-chan int) {
	for v := range in {
		fmt.Println(v)
	}
	fmt.Println("print done")
}
