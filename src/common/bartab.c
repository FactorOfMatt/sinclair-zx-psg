/*

bartab.c

generate bar table  (create assembly code for inclusion elsewhere)

M. Desmond, August 2025 - Sort of based on ZX Specturm BASIC program found in
Your Computer, March 1983, page 59

*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define bytes_per_line 18 /* 6 sets of 3*/
#define line_length 23  /* including spaces*/
#define bars 138

char* bartable[] = {
    "K!3 C5- M2. M!) MH) A2.", /* 1 */
    "K!3 C5- M2. M!- MH) A2.",
    "M!0 @5- F2. M!5 M95 F2.",
    "M!0 A5- F2. J!5 M!3 F2.",
    "M!5 E!! J!! J!- !52 J!!",
    "M!5 M!! J!! J!- !!0 J!!",

    "J5. F!. JF5 E15 J!. F>.", /* 7 */
    "F5. F!. JF5 C!5 F!. F!!",
    "J5. F!) HE5 E!5 E!0 F>.",
    "M5. F!) HE5 F!5 C!0 F!!",
    "R!! !!\" !!) H!! A!$ F>,",
    "M11 !!\" !!) E!! @!$ F!!",

    "F5. J5. O40 F52 A2. J5.", /* 13 */
    "F5. J5. O40 A52 A2. F5.",
    "A5. M5. L40 F52 F2. J5.",
    "A5. J5. L40 J52 F2. J5.",
    ">!! F2. H4. A!! J5. M2.",
    ">!! F2. H4. F!! J5. M2.",

    "M!- F!. J!. K!3 <!0 JF.", /* 19 */
    "M!- J!. J!. J!2 @!0 JF2",
    "Q!- M!0 F!. H!0 C!0 FJ5",
    "T!- H!0 F1. J!2 H!0 FJ2",
    "H!! C!$ A!! K!3 L!. JF:",
    "H!! L!$ A!! M!5 O!. JF.",

    "K95 L7. E!5 J5. M)) J!5", /* 25 */
    "J95 H7. H!5 F5. M)) F!5",
    "K95 C7. M!5 A5. M95 H!5",
    "H95 O7. H!5 A5. M53 E!5",
    "F!! L!! E!) J.5 !42 A!!",
    "E!! H!! E!) J.5 !20 A!!",

    "C40 C!. M0- F2. !M- F2.", /* 31 */
    "C40 J!. Q0- F5. !M0 E2.",
    "H40 H!0 M0- A2. A!5 F2.",
    "H40 M!0 H0- A5. A!0 J2.",
    "L7. L!$ E!! J2. !A- A!!",
    "L7. O!$ E!! J5. !A) F!!",

    "F2. E!) M2. C!3 F52 M0-", /* 37 */
    "E2. F!) M2. C!3 E52 M0-",
    "F2. H!) K2. K!3 F52 Q0-",
    "J2. E!) J2. H!3 A52 M0-",
    "A!! C!! H!! C!5 >!! H!!",
    "A!! A!! F!! E!5 :!! E!!",

    "M0- J5. J2. F52 F2. H!3", /* 43 */
    "M0- J5. J5. F52 A2. G!3",
    "M0- F5. F2. J52 J2. H!3",
    "H0- J5. F5. F52 F2. K!3",
    "Q!! M.2 A2. A!! M!! A!5",
    "Q!! R.2 A5. A!! J!! E!5",

    "JF. M0- H5) M2. M2. F52", /* 49 */
    "JF. M0- E5) M5. M5. F52",
    "FJ. Q0- A5) J2. F2. J52",
    "KH. Q0- A5) J5. F5. F52",
    "MJ! H!! !!5 F2. J2. M!!",
    "MJ! H!! !!5 F5. J5. M!!",

    "J!. J!. J5. H30 L70 F2.", /* 55 */
    "F!. F!. M5. C30 L70 E2.",
    "E!0 E!. R5. H30 O04 F2.",
    "A!0 F!. M5. H30 O04 J2.",
    "C!$ A!! J.5 L!! L.0 A52",
    "@!$ A!! F.5 L!! L.0 F52",

    "M!- M2. L!0 M0- K!3 R2.", /* 61 */
    "M!- M2. L!0 Q0- J13 Q2.",
    "Q!- J2. O!0 T0- H!3 R2.",
    "M!- J2. L!0 Q0- F!3 M2.",
    "H!! F!! H!. M-0 E!5 J!!",
    "M!! F!! L!. M-0 H!5 F!!",

    "LH. R2. M0- F!. M!. H5-", /* 67 */
    "LH. Q2. Q0- F!. H!. E5-",
    "HL! R2. M0- :!. C!. A5-",
    "HL! M2. M0- :!. C!. A5-",
    "LH. J.5 H-5 !!\" L!! M-0",
    "LH. F.5 H-5 !!\" L!! M-0",

    "F52 H5- M2. M0- K!3 L7.", /* 73 */
    "F52 H5- M2. H0- J!2 O7.",
    "J52 H5- F2. M0- H!0 T7.",
    "J52 M5- F2. Q0- H!0 07.",
    "A!! Q!! J.5 M-0 M!5 L.7",
    "A!! Q!! J.5 M-0 M!5 O.7",

    "HE) M0- L7. J5. L7. F52", /* 79 */
    "HE) L0- L7. H5. H7. J52",
    "M5) M0- 07. J5. C7. F52",
    "Q5) H0- 07. M5. C7. A52",
    "H!5 E-5 H.7 R.2 L.7 )!!",
    "H!5 A-5 H.7 M.2 L.7 )!!",

    "J!. L!. C!. J5. H73 HE.", /* 85 */
    "H!. L!. C!. J5. K73 FC.",
    "J!. O!. H!0 M5. H73 FC0",
    "M!. L!. F!0 M5. K73 EA0",
    "R!! H!! E!$ R.2 E<5 EA$",
    "M!! L!! C!$ R.2 H<5 C@$",

    "K95 HE5 H!3 H40 J!. J2.", /* 91 */
    "K95 HE5 K!3 C40 O!. F2.",
    "H95 EH! O!3 H40 M!0 M2.",
    "H95 EH! K!3 L40 Q!0 J2.",
    "E!! HE5 H!5 O!! L!$ A!!",
    "E!! HE! E!5 L!! O!$ M!!",

    "T40 M5- M0- M!5 F!2 E!)", /* 97 */
    "T40 M5- L0- J!5 A!2 E!)",
    "O40 Q5- M-0 H!) F!2 H!)",
    "L40 M5- Q-0 E!) J!2 H!)",
    "H.4 H!! H5- A!! M!F M!!",
    "C.4 H!! H5- A!! J!. M!!",

    "O0- JF5 H5- CC. L0. LC$", /* 103 */
    "M0- JF5 H5- JC. L0. HC0",
    "L-0 HE) M5- JE0 L0. L!/",
    "M-0 EA) H5- FC0 H0. L!0",
    "H5- AE! E!! EA$ O0. L!.",
    "H5- AE! H!! C@$ O0. L!0",

    "M!- C4. H5- F2. M0- H!3", /* 109 */
    "Q!- C4. J5- F2. M0- K!3",
    "M!- C.4 K5- A2. H0- C!3",
    "Q!- H.4 H5- A2. E0- H!3",
    "H!! L7. F!) J!! A-0 E!5",
    "H!! L7. E!) J!! A-0 H!5",

    "H@. J!. K!3 FA. H!. H!.", /* 115 */
    "H@. R!. H!3 FA- C!. G!.",
    "LH. Q!0 C!3 J!. L!. H!.",
    "LH. M!0 C!3 K!0 H!. L!.",
    "OL. O!$ E!5 K!2 O!! O!!",
    "OL. L!$ E!5 K!4 L!! L!!",

    "M0- F52 E!) K!. F2. H@.", /* 121 */
    "Q0- A52 E!) M!. E2. H!!",
    "M0- J52 H!) J!0 F2. H@.",
    "H0- F52 E!) F!0 J2. H!!",
    "E!! M!! C!! E!$ A.2 H@.",
    "A!! M!! A!! C!$ F.2 H!!",

    "M0- H!5 H!- H95 F2. M2.", /* 127 */
    "L0- H!4 H!- Q95 F2. M2.",
    "M0- A!5 E!- M95 F2. K2.",
    "H0- A!0 E!0 H95 H2. J2.",
    "E!! A!- A!! E!! J!! H!!",
    "A!! A!) A!! E!! J!! F!!",

    "J!. E5) K!3 A2. J!5 O0-", /* 133 */
    "M!. F5) O!3 A5! F!5 M0-",
    "M!0 H5) C!3 F2. E!) Q0-",
    "M!0 J5) C!3 F5! H!) M0-",
    "C!$ K-5 E!5 J2. M!! H-0",
    "L!$ H-5 H!5 J5! M!! M-0"
};

