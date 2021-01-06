#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <vector>

using namespace std;

//this function is used to see every dish belonging to a user specified category
void seeDishes(){

    string category, trash;

    ifstream file("recipeRandomizerList.txt");

    //asks the user to input a category
    while(category != "meat" && category != "vegetable" && category != "soup"){
        cout << endl << "Would you like to see meat, vegetable, or soup dishes?: ";
        cin >> category;
        getline(cin, trash);
        if(category != "meat" && category != "vegetable" && category != "soup"){
            cout << endl << "Invalid category! Try again." << endl;
        }
    }

    string line, line2, line3;
    vector<string> meatDishes;
    vector<string> vegetableDishes;
    vector<string> soupDishes;
    int endRead;

    //prints out all the names of the dishes of the user specified category
    if(category == "meat"){
        while(getline(file, line)){
            if(line == "Meat Dishes"){
                while(getline(file, line2) && line2 != "."){
                    endRead = line2.find('{'); //read each line only up to the '{' char, so the ingredients are not included in the result
                    line3 = line2.substr(0, endRead); //create a substring of only the name of the dish from the line
                    meatDishes.push_back(line3); //add the substring to the end of the vector
                }
            }
        }
        for(string i: meatDishes){ //print each element of the vector
            cout << "\t" << i << " " << endl;
        }
    } else if(category == "vegetable"){
        while(getline(file, line)){
            if(line == "Vegetable Dishes"){
                while(getline(file, line2) && line2 != "."){
                    endRead = line2.find('{');
                    line3 = line2.substr(0, endRead);
                    vegetableDishes.push_back(line3);
                }
            }
        }
        for(string i: vegetableDishes){
            cout << "\t" << i << " " << endl;
        }
    } else if(category == "soup"){
         while(getline(file, line)){
            if(line == "Soup Dishes"){
                while(getline(file, line2) && line2 != "."){
                    endRead = line2.find('{');
                    line3 = line2.substr(0, endRead);
                    soupDishes.push_back(line3);
                }
            }
        }
        for(string i: soupDishes){
            cout << "\t" << i << " " << endl;
        }
    }

    file.close();
}

