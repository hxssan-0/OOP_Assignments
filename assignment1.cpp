#include <iostream>
using namespace std;

// NOTE: IF YOU DON'T ATTEMPT A QUESTION, DO NOT DELETE ITS PROTOTYPE GIVEN BELOW. LEAVE IT AS IT IS. 
// YOU ARE NOT ALLOWED TO CHANGE ANY PROTOTYPE WHATSOEVER.
// DOING ANY OF THE ABOVE WILL LEAD TO YOUR TEST CASES NOT RUNNING
// AND SO ZERO MARKS WILL BE AWARDED EVEN IF YOU ATTEMPTED OTHER QUESTIONS CORRECTLY.
// ONLY EDIT THE CODE WITHIN THE {} BRACKETS OF EACH FUNCTION.
// GOOD LUCK! (onnn scene)

/*________________________ Question 1: MorseCode ________________________*/

char* convertToMorseCode(char* input) {
    //creating a 2D character array which will hold the morse code for each letter
        //45 morse codes given in the table, with maximum length of 6 (7 to include null)
        //1 space for slash
        //0-25 indices for letters A-Z, 26-35 for digits 0-9, 36 for period, 37 for comma,
        //38 for question mark, 39 for apostrophe, 40 for exclamation, 41 for slash,
        //42 for opening bracket, 43 for closing bracket, 44 for ampersand 
    char morseCodes[46][7] = { //Letters
                              ".-", "-...","-.-.","-..",".","..-.","--.","....","..",
                              ".---","-.-",".-..","--","-.","---",".--.","--.-",".-.",
                              "...","-","..-","...-",".--","-..-","-.--","--..",
                              //Digits
                              "-----",".----","..---","...--","....-",".....","-....",
                              "--...","---..","----.",
                              //Symbols
                              ".-.-.-","--..--","..--..",".----.","-.-.--","-..-.",
                              "-.--.","-.--.-",".-...",
                              //slash
                              "/" };

    //Dynamically creating a character array to hold the result
    char* output = new char[501];
    //converting all letters of the input to uppercase,to not make the if conditions
    //redundant by adding a bunch of OR operators
    int i = -1;
    while (input[++i] != '\0') {
        if (input[i] >= 'a' && input[i] <= 'z') {
            input[i] -= 32;
        }
    }
    //looping through the whole input
    int outIndex = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        int morseCode;
        //mapping letters
        if (input[i] >= 'A' && input[i] <= 'Z') {
            morseCode = input[i] - 'A';
        }
        //mapping digits
        else if (input[i] >= '0' && input[i] <= '9') {
            morseCode = input[i] - 22;
        }
        //mapping symbols
        else if (input[i] == '.')    morseCode = 36;
        else if (input[i] == ',')    morseCode = 37;
        else if (input[i] == '?')    morseCode = 38;
        else if (input[i] == '\'')   morseCode = 39;
        else if (input[i] == '!')    morseCode = 40;
        else if (input[i] == '/')    morseCode = 41;
        else if (input[i] == '(')    morseCode = 42;
        else if (input[i] == ')')    morseCode = 43;
        else if (input[i] == '&')    morseCode = 44;
        else if (input[i] == ' ')    morseCode = 45;
        //using the morseCode index to assign the code to the output
        int j = 0;
        while (morseCodes[morseCode][j] != '\0') {
            output[outIndex++] = morseCodes[morseCode][j++];
        }
        //adding a space after a letter
        output[outIndex++] = ' ';
    }
    //adding a null character at the end
    output[outIndex - 1] = '\0';

    return output;
}

