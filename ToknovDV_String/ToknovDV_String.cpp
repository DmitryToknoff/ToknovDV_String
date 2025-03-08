#include <iostream>
#include <algorithm>
#include "ToknovDV_String.hpp"


ToknovDV_String::ToknovDV_String()
{
    str = new char[sz];
}

ToknovDV_String::ToknovDV_String(const char* s)
{
    sz = len_string(s);
    str = new char[sz];
    std::copy(s, s+sz, str);
    
}

ToknovDV_String::ToknovDV_String(const ToknovDV_String& ts)
{
    this->sz = ts.sz;
    str = new char[sz];
    std::copy(ts.str, ts.str+sz, str);
}

ToknovDV_String::~ToknovDV_String()
{
    delete[] str;
}

void ToknovDV_String::get_string()
{
    for(int i = 0; i < sz; ++i)
        std::cout << str[i] << ' ';
    std::cout << std::endl;
}

size_t ToknovDV_String::get_length() const
{
    return sz;
}

size_t ToknovDV_String::len_string(const char* s)
{
    size_t cnt = 0;
    int i = 0;
    while(s[i] != '\0')
    {
        ++cnt;
        ++i;
    }
    
    return cnt;
}

void ToknovDV_String::concat(char*& new_s, const ToknovDV_String &ts1, const ToknovDV_String &ts2)
{
    for(size_t i = 0 ; i < ts1.sz; ++i)
        new_s[i] = ts1.str[i];
    
    for(size_t i = sz; i < ts1.sz+ts2.sz; ++i)
        new_s[i] = ts2.str[i-sz];
}

void ToknovDV_String::concat(char *& new_s, const char *&s, const ToknovDV_String &ts2, const size_t& sz1)
{
    for(size_t i = 0 ; i < ts2.sz; ++i)
        new_s[i] = ts2.str[i];
    
    for(size_t i = ts2.sz; i < ts2.sz+sz1; ++i)
        new_s[i] = s[i-ts2.sz];
}

char& ToknovDV_String::operator[](const size_t& index)
{
    if(index >= sz || index < 0)
        throw std::out_of_range("Index Error");
    
    return str[index];
}

const char& ToknovDV_String::operator[](const size_t& index) const
{
    if(index >= sz || index < 0)
        throw std::out_of_range("Index Error");
    
    return str[index];
}

ToknovDV_String& ToknovDV_String::operator= (const ToknovDV_String& ts)
{
    delete[] str;
    str = new char[ts.sz];
    sz = ts.sz;
    std::copy(ts.str, ts.str + sz, str);
    return *this;
}

ToknovDV_String ToknovDV_String::operator+ (const ToknovDV_String& ts)
{
    char* new_s = new char[sz + ts.sz];
    concat(new_s, *this, ts);
    
    ToknovDV_String tmp(new_s);
    delete[] new_s;
    
    return tmp;
}

ToknovDV_String ToknovDV_String::operator+ (const char& s)
{
    char* new_s = new char[sz+1];
    std::copy(str, str + sz, new_s);
    new_s[sz] = s;
    ToknovDV_String tmp(new_s);
    delete[] new_s;
    
    return tmp;
}

ToknovDV_String& ToknovDV_String::operator += (const ToknovDV_String& tk)
{
    ToknovDV_String tmp = *this + tk;
    delete[] str;
    sz = tmp.sz;
    str = new char[sz];
    std::copy(tmp.str, tmp.str+sz, str);

    return *this;
}

ToknovDV_String& ToknovDV_String::operator += (const char& s)
{
    char* new_s = new char[sz+1];
    std::copy(str, str + sz, new_s);
    new_s[sz] = s;
    delete[] str;
    str = new_s;
    ++sz;
    
    return *this;
}


bool ToknovDV_String::operator == (const ToknovDV_String &ts)
{
    if(sz != ts.sz) return false;
    
    for(size_t i = 0; i < sz; ++i)
        if(str[i] != ts.str[i])
            return false;
    
    return true;
}


