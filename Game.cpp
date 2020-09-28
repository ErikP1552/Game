//  Authors: Huy Tran, Erik Pantoja
//  A04725540
//  Due Date: Feb 6, 2019
//  Programming Assignment Number 1
//  Spring  2019 - CS 3358 - 253
//
//  Instructor: Husain Gholoom.
//  This assignment simulates a guessing game that generates a random 3-digit
//  number. The random number must not have any repeating digits (eg. 477).
//  After that, you get 10 chances to guess the 3-digit number, with clues
//  to help get you to the right direction. If you guess the correct number
//  before 10 guesses, the game quits the loop and asks if you want to play
//  again. If you do not correctly guess, then it shows the number and asks
//  if you want to play again. If user input is no/NO or n/N, program quits.

#include <iostream>
#include <cmath>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <ctype.h>
#include <cctype>
#include <locale>
#include <sstream>

using namespace std;

void theIntroduction();
void generateSecret(int, int);
void compareNumbers(int, int);
void playGame ();
void playAgain();
int guessFunction();
bool isNum(string input);

//  Plays the introduction and rules for the game
void theIntroduction(){
    cout << "Welcome to my Game Program. "<<endl;
    cout << "I am thinking of a 3-digit number. Try to guess what it is. ";
    cout << "Here are some clues: "<<endl<<endl;
    cout << "When I say:    It means " <<endl<<endl;
    cout << " B  No digit is correct" <<endl;
    cout<< " P  One digit is correct but in the wrong position." <<endl;
    cout << " F  One digit is correct and in the right position."<<endl;
    cout <<endl<<endl<<endl;
    cout <<" I have throught up a number. You have 10 guesses to get it"<<endl<<endl;;
    
};

//  takes NUM and arr[] as arguments and generates a random number until
//  it passes the check (no repeating numbers)
void generateSecret(int NUM, int arr[]){
    for (int i = 0; i < NUM; i++) {
        bool check;
        int num;    //the digit number
        do {
            num = rand() % NUM + 1;
            check = true;
            for (int j = 0; j < i; j++){
                if (num == arr[j]) {    //if the number is a repeating
                    check = false;      //digit, rerolls number
                    break;
                }
            }
        } while (!check);
        arr[i] = num;
    }
}
//  compares the numbers the user guesses with the secret number, with guesses
//  giving hints based on where the digit is.
void compareNumbers (int guess, int value[], int SIZE) {
    
    int digit[SIZE];    //the digit of the guess number
    int right = 0;    //counter for when getting 3 F's, ask to play again.
    int b = 0;    //if getting 3 incorrect numbers, cout "B"
    
    
    digit[0] = guess / 100 % 10;    //gets the 3rd digit number
    digit[1] = guess / 10 % 10;     //gets the 2nd digit number
    digit[2] = guess % 10;          //gets the 1st digit number
    
    if (digit[0] != value[0] && digit[0] != value[1] && digit[0] != value[2])
        b++;
    if (digit[1] != value[0] && digit[1] != value[1] && digit[1] != value[2])
        b++;
    if (digit[2] != value[0] && digit[2] != value[1] && digit[2] != value[2])
        b++;
    if (b == 3) {
        cout << "B";
    }
    
    if (digit[0] == value[0]) {    //3rd digit is in the correct place
        cout << "F";
        right++;
    } else if (digit[0] == value[1] || digit[0] == value[2]) {
        cout << "P";
    } else {cout << " ";}
    
    if (digit[1] == value[1]) {    //2nd digit is in the correct place
        cout << "F";
        right++;
    } else if (digit[1] == value[0] || digit[1] == value[2]) {
        cout << "P";
    } else {cout << " ";}
    
    if (digit[2] == value[2]) {    //1st digit is in the correct place
        cout << "F";
        right++;
    } else if (digit[2] == value[0] || digit[2] == value[1]) {
        cout << "P";
        
    } else {cout << " ";}
    
    if (right == 3) {    //getting all digits correct
        cout << "\tYou guessed it!" << endl;
        
        playAgain();
    }
    
}


int main () {
    theIntroduction();
    playGame();
    playAgain();
}


//  gives user 10 guess attempts and and calls guessFunction to give user
//  input of numbers and then compares. If number of attempts goes over 10,
//  game tells the user the number then asks to play again.
void playGame(){
    int guess = 0; // Used to fill guess with 0 instead of random
    const int SIZE = 3; //Size for the Array
    const int ATTEMPTS = 11; //Attempts to play
    int value[SIZE] = {0, 0, 0}; //Array creation
    const int NUM = 9; //Used for value of random number array
    bool correctGuess = false;
    srand (time(NULL));
    generateSecret(NUM, value);
    
    for (int i = 0; i<=11; i++){
        //cout << "\n REMOVE LATER: NUMBER IS " << value[0] << value[1]
        //<< value[2];
        
        for (int i = 0; i+1 < ATTEMPTS; i++) {
            cout << "\nGuess #" << i + 1 << ":";
            
            int  guess = guessFunction();
            compareNumbers (guess, value, SIZE);
        }
        cout <<endl<<" You are out of attempts, the number was : "
        << value[0] << value[1] << value[2] <<endl;
        playAgain();
    }
}

//  asks the user for input on whether or not they want to play again.
void playAgain(){
    cout << " Do you want to play again?(y/N or n/N:) ";
    string answerToPlayAgain;
    cin >> answerToPlayAgain;
    
    while (answerToPlayAgain != "Y" && answerToPlayAgain != "y"
           && answerToPlayAgain != "n" && answerToPlayAgain != "n"
           && answerToPlayAgain != "NO" && answerToPlayAgain != "no")
    {
        cout << "Invalid Input, Please enter correct input" <<endl;
        cout << " Do you want to play again?(y/N or n/N:) ";
        cin.clear();
        cin.ignore();
        cin >> answerToPlayAgain;
    }
    if ( answerToPlayAgain == "Y" || answerToPlayAgain == "y")
        playGame();
    else if ( answerToPlayAgain == "N" || answerToPlayAgain == "n")
    {
        exit(0);}
}



//  if inputing no/NO, program is terminated. If number is below 99 or over
//  999, shows error and asks to input again.
int guessFunction(){
    //INPUT is A STRING
    int guess;
    string input;
    cin >> input;
    //cout << input << " is your guess "<<endl;
    
    // Comparing to NO
    if (input == "NO"){
        cout << "Terminating Program"<<endl;
        exit(-1);
    }
    if (input == "no"){
        cout << "Terminating Program"<<endl;
        exit(-1);
    }
    //Convert String to int
    //String is -> input
    //Int is -> guess
    locale loc;
    while (!isdigit(input[0],loc)){
        cout << "Invalid Input, must be a value between 0 - 999 or no" <<endl;
        cin.clear();
        cin.ignore();
        cout << "Guess " << ":";
        cin >> input;
        cout << input << " is your guess "<<endl;
        // Comparing to NO
        if (input == "NO"){
            cout << "Terminating Program"<<endl;
            exit(-1);
        }
        if (input == "no"){
            cout << "Terminating Program"<<endl;
            exit(-1);
        }
    }
    stringstream ss(input);
    ss >> guess;
    //guess = stoi(input); //Does not appear to work on schools computers
    while (guess < 0 || guess > 999 || cin.fail())
    {
        cout << "Invalid Input, must be a value between 0 - 999 or no "<<endl;
        cin.clear();
        cin.ignore();
        cout << "Guess " << ":";
        cin >> guess;
    }
    return guess;
}


