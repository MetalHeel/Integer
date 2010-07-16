// --------------------------
// projects/integer/Integer.h
// Copyright (C) 20010
// Glenn P. Downing
// --------------------------

#ifndef Integer_h
#define Integer_h

// --------
// includes
// --------

#include <cassert> // assert
#include <iostream> // ostream
#include <stdexcept> // invalid_argument
#include <string> // string
#include <vector> // vector
#include <deque> // deque

using namespace std;

// -----------------
// shift_left_digits
// -----------------

/**
* @param b an iterator to the beginning of an input sequence (inclusive)
* @param e an iterator to the end of an input sequence (exclusive)
* @param x an iterator to the beginning of an output sequence (inclusive)
* @return an iterator to the end of an output sequence (exclusive)
* the sequences are of decimal digits
* output the shift left of the input sequence into the output sequence
* (s << n) => x
*/
template <typename II, typename OI>
OI shift_left_digits (II b, II e, int n, OI x) {
    OI location = x;
    while(b != e)
    {
      *location = *b;
      b++;
      location++;
    }

    for(int a = 0; a < n; a++)
    {
      *(location + a) = 0;
    }

    return location+n;}

// ------------------
// shift_right_digits
// ------------------

/**
* @param b an iterator to the beginning of an input sequence (inclusive)
* @param e an iterator to the end of an input sequence (exclusive)
* @param x an iterator to the beginning of an output sequence (inclusive)
* @return an iterator to the end of an output sequence (exclusive)
* the sequences are of decimal digits
* output the shift right of the input sequence into the output sequence
* (s >> n) => x
*/
template <typename II, typename OI>
OI shift_right_digits (II b, II e, int n, OI x) {
    e-=n;
    OI location = x;
    while(b != e)
    {
      *location = *b;
      b++;
      location++;
    }

    return location;}

// -----------
// plus_digits
// -----------

/**
* @param b an iterator to the beginning of an input sequence (inclusive)
* @param e an iterator to the end of an input sequence (exclusive)
* @param b2 an iterator to the beginning of an input sequence (inclusive)
* @param e2 an iterator to the end of an input sequence (exclusive)
* @param x an iterator to the beginning of an output sequence (inclusive)
* @return an iterator to the end of an output sequence (exclusive)
* the sequences are of decimal digits
* output the sum of the two input sequences into the output sequence
* (s1 + s2) => x
*/
template <typename II1, typename II2, typename OI>
OI plus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    int size1 = e1 - b1;
    int size2 = e2 - b2;
    OI endx;

    if(size2 > size1)
    {
      int car = 0;
      for(int i = 1; i <= size1; i++){
         int add = *(e2-i) + *(e1 - i) + car;
         *(x+size2 - i) = add % 10;
         car = add / 10; 
      } 
      
      for(int i = size1 + 1; i <= size2; i++){
        int add = *(e2-i) + car;
        *(x+size2-i) = add % 10;
        car = add / 10;
      }

      if(car > 0){
        endx = x + size2;
        for(int i = 1; i <= size2; i++){
          *endx = *(endx - 1);
          --endx;
        }
        *endx = car;
        endx = endx + size2 + 1;
      }
      else
        endx = x + size2;
    }
    else
    {
      int car = 0;
      for(int i = 1; i <= size2; i++){
         int add = *(e2-i) + *(e1 - i) + car;
         *(x+size1 - i) = add % 10;
         car = add / 10; 
      }

      if(size1 > size2){ 
        for(int i = size2 + 1; i <= size1; i++){
          int add = *(e1-i) + car;
          *(x+size1-i) = add % 10;
          car = add / 10;
        }}

      if(car > 0){
        endx = x + size1;
        for(int i = 1; i <= size1; i++){
          *endx = *(endx - 1);
          --endx;
        }
        *endx = car;
        endx = endx + size1 + 1;
      }
      else
        endx = x + size1;
    }
    
    return endx;}

// ------------
// minus_digits
// ------------

/**
* @param b an iterator to the beginning of an input sequence (inclusive)
* @param e an iterator to the end of an input sequence (exclusive)
* @param b2 an iterator to the beginning of an input sequence (inclusive)
* @param e2 an iterator to the end of an input sequence (exclusive)
* @param x an iterator to the beginning of an output sequence (inclusive)
* @return an iterator to the end of an output sequence (exclusive)
* the sequences are of decimal digits
* output the difference of the two input sequences into the output sequence
* (s1 - s2) => x
*/
template <typename II1, typename II2, typename OI>
OI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    int size1 = e1 - b1;
    int size2 = e2 - b2;
    OI endx;

    int borrow = 0;
    int carry = 0;
    for(int i = 1; i <= size2; i++){
        int t = *(e1-i) + borrow;
        if(t < *(e2 - i)){
           borrow = -1;
           carry = 10;
        }
        else
        {
          borrow = 0;
          carry = 0;
        }
        	
        int sub = (t + carry) - *(e2 - i);
        *(x+size1 - i) = sub;
    }

    if(size1 > size2){
      for(int i = size2 + 1; i <= size1; i++){
        int sub = 0;
        if(*(e1-i) == 0 && borrow == -1){
           sub = 9;
        }
        else{
           sub = *(e1-i) + borrow;
           borrow = 0;
        }
        *(x+size1-i) = sub;
      }
    }

    
    endx = x + size1;

    if(*x == 0)
      x = x + 1;


    return endx;}

