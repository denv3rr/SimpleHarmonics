# SimpleHarmonics

Exponentiation Sequence Creation

This program generates and visualizes modular exponentiation sequences.

<br><br>

- **Dynamic Sequence Generation**: Automatically generates sequences based on user-defined base and modulo values.
- **Visualization/Animation**: Displays a scrolling wave pattern of the sequence.
- **Note:** Using GNU MP Bignum Library for C++ (for precision integer values) and compiling with the following command:
- **Note:** Using **<conio.h>** - this is a Windows-only header file for console i/o operations. This means this program is **not yet** portable across different operating systems. Updating in the future for wider use.

<br><br>

## To Compile and Run

1. Clone repo
  
2. Run the following:

   - ```
     g++ -I ./ *.cpp -lgmp -lgmpxx
     ```

<br><br>

## Menu Options

### Main Menu

```
--- Control Menu ---
1. Set new base (current: 2)
2. Set new modulo (current: 9)
3. Start sequence
4. Start/Stop animation
5. Toggle loading bar (current: ON)
6. Settings
7. Exit program
Select an option:

```

### Settings Menu

```
--- Settings Menu ---
1. Set animation speed (current: 50ms)
2. Back to main menu
Select an option:

```

<br><br>

## Example Output

### Sequence Display
```
Initializing sequence with default base (2) and modulo (9)...

Generated Sequence Pattern:
Term 1: 2 [=====>                        ] 16%
Term 2: 4 [==========>                   ] 33%
Term 3: 8 [===============>              ] 50%
Term 4: 7 [====================>         ] 66%
Term 5: 5 [=========================>    ] 83%
Term 6: 1 [==============================] 100%

```
<br><br>

<div align="center">
  <a href="https://seperet.com">
    <img src=https://github.com/denv3rr/denv3rr/blob/main/Seperet_NightVision_Slam.gif/>
  </a>
</div>

[logo]: https://github.com/denv3rr/denv3rr/blob/main/Seperet_NightVision_Slam.gif "Seperet.com"
