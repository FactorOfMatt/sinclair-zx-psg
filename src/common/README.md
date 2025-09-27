# Notes on the MINUETZ program

The minuetz program consists three sections: the main BASIC program, some machine-code routines and a number of data-tables (mainly for the note-data in the bars).
The machine-code and data-tables are saved into a single file that is then loaded by the BASIC program.  The `bin2tap` program is used to create a single .tap file that contains both the BASIC program followed by the machine-code.

`zmakebas` supports the inclusion of comments in the BASIC text file by using the '#' character at the start of a line.  I've added many comments to the code.  They may aid or hinder your understanding of how the code works.  Comments added into `minuetz-basic.txt` in this way do not end up in the Spectrum BASIC image created by `zmakebas`.


## BASIC
There's a fair amount going on with the BASIC program (`minuetz-basic.txt`): some of it good, some of it bad and some of it downright weird.  Here are my thoughts.  

### Size Trick
The authors have seemingly used a few tricks in order to minimize the size of the program.  The program as written will fit into a 16K Spectrum.  A 16K Spectrum leaves about 9K for BASIC and variables (and in this case machine-code routines).
I haven't looked into how close they are cutting it.

- The use of the LET A = VAL "1234" pattern does in fact save a few bytes.  Spectrum BASIC embeds the floating-point representation of the number right after the text of the number itself this ends up being 6 more bytes.
  - 12345 takes 5+6 = 11 bytes
  - VAL "12345" takes 5 + 3 = 8 bytes.

This trick seems to be used 30 times.  That's 90 saved bytes!  Most of the instances come in not-so time critical sections of the code since this space-saving measure takes way longer to execute.

### Run once
The first line of the code as-written attempts to load the machine-code binary. Always.  There's no check to see if it looks like it's already loaded.  This seems very odd to me and must have been a nightmare during debug.
Adding an if isn't difficult (you'll see one way to do it commented out in the source) - but it does rather get in the way of line 2...

### Saving an image of the screen
The program lets you save a screenshot of the completed musical manuscript.  This is performed by saving an image of the screen.  The actual save is performed at line 2, which is called from line 224.  For some reason, the code on line 224 pokes the filename directly into the BASIC program at line 2.  The location (23785) is hardcoded and clearly just assumes that this is indeed the location of where the 10-character filename is between the quotes.  As such, if you wish to save the display you'd better ensure that line 1 and 2 are exactly as they are in the magazine else the filename will be poked into the wrong place.  
I have no idea why it was done this way.  It may be that string variables aren't allowed as filenames (which would seem very odd).

### Guess the key
The magazine article mentions that it can play the compositions "in one of two keys".  True.  But it seems to simply alternate the key being used each time the composition is played.  The method of picking the key also seems strange: all the divisors used to select the PSG notes are either multiplied by 5/6ths or 6/5ths based on the KY variable (line 254).  
Multiplying the divisor by 5/6ths lowers it to 83.3% of the value before it started.  This raises the pitch.  Multiplying it by 6/5ths puts it back.  
At 2MHz, A440 has a divisor of 249.  83.3% of this is 237 which creates a frequency of 527Hz which corresponds to C523 (ish) - or 20% higher as expected.  
I'm no musician, but simply rasing and lowering the pitch of notes doesn't seem like changing the key to me.

