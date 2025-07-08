package main

import (
	"flag"
	"io"
	"log"
	"net"
	"os"
)

var (
	TZ   = flag.String("tz", "Asia/Jakarta", "The timezone")
	port = flag.String("port", "8080", "The port")
)

func init() {
	flag.Parse()
}

func main() {
	if *TZ == "" {
		*TZ = "Asia/Jakarta"
	}

	if *port == "" {
		log.Fatalln("-port is not set")
	}

	conn, err := net.Dial("tcp", "localhost:"+*port)
	if err != nil {
		log.Fatalln(err)
	}
	defer conn.Close()
	conn.Write([]byte("SET_TZ=" + *TZ + "\n"))

	mustCopy(os.Stdout, conn)
}

func mustCopy(dst io.Writer, src io.Reader) {
	_, err := io.Copy(dst, src)
	if err != nil {
		log.Fatalln(err)
	}
}
