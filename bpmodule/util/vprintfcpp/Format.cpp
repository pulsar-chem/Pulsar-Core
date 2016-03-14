#include <cstring>

#include "Format.hpp"

// PrintF format
//%[flags][width][.precision][length]spec
//    flags: -+#0  or space
//    width: number
//precision: number
//   length: characters
//     spec: letter


namespace vprintfcpp {

namespace detail {


bool GetNextFormat_(FormatInfo & fi, const std::string & str)
{
    // Remember - str may be a reference to fi.suffix
    // Also remember - prefix will contain what to print out
    // if this function returns false

    const size_t len = str.length();

    // shouldn't release memory
    fi.prefix.clear();
    fi.format.clear();

    if(len == 0)
        return false;


    // Find a % not followed by another %, copying
    // into prefix as we go
    // we need to replace %% with %
    // we know len > 0 (already checked)
    size_t idx;
    for(idx = 0; idx < len; ++idx)
    {
        if(str[idx] == '%')
        {
            if(str[idx] == '%' && idx < (len-1) && str[idx+1] == '%')
            {
                fi.prefix += '%';
                idx++; // skip the second %
            }
            else
                break; // found a format spec
        }
        else
            fi.prefix += str[idx];
    }

    if(idx >= len)
        return false;
    

    size_t fmt_begin = idx;
    size_t flag_begin = fmt_begin+1;

    // first, the flag characters
    const char * validflags = "+- #0";
    size_t width_begin = flag_begin;
    while(width_begin < len && strchr(validflags, str[width_begin]) != nullptr)
        width_begin++;

    // now the width
    size_t prec_begin = width_begin;
    while(prec_begin < len && isdigit(str[prec_begin]))
        prec_begin++;

    // precision, including period
    size_t length_begin = prec_begin;
    if(length_begin < len && str[length_begin] == '.')
    {
        length_begin++;

        while(length_begin < len && isdigit(str[length_begin]))
            length_begin++;
    }

    // length
    size_t spec_begin = length_begin;
    const char * validlengthchars = "hljztL";
    while(spec_begin < len && strchr(validlengthchars, str[spec_begin]) != nullptr)
        spec_begin++;

    // specifier
    size_t end = spec_begin;
    const char * validspec = "diuoxXfFeEgGaAcsp?";  // n not supported, %% handled elsewhere
    if(end < len && strchr(validspec, str[end]) != nullptr)
        end++;

    // check some things
    // Specifier must be one character
    if(end-spec_begin != 1)
        throw std::runtime_error("Zero characters for type specifier");

    // Length must be 0, 1, or 2 characters
    size_t length_len = spec_begin-length_begin;
    if(length_len > 2)
        throw std::runtime_error("Format length specification must be 0, 1, or 2 characters");

    // now we have the format
    fi.format = str.substr(fmt_begin, length_begin-fmt_begin);

    // length
    memset(fi.length, 0, 3);
    memcpy(fi.length, str.c_str()+length_begin, length_len);


    // length can only be certain combinations
    const char * validlengths[8] = { "hh", "h", "l", "ll", "j", "z", "t", "L" };
    bool found = false;
    for(int i = 0; i < 8; i++)
    {
        if(strcmp(validlengths[i], fi.length))
            found = true;
    }
    if(!found)
        throw std::runtime_error("Invalid length specifier");

    // spec
    fi.spec = str[spec_begin];

    // suffix last, since it may be aliased
    fi.suffix = str.substr(end);

    return true;
}





void Format_(std::ostream & os, FormatInfo & fi, const std::string & str)
{
    // if GetNextFormat_ returns false, fi.prefix contains the
    // string with appropriate substitutions for %%, etc
    if(GetNextFormat_(fi, str))
        throw std::runtime_error("Not enough arguments given to format string");
    else
        os << fi.prefix;
}




} // close namespace detail
} // close namespace vprintfcpp