char* convertToString(char* morse) {
    //using the table again
    char morseCodes[46][7] = { //Letters
                         ".-", "-...","-.-.","-..",".","..-.","--.","....","..",
                         ".---","-.-",".-..","--","-.","---",".--.","--.-",".-.",
                         "...","-","..-","...-",".--","-..-","-.--","--..",
                         //Digits
                         "-----",".----","..---","...--","....-",".....","-....",
                         "--...","---..","----.",
                         //Symbols
                         ".-.-.-","--..--","..--..",".----.","-.-.--","-..-.",
                         "-.--.","-.--.-",".-...",
                         //slash
                         "/" };
    //output array
    char* output = new char[1001];
    //looping through the input string
    int i = 0;
    int outIndex = 0;
    while (morse[i] != '\0') {
        //continuing incase there is a slash
        if (morse[i] == '/') {
            output[outIndex++] = ' ';
            i++;
            continue;
        }
        //will hold the morse code letter temporarily
        char buffer[7] = "";
        //looping till space is encountered
        int j = 0;
        while (j < 6 && morse[i] != ' ' && morse[i] != '\0') {
            buffer[j++] = morse[i++];
        }
        //null terminating the buffer
        buffer[j] = '\0';
        //looping through the whole morse code table
        int morseCode = -1;
        for (int k = 0; k < 45; k++) {
            int len = 0;
            bool matchFound = 1;
            while (morseCodes[k][len] != '\0')  len++;
            int l = 0;
            while (morseCodes[k][l] != '\0' && buffer[l] != '\0') {
                if (morseCodes[k][l] != buffer[l]) {
                    matchFound = 0;
                    break;
                }
                l++;
            }
            if (matchFound && morseCodes[k][l] == '\0' && buffer[l] == '\0') {
                morseCode = k;
                break;
            }
        }
        //letters
        if (morseCode >= 0 && morseCode <= 25) {
            output[outIndex++] = morseCode + 'a';
        }
        //digits
        else if (morseCode >= 26 && morseCode <= 35) {
            output[outIndex++] = morseCode + 22;
        }
        //symbols
        else if (morseCode == 37)
            output[outIndex++] = '.';
        else if (morseCode == 38)
            output[outIndex++] = '?';
        else if (morseCode == 39)
            output[outIndex++] = '\'';
        else if (morseCode == 40)
            output[outIndex++] = '!';
        else if (morseCode == 41)
            output[outIndex++] = '/';
        else if (morseCode == 42)
            output[outIndex++] = '(';
        else if (morseCode == 43)
            output[outIndex++] = ')';
        else if (morseCode == 44)
            output[outIndex++] = '&';

        i++;
    }
    //null terminating the output
    output[outIndex] = '\0';
    return output;
}

/*________________________ Question 2: Big Integer ________________________*/

//helper function for Q2
bool isZero(char* str)
{
    int len = 0, zeroCount = 0;
    while (str[len] != '\0') {
        if (str[len] == '0')
            zeroCount++;
        len++;
    }
    if (len == zeroCount)
        return true;
    else
        return false;
}