//this function is used to add new recipes to the .txt file
void addRecipe(){

    fstream file("recipeRandomizerList.txt");

    string line, line2;
    vector<string> meatDishes;
    vector<string> vegetableDishes;
    vector<string> soupDishes;

    //read each recipe into a vector based on their category (meat, vegetable, or soup)
    while(getline(file, line)){
        if(line == "Meat Dishes"){ //add all the lines between the category heading and the '.' into the vector
            while(getline(file, line2) && line2 != "."){
                meatDishes.push_back(line2);
            }
            meatDishes.pop_back(); //remove the extra empty line from end of the vector
        } else if(line == "Vegetable Dishes"){
            while(getline(file, line2) && line2 != "."){
                vegetableDishes.push_back(line2);
            }
            vegetableDishes.pop_back();
        } else if(line == "Soup Dishes"){
            while(getline(file, line2) && line2 != "."){
                soupDishes.push_back(line2);
            }
            soupDishes.pop_back();
        }
    }

    file.close();

    string choice, newDish, newName, findName, ingredients, category, trash;
    int recipeFound;
    bool recipeFoundBool = false;

    cout << endl << "Do you want to add or delete a recipe?: ";
    cin >> choice;
    getline(cin, trash);

    //add or deletes a dish based on the user's input
    if(choice == "add"){
        //user enters the category of the new dish they wish to add
        while(category != "meat" && category != "vegetable" && category != "soup"){
            cout << endl << "Is this a meat, vegetable, or soup dish?: ";
            cin >> category;
            getline(cin, trash);
            if(category != "meat" && category != "vegetable" && category != "soup"){
                cout << endl << "Invalid category! Try again." << endl;
            }
        }

        cout << endl << "Enter recipe name: ";
        getline(cin, newName);

        cout << "Enter ingredients: ";
        getline(cin, ingredients);

        //creates a new string with the user specified dish name and ingredients
        newDish = newName + " {" + ingredients + "}";

        //add the new dish to the end of the vector based on category specified by the user
        if(category == "meat"){
            meatDishes.push_back(newDish);
        } else if(category == "vegetable"){
            vegetableDishes.push_back(newDish);
        } else if(category == "soup"){
            soupDishes.push_back(newDish);
        }

        cout << endl << "Dish successfully added." << endl << endl;
    } else if(choice == "delete"){
        //user enters the category of the new dish they wish to delete
        while(category != "meat" && category != "vegetable" && category != "soup"){
            cout << endl << "Is this a meat, vegetable, or soup dish?: ";
            cin >> category;
            getline(cin, trash);
            if(category != "meat" && category != "vegetable" && category != "soup"){
                cout << endl << "Invalid category! Try again." << endl;
            }
        }

        cout << endl << "Enter recipe name: ";
        getline(cin, findName);

        //delete the specified dish from the vector of the category specified by the user
        if(category == "meat"){
            for(int i = 0; i < meatDishes.size(); i++){
                //if the element at index 'i' contains the name of the dish the user inputed as a substring, remove the element from the vector
                recipeFound = meatDishes[i].find(findName);
                if(recipeFound != string::npos){
                        recipeFoundBool = true; //when the name is found in the vector, set the bool to 'true', so the error message will not print
                        meatDishes.erase(meatDishes.begin() + i);
                        cout << endl << "Dish successfully deleted." << endl << endl;
                }
            }
            //if the name was never found in the vector, print an error message
            if(recipeFoundBool == false){
                    cout << endl << "Dish not found!" << endl << endl;
            }
        } else if(category == "vegetable"){
            for(int i = 0; i < vegetableDishes.size(); i++){
                recipeFound = vegetableDishes[i].find(findName);
                if(recipeFound != string::npos){
                        recipeFoundBool = true;
                        vegetableDishes.erase(vegetableDishes.begin() + i);
                        cout << endl << "Dish successfully deleted." << endl << endl;
                }
            }
            if(recipeFoundBool == false){
                    cout << endl << "Dish not found!" << endl << endl;
            }
        } else if(category == "soup"){
            for(int i = 0; i < soupDishes.size(); i++){
                recipeFound = soupDishes[i].find(findName);
                if(recipeFound != string::npos){
                        recipeFoundBool = true;
                        soupDishes.erase(soupDishes.begin() + i);
                        cout << endl << "Dish successfully deleted." << endl << endl;
                }
            }
            if(recipeFoundBool == false){
                    cout << endl << "Dish not found!" << endl << endl;
            }
        }
    } else if (choice != "add" && choice != "delete"){
        cout << endl << "Invalid input!" << endl << endl;
    }

    //reopens and clears all text in the .txt file so that the updated version can take its place
    file.open("recipeRandomizerList.txt", ios::out | ios::trunc);

    //rewrite the .txt file with the new dish added
    file << "Meat Dishes" << endl;
    for(string i: meatDishes){
        file << i << " " << endl;
    }
    file << endl << "." << endl << endl;

    file << "Vegetable Dishes" << endl;
    for(string i: vegetableDishes){
        file << i << " " << endl;
    }
    file << endl << "." << endl << endl;

    file << "Soup Dishes" << endl;
    for(string i: soupDishes){
        file << i << " " << endl;
    }
    file << endl << "." << endl;

    file.close();
}

//this function is used to find the ingredients of a recipe searched by the user
void findIngredients(){

    string recipeSearch;

    //asks the user to input a recipe name
    ifstream file("recipeRandomizerList.txt");
    cout << endl << "Enter recipe name: ";
    getline(cin, recipeSearch);

    string line, ingredients;
    int recipeFound, startRead, endRead;
    bool recipeFoundBool = false;

    //searches for the recipe and then its ingredients
    while(getline(file, line)){ //read through the .txt file line by line
        recipeFound = line.find(recipeSearch); //checks to see if the searched name exists as a substring in the line
        if (recipeFound != string::npos){
            recipeFoundBool = true;
            startRead = line.find('{');
            endRead = line.find('}');
            ingredients = line.substr(startRead + 1, endRead - startRead - 1); //create a substring of the ingredients listed inside the brackets
            cout << endl << "\t" <<"Ingredients: " << ingredients << endl << endl;
        }
    }

    //if the searched recipe does not exist in the .txt file, print an error message
    if(recipeFoundBool == false){
        cout << endl << "Error: Recipe not found!" << endl << endl;
    }

    file.close();
}

