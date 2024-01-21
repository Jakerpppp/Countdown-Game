#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <string>
#include <sstream>
#include <vector>

std::string intToString(const int x) {
    std::ostringstream str;
    str << x;
    return str.str();
}

class CountdownSolution {
  
private:
    std::string solution;
    int value;
    
public:
    
    CountdownSolution() : solution(), value(0) {}
    
    CountdownSolution(const std::string & solutionIn, const int valueIn)
        : solution(solutionIn), value(valueIn) {
    }
    
    const std::string & getSolution() const {
        return solution;
    }
    
    int getValue() const {
        return value;
    }
    
};

// Do not edit above this line

//Takes a reverse polish(Left-Right-Root) expression and returns a double
double evaluateCountdown(std::string expression) 
{
    std::vector<std::string> numSeperated;
    std::vector<double> stack;
    std::string word = "";
    //Gives each number and expression seperated by a space
    for (int i = 0; i < expression.length(); i++){
        if (expression[i] == ' ') {
            numSeperated.push_back(word);
            word = "";
        } else {
            word = word + expression[i];
        }
    }
    numSeperated.push_back(word);

    //Stack Evaluation
    double temp;
    int stackPointer = -1;
    double b;
    double a;
    for (int i= 0; i < numSeperated.size(); i++) {
        if (numSeperated[i] != "+" && numSeperated[i] != "-" && numSeperated[i] != "*" && numSeperated[i] != "/") {
            stack.push_back(std::stod(numSeperated[i]));
            stackPointer++;
        } else {
            a = stack[stackPointer];
            stackPointer--;
            stack.pop_back();
            b = stack[stackPointer];
            stack.pop_back();
            if (numSeperated[i] == "+") {
                temp = b + a;
            }
            if (numSeperated[i] == "-") {
                temp = b - a;
            }
            if (numSeperated[i] == "/") {
                temp = b / a;
            }
            if (numSeperated[i] == "*") {
                temp = b * a;
            }
            stack.push_back(temp);
        }

    }
    return stack[stackPointer];
}

//given a number n, generates every permutation for the operators
std::vector<std::vector<std::string>> repitionsAllowed(std::vector<std::string> tempStore, int n, std::vector<std::string> operators) {
    std::vector<std::vector<std::string>> allPerms;
    if (tempStore.size() == n) {
        allPerms.push_back(tempStore);
        return allPerms;
    }
    else {
        for (std::string op : operators) {
            tempStore.push_back(op);
            std::vector<std::vector<std::string>> permutations = repitionsAllowed(tempStore,n,operators);
            allPerms.insert(allPerms.end(), permutations.begin(), permutations.end());
            tempStore.pop_back();
        }
    }

    return allPerms;

}

//Recrusively swap each number with another until all permutations are found
std::vector<std::vector<std::string>> recursivePermutations(std::vector<std::string> numbers, int index) 
{

    std::vector<std::vector<std::string>> solutions;
    // Base Case
    if (numbers.size() == index) {
        solutions.push_back(numbers);
        return solutions;
    }
    // Recursive Case
    else {
        for (int i = index; i < numbers.size(); i++) {
            std::swap(numbers[index], numbers[i]);
            std::vector<std::vector<std::string>> subPermutations = recursivePermutations(numbers,index + 1);
            solutions.insert(solutions.end(), subPermutations.begin(), subPermutations.end());
            std::swap(numbers[index], numbers[i]);
        }
    }
    return solutions;
}


CountdownSolution solveCountdownProblem(std::vector<int> numbers, int target) 
{   
    std::vector<std::string> operators{"+","-","*","/"};
    std::vector<std::string> tempStore;
    std::vector<std::vector<std::string>> opPermList = repitionsAllowed(tempStore, 5, operators);

    std::vector<std::string> newNumber;
    for (int num : numbers) {
        newNumber.push_back(intToString(num));
    }
    std::vector<std::vector<std::string>> newNumberers = recursivePermutations(newNumber, 0);

    std::string currentClosestExpression = "";
    double currentClosestNumber = -1;
    double currentClosestDifference = 1.0e10;
    std::string currentExpression = "";
    bool expressionFound = false;

   std::vector<std::string> evaluatedExpressions;

   //Refactor this by merging opList and newNumberers together
   //Then solve for everything in this new list

    //6 Digits
    int count = 0;
    for (auto op: opPermList) {
        for (auto newNumbers : newNumberers) {
            double result;
            currentExpression = "";
            currentExpression += newNumbers[0] + " " + newNumbers[1] + " ";
            currentExpression += op[0];
            //2 Digits
            result = evaluateCountdown(currentExpression);
            if (result == target){
                currentClosestExpression = currentExpression;
                return CountdownSolution(currentExpression, target);
            }
            if (abs(target - result) < currentClosestDifference){
                currentClosestNumber = result;
                currentClosestExpression = currentExpression;
                currentClosestDifference = abs(target - result);
            }
            currentExpression += " " + newNumbers[2] + " ";
            currentExpression += op[1];
            //3 digits
            result = evaluateCountdown(currentExpression);
            if (result == target){
                currentClosestExpression = currentExpression;
                return CountdownSolution(currentExpression, target);
            }
            if (abs(target - result) < currentClosestDifference){
                currentClosestNumber = result;
                currentClosestExpression = currentExpression;
                currentClosestDifference = abs(target - result);
            }
            currentExpression += " " + newNumbers[3]+ " ";
            currentExpression += op[2];
            //4 digits
            result = evaluateCountdown(currentExpression);
            if (result == target){
                currentClosestExpression = currentExpression;
                return CountdownSolution(currentExpression, target);
            }
            if (abs(target - result) < currentClosestDifference){
                currentClosestNumber = result;
                currentClosestExpression = currentExpression;
                currentClosestDifference = abs(target - result);
            }
            currentExpression += " " +newNumbers[4]+ " "; 
            currentExpression += op[3];
            //5 digits
            result = evaluateCountdown(currentExpression);
            if (result == target){
                currentClosestExpression = currentExpression;
                return CountdownSolution(currentExpression, target);
            }
            if (abs(target - result) < currentClosestDifference){
                currentClosestNumber = result;
                currentClosestExpression = currentExpression;
                currentClosestDifference = abs(target - result);
            }
            currentExpression += " " +newNumbers[5]+ " ";
            currentExpression += op[4];
            //6 Digits
            result = evaluateCountdown(currentExpression);
            if (result == target){
                currentClosestExpression = currentExpression;
                return CountdownSolution(currentExpression, target);
            }
            if (abs(target - result) < currentClosestDifference){
                currentClosestNumber = result;
                currentClosestExpression = currentExpression;
                currentClosestDifference = abs(target - result);
            }
        }
    }

    return CountdownSolution(currentClosestExpression, currentClosestNumber);    
}




// Do not edit below this line


#endif
