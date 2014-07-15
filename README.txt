Name: Era of Fantastic Colonies

Description: You just downloaded the hit new real time strategy game, `Era
of Fantastic Colonies.' It's now giving you trouble, asking for a CD key. 
Surely you purchased it, so that shouldn't be a problem. Can you get around
the obnoxious DRM?

How to Solve: The trick here is to bypass the CD key check. The `key' itself
is actually a random, changing value (so it's almost impossible to get the
correct one). This can be done in several ways, but my solution involved 
writing NOPs to the binary, starting after the stack space for local variables
was allocated and ending right before the call to SDL_Init (which is needed
for the `game'). When the edited binary is run, an SDL window pops up and
displays the flag (written as vector operations for obfuscation). (working
example is src/cracked_Game.bin)

What to distribute:
dist/Game.bin - The DRM protected `game'

Flag: MCA-B17EC0D3
