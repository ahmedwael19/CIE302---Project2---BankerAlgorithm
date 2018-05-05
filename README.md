# CIE302 (Operating Systems)- Project2 - BankerAlgorithm

Implementing  Multithreaded Banker Algorithm - Programming project for chapter 7, Operating Systems Concepts textbook.

This code is fully developed by Ahmed Wael and my colleague Mohamed Elsayed for the operating system class in spring 2018.


## Makefile:
The code can be compiled to produce output and cleaned to remove the output using make

```
$ make
gcc -pthread main.c -o main
$ ./main 2 3 4
$ make clean
rm -f main
```

## Error handling:
Code is capable of handling the input error cases.

```
$ ./main 2 3
usage: a.out <# of src 1> <# of src 2> <# of src 3>
$ ./main 2 4 -3
Argument -3 must be non-negative
```

## How to use
Determine the number of instances in each resource and let the program simulate kernel using banker algorithm.

```
$ ./main 100 100 100


Customer 1 is Requesting Resources:
6 7 8 
Available Resources : 
100 100 100 
The need : 
10 10 10 
The System is Safe 
Resources Granted 

Customer 0 is Requesting Resources:
6 7 8 
Available Resources : 
94 93 92 
The need : 
10 10 10 
The System is Safe 
Resources Granted 

Customer 0 is Requesting Resources:
2 1 1 
Available Resources : 
88 86 84 
The need : 
4 3 2 
The System is Safe 
Resources Granted 

Customer 0 is Requesting Resources:
2 2 1 
Available Resources : 
86 85 83 
The need : 
2 2 1 
The System is Safe 
Resources Granted 
Thread 0 finished execution 

Customer 2 is Requesting Resources:
6 7 8 
Available Resources : 
114 113 112 
The need : 
10 10 10 
The System is Safe 
Resources Granted 

Customer 3 is Requesting Resources:
6 7 8 
Available Resources : 
108 106 104 
The need : 
10 10 10 
The System is Safe 
Resources Granted 

Customer 3 is Requesting Resources:
2 1 1 
Available Resources : 
102 99 96 
The need : 
4 3 2 
The System is Safe 
Resources Granted 

Customer 3 is Requesting Resources:
2 2 1 
Available Resources : 
100 98 95 
The need : 
2 2 1 
The System is Safe 
Resources Granted 
Thread 3 finished execution 

Customer 2 is Requesting Resources:
2 1 1 
Available Resources : 
128 126 124 
The need : 
4 3 2 
The System is Safe 
Resources Granted 

Customer 2 is Requesting Resources:
2 2 1 
Available Resources : 
126 125 123 
The need : 
2 2 1 
The System is Safe 
Resources Granted 
Thread 2 finished execution 

Customer 4 is Requesting Resources:
6 7 8 
Available Resources : 
154 153 152 
The need : 
10 10 10 
The System is Safe 
Resources Granted 

Customer 4 is Requesting Resources:
2 1 1 
Available Resources : 
148 146 144 
The need : 
4 3 2 
The System is Safe 
Resources Granted 

Customer 4 is Requesting Resources:
2 2 1 
Available Resources : 
146 145 143 
The need : 
2 2 1 
The System is Safe 
Resources Granted 
Thread 4 finished execution 

Customer 1 is Requesting Resources:
2 1 1 
Available Resources : 
174 173 172 
The need : 
4 3 2 
The System is Safe 
Resources Granted 

Customer 1 is Requesting Resources:
2 2 1 
Available Resources : 
172 172 171 
The need : 
2 2 1 
The System is Safe 
Resources Granted 
Thread 1 finished execution 
Reached the end of the program!
```

## Built With

* [GCC](https://gcc.gnu.org/) - The GNU Compiler Collection
* [Ubuntu 16.04 LTS](releases.ubuntu.com/16.04/) - Xenial Xerus

## Authors

* **Mohamed Elsayed** - [Github](https://github.com/mohamedelsayed95)
* **Ahmed Wael** - [Github](https://github.com/ahmedwael19)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
