#include <tuple>
#include <utility>
#include <iostream>
#include <functional>
#include <algorithm>
#include <type_traits>
#include <vector>
#include <list>
#include <assert.h>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>
#include <cxxabi.h>

template <int N>
struct Fib {
	static long long int const
		value = Fib<N - 1>::value + Fib<N - 2>::value;
};
template<>
struct Fib<0> {
	static int const value = 0;
};
template<>
struct Fib<1> {
	static int const value = 1;
};


template<int ...Ints >
struct IntList;

template<int first, int... Ints>
struct IntList<first, Ints...> {
	static int const Head = first;
	using Tail = IntList<Ints...>;
};

template<>
struct IntList<> {};


template <typename TL>
struct Length {
	static int const value = 1 +
			Length<typename TL::Tail>::value;
};

template<>
struct Length<IntList<>> {
	static int const value = 0;
};


template<int H, typename ...Args>
struct IntCons;

template<int H, int... Types>
struct IntCons<H, IntList<Types...>> {
	using type = IntList<H, Types...>;
};


template<int M, class TL = IntList<>>
struct Generate;

template<int M, int ... Types>
struct Generate<M, IntList<Types...>> {
	static int const Head = M - 1;
    using type = Generate<M - 1, typename IntCons<M - 1, IntList<Types...>>::type>;
    using Tail = type;
};

template <int ... Types>
struct Generate<0, IntList<Types...>> {
	using type = IntList<0, Types...>;
};

template <typename TL>
void print(){
	std::cout << TL::Head << " ";
	print<typename TL::Tail>();
};
template<>
void print<IntList<>>(){
	std::cout << std::endl;
};

template<int N>
struct Square
{
	static constexpr int value = N * N;
};


int main (int argc, char** argv){
	std::cout << Fib<27>::value << '\n';
	std::cout << Fib<12>::value << std::endl;
    using primes = IntList<3, 4, 5, 7, 11, 13>;
    constexpr size_t len = Length<primes>::value;
//  using primes = IntList<3, 4, 5, 7, 11, 13>;
//	constexpr int head = primes::Head;
//	using odd_primes = primes::Tail;
//	constexpr size_t len = Length<primes>::value;
//  std::cout << len << '\n';
    char *realname;
    int status;
	using L1 = IntList<1,2,3,4>;
    //std::cout << typeid(L1).name() << '\n';
    using L2 = IntCons<0, L1>::type;               // IntList<0,1,2,3,4>
    //std::cout << typeid(L2).name() << '\n';      // 7IntList  IJLi0ELi1ELi2ELi3ELi4EEE

    IntCons<0, L1>::type u3;
    const std::type_info &ti3 = typeid(u3);
    realname = abi::__cxa_demangle(ti3.name(), 0, 0, &status);  // 8Generate I Li4E7IntListIJ  Li4EEEE
    std::cout << ti3.name() << " " << realname << " " << status << '\n';


    IntList<0,1,2,3,4> u1;
    const std::type_info &ti = typeid(u1);
    realname = abi::__cxa_demangle(ti.name(), 0, 0, &status);   // 8Generate I Li4E7IntListIJ  Li4EEEE
    std::cout << ti.name() << " " << realname << " " << status << '\n';

	using L3 = Generate<5>::type;      // IntList<0,1,2,3,4>
    Generate<5>::type u2;
    const std::type_info &ti2 = typeid(u2);
    realname = abi::__cxa_demangle(ti2.name(), 0, 0, &status);
    std::cout << ti2.name() << " " << realname << " " << status << '\n';

	//print<IntList<0,1,2,3,4,5>>();
	//print<IntCons<2,L2>::type>();
	//std::cout << typeid(Generate<5>::type).name() << '\n';


	//print<L3>();
	//constexpr size_t len = Length<L3>::value;
	//std::cout << len << '\n';
}

