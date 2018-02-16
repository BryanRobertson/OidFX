# OidFX

The source code for a little game I wrote back in 2005, in order to land my first programming job.

# WARNING THIS CODE IS TERRIBLE
## NO REALLY, I'M NOT BEING SELF DEPRECATING HERE, IT REALLY IS
The engine is full of all kinds of shonk that doesn't represent me as a programmer today. It's basically babby's first object-oriented cache-melting engine of horrors.

I found the source code on an old hard-drive, and it seemed like a shame to risk losing it at some point (as has happened with some other codebases that have outlived their usefulness as my skills have improved over the years). Begrudgingly, I felt that I should keep it around, as it is a part of my history. 

It doesn't play very well on modern machines, it glitches out a lot.
My gut feeling is that this is probably related to the fact that the timer class I wrote, only calls QueryPerformanceFrequency once on construction. At the time, the idea that the clockspeed could change at runtime hadn't really occured to me (probably got away with it at the time because it was mostly true on my desktop? I'm pretty sure I remember my laptop exhibiting weird behavior occasionally though)

Other howlers, include entity update being done recursively via the scene graph (hellooooo cache misses), shared pointers with atomic refcounts being copied around everywhere like there's no tomorrow. 
Those are just the ones I remembered.... I'm sure there's tons of shonk in there that I have forgotten about