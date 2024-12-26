#include <bits/stdc++.h>

using namespace std;

#define DIM 1000


//ex: base 16, A2B,CD in base 6 => 20015.44454513

/*
    Answers:
        Addition:
            3. 121B4EC
            7.  10540665
        Subtraction
            3. 4CECD
            8. 32010
        Multiplications
            2.  12C00A2
            5.  144114

        Divisions
            4.  13421, r 0
            7.  3011B r C

        Conversions:
            3.  1001000010100,1111010000010
            6.  2533120,0776
            11. 20141,05
            15. 989,78125
            20. FA,8E38(has a better aproximation)
            24. 1010513,3444043(better aproximation)

 */

static inline bool Powerof2(int x) {
    return ((x & (x - 1)) == 0);
}

//convert from base 16 to int
static inline int convert_b16_int(char ch) {
    int x = ch - 'A';
    return x + 10;
}

//convert from int to base 16
static inline char convert_int_b16(int x) {
    x -= 10;
    return char('A' + x);
}

//Test if the input is a valid number in the base p.
static inline bool Test_valid(string a, int p) {
    for(int i = 0; i < a.size(); i++) {
        int digit = (a[i] >= 'A' ? convert_b16_int(a[i]) : a[i] - '0');
        if(digit >= p)      //in base p we cannot have a digit >= to p.
            return 0;
    }
    return 1;
}

static inline string Add_numbers_base_p(string a, string b, int p) {
    reverse(a.begin(),a.end());     //reverse the numbers to make only one crossing
    reverse(b.begin(), b.end());

    int sizea = a.size(), sizeb = b.size();

    a.resize(a.size() + 100, '0');   //i put nesemnificative 0 at the begin of the number(it is reserved)
    b.resize(b.size() + 100, '0');

    int c[DIM] = {0};
    int i = 0, carry = 0;
    while(i < sizea || i < sizeb || carry) {
        if(a[i] >= 'A')         ///if the base is 16
            carry += convert_b16_int(a[i]);
        else carry += (a[i] - '0');

        if(b[i] >= 'A')
            carry += convert_b16_int(b[i]);
        else carry += (b[i] - '0');

        c[i++] = carry % p;
        carry /= p;
    }

    string ans ="";
    //convert the number from string to int
    for(int j = 0; j < i; j++)
        if(c[j] >= 10)      //if i need to put a letter.
            ans += convert_int_b16(c[j]);
        else ans += to_string(c[j]);

    reverse(ans.begin(), ans.end());

    return ans;
}

static inline string Sub_in_base_p(string a, string b, int p) {
    reverse(a.begin(), a.end());        //reverse the numbers to make only one crossing
    reverse(b.begin(), b.end());

    int sizea = a.size();
    a.resize(a.size() + 100, '0');        //i put nesemnificative 0 at the begin of the number(it is reserved)
    b.resize(b.size() + 100, '0');

    int c[DIM] = {0};
    int i = 0, t = 0;
    while(i < sizea || t != 0) {
        if(a[i] >= 'A')
            c[i] += convert_b16_int(a[i]);
        else c[i] += a[i] - '0';

        if(b[i] >= 'A')
            c[i] -= convert_b16_int(b[i]);
        else c[i] -= b[i] - '0';

        c[i] -= t;

        if(c[i] < 0)
            t = 1;  //if a borrow
        else t = 0;

        c[i++] = c[i] + t * p;
    }

    while(sizea > 0 && c[sizea - 1] == 0)   //i eliminate the nesemnificative 0
        sizea--;

    string ans = "";

    //convert the number from string to int
    for(int j = 0; j < sizea; j++)
        if(c[j] >= 10)
            ans += convert_int_b16(c[j]);
        else ans += to_string(c[j]);

    reverse(ans.begin(), ans.end());

    return ans;
}