#if 0
    // bar 103 - just so we can repeat it if we like for debug
    // V1: O J H C L L      sq sq sq sq q
    // V2: 0 F 5 C 0 C      sq sq sq sq sq sq
    // V3: - 5 - . . $      sq sq sq q sq
    //char* fakeout = "O0- JF5 H5- CC. L0. LC$";
#endif

#if 0
    // a simple test-bar
    // each voice emits 6 notes going down in frequency
    char* fakeout = "TG' SF& RE% QD$ PC# OB\"";
#endif

int main() {
    uint32_t nbars = sizeof(bartable)/sizeof(char*);
    if (0 && nbars != bars) {
        fprintf(stderr, "Wrong number of bars!  There should be %u but are %u.\n",
                bars, nbars);
        return 5;
    }

    printf("; bartable.src\n");
    printf("; Automatically generated.  Do not edit.\n\n");
    printf("bartable:\n");

    int err = 0;
    for (int bar = 0; bar < nbars; ++bar) {
        const char* cl = bartable[bar];
#if 0
        // an opportunity to use the same bar over-and-over for testing
        //cl = fakeout;
#endif
        size_t ll = strlen(cl);
        if (ll != line_length) {
            fprintf(stderr, "Wrong line length (is %zu, should be %u): %s in bar %d\n",
                   ll, line_length, cl, bar + 1);
            err = 5;
        }
        if ( (cl[3] != ' ') || (cl[7] != ' ') || (cl[11] != ' ') || (cl[15] != ' ') || (cl[19] != ' ')) {
            fprintf(stderr, "Expecting spaces between triplets: %s in bar %d\n", cl, bar + 1);
            err = 5;
        }
        printf("        dc.b ");
        for (int row = 0; row < 6; ++row) {
            const char* notes = &cl[row * 4];
            for (int k = 0; k < 3; ++k) {
                char n = notes[k];
                if ((n < '!') || (n > 'T')) {
                    fprintf(stderr, "Character out-of-range ('%c': %d) in bar %d\n", n, n, bar + 1);
                    err = 5;
                }
                printf("%3d", notes[k] - 33);
                if (!(row == 5 && k == 2)) {
                    printf(", ");
                }
            }
        }
        printf("  ; %s\n", cl);
    }

    return err;
}