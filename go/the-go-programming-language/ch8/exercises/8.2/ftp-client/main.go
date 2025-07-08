package main

import (
	"bufio"
	"flag"
	"fmt"
	"net"
	"os"
	"os/exec"
	"strings"
)

var host = flag.String("h", "", "host")
var port = flag.String("p", "", "port")

type state struct {
	currentDirectory    string
	previousCommand     string
	previousCommandArgs string
}

func main() {
	flag.Parse()

	fmt.Println(os.Getpid())

	c, err := net.Dial("tcp", *host+":"+*port)
	if err != nil {
		panic(err)
	}

	cReader := bufio.NewScanner(c)
	cWriter := bufio.NewWriter(c)
	stdinReader := bufio.NewScanner(os.Stdin)

	state := state{
		currentDirectory:    "",
		previousCommand:     "",
		previousCommandArgs: "",
	}

	go func() {
		for cReader.Scan() {
			msg := cReader.Text()
			if strings.HasPrefix(msg, "e:") {
				printError(msg[2:])
			} else if strings.HasPrefix(msg, "d:") {
				state.currentDirectory = msg[2:]
			} else {
				if state.previousCommand == "ls" {
					msg = strings.ReplaceAll(msg, " ", "\n") + "\n"
				}
				printCommandOutput(msg[2:] + "\n")
			}
			printPrompt(&state)
		}
		err := cReader.Err()
		if err != nil {
			printError(
				fmt.Sprintf("connection to server err: %v\n", err),
			)
		}
	}()

	for stdinReader.Scan() {
		input := stdinReader.Text()
		splits := strings.Split(input, " ")
		if len(splits) == 0 {
			continue
		}
		cmd := splits[0]
		switch cmd {
		case "clear":
			clearTerminal()
			printPrompt(&state)
		default:
			state.previousCommand = cmd
			state.previousCommandArgs = cmd[1:]
			sendToServer(cWriter, input)
		}
	}

	err = stdinReader.Err()
	if err != nil {
		panic(err)
	}
}

func sendToServer(writer *bufio.Writer, msg string) {
	_, err := writer.WriteString(msg + "\n")
	if err != nil {
		printError(fmt.Sprintf("cannot send to server: %v", err))
		return
	}
	if writer.Buffered() > 0 {
		err := writer.Flush()
		if err != nil {
			printError(fmt.Sprintf("cannot send to server: %v", err))
		}
	}
}

func printError(line string) {
	fmt.Printf("ERR: %s\n", line)
}

func printPrompt(state *state) {
	fmt.Printf("%s > ", state.currentDirectory)
}

func printCommandOutput(output string) {
	fmt.Printf("%s", output)
}

func clearTerminal() {
	cmd := exec.Command("clear")
	cmd.Stdout = os.Stdout
	cmd.Run()
}
