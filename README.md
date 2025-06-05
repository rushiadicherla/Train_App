# Train_App
Project is to implement TRAIN TICKET BOOKING APP with  options to signIN , signUP, booking ticket , cancelling ticket , checking  trains availablities.
Train Ticket Booking System - C Project
Usage Instructions:
-------------------
1. Compile the Project:
   $ make

2. Run the Application:
   $ ./bin/train_ticket   (on Linux/macOS)
   > train_ticket.exe     (on Windows after compilation with MinGW)

3. Features:
   - Sign up: Register a new user with a secure password.
   - Sign in: Login using existing credentials.
   - Add Train: Add new train data (admin only).
   - Reserve Ticket: Book train seats.
   - Cancel Ticket: Cancel previously booked tickets.
   - View Bookings: Check booking details by seat number.

4. File Structure:
   - include/train_ticket.h : Header file with all structure and function declarations.
   - src/*.c                : Source files implementing functionality.
   - data/*.txt             : Persistent storage for users, trains, and bookings.
   - bin/train_ticket       : Output executable.

5. Notes:
   - Passwords must contain uppercase, lowercase, digit, and special character.
   - You can only reserve up to the number of available seats.
   - Booking is allowed for up to 3 days from today (date check is basic).
