package main

import (
	"crypto/sha256"
	"crypto/sha512"
	"flag"
	"fmt"
	"io"
	"log"
	"os"
)

var algo = flag.String("algo", "sha256", "hash algorithm")

func init() {
	flag.Parse()
}

func main() {
	buf := make([]byte, 0, 1024)
	n, err := os.Stdin.Read(buf[len(buf):cap(buf)])
	buf = buf[:len(buf)+n]
	if err != nil && err != io.EOF {
		panic(err)
	}
	if len(buf) == 0 {
		log.Fatalln("empty input")
	}
	switch *algo {
	case "sha256":
		digest := sha256.Sum256(buf)
		fmt.Printf("%x\n", digest)
	case "sha512":
		digest := sha512.Sum512(buf)
		fmt.Printf("%x\n", digest)
	case "sha384":
		digest := sha512.Sum384(buf)
		fmt.Printf("%x\n", digest)
	default:
		panic("unknown algorithm")
	}
}