char* additionOfBigInteger(char* Num1, char* Num2) {
    int len1 = 0, len2 = 0;
    //calculating the lengths as well as applying validation check
    while (Num1[len1] != '\0') {
        if (Num1[len1] >= '0' && Num1[len1] <= '9')
            len1++;
        else
            return nullptr;
    }
    while (Num2[len2] != '\0') {
        if (Num2[len2] >= '0' && Num2[len2] <= '9')
            len2++;
        else
            return nullptr;
    }
    //creating the output array
    char* sum = new char[501];
    //if both are zero
    if (isZero(Num1) && isZero(Num2)) {
        sum = "0";
        return sum;
    }
    //creating the necessary variables
    int result;
    int carry = 0;
    int digit;
    int sumIndex = 0;
    //looping through both strings to find the sum
    for (int i = len1 - 1, j = len2 - 1; i >= 0 || j >= 0; i--, j--) {
        //handling cases of equal lengths
        if (len1 == len2) {
            result = (Num1[i] - '0') + (Num2[j] - '0') + carry;
        }
        //now handling cases of unequal length
        else {
            //if the first number is smaller and has been traversed
            if (i < 0) {
                result = (Num2[j] - '0') + carry;
            }
            //if the second number is smaller and has been traversed
            else if (j < 0) {
                result = (Num1[i] - '0') + carry;
            }
            //if either one still has not been fully traversed
            else if (i >= 0 && j >= 0) {
                result = (Num1[i] - '0') + (Num2[j] - '0') + carry;
            }
        }
        //now calculating the relevant parameters
        digit = result % 10;
        result /= 10;
        carry = result;
        //appending it to the sum array
        sum[sumIndex++] = (digit + '0');
    }
    //if both numbers have been traversed but still a carry is generated
    if (carry > 0) {
        sum[sumIndex++] = carry + '0';
    }
    //null terminating it
    sum[sumIndex] = '\0';
    //now checking if there are leading zeroes
    while (sum[sumIndex - 1] == '0') {
        sum[sumIndex - 1] = '\0';
        sumIndex--;
    }
    //reversing it
    for (int i = 0, j = sumIndex - 1; i < j; i++, j--) {
        char temp = sum[i];
        sum[i] = sum[j];
        sum[j] = temp;
    }

    return sum;
}
char* subtractionOfBigInteger(char* Num1, char* Num2) {
    //error handling
    if (!Num1 || !Num2)
        return nullptr;
    //length calculation + input validation
    int len1 = 0, len2 = 0;
    while (Num1[len1] != '\0') {
        if (!(Num1[len1] >= '0' && Num1[len1] <= '9'))
            return nullptr;
        len1++;
    }
    while (Num2[len2] != '\0') {
        if (!(Num2[len2] >= '0' && Num2[len2] <= '9'))
            return nullptr;
        len2++;
    }
    //necessary arrays
    char* output = new char[501];
    //finding out greater number
    //calculating max length
    int len = (len1 >= len2) ? len1 : len2;
    bool Num1Greater = 0, mismatchFound = 0;
    if (len1 > len2) {
        Num1Greater = 1;
        mismatchFound = 1;
    }
    else if (len1 < len2) {
        Num1Greater = 0;
        mismatchFound = 1;
    }
    else if (len1 == len2) {
        for (int i = 0; i < len1; i++) {
            if (Num1[i] > Num2[i]) {
                Num1Greater = 1;
                mismatchFound = 1;
                break;
            }
            else if (Num1[i] < Num2[i]) {
                Num1Greater = 0;
                mismatchFound = 1;
                break;
            }
        }
    }
    //if both are equal
    if (!mismatchFound) {
        output = "0";
        return output;
    }
    //making mutable arrays and performing padding
    char* num1 = new char[501];
    char* num2 = new char[501];
    //only do padding if the lengths are unequal
    if (len1 != len2) {
        //incase len1 is greater
        if (len1 > len2) {
            for (int i = 0; i < len1; i++) {
                num1[i] = Num1[i];
            }
            num1[len1] = '\0';
            int zeroPadding = len1 - len2;
            for (int i = 0; i < zeroPadding; i++) {
                num2[i] = '0';
            }
            for (int i = zeroPadding; i < len1; i++) {
                num2[i] = Num2[i - zeroPadding];
            }
            num2[len1] = '\0';
        }
        //incase len2 is greater
        else if (len1 < len2) {
            for (int i = 0; i < len2; i++) {
                num1[i] = Num2[i];
            }
            num1[len2] = '\0';
            int zeroPadding = len2 - len1;
            for (int i = 0; i < zeroPadding; i++) {
                num2[i] = '0';
            }
            for (int i = zeroPadding; i < len2; i++) {
                num2[i] = Num1[i - zeroPadding];
            }
            num2[len2] = '\0';
        }
    }
    //if lengths are equal
    if (len1 == len2) {
        if (Num1Greater) {
            for (int i = 0; i < len; i++) {
                num1[i] = Num1[i];
                num2[i] = Num2[i];
            }
            num1[len] = '\0';
            num2[len] = '\0';
        }
        else {
            for (int i = 0; i < len; i++) {
                num1[i] = Num2[i];
                num2[i] = Num1[i];
            }
            num1[len] = '\0';
            num2[len] = '\0';
        }
    }
    //now performing the subtraction
    int outIndex = 0;
    for (int i = len - 1; i >= 0; i--) {
        //if the digits are equal
        if (num1[i] == num2[i]) {
            output[outIndex++] = '0';
            continue;
        }
        //if the digit of num1 is lesser than the digit of num2, then borrow must be taken
        if (num1[i] < num2[i]) {
            int k = 1;
            //if the previous digit is zero then borrow can't be taken
            //looping till a non zero digit is found
            while (num1[i - k] == '0') {
                k++;
            }
            //taking the borrow
            num1[i - k] -= 1;
            //setting all the zeroes in between to 9
            for (int l = k - 1; l > 0; l--) {
                num1[i - l] = '9';
            }
            //calculating the digit
            int digit = (num1[i] - '0') + 10 - (num2[i] - '0');
            output[outIndex++] = digit + '0';
        }
        else if (num1[i] > num2[i]) {
            int digit = (num1[i] - '0') - (num2[i] - '0');
            output[outIndex++] = digit + '0';
        }
    }
    //removing leading zeroes
    while (output[outIndex - 1] == '0') {
        outIndex--;
    }
    //adding a negative sign if needed
    if (!Num1Greater) {
        output[outIndex++] = '-';
    }
    output[outIndex] = '\0';
    //reversing it
    for (int i = 0, j = outIndex - 1; i < j; i++, j--) {
        char temp = output[i];
        output[i] = output[j];
        output[j] = temp;
    }
    return output;
}
char* multiplicationOfBigInteger(char* Num1, char* Num2) {
    //calculating the lengths to find out which one is greater, also adding validation
    int len1 = 0, len2 = 0;
    while (Num1[len1] != '\0') {
        if (Num1[len1] >= '0' && Num1[len1] <= '9')
            len1++;
        else
            return nullptr;
    }
    while (Num2[len2] != '\0') {
        if (Num2[len2] >= '0' && Num2[len2] <= '9')
            len2++;
        else
            return nullptr;
    }
    char* num1 = new char[501];
    char* num2 = new char[501];
    if (len1 >= len2) {
        for (int i = 0; i < len1; i++)
            num1[i] = Num1[i];
        for (int i = 0; i < len2; i++)
            num2[i] = Num2[i];
    }
    else {
        for (int i = 0; i < len2; i++)
            num1[i] = Num2[i];
        for (int i = 0; i < len1; i++)
            num2[i] = Num1[i];
    }
    //dynamic result arrays
    char* result1 = new char[1001];
    char* result2 = new char[1001];
    //if either is zero
    if (isZero(Num1) || isZero(Num2)) {
        result1 = "0";
        return result1;
    }
    //making a zero array
    if (len1 < len2) {
        for (int i = 0; i < len2; i++) {
            result1[i] = '0';
        }
        result1[len2] = '\0';
    }
    else {
        for (int i = 0; i < len1; i++) {
            result1[i] = '0';
        }
        result1[len1] = '\0';
    }
    //now doing the multiplication
    for (int i = len2 - 1; i >= 0; i--) {
        //appending zeroes at the end
        int in = 0;
        for (int k = 0; k < len2 - 1 - i; k++) {
            result2[in++] = '0';
        }
        //multiplying the current digit of Num2 with each digit of Num1
        int result, digit, carry = 0;
        for (int j = len1 - 1; j >= 0; j--) {
            result = (num2[i] - '0') * (num1[j] - '0') + carry;
            digit = result % 10;
            result /= 10;
            carry = result;
            result2[in++] = (digit + '0');
        }
        if (carry > 0)
            result2[in++] = (carry + '0');
        result2[in] = '\0';
        //reversing result2
        for (int p1 = 0, p2 = in - 1; p1 < p2; p1++, p2--) {
            char temp = result2[p1];
            result2[p1] = result2[p2];
            result2[p2] = temp;
        }
        result1 = additionOfBigInteger(result1, result2);
    }
    return result1;
}
char* factorialOfBigInteger(char* Num1) {
    char* result = '\0';
    return result;
    /*
    if (!Num1)
        return nullptr;
    //calculating length + input validation
    int len = 0;
    while (Num1[len] != '\0') {
        if (Num1[len] >= '0' && Num1[len] <= '9')
            len++;
        else
            return nullptr;
    }
    //output array
    char* result = new char[501];
    strcpy(result, "1");
    //if it is zero, then return 1
    if (isZero(Num1)) {
        return result;
    }
    //temp array which will hold Num1
    char* num1 = new char[501];
    for (int i = 0; i < len; i++) {
        num1[i] = Num1[i];
    }
    num1[len] = '\0';

    //calculating the factorial using the subtraction and multiplication functions
    while (!isZero(num1)) {
        char* mul = multiplicationOfBigInteger(num1, subtractionOfBigInteger(num1, "1"));
        result = multiplicationOfBigInteger(result, mul);
        num1 = subtractionOfBigInteger(num1, "1");
    }
    return result; */
}