// -----------------
// multiplies_digits
// -----------------

/**
* @param b an iterator to the beginning of an input sequence (inclusive)
* @param e an iterator to the end of an input sequence (exclusive)
* @param b2 an iterator to the beginning of an input sequence (inclusive)
* @param e2 an iterator to the end of an input sequence (exclusive)
* @param x an iterator to the beginning of an output sequence (inclusive)
* @return an iterator to the end of an output sequence (exclusive)
* the sequences are of decimal digits
* output the product of the two input sequences into the output sequence
* (s1 * s2) => x
*/
template <typename II1, typename II2, typename OI>
OI multiplies_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
	int size1 = e1 - b1;
    int size2 = e2 - b2;
    OI endx = x + size2;
    int ten = 1;
    
    for(int i = 1; i <= size1; i++){
       *(endx - i) = *(e1-i);
    }    
    
    for(int i = 1; i <= size2; i++){
       int num = *(e2-i);
       for(int j = 0; j < num*ten; j++){
          if(i == 1 && j == 0){
             j++;
          }
          endx = plus_digits(b1, e1, x, endx, x);
       }
       ten = ten * 10;
    }
    
    return endx;}

// --------------
// divides_digits
// --------------

/**
* @param b an iterator to the beginning of an input sequence (inclusive)
* @param e an iterator to the end of an input sequence (exclusive)
* @param b2 an iterator to the beginning of an input sequence (inclusive)
* @param e2 an iterator to the end of an input sequence (exclusive)
* @param x an iterator to the beginning of an output sequence (inclusive)
* @return an iterator to the end of an output sequence (exclusive)
* the sequences are of decimal digits
* output the division of the two input sequences into the output sequence
* (s1 / s2) => x
*/
template <typename II1, typename II2, typename OI>
OI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
	 int size1 = e1 - b1;

    OI endx = x + size1;
    int count = 0;
    bool zero = false;    
    
    for(int i = 1; i <= size1; i++){
       *(endx - i) = *(e1-i);
    }    
    
    while(!zero){
       minus_digits(x, endx, b2, e2, x);
		 count++;
		 for(int i = 0; i < (endx - x); i++){
          if(*(x+i) == 0){
			    zero = true;          
          }
          else{
             zero = false;
             break;
          }
		 }
    }

    int digits = 0;
	 int t = count;    
    while(t > 0){
	    t = t / 10;
	    digits++;    
    }
    endx = x + digits;
    for(int i = digits - 1; i >= 0; i--){
	    *(x+i) = count % 10;
	    count /= 10;
    }
    
    return endx;}

// -------
// Integer
// -------

template < typename T, typename C = std::vector<T> >
class Integer {
    public:
        // -----------
        // operator ==
        // -----------

        /**
         * <your documentation>
         */
        friend bool operator == (const Integer& lhs, const Integer& rhs) {
            if(lhs.integer.size() != rhs.integer.size())
            	return false;
            else
            {
            	for(int i = 0; i < (int)lhs.integer.size(); i++)
            	{
            		if(lhs.integer[i] != rhs.integer[i])
            			return false;

            	}
            }

            return true;}

        // -----------
        // operator !=
        // -----------

        /**
         * <your documentation>
         */
        friend bool operator != (const Integer& lhs, const Integer& rhs) {
            return !(lhs == rhs);}

        // ----------
        // operator <
        // ----------

        /**
         * <your documentation>
         */
        friend bool operator < (const Integer& lhs, const Integer& rhs) {
            if(!lhs.negative && !rhs.negative){
            	if(lhs.integer.size() < rhs.integer.size())
            		return true;
        	    else
       	        {
           		 	for(int i = (int)lhs.integer.size(); i > -1; i--)
           		 	{
          		  		if(lhs.integer[i] > rhs.integer[i])
           		 			return false;
           		 	}
        	    }
        	}
            if(lhs.negative && !rhs.negative){
               return true;
        	}
            if(!lhs.negative && rhs.negative){
               return false;
        	} 
            if(lhs.negative && rhs.negative){
            	if(lhs.integer.size() < rhs.integer.size())
            		return false;
        	    else
       	        {
           		 	for(int i = (int)lhs.integer.size(); i > -1; i--)
           		 	{
          		  		if(lhs.integer[i] < rhs.integer[i])
           		 			return false;
           		 	}
        	    }
        	}        	
        	return true;}

