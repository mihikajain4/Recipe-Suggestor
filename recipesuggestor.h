#ifndef RECIPE_SUGGESTOR_H
#define RECIPE_SUGGESTOR_H

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Recipe
{
    public:
        string name;
        vector<string> ingredients;

        Recipe(string recipeline)
        {
            parserecipe(recipeline);
        }

        void parserecipe(string line)
        {
            size_t colon= line.find(":");
            name= line.substr(0, colon);
            string ingredients_str= line.substr(colon + 1);

            stringstream ss(ingredients_str);
            string ingredient;
            while(getline(ss, ingredient, ','))
            {
                ingredient.erase(remove_if(ingredient.begin(), ingredient.end(), ::isspace), ingredient.end());
                ingredients.push_back(normalize(ingredient));
            }
        }
        string normalize(string ingredient)
        {
            transform(ingredient.begin(), ingredient.end(), ingredient.begin(), ::tolower);
            
            static unordered_map<string,string> replacements={
                //plural
                {"tomatoes", "tomato"},
                {"potatoes", "potato"},
                {"onions", "onion"},
                {"eggs", "egg"},
                {"carrots", "carrot"},
                {"cucumbers", "cucumber"},
                {"chillies", "chilli"},
                {"cherries", "cherry"},
                {"apples", "apple"},
                {"bananas", "banana"},
                {"garlics", "garlic"},
                {"breads", "bread"},
                {"cheeses", "cheese"},
                {"mushrooms", "mushroom"},
                {"peppers", "pepper"},
                {"beans", "bean"},
                {"grapes", "grape"},
                {"leaves", "leaf"},
                
                //similar types
                {"oliveoil", "oil"},
                {"vegetableoil", "oil"},
                {"mustardoil", "oil"},
                {"sunfloweroil", "oil"},
                {"butter", "oil"},  
                {"ghee", "oil"},  
                {"brownrice", "rice"},
                {"whiterice", "rice"},
                {"greentea", "tea"},
                {"blacktea", "tea"},
                {"milktea", "tea"},
                {"greenchilli", "chilli"},
                {"redchilli", "chilli"},
                {"bellpepper", "pepper"},
                {"capsicum", "pepper"},
                {"cilantro", "coriander"},
                {"corianderleaves", "coriander"},
                {"corianderleaf", "coriander"},
                {"springonion", "onion"},
                {"scallions", "onion"},
                {"mozzarella", "cheese"},
                {"cheddar", "cheese"},
                {"mayonnaise", "sauce"},
                {"ketchup", "sauce"},
                {"soy sauce", "sauce"},
                {"sugarcane", "sugar"},
                {"jaggery", "sugar"},
                {"tomatoketchup", "sauce"},
                {"chocolatesyrup", "chocolate"},
                {"darkchocolate", "chocolate"},
                {"tapioca","sabudana"},
                {"sago","sabudana"},
                {"tapiocapearls","sabudana"},
                {"sagopearls","sabudana"},
                {"tapiocastarch","sabudana"},
                {"coconutmilk","milk"},
                {"almondmilk","milk"},
                {"soymilk","milk"},
                {"oatmilk","milk"},
                {"cashew milk","milk"},
                {"rice milk","milk"},
                {"coconutwater","water"},
                {"springwater","water"},
                {"mineralwater","water"},
                {"sparklingwater","water"},
            };

            string key =ingredient;
            key.erase(remove(key.begin(), key.end(), ' '), key.end()); // remove spaces

            if(replacements.find(key)!= replacements.end())
            {
                return replacements[key];
            }
            else
            {
                return ingredient;
            }
        }

        bool canmake(const vector<string>& useringredients_raw) 
        {
            vector<string> normalized_user_ingredients;
            for (const string& ing : useringredients_raw) 
            {
                normalized_user_ingredients.push_back(normalize(ing));
            }

            for (const string& required : ingredients) 
            {
                if (find(normalized_user_ingredients.begin(), normalized_user_ingredients.end(), required) == normalized_user_ingredients.end()) 
                {
                    return false;
                }
            }
            return true;
        }

        bool canmakeonemiss(const vector<string>& useringredients_raw, string& missingingredient_out) 
        {
            vector<string> normalized_user_ingredients;
            for (const string& ing : useringredients_raw) 
            {
                normalized_user_ingredients.push_back(normalize(ing));
            }

            int missingcount = 0;
            string missing;

            for (const string& required : ingredients) 
            {
                if (find(normalized_user_ingredients.begin(), normalized_user_ingredients.end(), required) == normalized_user_ingredients.end()) {
                    missingcount++;
                    missing = required;
                    if (missingcount > 1) return false;
                }
            }

            if (missingcount == 1) 
            {
                missingingredient_out = missing;
                return true;
            }

            return false;
        }

};

#endif