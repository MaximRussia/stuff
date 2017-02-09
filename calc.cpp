#include <cctype>  // isspace
#include <cstdlib>  // strtod, strtol
#include <functional>  // function
#include <iomanip>  // setw
#include <iostream>  // cerr
#include <string>  // cerr

template<typename T>
T strtot(const char* start, char** end) { return std::strtol(start, end, 0); }
template<>
double strtot(const char* start, char** end) { return std::strtod(start, end); }
template<>
float strtot(const char* start, char** end) { return std::strtod(start, end); }

template<typename T>
T eval(const char program[]) {
	const char* p = program;
	auto skip_ws = [&]() { while (*p && std::isspace(*p)) ++p; return *p; };
	auto peek = skip_ws;
	auto next = [&]() { return *p ? *p++ : 0; };
	auto moro = [&](char positive, char negative) {
		skip_ws();
		auto result = *p == negative ? -1 : (*p == positive ? 1 : 0);
		if (result) next();
		return result;
	};
	auto show_err = [&](std::string msg) {
		std::cout << "ERROR: " << msg << "\n"
				  << ">>> " << program << "\n"
				  << "    " << std::setw(p - program) << "" << "^\n";
	};
	std::function<T()> expr;
	std::function<T()> term;
	auto expr_and_err = [&]() {
		auto result = expr();
		if (peek() != 0 && peek() != ';') show_err("Unconsumed input");
		return result;
	};
	term = [&]() {
		if (int r = moro('+', '-')) return r > 0 ? term() : -term();
		if (peek() == '(') {
			next();
			auto result = expr();
			if (next() != ')') show_err("Unbalanced parens");
			return result;
		}
		char* pend;
		auto result = strtot<T>(p, &pend);
		if (p == pend) show_err("Expected a number or an expression");
		p = pend;
		return result;
	};
	auto mul = [&]() {
		auto result = term();
		while (int r = moro('*', '/')) {
			result = r > 0 ? result*term() : result/term();
		}
		return result;
	};
	auto add = [&]() {
		auto result = mul();
		while (int r = moro('+', '-')) result += r > 0 ? mul() : -mul();
		return result;
	};
	expr = add;
	return expr_and_err();
}

template<typename T>
void test(const char* s) {
	std::cout << s << " == (" << typeid(T).name() << ") " << eval<T>(s) << "\n";
}

int main() {
	test<int>("2+2*2");
	test<double>("2+2*2+5+5*6");
}
