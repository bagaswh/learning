package main

import (
	"fmt"
)

func deadlock() {
	ch1 := make(chan int)
	ch2 := make(chan int)
	go func() {
		inGoroutine := 1
		// goroutine blocks until someone reads from ch1
		ch1 <- inGoroutine
		fromMain := <-ch2
		fmt.Println("goroutine:", inGoroutine, fromMain)
	}()
	inMain := 2
	// goroutine blocks until someone reads from ch2
	ch2 <- inMain
	fromGoroutine := <-ch1
	fmt.Println("main:", inMain, fromGoroutine)
}

func solutionReorder() {
	ch1 := make(chan int)
	ch2 := make(chan int)
	go func() {
		inGoroutine := 1
		// goroutine blocks until someone reads from ch1
		fromMain := <-ch2
		ch1 <- inGoroutine
		fmt.Println("goroutine:", inGoroutine, fromMain)
	}()
	inMain := 2
	// goroutine blocks until someone reads from ch2
	ch2 <- inMain
	fromGoroutine := <-ch1
	fmt.Println("main:", inMain, fromGoroutine)
}

func solutionSelect() {
	ch1 := make(chan int)
	ch2 := make(chan int)
	go func() {
		inGoroutine := 1
		ch1 <- inGoroutine
		println("goroutine has written to ch1")
		fromMain := <-ch2
		fmt.Println("goroutine:", inGoroutine, fromMain)
	}()
	inMain := 2
	var fromGoroutine int
	select {
	case ch2 <- inMain:
	case fromGoroutine = <-ch1:
		println("main:", inMain, fromGoroutine)
	}
}
func main() {
	// deadlock()
	// solutionReorder()
	solutionSelect()
}

/*
	But as you can see, when the goroutine is blocked on ch1, the main goroutine is also blocked on ch2.
	Then deadlock occurs.

	One of the solutions is to reorder the fromMain := <-ch2 to before ch1 <- inGoroutine.
	The other solution is to use select statement to wait for the channel to be read.
*/
