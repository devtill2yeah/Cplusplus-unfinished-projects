
Vector<float> numbers;
Vector<char> plusIndex;
Vector<char> multIndex;

for (char i = end - 1; i >= start; --i)
{
    if ((eq[i] > 47 && eq[i] < 58) || eq[i] == 46)
    {
        if (tmpc >= MAX_NUMBER_LENGTH)
            return std::nanf("");
        tmp[tmpc++] = eq[i];
    }

    else if (eq[i] == '+')
    {
        if (tmpc > 0)
        {
            reversed = reverseString(tmp, tmpc);
            if (!reversed)
                return std::nanf("");
            plusIndex.push(numbers.push(strtof(reversed, nullptr)));
            free(reversed);
            tmpc = 0;
        }
        //handling wrong or weird inputs
        if (i == end - 1)
        {
            return std::nanf("")
        }
        //these two extra cases are necessary because a calculation like a++--+b is valid and equal to a+b
        else if (plusIndex.size() == 0 || (plusIndex.size() > 0 && numbers.size() != *plusIndex.at(plusIndex.size() - 1)))
        {
            plusIndex.push(numbers.size());
        }
    }

    char *reverseString(const char *string, char length)
    {
        auto tmp = (char *)malloc((length + 1) * sizeof(char));
        if (!tmp)
            return nullptr;
        tmp[length] = '\0';
        for (int i = 0; i < length; ++i)
        {
            tmp[i] = string[length - 1 - i];
        }
        return tmp; //make sure to free the returned pointer
    }

    else if (eq[i] == '-')
    {
        if (tmpc > 0)
        {
            reversed = reverseString(tmp, tmpc);
            if (!reversed)
                return std::nanf("");
            plusIndex.push(numbers.push(-strtof(reversed, nullptr)));
            free(reversed);
            tmpc = 0;
        }
        //handling wrong or weird inputs
        else if (i == end - 1)
        {
            return std::nanf("");
        }
        //these two extra cases are necessary because a calculation like a++--+b is valid and equal to a+b
        else if (plusIndex.size() == 0 || (plusIndex.size() > 0 && numbers.size() != *plusIndex.at(plusIndex.size() - 1)))
        {
            *numbers.at(numbers.size() - 1) *= -1;
            plusIndex.push(numbers.size());
        }
        else
        {
            *numbers.at(numbers.size() - 1) *= -1;
        }
    }

    else if (eq[i] == '*')
    {
        if (tmpc > 0)
        {
            reversed = reverseString(tmp, tmpc);
            if (!reversed)
                return std::nanf("");
            multIndex.push(numbers.push(strtof(reversed, nullptr)));
            free(reversed);
            tmpc = 0;
        }
        else if (i == end - 1 || i == start)
        {
            return std::nanf("");
        }
        //this case is for a*-b. because - is pushed into the plusIndex array we need to remove it.
        else if (plusIndex.size() > 0 && *plusIndex.at(plusIndex.size() - 1) == numbers.size())
        {
            plusIndex.pop();
            multIndex.push(numbers.size());
        }
        else
        {
            multIndex.push(numbers.size());
        }
    }
    else if (eq[i] == '/')
    {
        if (tmpc > 0)
        {
            reversed = reverseString(tmp, tmpc);
            if (!reversed)
                return std::nanf("");
            multIndex.push(numbers.push((float)1 / strtof(reversed, nullptr)));
            free(reversed);
            tmpc = 0;
        }
        else if (i == end - 1 || i == start)
        {
            return std::nanf("");
        }
        //this case is for a/-b. because - is pushed into the plusIndex array we need to remove it.
        else if (plusIndex.size() > 0 && *plusIndex.at(plusIndex.size() - 1) == numbers.size())
        {
            plusIndex.pop();
            (*numbers.at(numbers.size() - 1)) = 1 / (*numbers.at(numbers.size() - 1));
            multIndex.push(numbers.size());
        }
        else
        {
            (*numbers.at(numbers.size() - 1)) = 1 / (*numbers.at(numbers.size() - 1));
            multIndex.push(numbers.size());
        }
    }

    else if (eq[i] == ')')
    {
        //try to find a matching '(':
        char numClosingBrackets = 0;
        char foundMatching = 0;
        for (char j = i - 1; j >= start; --j)
        {
            if (eq[j] == ')')
                ++numClosingBrackets;
            else if (eq[j] == '(' && numClosingBrackets > 0)
                --numClosingBrackets;
            else if (eq[j] == '(' && numClosingBrackets == 0)
            {
                //matching '(' found
                if (!foundMatching)
                {
                    numbers.push(solve(eq, j + 1, i, vars));
                    i = j; //skip the part between () in parsing
                    foundMatching = 1;
                }
            }
        }
        if (!foundMatching)
            return std::nanf("");
    }
}

