package main

import "flag"

type Person struct {
	FirstName, LastName string
	Age                 int
}

func preallocatedAndPredeclared() {
	firstName := "Bagong"
	lastName := "Suaka"
	age := 29

	n := 10_000_000
	persons := make([]Person, 0, n)
	for range n {
		persons = append(persons, Person{
			FirstName: firstName,
			LastName:  lastName,
			Age:       age,
		})
	}
	_ = persons
}

func predeclared() {
	firstName := "Bagong"
	lastName := "Suaka"
	age := 29

	n := 10_000_000
	persons := make([]Person, 0)
	for range n {
		persons = append(persons, Person{
			FirstName: firstName,
			LastName:  lastName,
			Age:       age,
		})
	}
	_ = persons
}

var mode = flag.String("mode", "predeclared", "the mode")

func init() {
	flag.Parse()
}

func main() {
	r := [500_000]byte{}
	_ = r

	if *mode == "predeclared" {
		predeclared()
	} else {
		preallocatedAndPredeclared()
	}

}

/*
=== My notes ===

With "predeclared":

 $ GODEBUG=gctrace=1 ./ch6/exercises/ex3/main -mode predeclared
gc 1 @0.003s 2%: 0.035+2.2+0.006 ms clock, 0.70+0/2.6/0.31+0.13 ms cpu, 4->4->1 MB, 4 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 2 @0.007s 3%: 0.018+3.9+0.009 ms clock, 0.37+0/4.7/0+0.19 ms cpu, 5->5->2 MB, 5 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 3 @0.012s 4%: 0.19+7.0+0.006 ms clock, 3.8+0/7.5/0+0.12 ms cpu, 7->7->3 MB, 7 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 4 @0.021s 4%: 0.015+3.8+0.006 ms clock, 0.30+0/4.0/0+0.12 ms cpu, 6->6->3 MB, 6 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 5 @0.025s 4%: 0.020+3.4+0.003 ms clock, 0.40+0/3.5/0.65+0.062 ms cpu, 8->8->4 MB, 8 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 6 @0.030s 4%: 0.013+2.3+0.005 ms clock, 0.26+0/3.4/0.058+0.10 ms cpu, 10->10->5 MB, 10 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 7 @0.033s 5%: 0.065+8.4+0.004 ms clock, 1.3+0/9.6/0.26+0.091 ms cpu, 12->12->7 MB, 12 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 8 @0.042s 5%: 0.013+4.2+0.003 ms clock, 0.27+0/5.3/0.006+0.068 ms cpu, 15->15->8 MB, 15 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 9 @0.048s 5%: 0.012+10+0.005 ms clock, 0.25+0/10/0+0.10 ms cpu, 19->19->11 MB, 19 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 10 @0.058s 5%: 0.020+11+0.006 ms clock, 0.40+1.7/13/0.005+0.13 ms cpu, 24->24->13 MB, 24 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 11 @0.072s 5%: 0.049+6.5+0.005 ms clock, 0.98+1.0/8.8/0+0.10 ms cpu, 30->30->17 MB, 30 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 12 @0.082s 5%: 0.023+12+0.009 ms clock, 0.46+0/12/0+0.19 ms cpu, 38->38->21 MB, 38 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 13 @0.094s 5%: 0.010+23+0.006 ms clock, 0.20+0/23/0.002+0.13 ms cpu, 47->47->26 MB, 47 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 14 @0.122s 5%: 0.019+23+0.003 ms clock, 0.39+0/23/0+0.066 ms cpu, 59->59->33 MB, 59 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 15 @0.149s 5%: 0.019+16+0.004 ms clock, 0.38+0.026/23/1.0+0.096 ms cpu, 74->74->41 MB, 74 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 16 @0.166s 5%: 0.008+36+0.008 ms clock, 0.16+0.008/50/0+0.17 ms cpu, 93->93->51 MB, 93 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 17 @0.205s 5%: 0.019+30+0.005 ms clock, 0.38+0/37/0+0.11 ms cpu, 116->116->64 MB, 116 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 18 @0.243s 5%: 0.013+29+0.005 ms clock, 0.26+4.8/49/4.9+0.11 ms cpu, 145->145->81 MB, 145 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 19 @0.273s 5%: 0.011+70+0.005 ms clock, 0.23+0/87/1.6+0.10 ms cpu, 182->182->101 MB, 182 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 20 @0.347s 6%: 0.007+134+7.5 ms clock, 0.15+5.1/66/5.5+150 ms cpu, 227->385->284 MB, 227 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 21 @0.564s 5%: 0.019+158+0.004 ms clock, 0.38+8.0/190/99+0.099 ms cpu, 728->728->247 MB, 728 MB goal, 0 MB stacks, 0 MB globals, 20 P
gc 22 @0.732s 6%: 0.014+105+0.044 ms clock, 0.28+0/193/129+0.88 ms cpu, 555->555->555 MB, 555 MB goal, 0 MB stacks, 0 MB globals, 20 P

With "preallocatedAndPredeclared":

$ GODEBUG=gctrace=1 ./ch6/exercises/ex3/main -mode aa
gc 1 @0.001s 7%: 0.067+207+2.6 ms clock, 1.3+0/249/119+52 ms cpu, 381->382->381 MB, 382 MB goal, 0 MB stacks, 0 MB globals, 20 P

So, reduce the stress on the GC by slowing down the allocation on the heap.

https://www.ardanlabs.com/blog/2019/05/garbage-collection-in-go-part2-gctraces.html#:~:text=As%20I%20stated,down%20your%20application

*/
