#include <iostream>
#include <string>
#include <vector>
using namespace std;

/* NOTE:
Some Comments might not make sense because
what they referred to could've been removed
if you see a comment that makes no sense just ignore it */

string reverse(string reversant) //Not sure if necessary, but makes it tidier and i don't need to use string.insert
{
    string reversed = "";
    for (int i = reversant.length() - 1; i >= 0; --i)
    {
        reversed += reversant[i];
    }
    return reversed;
}

void str_add(string &add_to, string added) //add_to is the string that will be added to, i.e it is changed, but the added one stays the same
{
    int holder = 0;
    int column_sum = 0; //Sum for each column of numbers
    string result = "";
    string uncut_column_sum = "";
    string rvrs_shortest = reverse(add_to.length() <= added.length() ? add_to : added); //If their length is the same this is n1
    string rvrs_longest = reverse(add_to.length() > added.length() ? add_to : added); //If their length is the same this is n2
    int len_diff = rvrs_longest.length() - rvrs_shortest.length(); //So that the size is constant in the for loop, as i want the len diff of the original ones, not with the one with "shortest" having more zeros, that would break the code
    for (int i = 0; i + 1 <= len_diff; ++i) //If one is shorter, i need it to be filled with 0s. Not necessary, but tidier.
    {
        rvrs_shortest += "0";
    }
    for (int j = 0; j + 2 <= rvrs_longest.length(); ++j) //Minus 2 because the last column doesn't go here. Doesn't matter whether i say rvrs_longest.length() or rvrs_shortest.length()
    {
        uncut_column_sum = to_string((rvrs_shortest[j] - '0') + (rvrs_longest[j] - '0') + holder);
        column_sum = uncut_column_sum[uncut_column_sum.length() - 1] - '0';
        holder = stoi(uncut_column_sum) / 10; //Not a float, so it'll save the digits before the last one
        result += to_string(column_sum);
    }
    column_sum = (rvrs_shortest[rvrs_shortest.length() - 1] - '0') + (rvrs_longest[rvrs_longest.length() - 1] - '0') + holder; //rvrs_longest and rvrs_shortest are the same
    result += reverse(to_string(column_sum)); //reverse because it could be larger than 2 digits
    add_to = reverse(result);
}
void str_subtract(string &subtract_from, string subtracted) //Doesn't work on negative numbers, but we don't need them anyway (Note: you can still subtract larger from smaller, getting a negative integer, but we don't need that either)
{
    int column_sum = 0; //Sum for each column of numbers
    int group; //Sometimes i need to subtract a 2 digit number from 1 digit
    string result = "";
    string rvrs_shortest = reverse(subtract_from.length() <= subtracted.length() ? subtract_from : subtracted); //If their length is the same this is subtract_from
    string rvrs_longest = reverse(subtract_from.length() > subtracted.length() ? subtract_from : subtracted); //If their length is the same this is subtraced
    int len_diff = rvrs_longest.length() - rvrs_shortest.length(); //So that the size is constant in the for loop, as i want the len diff of the original ones, not with the one with "shortest" having more zeros, that would break the code
    for (int i = 0; i + 1 <= len_diff; ++i) //If one is shorter, i need it to be filled with 0s. Not necessary, but tidier.
    {
        rvrs_shortest += "0";
    }
    string rvrs_subtract_from = subtract_from.length() <= subtracted.length() ? rvrs_shortest : rvrs_longest;
    string rvrs_subtracted = subtract_from.length() > subtracted.length() ? rvrs_shortest : rvrs_longest;
    for (int j = 0; j + 2 <= rvrs_longest.length(); ++j)
    {
        if((rvrs_subtract_from[j] - '0') < (rvrs_subtracted[j] - '0'))
        {
            for (int k = j + 1; k + 1 <= rvrs_subtract_from.length(); ++k)
            {
                if (rvrs_subtract_from[k] - '0' != 0)
                {
                    group = stoi("1" + to_string(rvrs_subtract_from[j] - '0'));
                    column_sum = group - (rvrs_subtracted[j] - '0'); //Even though we have no holder here, this is still needed, without it we get a invalid_argument when it calls stoi() on the empty string
                    rvrs_subtract_from[k] = (rvrs_subtract_from[k] - '0' - 1) + '0'; //We use - '0' for char to int, + '0' is for int to char
                    for (int l = k - 1; l >= j + 1; --l) //If there are no zeros it won't start, since l wouldn't be >= j + 1
                    {
                        rvrs_subtract_from[l] = '9';
                    }
                    break;
                }
            }
        }
        else
        {
            column_sum = (rvrs_subtract_from[j] - '0') - (rvrs_subtracted[j] - '0');
        }
        result += to_string(column_sum);
        
    }
    column_sum = (rvrs_subtract_from[rvrs_subtract_from.length() - 1] - '0') - (rvrs_subtracted[rvrs_subtracted.length() - 1] - '0'); //rvrs_longest and rvrs_shortest are the same
    result += reverse(to_string(column_sum)); //reverse because it could be larger than 2 digits
    result = reverse(result);
    for (int i = 0; i <= result.length(); ++i)
    {
        if (result[i] == '0')
        {
            result.erase(i, i + 1);
            --i;
        }
        else
        {
            break;
        }
        
    }
    subtract_from = result;
}
long long regular = 0; //I declare the "regular" and odd integers outside so that when their value is changed it stays that way, otherwise i cannot get the next_regorodd
long long odd = 1;
long long i = -1;
long long next_regorodd() //Next Regular or Odd number (the sequence of regular numbers with a sequence of odd numbers (starting from three) between each number)
{
    ++i;
    if (i % 2 == 0)
    {
        ++regular;
        return regular;
    }
    odd += 2;
    return odd;
}
void reset_NRO() //This is just for tidyness in partition()'s outermost for loop start, and the variables are anyways public
{
    regular = 0;
    odd = 1;
    i = -1;
}
string partition(int n)
{
    string result = "0";
    long long nro;
    float nowAdd = 2; //This is like a bool, except to change the state you deduct twice; To determine whether to add or subtract at a certain step
    vector<string> partitions = {"1"};
    for (long long i = 1; i <= n; ++i)
    {
        reset_NRO();
        nro = 1; //Since whenever i call next_regorodd() it increments, i need to save it in a variable to be able to reuse the value
        result = "0";
        nowAdd = 2;
        for (long long location = nro - 1; nro <= partitions.size(); location = nro - 1) // not "location + nro - 1 <= partitions.size() - 1" because the minuses cancel out
        {
            if ((nowAdd == 2) || (nowAdd == 1.5)) //To Do: I'm not even using the 0, i can decrease the max value to 1
            {
                str_add(result, partitions[location]);
                nowAdd == 1.5 ? nowAdd = 0.5 : nowAdd = 1.5;
                nro += next_regorodd();
                continue; //So that it doesn't run the else code on the same partition
            }
            else //If it's 1 or 1.25
            {
                str_subtract(result, partitions[location]);
                nowAdd == 1 ? nowAdd = 2 : nowAdd = 1;
                nro += next_regorodd();
                continue; //So that it doesn't run the else code on the same partition
            }
        }
        partitions.insert(partitions.begin(), result);
    }
    return result;
}
int main()
{
    cout << partition(665) << "\n";
}