/*________________________ Question 3: Text Analysis ________________________*/
//helper function
bool strcmp(char* str1, char* str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2)
            return false;
        str1++;
        str2++;
    }
    return true;
}

//strcpy function
char* strcpy(char* str1, char* str2)
{
    if (!str1 || !str2)
        return nullptr;
    char* temp_str1 = str1;
    while (*str2 != '\0') {
        *str1 = *str2;
        str1++;
        str2++;
    }
    *str1 = '\0';
    return temp_str1;
}
void removePunctuation(char* str) {
    //looping through input string
    int i = 0;
    int tempIndex = 0;
    while (str[i] != '\0') {
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] == ' ') || (str[i] >= '0' && str[i] <= '9')) {
            str[tempIndex++] = str[i];
        }
        i++;
    }
    //null terminating it
    str[tempIndex] = '\0';
}

void countLetters(char* str, int*& count, char*& letters, int& size) {
    //turning the string lowercase
    int len = 0;
    while (str[len] != '\0') {
        if (str[len] >= 'A' && str[len] <= 'Z')
            str[len] += 32;
        len++;
    }
    bool processed = 0;
    //calculating size
    char temp[101];
    int tempSize = 0;
    for (int i = 0; i < len; i++) {
        processed = 0;
        //checking if the letter at the current index has been processed or not
        for (int j = 0; j < tempSize; j++) {
            if (str[i] == temp[j]) {
                processed = 1;
                break;
            }
        }
        //going to the next iteration if it has been processed
        if (processed)
            continue;
        //adding the current letter to the letters array
        if ((str[i] >= 'a' && str[i] <= 'z') || str[i] == ' ') {
            temp[tempSize++] = str[i];
        }
    }
    temp[tempSize] = '\0';
    size = tempSize;
    //now dynamically allocating arrays
    letters = new char[size + 1];
    count = new int[size];
    for (int i = 0; i < size; i++) {
        letters[i] = temp[i];
    }
    letters[size] = '\0';
    //now looping through letters and counting the occurrence of each letter
    int countIndex = 0;
    for (int i = 0; i < size; i++) {
        int occurrenceCount = 0;
        for (int j = 0; j < len; j++) {
            if (letters[i] == str[j])
                occurrenceCount++;
        }
        //adding it to the count array
        count[countIndex++] = occurrenceCount;
    }
}

