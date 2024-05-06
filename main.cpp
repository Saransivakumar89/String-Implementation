#include<iostream>
#include<cstring>
using namespace std;

class String {
    char * string;
    unsigned int len;

public:
    String(): string(nullptr), len(0) {} // Initializer List

    String(const char *s) // Parameterized Constructor
    {
        len = strlen(s);
        string = new char[len + 1];
        strcpy(string, s);
    }

    String(const String &other) // Copy Constructor
    {
        len = other.len;
        string = new char[len + 1];
        strcpy(string, other.string);
    }

    String & operator=(const String &s) // Copy Assignment Constructor
    {
        if(this != &s)
        {
            delete[] string;
            len = strlen(s.string);
            string = new char[len + 1];
            if(s.string)
                strcpy(string, s.string);
            else
                string[0] = '\0';
        }
        return *this;
    }

    friend ostream& operator<<(ostream& output, const String& s);
    friend istream& operator>>(istream& input, String& s);

    unsigned int length() const
    {
        return len;
    }

    bool empty() const
    {
        return len == 0;
    }

    void clear()
    {
        delete[]string;
        string = nullptr;
        len = 0;
    }

    void append(const String& other)
    {
        char* temp = new char[len + other.len + 1];
        strcpy(temp, string);
        strcat(temp, other.string);
        delete[] string;
        string = temp;
        len += other.len;
    }

    const String& substr(int pos, int length) const
    {
        static String emptyString; // Static empty string to return if conditions fail
        if (pos < 0 || pos >= len || length <= 0)
            return emptyString;

        length = min(length, static_cast<int>(len - pos));

        char* temp = new char[length + 1];
        strncpy(temp, string + pos, length);
        temp[length] = '\0';
        static String result(temp);
        delete[] temp;
        return result;
    }

    ~String() // Destructor
    {
        delete[] string;
    }
};

ostream & operator<<(ostream& output, const String & s)
{
    output << s.string;
    return output;
}

istream & operator>>(istream & input, String & s)
{
    char buffer[100];
    input >> buffer;
    delete[] s.string;
    s.len = strlen(buffer);
    s.string = new char[s.len + 1];
    strcpy(s.string, buffer);
    return input;
}

int main()
{
    String str1;
    String str2 = "Hi";

    cout << "String-2: " << str2 << endl;
    cout << "Length of String-2: " << str2.length() << endl;
    cout << "Is String-2 empty? " << (str2.empty() ? "Yes" : "No") << endl;

    String str3 ;
    cout << "Enter String-3: ";
    cin >> str3;

    str2 = str3;

    cout << "String-2: " << str2 << endl;
    cout << "String-3: " << str3 << endl;

    String str4 = "Peter\n";

    //str2.clear();
    str2.append(str4);

    cout << "String-2 after append: " << str2 << endl;


    const String& substr = str2.substr(3, 7); 
    cout << "Substring: " << substr << endl;

    return 0;
}
