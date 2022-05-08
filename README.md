# Philosopher
A small simulation of the famous problem of the dining philosophers programed in C

## How to run it
  * Use ``make`` to generate the  binary ``philo``
  * Run ``./philo [NumOfPhilos] [TimeToDead] [TimeToEat] [TimeToSleep]``

  Example: ``./philo 3 310 100 100``
  Example: ``./philo 2 410 200 200 5`` Optional must eat arg
## Makefile
   
  ``clean``: remove objects
  
  ``fclean``: remove binaries
  
  ``re``: generate all again