### Guess the entrypoint
The BASIC code calls into the machine-code rotuines in several places.  For non-system calls this is done by variables (PL, DI and SORT).  These entrypoints are hardcoded in the BASIC and have to point exactly into the ml routines.  This is not particularly robust and discourages changes to the ml routines.  A jump table right at the end of the 16K RAM memory space (right before 32K I'm assuming might have been a better choice here.  The BASIC could peek a few well-known locations and set PL, DI and SORT without regard for if the ml routines have changed.

Similarly there are some data-tables shared between the BASIC and machine code.  The locations for these tables (LD, RD, DT, DI etc) are also hardcoded in the BASIC program.  These could also benefit from a pointer-table of some kind.

### Self modification
We've already seen that the BASIC code self-modifies itself for the screen-shot filename.  We've already seen that the BASIC code modifies the frequencies of the notes.  Are we done with all the runtime modifications?  No.  Not even close.
The BASIC program modifies the machine code in several places:
- line 220 modifies the ml to point to either the first-half or the second-half of the rolled-dice table.
- line 254 modifies the ml to adjust for the selected tempo.  (and is also where the frequencies are modified by 5/6 or 6/5)
- line 8530 resets the ml bar-table pointer to point to the start of the bartable
- line 8630 adjusts the ml bar-table pointer based on the voice being displayed
- line 9800 resets the ml bar-table pointer as line 8530
- line 9830 resets the ml bar-table pointer as line 8530

## Assembly Code
I'm no expert in Z80, but for the most part the assembly code seems fine to me.  Aside from the blatant self-modification that is.  To make such modifications a little easier to understand I gave each location a label starting with smc.  The label istself is usually a byte before the actual bytes that get modified (the actual instruction doesn't change, jusr the operand).  The locations of the modified code are:  
- $7e18 (32280) `smc_rndtablo        ld hl, rndtable`
- $7e22 (32290) `smc_bartablo        ld hl, bartable`
- $7e3b (32315) `smc_notesortend     ld b, barcount+slotcount`
- $7e64 (32357) `smd_rnd_low         ld de, rndtable`

- `playmain` contains code that updates the address at `smc_rnd_low`
- `musicbox` contains code that updates the address at `smc_rndtablo`
- `part` contains code that updates the address at `smc_notesoertend`
- the BASIC program contains the code that upates the address at smc_rndlatblo (line 220).

## Matthew's verdict
Given the memory constraints a 16K Spectrum imposes on the programmer and the quite ambitious nature of the Minuetz program I think the original authors did a pretty fantasic job.  The effort to save space and judicious use of machine-code really did enable Spectrum users to play decent-sounding music on their machines.  The self-modifying code isn't ideal - neother is the notion that it always wants to load the machine-code from tape each time the program RUNs - but these are just the sacrifices that have to be made.


## Bugs
The minuetz program presented here (at least on the initial commit) seems to have a bug or two.  Naturally this could be to me misreading or mistyping the program in the first place.  I'm relatively sure the assembler file generates the correct code - I have compared the bytes with those listed in the article (which includes the data-tables too).  The largest potential for mistakes is the 138 bars of 18 notes I had to type in.

Here are some issues I've noticed but not yet determined if they're typos or real bugs - and I certainly haven't fixed them.

- Holey notes.  The circle commands that make up the 1/4, 1/8 and 1/16 notes don't fill in the entire circular area entirely.  The cover of the magazine seems to show the same thing on the screen.  I consider this an actual bug.
- Odd rest placement.  1/8 note rests are inconsistently spaced in their bar and are even inconsistent between bars.  This does look different from the magazine scan - likely an oopsie.
- Ledger lines are inconsistent at the top of the top treble stave (possibly elswhere).  The magazine cover shows the same thing.
- Many of the voice 2 and voice 3 notes (usually on the bass stave but not always) seem to be the same note.  This seems inlikely.  There is no example in the article where two notes from different voices are coincident.  Likely a typo.
- I created a debug version of the code that always uses 6-note scale for every bar.  It was clear that the handling of accidentals isn't quite right.  For display the code pretends the accidental is really just the non-accidental note in the same place - then adds the sharp sign.  During playback this pretending isn't always undone properly.

## Future?
I'm not sure if I will try to continue the noble work of RK Hopkins and HJ Laverty or if others may take up the mantle - but I'd like to think that somebody might.

- If we removed the 16K constraint, we could remove some of the space-spaving and time-costing optimizations.  This would greatly help with comprehension.
- It might be nice to use more features of the PSG.  Possibly different volumes for the 3 voices and maybe envelope control.
- The program has a hardcoded frequency table.  The numbers in this table were calculated by the authors and presumably based on what they thought their RC controlled clock source ran at (mine runs at about 1.65MHz).  It seems very unlikely that any two sound cards would be in tune with each other. It should be easy for this table to be semi modifiable by creating a C program that creates an assembler source fragments based on a clock frequency passed on the command-line.
  - The Specturm is also capable of calculating these values itself and possibly poking them into the correct place in memory.
- I suspect there is a way to load both the BASIC program plus the data tables in machine code all in one go - I just don't know enough to do it at the moment.
- Who knows?