if (tmpc > 0)
{
    reversed = reverseString(tmp, tmpc);
    if (!reversed)
        return std::nanf("");
    numbers.push(strtof(reversed, nullptr));
    free(reversed);
    tmpc = 0;
}

if (numbers.size() == 0)
    return std::nanf("")
else if (multIndex.size() > 0)
{
    for (char i = multIndex.size() - 1; i >= 0; --i)
    {
        //check if '*' is associated with two numbers:
        if (*multIndex.at(i) >= numbers.size())
            return std::nanf("");
        (*numbers.at(*multIndex.at(i) - 1)) *= (*numbers.at(*multIndex.at(i)));
    }
}

float result = *numbers.at(0)
for (char i = 0; i < plusIndex.size(); ++i)
{
    result += *numbers.at(*plusIndex.at(i));
}
return result;
}

else if (eq[i] == '^')
{
    if (tmpc > 0)
    {
        reversed = reverseString(tmp, tmpc);
        if (!reversed)
            return std::nanf("");
        multIndex.push(numbers.push(strtof(reversed, nullptr)));
        powIndex.push(numbers.size());
        free(reversed);
        tmpc = 0;
    }
    else if (i == end - 1 || i == start)
    {
        return std::nanf("");
    }
    else
    {
        multIndex.push(numbers.size());
        powIndex.push(numbers.size());
    }
}

if (powIndex.size() > 0)
{
    for (char i = powIndex.size() - 1; i >= 0; --i)
    {
        //check if '*' is associated with two numbers:
        if (*powIndex.at(i) >= numbers.size())
            return std::nanf("");
        (*numbers.at(*powIndex.at(i) - 1)) = pow((*numbers.at(*powIndex.at(i))), (*numbers.at(*powIndex.at(i) - 1)));
        (*numbers.at(*powIndex.at(i))) = 1;
    }
}

else
{
    //unary operators:
    //trig functions work with rad not deg!
    if (i > 2 && eq[i] == 'n' && eq[i - 1] == 'i' && eq[i - 2] == 's' && eq[i - 3] == 'a')
    {
        if (numbers.size())
            *numbers.at(numbers.size() - 1) = asin(*numbers.at(numbers.size() - 1));
        i -= 3;
        if (plusIndex.size() > 0 && *plusIndex.at(plusIndex.size() - 1) == numbers.size())
        {
            plusIndex.pop();
        }
    }
    else if (i > 1 && eq[i] == 'n' && eq[i - 1] == 'i' && eq[i - 2] == 's')
    {
        if (numbers.size())
            *numbers.at(numbers.size() - 1) = sin(*numbers.at(numbers.size() - 1));
        i -= 2;
        if (plusIndex.size() > 0 && *plusIndex.at(plusIndex.size() - 1) == numbers.size())
        {
            plusIndex.pop();
        }
    }
    else
        return std::nanf("");
}

//constants
if (i > 0 && eq[i] == 'i' && eq[i - 1] == 'p')
{
    if (numbers.size())
        numbers.push(M_PI);
    i -= 1;
}

float solve(const char *eq, char start, char end, const float *vars = nullptr);

else if (i > 1 && eq[i] == 's' && eq[i - 1] == 'n' && eq[i - 2] == 'a')
{
    if (vars)
        numbers.push(vars[0]);
    else
        numbers.push(std::nanf(""));
    i -= 2;
}

#ifndef SOLVE_VECTOR_H
#define SOLVE_VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_ARRAY_SIZE 10
#define DEFAULT_INCREMENT 10
#define MAX_NUMBER_LENGTH 10

#include "solve.h"
#include "vector.h"

