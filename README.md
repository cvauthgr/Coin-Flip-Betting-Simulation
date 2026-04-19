# Coin-Flip-Betting-Simulation

<img width="720" height="360" alt="pixil-frame-0 (1)" src="https://github.com/user-attachments/assets/09f6cbca-9f97-4a72-b56a-11b96511631d" />

I implemented a simple coin flip betting simulator engine in C++23 

>[!CAUTION]
>This version is incomplete and unsafe , don't rely on any of it's parts for anything you make

## What this program does

`For anyone wondering , no , this program won't help you become a millionaire by backtesting your favorite coin flip gambling strategy`

In it's core the program is fairly simple and has two modes 

1) Mode 1 : Monothreading
2) Mode 2 : Multithreading (` Take that GIL `)

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

In the core of this program lies a simple function template . Navigating to the `RandomGen.h` header file we see at the bottom :

```
template < typename T > 
inline T getReal(T min , T max)
{
    return std::uniform_real_distribution<T>{ min , max }(mt) ;
}
```

This inline function template is vital for the execution of our simulations

-> Inline guarantees that in every `.cpp` file there will be only one instance of our function to avoid violation of the ODR 

-> Using the template we can input arguments of the same floating data type (only tested for floating fundamental data types [C++ Fundamental Data Types(https://en.cppreference.com/cpp/language/types)) in a logical order and receive a pseudorandom random 64 bit number inbetween those two parameters we gave the `getReal()` function (inclusive) . We use the pseudo random number generator mersenne twister 
[C++ Mersenne Twister](https://en.cppreference.com/cpp/numeric/random/mersenne_twister_engine)
and we seed it at the start of each coal to the `getReal()` function with a std::random_device type number form the OS [Pseudorandom Numbers Coming From The OS](https://en.cppreference.com/cpp/numeric/random/random_device) . Cpp reference gives a very good example on that exact thing .

->The return type matches the function parameters and by using `return std::uniform_real_distribution<T>` we ensure that each number appears with the same frequency . Although in the specific program we will never see a repeating number as this prng has a range of 0 - 2^19937 - 1 [Mersenne Twister 64 bit Range -  Characteristics Section](https://en.wikipedia.org/wiki/Mersenne_Twister)

### Examples

In main we can call 

```
std::cout << getReal( 1.0 , 10.0 ) ; // Each number must be of floating data type
```

And we receive : `9.56512` which is valid

If we try to call

```
std::cout << getReal( 1 , 10 ) ;
```
We get 

```
ERROR!
In file included from /usr/local/include/c++/14.2.0/random:48,
                 from /tmp/V71X4w0gMq/main.cpp:1:
/usr/local/include/c++/14.2.0/bits/random.h: In instantiation of 'class std::uniform_real_distribution<int>':
/tmp/V71X4w0gMq/main.cpp:20:58:   required from 'T rnd::getReal(T, T) [with T = int]'
   20 |     return std::uniform_real_distribution<T>{ min , max }(mt) ;
      |            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~
/tmp/V71X4w0gMq/main.cpp:28:30:   required from here
   28 |     std::cout << rnd::getReal( 1 , 10 ) ;
      |                  ~~~~~~~~~~~~^~~~~~~~~~
/usr/local/include/c++/14.2.0/bits/random.h:1883:56: error: static assertion failed: result_type must be a floating point type
 1883 |       static_assert(std::is_floating_point<_RealType>::value,
      |                                                        ^~~~~
/usr/local/include/c++/14.2.0/bits/random.h:1883:56: note: 'std::integral_constant<bool, false>::value' evaluates to false

```
Because regardless that our function can accept both integral values `std::uniform_real_distribution<T>` only accepts floating data types as valid template parameters 

A simple fix is changing it to `std::uniform_int_distribution<T>` but then the function will accept only integral type parameters 

# How to run YOUR simulations using this program

## Step 1 : Configurating each players data 

To set each strategies simulation parameters we move to the `CasesInfo.h` header file .

There we can see 4 class objects :

```
inline GamblerInfo TimidStrategyPlayer { 50 , 0.5 , 1 , 150 } ; // Timid strategy
inline GamblerInfo BoldStrategyPlayer { 50 , 0.5 , 1 , 150 } ; //Bold strategy 
inline GamblerInfo MartinGaleStrategyPlayer { 50 , 0.5 , 1 , 150 } ; // Martingale strategy
inline GamblerInfo ForgetfulStrategyPlayer { 50 , 0.5 , 1 , 150 } ; // Random betting strategy
```

Each is corresponding to a specific strategy as depicted by the respecting comments

To change each simulation's parameters we change the values of the objects above according to this template 

```
StrategyNamePlayer { StartingBalance , PropabilityOfWinningTheCoinFlip , InitialBet , Goal }
```

All parameters are of type `double` so they should not exceed values outside the range of  2.22507e-308 to 1.79769e+308

### Example 

Lets initialize a martingale strategy player which starts with :

1) 100 $ 
2) Has an edge against the house P = 0.51
3) Bets start at 25 $
4) Wants to 10x his initial capital so 1000$ goal

`inline GamblerInfo MartingaleStrategyPlayer { 100 , 0.51 , 25 , 1000 } ; `

>[!Warning]
>Do not initialize a new class object just change the existing values from the simualtion object you want to initiate found in the `CasesInfo.h` header file

### The CoinFlipSimulation function

The function `CoinFlipSimulation()` is responsible for initializing the the monothreading simulation process 

We can pass 3 arguments :
1) The player's info
2) The betting method we want to simulate
3) The struct we want to return to receive the results of our simulation

On the more technical side : `inline SimulationStatististics& CoinFlipSimulation( GamblerInfo& Player , BettingMethod method , SimulationStatististics& stats)` this is our simulator in it's true form 

We pass two class objects by reference to avoid expensive copies and an enumerator from an enum class ( located in the `Enum.h` header file ) to select another function to be called by our function to initialize the simulation!

`python devs in sambles right now (joke!!!) ` 

 In reality what happens is :

 _start -> main -> CoinFlipSimulation -> NameOfBettingStrategy -> writeToFile -> plot -> _end

 ### The functions writeToFile,plot and the convencience of using gnuplot

 In their respecting files `FileHandler.h` and `Plotting.h` we can find (excluding the error handling functions) two new functions which are operating in the background but give us huge side effects 

 writeToFile