static inline string Multiply_in_basep_digit(string a, string b, int p) {
    reverse(a.begin(), a.end());     //reverse the numbers to make only one crossing

    int digit;
    if(b[0] >= 'A')         //if the digit is in base 16
        digit = convert_b16_int(b[0]);
    else digit = b[0] - '0';

    int sizea = a.size();
    a.resize(a.size() + 100, '0');      //i put nesemnificative 0 at the begin of the number(it is reserved)

    int c[DIM] = {0};
    int i = 0, carry = 0;
    while(i < sizea || carry) {
        if(a[i] >= 'A')
            carry += convert_b16_int(a[i]) * digit;
        else carry += (a[i] - '0') * digit;

        c[i++] = carry % p;
        carry /= p;
    }

    string ans = "";

    //convert the number from string to int
    for(int j = 0; j < i; j++)
        if(c[j] >= 10)
            ans += convert_int_b16(c[j]);
        else ans += to_string(c[j]);

    reverse(ans.begin(), ans.end());
    return ans;
}

static inline string  Division_in_basep_digit(string a, string b, int p, string &rest) {
    reverse(a.begin(), a.end());    //reverse the numbers to make only one crossing

    int digit;
    if(b[0] >= 'A')     //if the digit is in base 16
        digit = convert_b16_int(b[0]);
    else digit = b[0] - '0';

    int sizea = a.size();
    a.resize(a.size() + 100, '0');   //i put nesemnificative 0 at the begin of the number(it is reserved)

    int c[DIM] = {0};
    int i = sizea - 1, t = 0;
    while(i >= 0) {
        if(a[i] >= 'A')
            t = t * p + convert_b16_int(a[i]);
        else t = t * p + (a[i] - '0');

        c[i--] = t / digit;
        t %= digit;
    }
    while(sizea > 0 && c[sizea - 1] == 0)   //i eliminate the nesemnificative 0
        sizea--;


    string ans = "";
    //convert the number from string to int
    for(int j = 0; j < sizea; j++)
        if (c[j] >= 10)
            ans += convert_int_b16(c[j]);
        else ans += to_string(c[j]);

    if(t >= 10)             //if the remeinder is in base 16
        rest += convert_int_b16(t);
    else rest += to_string(t);

    reverse(ans.begin(), ans.end());

    return ans;

}

///When the p is smaller than destination base
static inline string Substitution_method(string a, int p, int dest) {
    int poz = a.find(',');     //separate the int part from float part
    if(poz == -1)                   //if a have a int number.
        poz = a.size();

    string ans_int = "";
    string p_power = "1";
    string power;
    if(p >= 10)
        power = convert_int_b16(p);
    else power = to_string(p);

    for(int i = poz - 1; i >= 0; i--) {
        string x = "";      //i can t use in function just a[i];
        x += a[i];

        string aux = Multiply_in_basep_digit(p_power, x, dest);     //current digit * the power of the position.
        ans_int = Add_numbers_base_p(ans_int, aux, dest);           //add to the int part.
        p_power = Multiply_in_basep_digit(p_power, power, dest);    //new power
    }

    if(poz == a.size())     //if a don t have the  coma.
        return  ans_int;

    //make the float part.
    p_power = power;
    string ans_float = "";
    for(int i = poz + 1; i < a.size(); i++) {
        string x = "", aux, r;
        x += a[i];
        x += "00000000000000";        //for a better precision
        int j = i - poz;        //number of division on each step

        while(j--) {        ///division on p^j
            aux = Division_in_basep_digit(x, p_power, dest, r);
            x = aux;
        }
        ans_float = Add_numbers_base_p(ans_float, aux, dest);
    }

    ans_int += ",";
    while(ans_float.size() != 1 && ans_float[ans_float.size() - 1] == '0')  //eliminate the insignifiante 0
        ans_float.pop_back();

    return ans_int + ans_float;     ///compute the value.
}