        // -----------
        // operator <=
        // -----------

        /**
         * <your documentation>
         */
        friend bool operator <= (const Integer& lhs, const Integer& rhs) {
            return !(rhs < lhs);}

        // ----------
        // operator >
        // ----------

        /**
         * <your documentation>
         */
        friend bool operator > (const Integer& lhs, const Integer& rhs) {
            return (rhs < lhs);}

        // -----------
        // operator >=
        // -----------

        /**
         * <your documentation>
         */
        friend bool operator >= (const Integer& lhs, const Integer& rhs) {
            return !(lhs < rhs);}

        // ----------
        // operator +
        // ----------

        /**
         * <your documentation>
         */
        friend Integer operator + (Integer lhs, const Integer& rhs) {
            return lhs += rhs;}

        // ----------
        // operator -
        // ----------

        /**
         * <your documentation>
         */
        friend Integer operator - (Integer lhs, const Integer& rhs) {
            return lhs -= rhs;}

        // ----------
        // operator *
        // ----------

        /**
         * <your documentation>
         */
        friend Integer operator * (Integer lhs, const Integer& rhs) {
            return lhs *= rhs;}

        // ----------
        // operator /
        // ----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs == 0)
         */
        friend Integer operator / (Integer lhs, const Integer& rhs) {
            return lhs /= rhs;}

        // ----------
        // operator %
        // ----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs <= 0)
         */
        friend Integer operator % (Integer lhs, const Integer& rhs) {
            return lhs %= rhs;}

        // -----------
        // operator <<
        // -----------

        /**
         * <your documentation>
         */
        friend Integer operator << (Integer lhs, int rhs) {
            return lhs <<= rhs;}

        // -----------
        // operator >>
        // -----------

        /**
         * <your documentation>
         */
        friend Integer operator >> (Integer lhs, int rhs) {
            return lhs >>= rhs;}

        // -----------
        // operator <<
        // -----------

        /**
         * <your documentation>
         */
        friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
           int sum = 0;
           int ten = 1;
           if(rhs.negative == true)
              ten = -1;
           for(int i = (int) rhs.integer.size() - 1; i > -1; i--)
            {
               sum += rhs.integer[i] * ten;
			   ten *= 10;
            }
            
