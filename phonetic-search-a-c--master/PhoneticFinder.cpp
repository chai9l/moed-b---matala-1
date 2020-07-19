#include "PhoneticFinder.hpp"
#include <iostream>
#include <string>


using namespace std;

// worker function for checking all the possible chars switches in a word.
int asciiCheck(string current, string temp, int i, char a , char b , char c) {
    if(current.at(i) == a || current.at(i) == a-32) {
        if(temp.at(i) == b || temp.at(i) == b-32)
            return 1;
    }
    if(current.at(i) == b || current.at(i) == b-32) {
        if(temp.at(i) == a || temp.at(i) == a-32)
            return 1;
    }
    if(c != '#') {
        if (current.at(i) == b || current.at(i) == b - 32) {
            if (temp.at(i) == c || temp.at(i) == c - 32)
                return 1;
        }
        if (current.at(i) == c || current.at(i) == c - 32) {
            if (temp.at(i) == b || temp.at(i) == b - 32)
                return 1;
        }
        if (current.at(i) == c || current.at(i) == c - 32) {
            if (temp.at(i) == a || temp.at(i) == a - 32)
                return 1;
        }
        if (current.at(i) == a || current.at(i) == a - 32) {
            if (temp.at(i) == c || temp.at(i) == c - 32)
                return 1;
        }
    }

    return 0;
}

//worker function that uses asciiCheck function as a base, it checks if a certain case happens
//and if it does it returns 1.
int asciiSearch(string current, string temp, int i) {

    int sum = 0;

    //if the current's letter at 'i' is uppercase and on temp's 'i' is lowercase
    if((current.at(i) + 32) == temp.at(i)) {
        return 1;
    }

    //if the temp's letter at 'i' is uppercase and on current's 'i' is lowercase.
    if((temp.at(i) + 32) == current.at(i)) {
        return 1;
    }

    //checking all the possible cases described in the problem.
    // # is used only for the case of between 2 letters, (a shorter code).
    sum += asciiCheck(current,temp,i,'v','w','#');
    sum += asciiCheck(current,temp,i,'g','j','#');
    sum += asciiCheck(current,temp,i,'s','z','#');
    sum += asciiCheck(current,temp,i,'d','t','#');
    sum += asciiCheck(current,temp,i,'o','u','#');
    sum += asciiCheck(current,temp,i,'i','y','#');
    sum += asciiCheck(current,temp,i,'b','f','p');
    sum += asciiCheck(current,temp,i,'c','k','q');
    if(sum == 1)
        return 1;
    else
        return 0;
}

// Manager function that uses asciiSearch if the word we're looking for has the same length
// and if it's not the exact word, for an example (dont , donb).
int check(string temp, string current) {

    int count = 0;

    //if lengths are not equal the current word is not the word we're looking for.
    if(temp.length() != current.length()) {
        return -1;
    }

    else {
        for(int i = 0 ; i < current.length() ;i++) {
            //checks if the current word is the same as the temp word letter by letter.
            if(current.at(i) == temp.at(i)) {
                count++;
                if(count == current.length())
                    return 1;
            }
            //if the word is not the same we're checking the given word via asciiSearch
            //meaning if its one of the possible cases we're returning 1.
            else {
                count += asciiSearch(current,temp,i);
                if(count == current.length())
                    return 1;
            }
        }
    }
    //we're returning 0 if the current word is not relate-able to the temp word.
    return 0;
}

string phonetic::find(string text, string current) {

    if(current.empty())
        return "the word is empty";

    string temp = ""; //used to copy word by word from the given text.
    int getErr = 0; //used to use the check functions and get a numerical value from the check functions.
    int saveIndex = 0; //saving index, used as a reference to the index after we found a space.

    for(int i = 0 ; i < text.length() ; i++) {

        //when reaching a space in the given text we're sending the temp word to our check functions
        //if its a relate-able word we're returning 1 else we're clearing the temp word and keep on going
        //until the next space.
        if(text.at(i) == ' ') {
            getErr = check(temp, current);
            saveIndex = i + 1;
            if(getErr == 1) {
                return temp;
            }
            else
                temp.clear();
        }

        //checking the last word in the given text, meaning we're using the last time we saw a space
        //then saving the index afterwards, and then using the location we found to fill in a new temp word
        //and check if it's relate-able or not.
        else if(i == text.length()-1) {
            temp.clear();
            for(int j = saveIndex ; j < text.length() ; j++)
                temp += text.at(j);
            getErr = check(temp, current);
            if(getErr == 1) {
                return temp;
            }
        }

        //filling temp until we reach a space in the given text.
        else {
            temp += text.at(i);
        }
    }
    //if word was not found we're throwing an exception.
    return "this word doesn't exist in the text";
}