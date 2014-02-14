#ifdef PICOSHA2_UNIT_TEST
#include "picosha2.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace picosha2;

template<typename InIter>
void OutputHex(InIter first, InIter last, std::ostream& os){
	os.setf(std::ios::hex, std::ios::basefield);
	while(first != last){
		os.width(2);
		os.fill('0');
		os << static_cast<unsigned int>(*first);
		++first;
	}	
	os.setf(std::ios::dec, std::ios::basefield);
}

template<typename InIter>
void OutputHexLine(InIter first, InIter last, std::ostream& os){
	OutputHex(first, last, os);
	os << "\n";
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

template<typename OutIter>
void HexStringToBytes(const std::string& hex_str, OutIter out){
	std::istringstream iss(hex_str);
	InputHex(iss, out);
}

template<typename InIter>
std::string BytesToHexString(InIter first, InIter last){
	std::ostringstream oss;
	OutputHex(first, last, oss);
	return oss.str();
}

template<typename InIter1, typename InIter2>
bool IsSame(InIter1 first1, InIter1 last1, InIter2 first2, InIter2 last2){
	if(std::distance(first1, last1) != std::distance(first2, last2)){
		return false;
	}
	return std::search(first1, last1, first2, last2) != last1;
}


void Test(){
	typedef std::pair<std::string, std::string> mess_and_hash;
	const std::pair<std::string, std::string> message_list[3] = {
		mess_and_hash("", 
				"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"),
		mess_and_hash("The quick brown fox jumps over the lazy dog",
				"d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592"),
		mess_and_hash("The quick brown fox jumps over the lazy dog.",
				"ef537f25c895bfa782526529a9b63d97aa631564d5d789c2b765448c8635fb6c")
	};

	for(std::size_t i = 0; i < 3; ++i){
		std::string src = message_list[i].first;
		std::vector<byte_t> ans;
		HexStringToBytes(message_list[i].second, std::back_inserter(ans));
		{
			std::vector<byte_t> hashed(32, 0);
			hash256(src.begin(), src.end(), hashed.begin());
			std::cout << "src: \"" << src << "\"\n";
			OutputHexLine(hashed.begin(), hashed.end(), std::cout << "hashed: ");
			OutputHexLine(ans.begin(), ans.end(), std::cout << "answer: ");
			if(IsSame(hashed.begin(), hashed.end(), ans.begin(), ans.end())){
				std::cout << "collect!" << std::endl;
			}
			else {
				std::cout << "error!" << std::endl; 
			}
			std::cout << "\n";
		}
	}
}

int main(int argc, char* argv[])
{
	Test();

    return 0;
}

#endif
