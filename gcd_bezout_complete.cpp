#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

// Author: Amber Garcia
// Last update: 3/24/2021
// Excercise for Discrete Mathematics
// Detects Prime Numbers, Computes Greatest Common Denominator, and finds Bezout's coefficients of two integers.

//----------------------------------------------------------------------------------------------
/* bool isprime(int n);
    - Detects if prime or composite. 
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
/* void gcd_eea();
    - Given two integers, computes and prints process to find greatest common denominator of the two.
    - Additionally detects if two integers are relatively prime.
*/
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
      int q, r; //quotient and remainder
      while(true){
        q = a / b; 
        if(a % b == 0){
          //Ending condition
          cout << a << " = " << b << "*" << q << " + " << (a%b) << endl;
          break;
        }
        if(a % b != 0){
          r = a % b;
        }
        cout << a << " = " << b << "*" << q << " + " << r << endl;
        a = b;
        b = r;
      }
      cout << "The greatest common denominator of " << user_input_a << " and " << user_input_b << " is " << r << endl << endl;
    }
}

//----------------------------------------------------------------------------------------------
/* void bezout_eeea;
    - In addition to gcd_eea(), computes bezouts coefficients:
    - such that gcd(a,b) = as + bt for a > b
    - This code uses vectors in order to store the values of q, s, and t to reuse them.
*/
void bezout_eeea(){

    int user_input_a, user_input_b;
   
    cout << "Enter first integer." << endl;
    cin >> user_input_a;
    cout << "Enter second integer." << endl;
    cin >> user_input_b;

    if(isprime(user_input_a) && isprime(user_input_b)){
      cout << "Integers:" << user_input_a << " and " << user_input_b << " are relatively prime, with their greatest common divider being 1." << endl << endl;
    }else{
      //largest integer becomes dividend [a]. smallest is divisor [b]
      int a, b;
      if(user_input_a > user_input_b){
        a = user_input_a;
        b = user_input_b;
      }else{
        a = user_input_b;
        b = user_input_a;
      }
      
      // gcd(a,b) = at + bs where a > b
       
      int j = 0; //Index
      int q,r; //quotient and remainder
      int s,t; //bezout coefficients s and t
       
      /* In order to find Bezout's Coefficients:
      * s[j] = s[j-2] - q[j-2]*s[j-1]
      * t[j] = t[j-2] - q[j-2]*t[j-1]
      * Only if j > 2.
      */
      vector<int> q_tracker; //Keep track of quotient
       
      // Initialize the first two values of s and t
      vector<int> s_tracker; //s[0] = 1, s[1] = 0
      s_tracker.push_back(1); 
      s_tracker.push_back(0);
       
      vector<int> t_tracker; //t[0] = 0, t[1] = 1
      t_tracker.push_back(0);
      t_tracker.push_back(1);
      

      while(true){


        q = a / b;
        q_tracker.push_back(q);
         
        if(j>=2){
          // Calculate s and j
          s = s_tracker.at(j-2) - q_tracker.at(j-2) * s_tracker.at(j-1);
          s_tracker.push_back(s);
          t = t_tracker.at(j-2) - q_tracker.at(j-2) * t_tracker.at(j-1);
          t_tracker.push_back(t);
        }
        if(a % b == 0){
          if(j>=1){ //or if j != 0
            j++;
            //Calculate s and j again before ending
            s = s_tracker.at(j-2) - q_tracker.at(j-2) * s_tracker.at(j-1);
            s_tracker.push_back(s);
            t = t_tracker.at(j-2) - q_tracker.at(j-2) * t_tracker.at(j-1);
            t_tracker.push_back(t);
          }else{
            //j = 0
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
    }
}
//----------------------------------------------------------------------------------------------
/* int ask_method();
    - Asks user for what they want to compute [GCD or BEZOUT]
*/
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
