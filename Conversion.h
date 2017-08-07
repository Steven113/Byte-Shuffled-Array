#ifndef CONVERSION
#define CONVERSION
//from https://stackoverflow.com/questions/5055636/casting-an-object-to-char-for-saving-loading
template<class To, class From>
To any_cast(From v)
{
    return static_cast<To>(static_cast<void*>(v));
}
#endif