///When p is greater than destination base
static inline string Succesive_div_mul_basep(string a, int p, int dest) {
    int poz = a.find(',');     //separate the int part from float part
    if(poz == -1)
        poz = a.size();

    string ans_int = "";
    string int_part = "";
    for(int i = 0; i < poz; i++)    //the int part of the number.
        int_part += a[i];

    string digit;
    if(dest >= 10)
        digit = convert_int_b16(dest);  //the digit i will divide and multiply
    else digit = to_string(dest);

    //division a with dest in base p till a is 0;
    while(int_part.size() != 0) {
        string rest = "";
        int_part = Division_in_basep_digit(int_part, digit, p, rest);
        ans_int += rest;
    }

    //i need to reverse the remainders
    reverse(ans_int.begin(), ans_int.end());
    if(poz == a.size())     //if a don t have a coma
        return ans_int;


    string ans_float = "";
    string float_part = "0";
    for(int i = poz + 1; i < a.size(); i++)
        float_part += a[i];

    int i = 0;
    while(i < 10) {      //numbers of zecimals;
        float_part = Multiply_in_basep_digit(float_part, digit, p);
        i++;
        if(float_part[0] - '0' >= 10)
            ans_float += convert_int_b16(float_part[0] - '0');
        else ans_float += float_part[0];

        float_part[0] = '0';
    }

    ans_int += ",";
    //eliminate the insignifiant 0
    while(ans_float.size() != 1 && ans_float[ans_float.size() - 1] == '0')
        ans_float.pop_back();

    return ans_int + ans_float;
}

static inline string Intermediare_base_converter(string a, int p, int dest) {
    string ans;
    if(p > 10)        ///convert from p in base 10
        ans = Succesive_div_mul_basep(a, p, 10);
    else ans = Substitution_method(a, p, 10);

    cout << "Number in base 10 = " << ans << '\n';

    if(dest < 10)       //Convert from base 10 to destination base
        ans = Succesive_div_mul_basep(ans, 10, dest);
    else ans = Substitution_method(ans, 10, dest);

    return ans;
}

//Rapid conversion.

static inline int LOG(int x) {
    int lg = 0;
    while(x != 1) {
        lg++;
        x /= 2;
    }

    return lg;
}

static inline string Rapid_conversion(string a, int p, int dest) {
    int lg = LOG(p);
    string aux = "";

    ///convert the number to base 2
    for(int i = 0; i < a.size(); i++)
        if(a[i] != ',') {
            string x = "";
            x += a[i];
            x = Succesive_div_mul_basep(x, p, 2);  ///convert from base p to base 2

            if(x.size() != lg){         ///put nesemnificative 0 in front of the result if i don t have enough 0
                int y = lg - x.size();
                while(y--)
                    aux += "0";
            }
            aux += x;
        }else aux += ",";

    string ans = "";
    aux = "0000" + aux;     //insignifiant 0
    int poz = aux.find(',');

    if(poz == -1)
        poz = aux.size();

    ///convert the first part;
    lg = LOG(dest);
    for(int i = poz - 1; i >= lg - 1; i -= lg) {
        string x = aux.substr(i - lg + 1, lg);
        x = Substitution_method(x, 2, dest);
        ans += x;
    }

    //delete the insignifiant 0.
    while(ans[ans.size() - 1] == '0')
        ans.pop_back();

    reverse(ans.begin(), ans.end());

    if(poz == aux.size())
        return  ans;

    ans += ',';
    aux = aux + "0000";
    for(int i = poz + 1; i  < aux.size() - lg; i += lg) {
        string x = aux.substr(i, lg);
        x = Substitution_method(x, 2, dest);
        ans += x;
    }

    return ans;
}

