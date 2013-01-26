//Some of this is from GotW #88, google away

//This will only work on the stack, as far as I know.  Do not think it will work on
//class members
#define DelayDest(type) const type&

template<int N>
struct ConstStr
{
	ConstStr (const char * str):str(str){}
	const char *str;
	enum { size = N -1};
};

//You've got to delete this one
template<int N>
const ConstStr<N>& MakeConstStrInClass(const char (&str)[N] )
{
	ConstStr<N> *ret = new ConstStr<N>(&str[0]);
	return *ret;
}

//This requires DelayDest(auto), it will get deleted when the DelayDest(auto) var
//goes out of scope
template<int N>
ConstStr<N> MakeConstStr(const char (&str)[N])
{
	return ConstStr<N> (str);
}