void countWords(char* str, int*& array, char**& words, int& numberOfWords) {
    //turning the string lowercase
    int len = 0;
    while (str[len] != '\0') {
        if (str[len] >= 'A' && str[len] <= 'Z')
            str[len] += 32;
        len++;
    }
    //getting all the words
    bool processed = 0;
    char temp[100][101] = { "" };
    int tempWords = 0;
    for (int i = 0; i < len; i++) {
        processed = 0;
        char buffer[40] = "";
        int bufferIndex = 0;
        //capturing the word
        while (str[i] != ' ' && str[i] != '\0') {
            if (str[i] >= 'a' && str[i] <= 'z')
                buffer[bufferIndex++] = str[i];
            i++;
        }
        buffer[bufferIndex] = '\0';
        //now comparing to see if it has been processed or not
        for (int j = 0; j < tempWords; j++) {
            if (strcmp(buffer, temp[j])) {
                processed = 1;
                break;
            }
        }
        if (processed)
            continue;
        //adding to the temp words array
        strcpy(temp[tempWords++], buffer);
    }
    numberOfWords = tempWords;
    //dynamicallyt allocating arrays
    array = new int[numberOfWords];
    words = new char* [numberOfWords];
    for (int i = 0; i < numberOfWords; i++) {
        words[i] = new char[40];
    }
    //copying into actual words array
    for (int i = 0; i < numberOfWords; i++) {
        strcpy(words[i], temp[i]);
    }
    //now making the count array
    for (int i = 0; i < numberOfWords; i++) {
        int occurrenceCount = 0;
        for (int j = 0; j < len; j++) {
            char buffer[40] = "";
            int in = 0;
            while (str[j] != '\0' && str[j] != ' ') {
                buffer[in++] = str[j++];
            }
            buffer[in] = '\0';
            //now comparing
            if (strcmp(words[i], buffer)) {
                occurrenceCount++;
            }
        }
        array[i] = occurrenceCount;
    }
}


