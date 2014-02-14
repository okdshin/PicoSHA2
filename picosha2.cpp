#ifdef PICOSHA2_UNIT_TEST
#include "picosha2.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace picosha2;

template<typename RaIter>
void OutputHex(RaIter begin, RaIter end, std::ostream& os){
	os.setf(std::ios::hex, std::ios::basefield);
	while(begin != end){
		os.width(2);
		os.fill('0');
		os << static_cast<unsigned int>(*begin);
		++begin;
	}	
	os.setf(std::ios::dec, std::ios::basefield);
}

template<typename OutIter>
void InputHex(std::istream& is, OutIter out){
	char c;
	std::vector<char> buffer;
	while(is){
		if(buffer.size() == 2){
			*(out++) = (buffer.front()*16+buffer.back());
			buffer.clear();
		}
		is >> c;
		if('0' <= c && c <= '9'){
			buffer.push_back(c-'0');
		}else
		if('a' <= c && c <= 'f'){
			buffer.push_back(c-'a'+10);	
		}
	}
}

int main(int argc, char* argv[])
{
	std::string message = "The quick brown fox jumps over the lazy dog";
	//std::string message = "";
	OutputHex(message.begin(), message.end(), std::cout << "src : ");
	std::cout << "\n";
	std::vector<unsigned char> result(32, 0);
	picosha2::hash(message.begin(), message.end(), result.begin());
	OutputHex(result.begin(), result.end(), std::cout << "hash: ");
	std::cout << "\n";

	std::vector<byte_t>collect_answer;
	std::string collect_answer_hex_str = 
		"d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592";
	std::cout << "coll: " << collect_answer_hex_str << std::endl;
	std::istringstream iss(collect_answer_hex_str);
	InputHex(iss, std::back_inserter(collect_answer));
	OutputHex(collect_answer.begin(), collect_answer.end(), std::cout << "coll: ");
	std::cout << "\n";
	if(collect_answer.end() != 
			std::search(collect_answer.begin(), collect_answer.end(), 
				result.begin(), result.end())){
		std::cout << "collect!!" << std::endl; 
	}
	else {
		std::cout << "incollect..." << std::endl;
	}


    return 0;
}

#endif
