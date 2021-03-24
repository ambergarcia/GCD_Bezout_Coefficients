#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

// Author: Amber Garcia
// Excercise for Discrete Mathematics
// Detects Prime Numbers, Computes Greatest Common Denominator, and finds Bezout's coefficients of two integers.


/* ERROR LOG AND FIXES
3/18/2021 9:54 PM EST
   - askmethod() isprime() gcd_eea() works for all integers properly.
   - bezout_eeea() needs better optimization
      - Requires that you save at least 3 values of q, s, and t into the backlogs to pull back out
      - when calculating s and t.
  3/18/2021 12:13 AM EST
   - bezout_eeea's for loop for storing information for each while loop is not consistent, and is incorrect. Needs fixing.:
  3/21/2021 11:18 PM EST
   - Switched arrays for vectors for better optimization. Compiles fine, but computation error for s value.
    - In order to fix s, we need to allow for the loop to reoccur [j++] in order to access the new q for a new value
    - s and t when 0 < j < 1 is incorrect fix
    - s and t miscalculating bezout coefficients at j = 2 and a%b = 0 [?]
   - t values uncalculated, q values store just fine.
  3/23/2021 9:41 PM EST
*/

//----------------------------------------------------------------------------------------------
/* bool isprime(int n);
    - Calculates sqrt(n)
    - Detects if n is divisible by 2
    - Detects if 0 or 1, neither are prime Numbers
    - 
*/
bool isprime(int n){

    int prime_sq = sqrt(n);

    if(n % 2 != 0){
      //Check if the number is prime.
      if(n == 0 || n == 1){
        return n; //Not prime numbers
      }
      for(int i = 2; i <= prime_sq; i++){
        if(n % i == 0){
          return false; //Not prime
        }
      }
        return true; //Input is prime.
    }
    return false;
}

//----------------------------------------------------------------------------------------------
void gcd_eea(){
    int user_input_a, user_input_b;

    cout << "Enter first integer." << endl;
    cin >> user_input_a;
    cout << "Enter second integer." << endl;
    cin >> user_input_b;

    if(isprime(user_input_a) && isprime(user_input_b)){
      cout << "Integers:" << user_input_a << " and " << user_input_b << " are relatively prime, with their greatest common divider being 1." << endl << endl;
    }else{
      //largest integer becomes divisor [a]. smallest is dividend [b]
      int a, b;
      if(user_input_a > user_input_b){
        a = user_input_a;
        b = user_input_b;
      }else{
        a = user_input_b;
        b = user_input_a;

      }
      //gcd(a,b) = gcd(b,a mod b) = ....
      int j = 0;
      int q, r; //quotient and remainder
      while(true){
        q = a / b;
        if(a % b == 0){
          cout << a << " = " << b << "*" << q << " + " << (a%b) << endl;

          break;
        }
        if(a % b != 0){
          r = a % b;
        }
        cout << a << " = " << b << "*" << q << " + " << r << endl;
        a = b;
        b = r;

        j++;
      }
      cout << "The greatest common denominator of " << user_input_a << " and " << user_input_b << " is " << r << endl << endl;
    }
}

//----------------------------------------------------------------------------------------------
void bezout_eeea(){
    //This will be in table form instead, in order to compute s and t.
    //The program will be parallel to eea, but will also compute s,t and j+1 for s,t.

    int user_input_a, user_input_b;

    cout << "Enter first integer." << endl;
    cin >> user_input_a;
    cout << "Enter second integer." << endl;
    cin >> user_input_b;

    if(isprime(user_input_a) && isprime(user_input_b)){
      cout << "Integers:" << user_input_a << " and " << user_input_b << " are relatively prime, with their greatest common divider being 1." << endl << endl;
    }else{
      //largest integer becomes divisor [a]. smallest is dividend [b]
      int a, b;
      if(user_input_a > user_input_b){
        a = user_input_a;
        b = user_input_b;
      }else{
        a = user_input_b;
        b = user_input_a;
      }
      // gcd(a,b) = at + bs where a > b
      int j = 0;
      int q,r; //quotient and remainder
      //int q_tracker[2]; // q tracking
      //int st_tracker[2][2]; // s is row 0, t is row 1
      vector<int> q_tracker;
      vector<int> s_tracker;
      s_tracker.push_back(1);
      s_tracker.push_back(0);
      vector<int> t_tracker;
      t_tracker.push_back(0);
      t_tracker.push_back(1);
      int s,t;

      while(true){


        q = a / b;
        q_tracker.push_back(q);
        if(j>=2){
          s = s_tracker.at(j-2) - q_tracker.at(j-2) * s_tracker.at(j-1);
          s_tracker.push_back(s);
          t = t_tracker.at(j-2) - q_tracker.at(j-2) * t_tracker.at(j-1);
          t_tracker.push_back(t);

        }
        if(a % b == 0){
          if(j>=1){ //or if j != 0
            j++;

            s = s_tracker.at(j-2) - q_tracker.at(j-2) * s_tracker.at(j-1);
            s_tracker.push_back(s);
            t = t_tracker.at(j-2) - q_tracker.at(j-2) * t_tracker.at(j-1);
            t_tracker.push_back(t);
          }else{
            s = r;
            t = q_tracker.at(j);
          }

          cout << a << " = " << b << "*" << q << " + " << (a%b) << endl;
          break;
        }
        if(a % b != 0){
          r = a % b;
        }
        cout << a << " = " << b << "*" << q << " + " << r << endl;
        a = b;
        b = r;

        j++;
      }
      cout << "Bezout's Coefficients of " << user_input_a << " and " << user_input_b << " is " << "s = " << s << " and t = " << t << endl << endl;
      //cout << "gcd(" << a << ", " << b << ") = " << a << "*" << s << " + " << b << "*" << t << " = " << r << endl;
    }
}
//----------------------------------------------------------------------------------------------
int ask_method(){
  string user_input_mathematical;
  bool yess = false;
  while(true){
    cout << "Choose an option: " << endl;
    cout << "Enter 'GCD' to find greatest common denominator of two integers." << endl;
    cout << "Enter 'BEZOUT' to find Bezout's coefficients of your given two integers." << endl;
    cout << "Enter 'QUIT' to exit program." << endl;

    cin >> user_input_mathematical;
    if(user_input_mathematical == "GCD"){
      gcd_eea();

    }else if(user_input_mathematical == "BEZOUT"){
      bezout_eeea();

    }else if(user_input_mathematical == "QUIT"){
      cout << "Thank you for your time." << endl;
      return 0;
    }
    else{
      cout << "Incorrect input." << endl;
    }

  }
}

int main(){
  ask_method();
  return 0;
}