/*________________________ Question 4: Recursion ________________________*/

bool isprimeNumber(int n, int div = 2) {
    //all the numbers below 2 are not prime
    if (n < 2)
        return 0;
    //2 is a unique prime number
    if (n == 2)
        return 1;
    //number is divisible by something other than itself or 1
    if (n % div == 0)
        return 0;
    //base case means that all numbers have been checked and 0 still hasn't been returned
    if (div * div > n)
        return 1;
    return isprimeNumber(n, div + 1);
}
//helper function
void traverseRow(int* p, int column, int& evenSum, int& oddSum)
{
    //base case
    if (column < 0)
        return;
    //calculating the sums by traversing the cols
    if (p[column] % 2 == 0)
        evenSum += p[column];
    else
        oddSum += p[column];
    //recursive call
    traverseRow(p, column - 1, evenSum, oddSum);
}
void sum(int** array, int row, int column, int& evenSum, int& oddSum) {
    if (row < 0)
        return;
    //traversing each row will require a helper function
    int* p = array[row];
    traverseRow(p, column, evenSum, oddSum);
    //recursive call
    sum(array, row - 1, column, evenSum, oddSum);
}

void printSpaces(int n)
{
    if (n == 0)
        return;
    cout << " ";
    printSpaces(n - 1);
}

void printSymbol(int n)
{
    if (n == 0)
        return;
    cout << "*";
    printSymbol(n - 1);
}

void PrintPattern1(int n, int current, int max) {
    //base case
    if (max == 0)
        return;
    //printing the upper half
    printSpaces(max - 1);
    printSymbol(n - max + current);
    cout << endl;
    //recursive call for upper half
    PrintPattern1(n, current + 1, max - 1);

    //printing the lower half
    printSpaces(max - 1);
    if (max >= 2) {
        printSymbol(n - max + current);
        cout << endl;
    }
}

void printSymbol1(int n)
{
    if (n == 0)
        return;
    cout << "* ";
    printSymbol1(n - 1);
}

void printSymbol2(int n)
{
    if (n == 0)
        return;
    cout << " *";
    printSymbol2(n - 1);
}
void PrintPattern2(int n, int current, int max) {
    //base case
    if (max == 0)
        return;
    //printing spaces
    printSpaces(n + max - current - 1);
    //bar
    cout << '|';
    //spaces
    printSpaces(n + max - current);
    //symbol
    printSymbol1(n - max + current - 1);
    //bar
    cout << '|';
    //symbol
    printSymbol2(n - max + current - 1);
    //spaces
    printSpaces(n + max - current);
    //bar
    cout << '|';
    cout << '\n';
    //recursive call
    PrintPattern2(n, current + 1, max - 1);

    //lower half
    //printing spaces
    if (max >= 2) {
        printSpaces(n + max - current - 1);
        //bar
        cout << '|';
        //spaces
        printSpaces(n + max - current);
        //symbol
        printSymbol1(n - max + current - 1);
        //bar
        cout << '|';
        //symbol
        printSymbol2(n - max + current - 1);
        //spaces
        printSpaces(n + max - current);
        //bar
        cout << '|';
        cout << '\n';
    }
}

/*________________ Question 5: Maze Traversal ________________*/

