
Drive link to video:
https://drive.google.com/file/d/17z-OzBYIClYzMhaOc0SQM1ngDm-hTcny/view?usp=sharing

-------------------------------------------------------------------------------------------------------------------------------------------------------------

This README file summarises my, that is Rohan Nafde's CS project.
It will tell the features involved and guide on how the game works.
Please read it in a maximized window.

-------------------------------------------------------------------------------------------------------------------------------------------------------------

Game - Bubble Shooter

Dev - Rohan Nafde

Purpose - CS Project

-------------------------------------------------------------------------------------------------------------------------------------------------------------

About the game -

From the title, it is clear that this game involves shooting bubbles.

You are given a shooter that moves left and right (not up and down) that shoots bullets.

A bubble moves in a parabolic path (i.e., similar to a motion in gravity).

Bullets, upon hitting these bubbles, pop it and disappear themselves too.

Your task is simple... shoot all the bubbles in the play area to complete the level.

But be careful! If a bubble hits your shooter, you lose some health! Upon reaching zero health, GAME OVER!

-------------------------------------------------------------------------------------------------------------------------------------------------------------

Game Window - 

1) Top-left part shows your score

2) Middle-left part at the top shows your current level

3) Middle-right part shows your health

4) Top-right part shows the time left in hand for you to complete the level

5) The two horizontal blue lines near the top and bottom show the upper and lower boundaries of the play area.
   Note that the left and right boundaries are simply the left and right borders of the canvas window.

6) The moving balls are the bubbles to shoot

7) The green candle-like thing is the shooter

8) Upon shooting, the red square coming out the shooter is a bullet

-------------------------------------------------------------------------------------------------------------------------------------------------------------

How to play - 

Press 'w' to shoot a bullet.
Press 'a' to move shooter left.
Press 'd' to move shooter right
Press 'q' to quit (but remember winners never quit ;))

-------------------------------------------------------------------------------------------------------------------------------------------------------------

Note - The window was changed from 500x500 to 960x540 (a standard 16:9 resolution)
       The refresh rate of the game is 50Hz

-------------------------------------------------------------------------------------------------------------------------------------------------------------

How the game works -
 
1) A bullet, on hitting a bubble, pops it and disappears itself

2) Upon hitting a bubble, you gain a score worth the level you are currently playing (e.g., you earn 6 points per bubble popped in level 6)

3) Once a bullet is shot, a 0.2s cooldown is introduced before shooting another bullet
   This increases the difficulty so that someone doesn't just spam the 'w' key and shoot many bullets at once.

4) Every bubble you shoot, one point is taken from your score. This is done to check accuracy.
   Note that you cannot drop down below 0 in the score (illogical)

5) Your shooter has five hit points (HP), meaning it can be hit five times in one level, after which the health regenerates back to full.
   This is done purposely because keeping track of health and only five hit points would make the game very difficult. Hence health is reset.

6) The shooter, once hit by a bubble, reduces the health by one HP, and your score also reduces by one.
   But now that the shooter has been hit, you get 0.5 seconds of invincibility so that you don't die immediately.
   The message of you having invincibility pops up in the center of the play area in green letters.
   The bubble, after hitting you, continues its trajectory disregarding the shooter’s presence, i.e., it doesn't bounce off the shooter but instead goes through it.

7) Each level you advance, there is a:
   I)	Increase in number of bubbles by 1
   ii)	25% increase in bubble radius
   iii)	25% increase in velocity of the bubble and bullet (velocity of movement of shooter doesn't change)
   iv)	50% increase in gravity, i.e., downward acceleration.
   v)	5 seconds additional time

8) The timer shows the amount of time you have left in hand. It starts to flash red and black once below 10 seconds, indicating you to hurry and finish the level before time runs out.

9) Each level, the spawned bubbles have different colors from the previous one.
   Each bubble in the level has a different starting velocity (in both x and y directions) and different starting directions but the same downward acceleration.
   But these colors and values are always the same when you load up a new game from level 1.

-------------------------------------------------------------------------------------------------------------------------------------------------------------
