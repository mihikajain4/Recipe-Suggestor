#include "recipesuggestor.h"


int main()
{
    vector<Recipe> recipes;
    ifstream file("recipes.txt");
    string line;

    if (!file.is_open())
    {
        cerr << "Error opening recipes.txt" << endl;
        return 1;
    }
    while(getline(file,line))

        if(!line.empty())
        {
            recipes.push_back(Recipe(line));
        }
    cout<<"Enter your available ingredients(comma separated): ";
    string input;
    getline(cin,input);
    
    vector<string> useringredientsraw;
    stringstream ss(input);
    string ingredient;

    while(getline(ss, ingredient, ','))
    {
        ingredient.erase(remove_if(ingredient.begin(), ingredient.end(), ::isspace), ingredient.end());
        
        Recipe temp("");
        string normalized_ingredient = temp.normalize(ingredient);
        useringredientsraw.push_back(normalized_ingredient);   
    }

    cout<<"\nRecipes you can make with the available ingredients:\n";
    bool foundexact = false;
    for(Recipe& r:recipes)
    {
        if(r.canmake(useringredientsraw))
        {
            cout<<r.name<<endl;
            foundexact=true;
        }
    }
    cout << "\nRecipes you can almost make with 1 missing ingredient:\n";
    bool foundalmost = false;
    for (Recipe& r : recipes) 
    {
        string missing;
        if (r.canmakeonemiss(useringredientsraw, missing)) {
            cout << "You can make " << r.name << " with one more ingredient: " << missing << endl;
            foundalmost = true;
        }
    }

return 0;
}