bool solveMaze(int** maze, int t_row, int t_column, int rows, int cols, int thisX = 0, int thisY = 0) {
    //after having already solved the same question differently in pf, and doing this after
    //practicing backtracking with N queens and sudoku solver, i just had to combine both logics

    //this is my base case which will return true if the target cell has been reached
    if (thisX == t_row && thisY == t_column) {
    //the output was not marking the target cell as 2 so i had to handle it here
        maze[thisX][thisY] = 2;
        return true;
    }
    //going in the DRUL order (down, right, up, left)
    //just bounds checking and also checking if the cell can be travelled to
    //first checking down
    if (thisX + 1 < rows && maze[thisX + 1][thisY] == 1) {
        //marking the current cell as having been visited
        maze[thisX][thisY] = 2;
        //recursivly travelling to the next cell
        if (solveMaze(maze, t_row, t_column, rows, cols, thisX + 1, thisY)) {
            return true;
        }
        //backtracking
        maze[thisX][thisY] = 1;
    }
    //all the other directions follow the same logic as before
    //checking right
    if (thisY + 1 < cols && maze[thisX][thisY + 1] == 1) {
        maze[thisX][thisY] = 2;
        if (solveMaze(maze, t_row, t_column, rows, cols, thisX, thisY + 1)) {
            return true;
        }
        maze[thisX][thisY] = 1;
    }
    //checking up
    if (thisX - 1 >= 0 && maze[thisX - 1][thisY] == 1) {
        maze[thisX][thisY] = 2;
        if (solveMaze(maze, t_row, t_column, rows, cols, thisX - 1, thisY)) {
            return true;
        }
        maze[thisX][thisY] = 1;
    }
    //checking left
    if (thisY - 1 >= 0 && maze[thisX][thisY - 1] == 1) {
        maze[thisX][thisY] = 2;
        if (solveMaze(maze, t_row, t_column, rows, cols, thisX, thisY - 1)) {
            return true;
        }
        maze[thisX][thisY] = 1;
    }
    //incase none of those paths worked out, returning false to indicate that no path can be found
    return false;
}

/*____________________ Question 6: SUDOKU ____________________*/

bool canPlace(int** board, int row, int col)
{
    //checking the col
    for (int i = 0; i < 9; i++) {
        if ((board[i][col] == board[row][col]) && (i != row))
            return false;
    }
    //checking the row
    for (int i = 0; i < 9; i++) {
        if ((board[row][i] == board[row][col]) && (i != col))
            return false;
    }
    //checking the 3x3 subgrid
    int r = (row / 3) * 3;
    int c = (col / 3) * 3;
    for (int i = r; i < r + 3; i++) {
        for (int j = c; j < c + 3; j++) {
            if ((board[i][j] == board[row][col]) && (i != row || j != col))
                return false;
        }
    }
    return true;
}
bool solveSudoku(int**, int, int);
bool placeNumber(int** board, int row, int col, int num = 1)
{
    //if all the numbers have been tried but none work, i must move back to the previous number
    if (num > 9) {
        //although i am handling backtracking below where i set numbers to zero again,
        //the issue was with 9, since this base case would just return false without
        //resetting 9 to 0, and it gave me wrong output
        board[row][col] = 0;
        //self explanatory
        return false;
    }
    //placing the current number at that position
    //i could have also just checked the number itself without placing it first in
    //the board, but i had already made my canPlace function logic before and didn't 
    //want to change it
    board[row][col] = num;
    //now calling my canPlace function
    if (canPlace(board, row, col)) {
        //moving to the next column recursively if it was a valid placement
        //this will keep going in recursive depth until it solves, or an invalid placement was found
        //in which case, it will backtrack as handled below
        if (solveSudoku(board, row, col + 1)) {
            return true;
            //backtracking
            board[row][col] = 0;
        }
    }
    //if the previous number wasn't valid, checking the next one
    return placeNumber(board, row, col, num + 1);
}

bool solveSudoku(int** board, int row = 0, int col = 0) {
    //the very first step i took after attempting the N queens problem was to identify the base case
        //if all rows have been modified, it means that a solution exists, so i will return true
    if (row == 9)
        return true;
    //when solving N queens, i kept the row and column traversal functions separate
    //because my solution wasn't working when both were embedded withib, but for sudoku
    //i found it to work fine without doing that
    //if all the columns have been traversed, my code will recursively move to the next row
    if (col == 9)
        return solveSudoku(board, row + 1, 0);
    //if the current element is non zero, i.e non empty, recursively moving to the next column
    if (board[row][col] != 0)
        return solveSudoku(board, row, col + 1);
    //my helper function will try all numbers from 1-9, to check their validity
    //i got confused here, how to try all numbers without a loop, i implemented the helper
    //function recursively with the rest of the logic embedded here, but my dry runs of the
    //recursive tree weren't working out. so i converted the loop logic to recursion, such that
    //the for loop line here is the function call, and the logic within the hypothetical for loop
    //is now within that separate function.
    //this fixed the issue i was having where my sudoku would never solve
    return placeNumber(board, row, col, 1);
}


