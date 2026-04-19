# Coin-Flip-Betting-Simulation

<img width="720" height="360" alt="pixil-frame-0 (1)" src="https://github.com/user-attachments/assets/09f6cbca-9f97-4a72-b56a-11b96511631d" />

I implemented a simple coin flip betting simulator engine in C++23 

>[!CAUTION]
>This version is incomplete and unsafe , don't rely on any of it's parts for anything you make

## What this program does

`For anyone wondering , no , this program won't help you become a millionaire by backtesting your favorite coin flip gambling strategy`

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

### Monothreading mode 

In this mode the program executes on a single logical processor (thread) simulating a single strategy at a time untill it finishes 

### Multithreading mode 

In this mode the program simulates all strategies N-th times parrallel to each other and returns the total success rate for each one (more on this later)

## Betting strategies 

In the file `BettingStrats` i have implemented 4 betting strategies the user of this program can simulate 

1) Timid : The timid strategy bets the same fixed amount each round regardless of outcome untill either it achieves it's goal or bankrupts the player
2) Bold : The bold strategy bets all of the balance if the players balance is less that half of the goal and bets the amount needed to hit the goal if the balance exceeds half of the goal
3) Martingale : This strat relies on the very simple technique of doubling the bet after every loss hoping for a big win . I implemented it with a twist . If the player is in a consecutive loss spree and has to double his/her bet but this isn't possible due to missing funds the program goes all in either letting them continue to playing or bankrupting in a single bet
4) RandomBets : This is the one strat that i had the most fun implementing . The idea behind it is very simple . The gambler has one too many shots of tequila (or something stronger) before starting to play . So now the only thing he remembers is how much he has to win . Every round he bets random amounts . Thankfully for us one of his friends is there reminding him of the possible bets he can make , so he doesn't  bet more than he has or leaves before he hits his goal . Thank you friend !

## The `RandomGen.h` file 