            return lhs << sum;}

        /**
         * absolute value
         * <your documentation>
         */
        friend Integer abs (Integer x) {
            return x.abs();}

        /**
         * power
         * <your documentation>
         * @throws invalid_argument if (x == 0) && (e == 0)
         * @throws invalid_argument if (e < 0)
         */
        friend Integer pow (Integer x, int e) {
            return x.pow(e);}

    private:
        // ----
        // data
        // ----

        C integer;
        deque<char> strint;
        bool negative;

    private:
        // -----
        // valid
        // -----

        bool valid ()  {
            for(int y = 0; y < (int)integer.size(); y++)
              if(integer[y] > 9 || (integer[y] * -1) > 9)
                 return false;

            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Integer (int value) {
            negative = false;
            int neg = 1;
            if(value < 0){ 
               neg = -1;
               value = value * neg;
               negative = true;
            }
            
            while((value) > 9){
              integer.push_back((value % 10));
              value = value / 10;
            }

            integer.push_back(value);
            int f = 0;
            int b = (int)integer.size() - 1;
            while(f < b)
            {
              int t = integer[f];
              integer[f] = integer[b];
              integer[b] = t;
              f++;
              b--;


            }

            assert(valid());
       }

        /**
         * <your documentation>
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            negative = false;
            for(int i = 0; i < (int)value.length(); i++) {
              strint.push_back(value.at(i));
            }
            int neg = 1;
            if(strint[0] == '-'){
              neg = -1;
              negative = true;
              strint.erase(strint.begin());
            }
            for(int x = 0; x < (int)strint.size(); x++) {
              int test = atoi(&strint[x]);
              if(test == 0)
              {
                if(strint[x] != '0')
                  throw std::invalid_argument("Integer::Integer()");
              }
              integer.push_back(test);
            }
            
            if (!valid())
                throw std::invalid_argument("Integer::Integer()");}

        // Default copy, destructor, and copy assignment.
        // Integer (const Integer&);
        // ~Integer ();
        // Integer& operator = (const Integer&);
        
        // ------------
        // getOnesPlace
        // ------------

        /**
         * <documentation yo>
         */
        T* getOnesPlace() {
          return integer.end();
        }

        // ---------------
        // getMostSigPlace
        // ---------------

        /**
         * <documentation yo>
         */
        T* getMostSigPlace() {
          return integer.front();
        }
        
        // ---------------
        // getSize
        // ---------------

        /**
         * <documentation yo>
         */
        int getSize() {
          return integer.size();
        }
        
        // ----------
        // operator -
        // ----------

        /**
         * <your documentation>
         */
        Integer operator - () const {              
           int sum = 0;
           int ten = -1;
           if(negative == true)
              ten = 1;
           for(int i = (int) integer.size() - 1; i > -1; i--)
            {
               sum += integer[i] * ten;
			   ten *= 10;
            }
            return Integer(sum);}

        // -----------
        // operator ++
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator ++ () {
            *this += 1;
            return *this;}

        /**
         * <your documentation>
         */
        Integer operator ++ (int) {
            Integer x = *this;
            ++(*this);
            return x;}

        // -----------
        // operator --
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -- () {
            *this -= 1;
            return *this;}

        /**
         * <your documentation>
         */
        Integer operator -- (int) {
            Integer x = *this;
            --(*this);
            return x;}

        // -----------
        // operator +=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator += (const Integer& rhs) {
        	if(!negative && !rhs.negative){
		       plus_digits(rhs.integer.begin(), rhs.integer.end(), integer.begin(), integer.end(), integer.begin());
		    }
		    if(negative && !rhs.negative){
        	   if(-*this <= rhs){
		          minus_digits(rhs.integer.begin(), rhs.integer.end(), integer.begin(), integer.end(), integer.begin());
		          negative = false;
		       }
		       else{
		          minus_digits(integer.begin(), integer.end(), rhs.integer.begin(), rhs.integer.end(), integer.begin());
		       }
		    }
		    if(!negative && rhs.negative){
        	   if(*this >= -rhs){
		          minus_digits(integer.begin(), integer.end(), rhs.integer.begin(), rhs.integer.end(), integer.begin());
		       }
		       else{
		          minus_digits(rhs.integer.begin(), rhs.integer.end(), integer.begin(), integer.end(), integer.begin());
		          negative = true;
		       }
		    }
        	if(negative && rhs.negative){
		          minus_digits(integer.begin(), integer.end(), rhs.integer.begin(), rhs.integer.end(), integer.begin());
		    }
		    C int2;
		    for(int i = 0; i < (int)integer.size(); i++){
		       if(integer[i] != 0 || i == ((int) integer.size() - 1)){
		          int2.push_back(integer[i]);
		       }
		    }
		    integer = int2;
            return *this;}

        // -----------
        // operator -=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -= (const Integer& rhs) {
        	if(!negative && !rhs.negative){
        	   if(*this >= rhs)
		          minus_digits(integer.begin(), integer.end(), rhs.integer.begin(), rhs.integer.end(), integer.begin());
		       else{
		          minus_digits(rhs.integer.begin(), rhs.integer.end(), integer.begin(), integer.end(), integer.begin());
		          negative = true;
		       }
		    }
		    if(negative && !rhs.negative)
		       plus_digits(rhs.integer.begin(), rhs.integer.end(), integer.begin(), integer.end(), integer.begin());
		    if(!negative && rhs.negative)
		       plus_digits(rhs.integer.begin(), rhs.integer.end(), integer.begin(), integer.end(), integer.begin());
        	if(negative && rhs.negative){
        	   if(*this < rhs)
		          minus_digits(integer.begin(), integer.end(), rhs.integer.begin(), rhs.integer.end(), integer.begin());
		       else{
		          minus_digits(rhs.integer.begin(), rhs.integer.end(), integer.begin(), integer.end(), integer.begin());
		          negative = false;
		       }
		    }		
		    C int2;
		    for(int i = 0; i < (int)integer.size(); i++){
		       if(integer[i] != 0 || i == ((int) integer.size() - 1)){
		          int2.push_back(integer[i]);
		       }
		    }
		    integer = int2;
            return *this;}

        // -----------
        // operator *=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator *= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator /=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs == 0)
         */
        Integer& operator /= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator %=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs <= 0)
         */
        Integer& operator %= (const Integer& rhs) {
            // <your code>
            return *this;}

        // ------------
        // operator <<=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator <<= (int n) {
            // <your code>
            return *this;}

        // ------------
        // operator >>=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator >>= (int n) {
            // <your code>
            return *this;}

        // ---
        // abs
        // ---

        /**
         * absolute value
         * <your documentation>
         */
        Integer& abs () {
            for(int i = 0; i < (int)integer.size(); i++)
            {
            	if(integer[i] < 0)
            		integer[i] = integer[i] * -1;
            }
            return *this;}

        // ---
        // pow
        // ---

        /**
         * power
         * <your documentation>
         * @throws invalid_argument if (this == 0) && (e == 0)
         * @throws invalid_argument if (e < 0)
         */
        Integer& pow (int e) {
            if(e % 2 == 0){
               
            }
            else{
            
            }
            return *this;}};

#endif // Integer_h
