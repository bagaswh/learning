package main

import (
	"fmt"
	"net"
	"time"
)

func main() {
	listener, err := net.Listen("tcp", ":8080")
	if err != nil {
		panic(err)
	}
	defer listener.Close()

	for {
		conn, err := listener.Accept()
		fmt.Println("Accepted connection", conn.RemoteAddr())
		if err != nil {
			panic(err)
		}
		go handleConnection(conn, time.Now())
	}
}

func handleConnection(conn net.Conn, startTime time.Time) {
	defer conn.Close()
	for {
		elapsed := time.Since(startTime)
		_, err := conn.Write([]byte(elapsed.String() + "\n"))
		if err != nil {
			fmt.Println(conn.RemoteAddr(), "error", err)
			return
		}
		time.Sleep(time.Second)
		fmt.Println(conn.RemoteAddr(), "written")
	}
}