template <typename T>
class Vector
{
    T *data;
    char length;
    char currentIndex;

public:
    Vector();
    ~Vector();
    char resize(char size = 0);
    T *at(int index);
    char push(T value); //return size() after adding new element
    char pop();
    char size(); //return number of elements in data array
    T *getData();
    char insert(T value, char index);
    char remove(char startIndex, char endIndex); //start and endindex will also be removed! return number of elements after removal
    char clear();
};

template <typename T>
char Vector<T>::clear()
{
    currentIndex = 0;
    //check if array exists. if not use malloc
    if (!data)
    {
        data = (T *)malloc(DEFAULT_ARRAY_SIZE * sizeof(T));
    }
    else
    {
        data = (T *)realloc(data, DEFAULT_ARRAY_SIZE * sizeof(T));
    }
    if (!data)
    {
        length = 0;
        return 0;
    }
    else
    {
        length = DEFAULT_ARRAY_SIZE;
        return length;
    }
}

template <typename T>
char Vector<T>::insert(T value, char index)
{
    if (currentIndex >= length)
    {
        if (!resize(length + DEFAULT_INCREMENT))
            return 0;
    }
    if (index != currentIndex && index >= 0 && index < currentIndex)
    {
        memmove(at(index + 1), at(index), sizeof(T) * (currentIndex - index));
        data[index] = value;
    }
    else if (index == currentIndex)
        data[index] = value;

    return ++currentIndex;
}

template <typename T>
char Vector<T>::remove(char startIndex, char endIndex)
{
    if (startIndex >= 0 && startIndex < size() && endIndex >= startIndex && endIndex < size())
    {

        //we do not overwrite values that have index greater than currentIndex! we memcpy all elements after endindex to starrtindex
        memmove(at(startIndex), at(endIndex), sizeof(T) * (currentIndex - 1 - endIndex));

        currentIndex -= (endIndex - startIndex) + 1; //adjust number of elements counter
    }
    return currentIndex;
}

template <typename T>
T *Vector<T>::getData()
{
    return data;
}

template <typename T>
Vector<T>::Vector() : currentIndex(0)
{
    data = (T *)malloc(DEFAULT_ARRAY_SIZE * sizeof(T));
    if (!data)
        length = 0;
    else
        length = DEFAULT_ARRAY_SIZE;
}
template <typename T>
Vector<T>::~Vector()
{
    free(data);
}
template <typename T>
T *Vector<T>::at(int index)
{
    if (index < 0 || index >= length)
        return NULL;
    return &data[index];
}
template <typename T>
char Vector<T>::resize(char size)
{
    //check if array exists. if not use malloc
    if (!data)
    {
        data = (T *)malloc(DEFAULT_ARRAY_SIZE * sizeof(T));
    }
    else
    {
        data = (T *)realloc(data, size * sizeof(T));
    }
    if (!data)
    {
        length = 0;
        return 0;
    }
    else
    {
        length = size;
        return size;
    }
}

template <typename T>
char Vector<T>::size()
{
    return currentIndex;
}

template <typename T>
char Vector<T>::push(T value)
{
    if (currentIndex >= length)
    {
        if (!resize(length + DEFAULT_INCREMENT))
            return 0;
    }

    data[currentIndex] = value;
    return ++currentIndex;
}

template <typename T>
char Vector<T>::pop()
{
    if (currentIndex > 0)
    {
        return --currentIndex;
    }
    return 0;
}

#endif //SOLVE_VECTOR_H

#ifndef SOLVE_SOLVE_H
#define SOLVE_SOLVE_H

#include <math.h>

float solve(const char *eq, char start, char end, const float *vars = nullptr);

char *reverseString(const char *string, char length);

#endif //SOLVE_SOLVE_H

#include <math.h>

char *reverseString(const char *string, char length)
{
    auto tmp = (char *)malloc((length + 1) * sizeof(char));
    if (!tmp)
        return nullptr;

    tmp[length] = '\0';
    for (int i = 0; i < length; ++i)
    {
        tmp[i] = string[length - 1 - i];
    }
    return tmp; //make sure to free the returned pointer
}

