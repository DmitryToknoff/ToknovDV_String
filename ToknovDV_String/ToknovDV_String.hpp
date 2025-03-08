#ifndef ToknovDV_String_
#define ToknovDV_String_

/* The classes below are exported */
#pragma GCC visibility push(default)
#pragma once


class ToknovDV_String{
    size_t sz = 0;
    char* str = nullptr;

public:
    ToknovDV_String();
    ToknovDV_String(const char* s);
    ToknovDV_String(const ToknovDV_String& ts);
    ~ToknovDV_String();
    void get_string();
    size_t get_length() const;
    ToknovDV_String& operator = (const ToknovDV_String& ts);
    char& operator [] (const size_t& index);
    const char& operator [] (const size_t& index) const;
    ToknovDV_String operator + (const ToknovDV_String& ts);
    ToknovDV_String operator + (const char& s);
    ToknovDV_String& operator += (const ToknovDV_String& ts);
    ToknovDV_String& operator += (const char& s);
    bool operator == (const ToknovDV_String& ts);
    bool operator != (const ToknovDV_String& ts);
    bool operator < (const ToknovDV_String& ts);
    bool operator > (const ToknovDV_String& ts);
    bool operator >= (const ToknovDV_String& ts);
    bool operator <= (const ToknovDV_String& ts);
    void append(const ToknovDV_String& ts);
    ToknovDV_String substr(const size_t& start, const size_t& count);
    void erase(const size_t idx);
    friend std::ostream& operator << (std::ostream& os, const ToknovDV_String& ts);
    friend std::istream& operator >> (std::istream& is, ToknovDV_String& ts);
    friend std::istream& getline(std::istream& is, ToknovDV_String& ts);
    
private:
    size_t len_string(const char* s);
    void concat(char*& s, const ToknovDV_String& ts1, const ToknovDV_String& ts2);
    void concat(char*& new_s, const char*& s, const ToknovDV_String& ts2, const size_t& sz1);
};

std::istream& getline(std::istream& is, ToknovDV_String& ts);
bool word_isdigit(const ToknovDV_String& ts);
bool isalpha(const char& c);

#pragma GCC visibility pop
#endif
