# 🐍Snake Game

## 📜Backstory

This is an Arduino UNO project for the course “Introduction to robotics” at the Faculty of Mathematics and Informatics. It was assembled during the lab and at home and coded over the course of several days (including time to research) .

## 💬Description

This project is the classic snake game, a fun and challenging game implemented on a 8x8 LED matrix, using a joystick and LCD for user input and score tracking, and a buzzer for sound effects. This project is a great example of how to combine multiple hardware components and create a functional game with Arduino.

![tempFileForShare_20221215-164035](https://user-images.githubusercontent.com/68808448/207910217-64bc0dbe-2966-4182-a7fb-04c995364e4d.jpg)

## 🎦Short demo

[Youtube link](https://youtu.be/Tr-S0kC32G0)

<details>
<summary>

## 🛠️Setup

</summary>

### Components

- 1 Liquid crystal display
- 1 8x8 LED matrix
- 1 joystick
- 1 potentiometer (optional)
- 1 buzzer
- 1 MAX7219/MAX7221 driver
- 220 $\Omega$ & 100 $\Omega$ resistors
- 1 electrolytic capacitor of 10 μF
- 1 ceramic capacitor of 104 pF
- wires per logic

### Connections

![image](https://user-images.githubusercontent.com/68808448/207910455-2a0b48e5-d1aa-4618-b89b-b952337dbb87.png)

| Max7219 Driver Pins | Arduino Pins |
| --- | --- |
| 4 (GND) | GND |
| 9 (GND) | GND |
| 18 (ISET) | 5V, through a 10k or 100k+ resistor |
| 19 (V+) | 5V |
| 1 (DIN) | 13 |
| 12 (LOAD/CS) | 11 |
| 13 (CLK) | 12 |

There are also 2 capacitors that are connected in parallel to
the + and - of our circuit.
● 1 electrolytic capacitor of 10 μF
● 1 ceramic capacitor of 104 pF

| Display PIN | Function | Arduino pin |
| --- | --- | --- |
| VSS (1) | Ground | GND |
| VDD (2) | 5V | 5V |
| V0 (3)  | Contrast adjustment | 5 |
| RS (4) | Register Select. RS=0: Command, RS=1: Data | 9 |
| RW (5) | Read/Write (R/W). R/W=0: Write, R/W=1: Read | GND |
| E (6) | Clock (enable). Falling edge triggered | 8 |
| D0 (7) | Bit 0 (Not used in 4-bit operation) | - |
| D1 (8) | Bit 1 (Not used in 4-bit operation) | - |
| D2 (9) | Bit 2 (Not used in 4-bit operation) | - |
| D3 (10) | Bit 3 (Not used in 4-bit operation) | - |
| D4 (11) | Bit 4 | 7 |
| D5 (12) | Bit 5 | 6 |
| D6 (13) | Bit 6 | 3 |
| D7 (14) | Bit 7 | 4 |
| A (15) | Back-light Anode(+) | 10 (with 220+ ohm resistor) |
| K (16) | Back-light Cathod(-) | GND |

| Joystick pin | Arduino pin |
| --- | --- |
| VRx | A0 |
| VRy | A1 |
| SW | 0 |

Buzzer:  A2 (Arduino pin) (through a potentiometer in series with a 100 $\Omega$ resistor)

</details>

<details>
<summary>

## 📑Menu

</summary>

### 📋Main menu
![20221213_194443](https://user-images.githubusercontent.com/68808448/207910503-152076d8-1ffe-45a3-905e-72661a2b0738.jpg)

The menu is easy to navigate using the joystick and the LCD display. Simply select an option by flicking the joystick up or down. The current option is indicated by a right pointing arrow. To access an option flick the joystick to the right. To go back flick the joystic to the left. Each menu has a different icon shown on the LED matrix.

The menu has the following options:

- 🎮 Start Game: start a new game of Snake
- 🏆 Highscores: view the current highscores
- ⚙️ Settings: customize the game settings, such as difficulty level, sound effects, and other options.
- ℹ️ About: learn more about the game and its creators.
- ❔ How to Play: get brief instructions on how to play the game.

### 🏆Highscores

![20221213_194802](https://user-images.githubusercontent.com/68808448/207910567-1f5ffea9-1378-4d8e-871d-e8a801b7906e.jpg)

Highscores are saved in the EEPROM.

This menu is a leaderboard that tracks the top 5 scores of all time. The highscores menu shows the name of the player and their score, ranked from the first to the fifth place. When there are no highscores, “No highscores” message will be displayed instead.

The names are limited to 5 letters, so you should try to come up with a creative name.

### ⚙️Settings

![20221213_194845](https://user-images.githubusercontent.com/68808448/207910638-962bfd1b-b3f9-4def-9186-114f0da43ba9.jpg)

All settings are saved in the EEPROM.

The settings menu has the following options:

- Difficulty: choose from 6 levels of difficulty, ranging from easy to hard. The higher the difficulty, the faster the snake moves and the more challenging the game becomes but also the score increases more. In the first 2 levels, the snake moves faster and gets bigger with every piece of food eaten, in the next 2 levels the snake's speed and length stay the same but a timer for food is introduced. In the last 2 levels both game mechanics are combined.
- LCD Contrast: adjust the contrast of the LCD display to change the visibility of the text.
- LCD Brightness: control the brightness of the backlight of the LCD display, allowing you to play in different lighting conditions.
- Matrix Brightness: control the brightness of the LED matrix, allowing you to adjust the intensity of the 8x8 LED matrix.
- Sound: toggle all sound effects on or off. Volume can be adjusted with the potentiometer.
- Reset Highscores: reset the highscores leaderboard, allowing you to start fresh.

### ℹ️About!

![20221213_194854](https://user-images.githubusercontent.com/68808448/207910782-ad374cff-d3e3-4f8a-8ea0-f620f476917a.jpg)

The about section displays the name of the game, my name, and the link to the project on GitHub. This information is useful for players who want to learn more about the game for anyone who wants to contribute to the project and help improve the game.

### ❔How to play

![20221213_194902](https://user-images.githubusercontent.com/68808448/207910844-78af95a8-993d-4931-895e-e963a6b26d56.jpg)

This a brief tutorial on the rules and mechanics of the game such as:

- The snake can move up, down, left, right using the joystick.
- After level 3 a timer is used for food, so you have to be quick.
- You can pass through walls (and appear on the other side of the matrix), but be careful to not hit the snake’s tail.

</details>

<details>
<summary>

## 🕹️Gameplay

</summary>

![20221215_152317_1_1](https://user-images.githubusercontent.com/68808448/207926063-d4c55ae7-91ea-49b7-934a-96071735e619.gif)

![20221213_194915](https://user-images.githubusercontent.com/68808448/207910970-13ea8367-53cf-4476-8d60-448315d7a2c9.jpg)

The gameplay is simple and intuitive, you use the joystick to control the snake and navigate through the LED matrix. The current difficulty level, score and food timer are displayed on the LCD.

There are no obstacles, so you can focus on collecting food and scoring points. However, the game becomes more challenging as you advance to higher levels, where the snake moves faster and the availability of food is limited by a timer. 

One extra feature is that the snake can move through the walls of the game board, allowing the snake to wrap around to the other side. This adds an extra layer of strategy to the game, so you must plan your moves carefully to avoid hitting the snake’s tail when you exit on the other side.

You can pause the game by pressing the joystick button. Press again to unpause.

![image](https://user-images.githubusercontent.com/68808448/208480633-10549f8a-7666-4017-b06f-2fa3f7c70351.png)


### 💀Game over

The game is over when the snake touches its tail. The LCD displays a “Game over” message and shortly after the final score and the total time played.

![20221213_194950](https://user-images.githubusercontent.com/68808448/207911036-197abcbd-e9c1-4a0d-907d-ea7a6bd3ede4.jpg)

If your final score is a new highscore (or in top 5), you are informed and must enter your name. The name is limited to 5 characters. Select the letter by flicking left or right and change it by flicking up or down. When you are done, position the cursor on the arrow and press the joystick to save your highscore.

![20221213_194957](https://user-images.githubusercontent.com/68808448/207911084-0b5c5437-15d3-496a-98dd-080feb81af97.jpg)
