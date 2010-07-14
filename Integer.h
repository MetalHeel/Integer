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
        if(*(e1-i) < *(e2 - i)){
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
        int sub = *(e1-i);
        *(x+size1-i) = sub;
      }
    }

    if(*x == 0)
      x = x + 1;

    endx = x + size1;

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
    /*int size1 = e1 - b1;
    int size2 = e2 - b2;
    OI endx;
    int accum[];
    II2 addin;

    for(int i = 1; i < size2; i++)
    {
      for(int j = 0; j < size1; j++)
      {
        *(accum + 
      }
    }*/
    return x;}

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
    // <your code>
    return x;}

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
            // <your code>
            return false;}

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
            // <your code>
            return false;}

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
            // <your code>
            return lhs << "0";}

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

    private:
        // -----
        // valid
        // -----

        bool valid ()  {
            for(int y = 0; y < (int)integer.size(); y++)
              if(integer[y] > 9)
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
            while(value > 9){
              integer.push_back(value % 10);
              value = value / 10;
            }
            integer.push_back(value);
            int count = 0;
            for(int i = 1; i < (int)integer.size(); i++)
            {
              int t = *(integer.rbegin());
              *(integer.rbegin() - count) = *(integer.rend() + i);
              *(integer.rend() + i) = t;
              ++count;
            }
            assert(valid());}

        /**
         * <your documentation>
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            for(int i = 0; i < (int)value.length(); i++) {
              strint.push_back(value.at(i));
            }
            int temp = 1;
            if(strint[0] == '-'){
              temp = -1;
              strint.erase(strint.begin());
            }
            for(int x = 0; x < (int)strint.size(); x++) {
              int test = temp * atoi(&strint[x]);
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
          return integer.front();
        }

        // ---------------
        // getMostSigPlace
        // ---------------

        /**
         * <documentation yo>
         */
        T* getMostSigPlace() {
          return integer.end();
        }
        // ----------
        // operator -
        // ----------

        /**
         * <your documentation>
         */
        Integer operator - () const {
            // <your code>
            return Integer(0);}

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
            // <your code>
            return *this;}

        // -----------
        // operator -=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -= (const Integer& rhs) {
            // <your code>
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
            // <your code>
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
            // <your code>
            return *this;}};

#endif // Integer_h
