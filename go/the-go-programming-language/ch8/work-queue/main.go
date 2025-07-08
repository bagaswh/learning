package main

import (
	"fmt"
	"time"
)

func main() {
	queue := make(chan string, 10)
	done := make(chan struct{})

	go receiveWork(queue)
	go routeWork(queue, done)

	<-done
}

func receiveWork(out chan<- string) {
	works := []string{"small", "medium", "large"}
	for _, work := range works {
		out <- work
		time.Sleep(time.Millisecond * 100)
	}
	close(out)
}

func routeWork(in <-chan string, out chan<- struct{}) {
	for {
		work, ok := <-in
		if !ok {
			break
		}
		switch work {
		case "small":
			smallWork()
		case "medium":
			mediumWork()
		case "large":
			largeWork()
		}
	}
	out <- struct{}{}
}

func smallWork() {
	fmt.Println("doing small work")
	time.Sleep(time.Millisecond * 444)
	fmt.Println("im done doing smal work")
}
func mediumWork() {
	fmt.Println("doing medium work")
	time.Sleep(time.Millisecond * 2444)
	fmt.Println("im done doing medim work")
}
func largeWork() {
	fmt.Println("doing large work")
	time.Sleep(time.Millisecond * 4444)
	fmt.Println("im done doing large work")
}
