# Electronic Voting Machine Using Arduino

This project implements an **Electronic Voting Machine (EVM)** using an Arduino board with an ATmega328P microcontroller, a keypad for user input, and an LCD for displaying messages and voting results. The EVM allows users to cast votes for multiple parties and provides an administrative interface for managing the system, including setting the number of parties, resetting votes, and viewing the results.

## Features

- **Voter Interface**: Allows voters to cast their votes for their preferred party using a keypad.
- **Administrator Interface**: Allows the administrator to:
  - Set the number of parties.
  - View voting results.
  - Reset votes.
- **LCD Display**: Displays instructions, vote confirmations, and results.
- **Security**: A password-protected admin interface to prevent unauthorized access.

## Components

- **Arduino Board**: ATmega328P microcontroller.
- **16x2 LCD Display**: Used to display messages and results.
- **4x4 Keypad**: Used for input (voter ID, admin password, vote casting).
- **Power Source**: USB or external power supply for Arduino.
  
## Circuit Diagram

- **LCD Pins**:
  - RS: Pin 12
  - E: Pin 11
  - Data Pins: Pins 6, 5, 4, 3
- **Keypad Pins**:
  - Row Pins: A0, A1, A2, A3
  - Column Pins: 10, 9, 8, 7

## Installation and Setup

1. **Clone or download** the project.
2. **Connect the hardware components** as per the circuit diagram.
3. **Upload the code** to the Arduino board using the Arduino IDE.
4. **Open the Serial Monitor** (optional) to view system logs.
5. **Start the machine**:
   - Voters can press `B` to cast their votes.
   - Admins can press `A` to access the admin interface after entering the password.

## Usage

### Voting

1. Press `B` to enter voting mode.
2. Enter the party number using the keypad (0 to the number of parties).
3. Confirm the vote, and the machine will display a confirmation message.

### Admin Interface

1. Press `A` to enter admin mode.
2. Enter the admin password (default: `997`).
3. Available options:
   - **C**: View the current results.
   - **D**: Reset votes.
   - **CC**: Print party-wise votes.
   - **DD**: Change the number of parties.

### Resetting Votes

The admin can reset all the votes by pressing `D` after entering admin mode.

## Code Explanation

- **Keypad Input**: The `Keypad` library is used to handle user inputs from the 4x4 keypad.
- **LCD Display**: The `LiquidCrystal` library is used to manage the 16x2 LCD display.
- **Voting Logic**: Votes are stored in an array, and users can cast votes for any of the available parties.
- **Admin Features**: Admin features like resetting the votes, changing the number of parties, and viewing results are password-protected.

## Future Enhancements

- Add RFID or biometric authentication for voters.
- Store votes in non-volatile memory to retain data after power loss.
- Extend support for larger screens or touch displays.

## License

This project is open-source and can be used and modified freely.