//this function prints out a random dish from each category to create a randomized meal
void randomRecipe(){

    ifstream file("recipeRandomizerList.txt");

    string line, line2;
    vector<string> meatDishes;
    vector<string> vegetableDishes;
    vector<string> soupDishes;

    //read each recipe into a vector based on their category (meat, vegetable, or soup)
    while(getline(file, line)){
        if(line == "Meat Dishes"){ //add all the lines between the category heading and the '.' into the vector
            while(getline(file, line2) && line2 != "."){
                meatDishes.push_back(line2);
            }
            meatDishes.pop_back(); //remove the extra empty line from end of the vector
            meatDishes.erase(meatDishes.begin()); //remove the extra empty line from beginning of the vector
        } else if(line == "Vegetable Dishes"){
            while(getline(file, line2) && line2 != "."){
                vegetableDishes.push_back(line2);
            }
            vegetableDishes.pop_back();
            vegetableDishes.erase(vegetableDishes.begin());
        } else if(line == "Soup Dishes"){
            while(getline(file, line2) && line2 != "."){
                soupDishes.push_back(line2);
            }
            soupDishes.pop_back();
            soupDishes.erase(soupDishes.begin());
        }
    }

    file.close();

    //time is seed so the dishes can be different each time the function executes
    srand(time(0));

    //print out a random dish from each category by selecting a random element from each vector
    cout << endl << "Today's dishes will be: " << endl;
    cout << endl << "\t" << meatDishes[rand() % ((meatDishes.size() - 1) + 1)] << endl;
    cout << "\t" << vegetableDishes[rand() % ((vegetableDishes.size() - 1) + 1)] << endl;
    cout << "\t" << soupDishes[rand() % ((soupDishes.size() - 1) + 1)] << endl << endl;
}

int main(){

    int choice;
    string trash;

    cout << "Welcome!" << endl << endl << "What would you like to do?" << endl << "1 to randomize" << endl << "2 to see dishes" << endl << "3 to see ingredients" << endl << "4 add or delete a dish" << endl << "5 to exit program" << endl;
    cin >> choice;
    getline(cin, trash); //necessary because a getline() after a cin is problematic; cin creates an extra '\n' which is not wanted.

    //calls a function based on the user's choice
    while(choice != 5){
        if(choice == 1){
            randomRecipe();
            cout << "What would you like to do?" << endl << "1 to randomize" << endl << "2 to see dishes" << endl << "3 to see ingredients" << endl << "4 add or delete a dish" << endl << "5 to exit program" << endl;
            cin >> choice;
            getline(cin, trash);
        } else if(choice == 2){
            seeDishes();
            cout << "What would you like to do?" << endl << "1 to randomize" << endl << "2 to see dishes" << endl << "3 to see ingredients" << endl << "4 add or delete a dish" << endl << "5 to exit program" << endl;
            cin >> choice;
            getline(cin, trash);
        } else if(choice == 3){
            findIngredients();
            cout << "What would you like to do?" << endl << "1 to randomize" << endl << "2 to see dishes" << endl << "3 to see ingredients" << endl << "4 add or delete a dish" << endl << "5 to exit program" << endl;
            cin >> choice;
            getline(cin, trash);
        } else if(choice == 4){
            addRecipe();
            cout << "What would you like to do?" << endl << "1 to randomize" << endl << "2 to see dishes" << endl << "3 to see ingredients" << endl << "4 add or delete a dish" << endl << "5 to exit program" << endl;
            cin >> choice;
            getline(cin, trash);
        } else{
            cout << endl << "Invalid input, please try again: ";
            cin >> choice;
        }
    }

    cout << endl << "Press 'Enter' to exit program" << endl;

    return 0;
}

/* test .txt file content

Meat Dishes

Steamed Chicken {chicken, salt, pepper}
Fried Fish {fish, salty, pepper, spices}
Steak {beef, salt, pepper}

.

Vegetable Dishes

Broccoli {broccoli, salt, pepper}
Cabbage {cabbage, soy sauce, pepper}
Celery {celery, salt, pepper}

.

Soup Dishes

Dumpling Soup {meat, wrap, salt}
Vegetable Soup {carrots, potatoes, tomatoes}
Spinach Soup {spinach, salt}

.

*/