bool ToknovDV_String::operator != (const ToknovDV_String& ts)
{
    return !(*this == ts);
}


bool ToknovDV_String::operator < (const ToknovDV_String& ts)
{
    size_t min_sz = (sz < ts.sz) ? sz : ts.sz;
    
    for(size_t i = 0; i < min_sz; ++i)
        if(str[i] < ts.str[i])
            return true;
        else if(str[i] > ts.str[i])
            return false;
    
    if(sz < ts.sz) return true;
    
    return false;
}

bool ToknovDV_String::operator > (const ToknovDV_String& ts)
{
    return (!(*this < ts)) && *this != ts;
}

bool ToknovDV_String::operator <= (const ToknovDV_String& ts)
{
    return *this < ts || *this == ts;
}

bool ToknovDV_String::operator >= (const ToknovDV_String& ts)
{
    return *this > ts || *this == ts;
}

void ToknovDV_String::append(const ToknovDV_String &ts)
{
    *this += ts;
}

ToknovDV_String ToknovDV_String::substr(const size_t &start, const size_t& count)
{
    if(start > sz || start < 0)
        return ToknovDV_String();
    
    size_t mn_cnt = (sz <= start + count ? sz : start + count);
    char* tmp = new char[mn_cnt];
    
    for(size_t i = start; i < mn_cnt; ++i)
    {
        tmp[i-start] = str[i];
    }
    ToknovDV_String res = tmp;
    delete[] tmp;
    
    return res;
}


std::ostream& operator << (std::ostream& os, const ToknovDV_String& ts)
{
    for(size_t i = 0; i < ts.sz; ++i)
        os << ts.str[i];
    
    return os;
}

std::istream& operator >> (std::istream& is, ToknovDV_String& ts)
{
    size_t buffer_size = 10;
    size_t len = 0;
    char* s = new char[buffer_size];
    char c;
    
    
    while(is.get(c))
    {
        if ((c == ' ' || c == '\n') && len >0) break;
        else if(len <= 0 && (c == ' ' || c == '\n'))
            continue;
        
        if(len == buffer_size)
        {
            char* tmp_s = new char[buffer_size + 10];
            buffer_size += 10;
            std::copy(s, s+len, tmp_s);
            delete[] s;
            s = tmp_s;
        }
        
        s[len] = c;
        ++len;
    }
    
   if(len > 0)
   {
        delete[] ts.str;
        ts.str = new char[len];
        std::copy(s, s+len, ts.str);
        ts.sz = len;
        delete[] s;
    } else
        delete[] s;
    
    
    return is;
}

void ToknovDV_String::erase(const size_t idx)
{
    if(idx >= sz || idx < 0)
        throw std::out_of_range("");
    
    char* s = new char[sz-1];
    
    for(size_t i = idx; i < sz-1; ++i)
        std::swap(str[i], str[i+1]);
    
    --sz;
    
    std::copy(str, str+sz, s);
    delete[] str;
    str = s;
    
}

std::istream& getline(std::istream& is, ToknovDV_String& ts)
{
    size_t buffer_size = 10;
    size_t len = 0;
    char* s = new char[buffer_size];
    char c;
    
    
    while(is.get(c))
    {
        if (c == '\n' && len > 0) break;
        if(len == buffer_size)
        {
            char* tmp_s = new char[buffer_size + 10];
            buffer_size += 10;
            std::copy(s, s+len, tmp_s);
            delete[] s;
            s = tmp_s;
        }
        
        s[len] = c;
        ++len;
    }
    
    
    if(len > 0)
    {
        delete[] ts.str;
        ts.str = new char[len];
        std::copy(s, s+len, ts.str);
        ts.sz = len;
        
        delete[] s;
    } else
        delete[] s;
    
    return is;
}


bool word_isdigit(const ToknovDV_String& ts)
{
    for(size_t i = 0; i < ts.get_length(); ++i)
        if (ts[i] < 48 || ts[i] > 57)
            return false;
    
    return true;
}

bool isalpha(const char& c)
{
    return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}
