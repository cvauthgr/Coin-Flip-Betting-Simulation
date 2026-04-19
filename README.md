# Coin-Flip-Betting-Simulation

<img width="720" height="360" alt="pixil-frame-0 (1)" src="https://github.com/user-attachments/assets/09f6cbca-9f97-4a72-b56a-11b96511631d" />

I implemented a simple coin flip betting simulator engine in C++23 

>[!CAUTION]
>This version is incomplete and unsafe , don't rely on any of it's parts for anything you make

## What this program does

`( For anyone wondering , no , this program won't help you become a millionaire by backtesting your favorite coin flip gambling strategy ) `

In it's core the program is fairly simple and has two modes 

1) Mode 1 : Monothreading
2) Mode 2 : Multithreading 

### How to switch between modes 

First navigate to the `ProgramMode.h` header file and uncomment the mode you want the program to execute in 

Example : The program will execute in a single thread

```
#define MONOTHREADING
//#define MULTITHREADING
```
Example : The program will execute on 16 threads 

```
//#define MONOTHREADING
#define MULTITHREADING
```

>[!WARNING]
>Only one mode should be used at a time , otherwise UB takes place 