int main() {
    while(1) {
        cout << "\nMade by Grancea Alexandru\n\n";

        cout << "Press 1 if you want to add two numbers in a base p\n";
        cout << "Press 2 if wou want to subtract two numbers in a base p\n";
        cout << "Press 3 if you want to multiply by one digit in a base p\n";
        cout << "Press 4 if you want to divide by one digit in a base p\n";
        cout << "Press 5 if you want to convert a number from a base p to a base b using substitution method\n";
        cout
                << "Press 6 if you want to convert a number from a base p to a base b using succesive divisions and multiplications method\n";
        cout << "Press 7 if you want to convert a number from a base p to a base b using 10 as intermediare base\n";
        cout << "Press 8 if you want to apply the rapid conversion between two bases that are power of 2\n";

        int option;
        cout << "option =";
        cin >> option;

        int p;
        string a, b, c;
        if (option == 1) {
            cout << "Tell the base p, where do you want to make the addition\n";
            cout << "p = ";
            cin >> p;
            cout << "Tell me 2 numbers in the base " << p << " that you want to add\n";
            cout << "a =";
            cin >> a;
            cout << "b =";
            cin >> b;

            if (!Test_valid(a, p) || !Test_valid(b, p)) {
                cout << "Invalid input";
                return 0;
            }

            c = Add_numbers_base_p(a, b, p);
            cout << "The addition is = " << c;

        } else if (option == 2) {
            cout << "Tell the base p, where do you want to make the subtraction\n";
            cout << "p =";
            cin >> p;
            cout << "Tell me 2 numbers in the base " << p << " that you want to subtract\n";
            cout << "a =";
            cin >> a;
            cout << "b =";
            cin >> b;

            if (!Test_valid(a, p) || !Test_valid(b, p)) {
                cout << "Invalid input";
                return 0;
            }


            c = Sub_in_base_p(a, b, p);
            cout << "The subtraction is = " << c;

        } else if (option == 3) {
            cout << "Tell the base p, where do you want to make the multiplication\n";
            cout << "p =";
            cin >> p;
            cout << "Tell me a number in the base " << p << " that you want to multiply\n";
            cout << "a =";
            cin >> a;
            string digit;
            cout << "Tell me the digit that you want to multiply by\n";
            cout << "digit =";
            cin >> digit;

            if (!Test_valid(a, p) || !Test_valid(digit, p)) {
                cout << "Invalid input";
                return 0;
            }


            //A23F4, B
            c = Multiply_in_basep_digit(a, digit, p);
            cout << "The product is = " << c;
        } else if (option == 4) {
            cout << "Tell the base p, where do you want to make the division\n";
            cout << "p =";
            cin >> p;
            cout << "Tell me a number in the base " << p << " that you want to divide\n";
            cout << "a =";
            cin >> a;
            string digit;
            cout << "Tell me the digit that you want to divide by\n";
            cout << "digit =";
            cin >> digit;

            if (!Test_valid(a, p) || !Test_valid(digit, p)) {
                cout << "Invalid input";
                return 0;
            }

            string rest = "";
            //1FED0205 9
            c = Division_in_basep_digit(a, digit, p, rest);
            cout << "The division is = " << c << " and the remeinder = " << rest;

        } else if (option == 5) {
            cout << "Tell the base p, that do you want to convert\n";
            cout << "p =";
            cin >> p;

            cout << "Tell me a number in the base " << p << " that you want to convert\n";
            cout << "a =";
            cin >> a;

            int d;
            cout << "Tell the destination base d\n";
            cout << "d =";
            cin >> d;

            if (!Test_valid(a, p) || d < p) {
                cout << "Invalid input";
                return 0;
            }

            c = Substitution_method(a, p, d);
            cout << c;

        } else if (option == 6) {
            cout << "Tell the base p, that do you want to convert\n";
            cout << "p =";
            cin >> p;

            cout << "Tell me a number in the base " << p << " that you want to convert\n";
            cout << "a =";
            cin >> a;

            int d;
            cout << "Tell the destination base d\n";
            cout << "d =";
            cin >> d;

            if (!Test_valid(a, p) || d > p) {
                cout << "Invalid input";
                return 0;
            }

            c = Succesive_div_mul_basep(a, p, d);
            cout << c;
        } else if (option == 7) {
            cout << "Tell the base p, that do you want to convert\n";
            cout << "p =";
            cin >> p;

            cout << "Tell me a number in the base " << p << " that you want to convert\n";
            cout << "a =";
            cin >> a;

            int d;
            cout << "Tell the destination base d\n";
            cout << "d =";
            cin >> d;

            if (!Test_valid(a, p)) {
                cout << "Invalid input";
                return 0;
            }

            c = Intermediare_base_converter(a, p, d);
            cout << c;

        } else if (option == 8) {
            cout << "Tell the base p, that do you want to convert\n";
            cout << "p =";
            cin >> p;

            cout << "Tell me a number in the base " << p << " that you want to convert\n";
            cout << "a =";
            cin >> a;

            int d;
            cout << "Tell the destination base d\n";
            cout << "d =";
            cin >> d;

            if (!Test_valid(a, p) || Powerof2(d) == 0 || Powerof2(p) == 0) {
                cout << "Invalid input";
                return 0;
            }

            cout << Rapid_conversion(a, p, d);

        }
    }
    return 0;
}