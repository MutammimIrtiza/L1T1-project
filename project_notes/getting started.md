
## related: [[skipped for now]]


- ## jumps:
no rotation
state = jump
initial speed u
u decreases gradually
at peak, state = fall
same as before but reverse
at ground level, state = ground

- ## landing 
have platform arrays
continuously check if there is a platform below : compare y of character to y of obstacles
it was falling, now i want it not to fall
so change state from fall to ground (though i am not actually on the ground, this should work)

 - ## obstacles: 
arrays for obstacle x, y, width, height
check for collisions each frame
### triangular obstacle:
idk

- ## small stuff: 
main menu
settings
leaderboards
progress bar
pause menu
return to main menu


 
- ### delay in continuous jump from ground, but no delay in continuous jump from obstacle

- # there can be hundreds of < <= > >= combinations, and i don't know which one will work smoothest

	
	