float solve(const char *eq, char start, char end, const float *vars)
{
    //check if eq is valid
    //if not, return NaN
    if (end <= start)
        return NAN;

    //create new arrays to store numbers and operators
    Vector<float> numbers;
    Vector<char> plusIndex;
    Vector<char> multIndex;
    Vector<char> powIndex;

    auto tmp = (char *)malloc(MAX_NUMBER_LENGTH * sizeof(char));
    if (!tmp)
        return NAN;
    char tmpc = 0;
    char *reversed;

    //parse string eq
    //parsing from right to left allows us to
    //e.g. multiply the number to the right of binary operators with -1 for subtraction
    for (char i = end - 1; i >= start; --i)
    {
        //check if current char is number or decimalpoint '.' using ascii
        if ((eq[i] > 47 && eq[i] < 58) || eq[i] == 46)
        {
            if (tmpc >= MAX_NUMBER_LENGTH)
                return NAN;

            tmp[tmpc++] = eq[i];
        }
        //if current char is + or - add tmp to numbers array if it is not empty
        //if it is empty: ignore if current char is '+' and mult the last number in numbers with -1 if it is '-'.
        //->do not add to plusIndex array
        else if (eq[i] == '+')
        {
            if (tmpc > 0)
            {
                reversed = reverseString(tmp, tmpc);
                if (!reversed)
                    return NAN;
                plusIndex.push(numbers.push(strtod(reversed, nullptr)));
                free(reversed);
                tmpc = 0;
            }
            //handling wrong or weird inputs
            else if (i == end - 1)
            {
                return NAN;
            }
            //these two extra cases are necessary because a calculation like a++--+b is valid and equal to a+b
            else if (plusIndex.size() == 0 || (plusIndex.size() > 0 && numbers.size() != *plusIndex.at(
                                                                                             plusIndex.size() - 1)))
            {
                plusIndex.push(numbers.size());
            }
        }
        else if (eq[i] == '-')
        {
            if (tmpc > 0)
            {
                reversed = reverseString(tmp, tmpc);
                if (!reversed)
                    return NAN;
                plusIndex.push(numbers.push(-strtod(reversed, nullptr)));
                free(reversed);
                tmpc = 0;
            }
            //handling wrong or weird inputs
            else if (i == end - 1)
            {
                return NAN;
            }
            //these two extra cases are necessary because a calculation like a++--+b is valid and equal to a+b
            else if (plusIndex.size() == 0 || (plusIndex.size() > 0 && numbers.size() != *plusIndex.at(
                                                                                             plusIndex.size() - 1)))
            {
                *numbers.at(numbers.size() - 1) *= -1;
                plusIndex.push(numbers.size());
            }
            else
            {
                *numbers.at(numbers.size() - 1) *= -1;
            }
        }
        //check for multiplication
        else if (eq[i] == '*')
        {
            if (tmpc > 0)
            {
                reversed = reverseString(tmp, tmpc);
                if (!reversed)
                    return NAN;
                multIndex.push(numbers.push(strtod(reversed, nullptr)));
                free(reversed);
                tmpc = 0;
            }
            else if (i == end - 1 || i == start)
            {
                return NAN;
            }
            //this case is for a*-b. because - is pushed into the plusIndex array we need to remove it.
            else if (plusIndex.size() > 0 && *plusIndex.at(plusIndex.size() - 1) == numbers.size())
            {
                plusIndex.pop();
                multIndex.push(numbers.size());
            }
            else
            {
                multIndex.push(numbers.size());
            }
        }
        else if (eq[i] == '/')
        {
            if (tmpc > 0)
            {
                reversed = reverseString(tmp, tmpc);
                if (!reversed)
                    return NAN;
                multIndex.push(numbers.push((float)1 / strtod(reversed, nullptr)));
                free(reversed);
                tmpc = 0;
            }
            else if (i == end - 1 || i == start)
            {
                return NAN;
            }
            //this case is for a/-b. because - is pushed into the plusIndex array we need to remove it.
            else if (plusIndex.size() > 0 && *plusIndex.at(plusIndex.size() - 1) == numbers.size())
            {
                plusIndex.pop();
                (*numbers.at(numbers.size() - 1)) = 1 / (*numbers.at(numbers.size() - 1));
                multIndex.push(numbers.size());
            }
            else
            {
                (*numbers.at(numbers.size() - 1)) = 1 / (*numbers.at(numbers.size() - 1));
                multIndex.push(numbers.size());
            }
        }
        else if (eq[i] == '^')
        {
            if (tmpc > 0)
            {
                reversed = reverseString(tmp, tmpc);
                if (!reversed)
                    return NAN;
                multIndex.push(numbers.push(strtod(reversed, nullptr)));
                powIndex.push(numbers.size());
                free(reversed);
                tmpc = 0;
            }
            else if (i == end - 1 || i == start)
            {
                return NAN;
            } //this case is for a/-b. because - is pushed into the plusIndex array we need to remove it.
            else if (plusIndex.size() > 0 && *plusIndex.at(plusIndex.size() - 1) == numbers.size())
            {
                plusIndex.pop();
                multIndex.push(numbers.size());
                powIndex.push(numbers.size());
            }
            else
            {
                multIndex.push(numbers.size());
                powIndex.push(numbers.size());
            }
        }
        //if we find a closing bracket, try to find a matching opening bracket and call solve recursively
        else if (eq[i] == ')')
        {
            //try to find a matching '(':
            char numClosingBrackets = 0;
            char foundMatching = 0;
            for (char j = i - 1; j >= start; --j)
            {
                if (eq[j] == ')')
                    ++numClosingBrackets;
                else if (eq[j] == '(' && numClosingBrackets > 0)
                    --numClosingBrackets;
                else if (eq[j] == '(' && numClosingBrackets == 0)
                {
                    //matching '(' found
                    if (!foundMatching)
                    {
                        numbers.push(solve(eq, j + 1, i, vars));
                        i = j; //skip the part between () in parsing
                        foundMatching = 1;
                    }
                }
            }
            if (!foundMatching)
                return NAN;
        }
        else
        {
            //unary operators:
            //trig functions work with rad not deg!
            if (i > 2 && eq[i] == 'n' && eq[i - 1] == 'i' && eq[i - 2] == 's' && eq[i - 3] == 'a')
            {
                if (numbers.size())
                    *numbers.at(numbers.size() - 1) = asin(*numbers.at(numbers.size() - 1));
                i -= 3;
                if (plusIndex.size() > 0 && *plusIndex.at(plusIndex.size() - 1) == numbers.size())
                {
                    plusIndex.pop();
                }
            }
            else if (i > 1 && eq[i] == 'n' && eq[i - 1] == 'i' && eq[i - 2] == 's')
            {
                if (numbers.size())
                    *numbers.at(numbers.size() - 1) = sin(*numbers.at(numbers.size() - 1));
                i -= 2;
                if (plusIndex.size() > 0 && *plusIndex.at(plusIndex.size() - 1) == numbers.size())
                {
                    plusIndex.pop();
                }
            }
            else if (i > 2 && eq[i] == 's' && eq[i - 1] == 'o' && eq[i - 2] == 'c' && eq[i - 3] == 'a')
            {
                if (numbers.size())
                    *numbers.at(numbers.size() - 1) = acos(*numbers.at(numbers.size() - 1));
                i -= 3;
                if (plusIndex.size() > 0 && *plusIndex.at(plusIndex.size() - 1) == numbers.size())
                {
                    plusIndex.pop();
                }
            }
            else if (i > 1 && eq[i] == 's' && eq[i - 1] == 'o' && eq[i - 2] == 'c')
            {
                if (numbers.size())
                    *numbers.at(numbers.size() - 1) = cos(*numbers.at(numbers.size() - 1));
                i -= 2;
                if (plusIndex.size() > 0 && *plusIndex.at(plusIndex.size() - 1) == numbers.size())
                {
                    plusIndex.pop();
                }
            }
            else if (i > 2 && eq[i] == 'n' && eq[i - 1] == 'a' && eq[i - 2] == 't' && eq[i - 3] == 'a')
            {
                if (numbers.size())
                    *numbers.at(numbers.size() - 1) = atan(*numbers.at(numbers.size() - 1));
                i -= 3;
                if (plusIndex.size() > 0 && *plusIndex.at(plusIndex.size() - 1) == numbers.size())
                {
                    plusIndex.pop();
                }
            }
            else if (i > 1 && eq[i] == 'n' && eq[i - 1] == 'a' && eq[i - 2] == 't')
            {
                if (numbers.size())
                    *numbers.at(numbers.size() - 1) = tan(*numbers.at(numbers.size() - 1));
                i -= 2;
                if (plusIndex.size() > 0 && *plusIndex.at(plusIndex.size() - 1) == numbers.size())
                {
                    plusIndex.pop();
                }
            }
            else if (i > 0 && eq[i] == 'n' && eq[i - 1] == 'l')
            {
                if (numbers.size())
                    *numbers.at(numbers.size() - 1) = log(*numbers.at(numbers.size() - 1));
                i -= 3;
                if (plusIndex.size() > 0 && *plusIndex.at(plusIndex.size() - 1) == numbers.size())
                {
                    plusIndex.pop();
                }
            }
            else if (i > 1 && eq[i] == 'g' && eq[i - 1] == 'o' && eq[i - 2] == 'l')
            {
                if (numbers.size())
                    *numbers.at(numbers.size() - 1) = log10(*numbers.at(numbers.size() - 1));
                i -= 2;
                if (plusIndex.size() > 0 && *plusIndex.at(plusIndex.size() - 1) == numbers.size())
                {
                    plusIndex.pop();
                }
            }

            //constants
            else if (i > 0 && eq[i] == 'i' && eq[i - 1] == 'p')
            {
                numbers.push(M_PI);
                i -= 1;
            }
            else if (eq[i] == 'e')
            {
                numbers.push(M_E);
            }
            else if (i > 1 && eq[i] == 's' && eq[i - 1] == 'n' && eq[i - 2] == 'a')
            {
                if (vars)
                    numbers.push(vars[0]);
                else
                    numbers.push(NAN);
                i -= 2;
            }
            else
                return NAN;
        }
    }

    //push to numbers array one last time
    if (tmpc > 0)
    {
        reversed = reverseString(tmp, tmpc);
        if (!reversed)
            return NAN;
        numbers.push(strtod(reversed, nullptr));
        free(reversed);
        tmpc = 0;
    }

    //parsing eq is done.
    //start computing result:
    //rules:
    //brackets first (already done in parsing)
    //mult and div before add and sub
    //equal priority operations from left to right
    //we do not need to worry about the last point as we are replacing all divisions (a/b) with a*(1/b)
    //and all subtractions (a+b) with (a+(-b))
    //+ and * are commutative.

    if (numbers.size() == 0)
        return NAN;

    //we start with power a^b
    if (powIndex.size() > 0)
    {
        for (char i = powIndex.size() - 1; i >= 0; --i)
        {
            //check if '*' is associated with two numbers:
            if (*powIndex.at(i) >= numbers.size())
                return NAN;
            (*numbers.at(*powIndex.at(i) - 1)) = pow((*numbers.at(*powIndex.at(i))), (*numbers.at(*powIndex.at(i) - 1)));
            (*numbers.at(*powIndex.at(i))) = 1;
        }
    }

    //as we parsed eq from right to left, we have to go through the arrays from right to left
    //in to do calculations from left to right :)

    //because * is commutative we calculate the result for the multiplication from right to left
    //this makes it easier as we can store the result of a*b in a
    //e.g. a*(b*c)*d:
    //first the () was done in the parsing step so it is now a*e*d
    // we compute e*d=:f and replace e with the result f
    //this results in a*f*d. however we will ignore d and calculate a*f and replace a with the result.
    if (multIndex.size() > 0)
    {
        for (char i = multIndex.size() - 1; i >= 0; --i)
        {
            //check if '*' is associated with two numbers:
            if (*multIndex.at(i) >= numbers.size())
                return NAN;
            (*numbers.at(*multIndex.at(i) - 1)) *= (*numbers.at(*multIndex.at(i)));
        }
    }

    //add the remaining numbers and return the result
    //example: a+b*c+d
    //based on the previous step we know that the result of b*c will be stored in b
    //need to ignore c. this can be done using the value stored in the next plusIndex.
    //sum the first number and all numbers that are to the right of a + symbol.
    //these numbers have an index of *plusIndex.at()-1

    float result = *numbers.at(0);
    if (numbers.size() > 1)
    { //if numbers.size == 1 we have a leading +-. we ignore it.
        for (char i = 0; i < plusIndex.size(); ++i)
        {
            result += *numbers.at(*plusIndex.at(i));
        }
    }
    free(tmp);

    return result;
}



