package main

import (
	"fmt"

	"github.com/bagaswh/learning-go-2e/ch3/set"
)

func main() {
	set := set.New[int]()
	set.Add(1)
	set.Add(2)
	set.Add(3)
	set.Add(4)
	set.Add(5)

	set.Iterate(func(v int) {
		fmt.Println(v)
	})
}
