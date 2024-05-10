/*
Python.h contains pythonic utilites for c++

Current features:
-assert
-customizable assertion function
-print
-len
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <initializer_list>


#ifndef CPP_PYTHON_H
#define CPP_PYTHON_H

namespace py
{   
    // ---------------------------- //
    // --Helper functions/classes-- //
    // ---------------------------- //
    
    template< typename T>
    class HasLengthFunction
    {
        typedef char True[1];
        typedef char False[2];

        template< typename K>
        static True& test(decltype(&K::length));

        template<typename>
        static False& test(...);

    public:
        static const bool value = sizeof(test<T>(0)) == sizeof(True);
    };

    template< typename T>
    class HasLenFunction
    {   
        typedef char True[1];
        typedef char False[2];

        template< typename K>
        static True& test(decltype(&K::__len__));

        template<typename>
        static False& test(...);

    public:
        static const bool value = sizeof(test<T>(0)) == sizeof(True);
    };

    template< typename T>
    class HasReprFunction
    {   
        typedef char True[1];
        typedef char False[2];

        template< typename K>
        static True& test(decltype(&K::__repr__));

        template<typename>
        static False& test(...);

    public:
        static const bool value = sizeof(test<T>(0)) == sizeof(True);
    };

    // -------------- //
    // --Exceptions-- //
    // -------------- //

    // Base exception class
    class Exception : public std::exception
    {
    public:
        std::string ErrMsg = "";
        Exception(std::string errMSg="") {this->ErrMsg = errMSg;}
        std::string __repr__(){return this->ErrMsg;}
    };

    // Assertion failed
    class AssertionError : public Exception
    {
    public:
        AssertionError(std::string errMsg="") {this->ErrMsg = errMsg;}
    };

    // Wrong argument value of correct type
    class ValueError : public Exception
    {
    public:
        ValueError(std::string errMsg="") {this->ErrMsg = errMsg;}
    };

    // ----------------------- //
    // --Customization utils-- //
    // ----------------------- //
    
    std::string defaultAssertionFunction(std::string message)
    {
        std::string p_message = message.length() != 0 ? ": " + message : "";

        return std::string("AssertionError") + p_message;
    }

    std::string (*DefaultAssertionFunctionPtr) (std::string) = defaultAssertionFunction;

    // -------------------------- //
    // --Pythonic c++ utilities-- //
    // -------------------------- //
    
    // Pythonic print function
    // Prints the value to a stream.
    template< typename T>
    void print(T objects, std::string end="\n", bool flush=false)
    {   
        if constexpr (HasReprFunction<T>::value)
            std::cout << objects.__repr__();
        else
            std::cout << objects;

        if (flush)
            std::cout << end << std::flush;
        else
            std::cout << end;
    }

    // Pythonic print function
    // Prints the value to a stream.
    template< class T>
    void print(std::initializer_list<T> list, std::string sep=" ", std::string end="\n", bool flush=false)
    {   
        for (auto item: list)
        {
            print(item, "", false);
            print(sep, "", false);
        }

        if (flush)
            std::cout << end << std::flush;
        else
            std::cout << end;
    }

    // Python assert keyword
    // Raises an AssertionError if the  condition provided is false
    void assert(bool flag, std::string message="")
    {
        if ( !flag)
            throw AssertionError(DefaultAssertionFunctionPtr(message));
    }

    // Pythonic len() function for C++
    // Works on objects with 'length()' or '__len__()' method
    template < typename T>
    size_t length(T obj)
    {
        if constexpr (HasLengthFunction<T>::value)
            return obj.length();
        else if constexpr (HasLenFunction<T>::value)
            return obj.__len__();
        else
            {
                std::string errMsg = std::string("object of type '") + typeid(obj).name() + std::string("' has no len()");

                throw ValueError(errMsg);
            }
    }

    // Python len() function
    // Same as 'length()' but returns an integer instead
    template< typename T>
    int len(T obj)
    {
        try
        {
            return (int)(length(obj));
        }
        catch (std::exception& e)
        {
            throw;
        }
    }

    // Work in progress
    // File system
    
    // Wrapper class to work with files
    /* class File
    {
    public:
        FILE file = nullptr;
        OpeningMode mode = nullptr;

        File(FILE* &file, OpeningMode mode)
        {
            this->file = file;
            this->mode = mode;
        }

        void close()
        {
            fclose(this->file);
        }
    };


    enum class OpeningMode
    {
        R = 1,
        X = 2,
        A = 3,
        T = 4,
        B = 5,
        PLUS = 6
    };

    File open(std::string path, OpeningMode mode=OpeningMode::R)
    {   
        FILE* file = nullptr

        if (mode == OpeningMode::B)
            file = &fopen(path, _ios_base::in | _ios::binary);
        else
            file = &fopen(path, _ios_base::in);

        return File(file, mode);
    } */
}

#endif
