#ifdef PICOSHA2_UNIT_TEST
#include "picosha2.h"
#include <iostream>
#include <list>

#define PICOSHA2_CHECK_EQUAL(a, b){\
	if(a == b){\
		std::cout << "\033[32m" << __FUNCTION__ << "(LINE:" << __LINE__ << ") is succeeded." << "\033[39m" << std::endl;\
	}\
	else{\
		std::cout << "\033[31m" << __FUNCTION__ << "(LINE:" << __LINE__ << ") is failed.\n\t" << #a << " != " << #b \
		<< "\033[39m" << std::endl;\
	}\
}
#define PICOSHA2_CHECK_EQUAL_BYTES(a, b){\
	if(is_same_bytes(a, b)){\
		std::cout << "\033[32m" << __FUNCTION__ << "(LINE:" << __LINE__ << ") is succeeded." << "\033[39m" << std::endl;\
	}\
	else{\
		std::cout << "\033[31m" << __FUNCTION__ << "(LINE:" << __LINE__ << ") is failed.\n\t" << #a << " != " << #b \
		<< "\033[39m" << std::endl;\
	}\
}

template<typename InIter1, typename InIter2>
bool is_same_bytes(InIter1 first1, InIter1 last1, InIter2 first2, InIter2 last2){
	if(std::distance(first1, last1) != std::distance(first2, last2)){
		return false;
	}
	return std::search(first1, last1, first2, last2) != last1;
}

template<typename InContainer1, typename InContainer2>
bool is_same_bytes(const InContainer1& bytes1, const InContainer2& bytes2){
	return is_same_bytes(bytes1.begin(), bytes1.end(), bytes2.begin(), bytes2.end());
}

template<typename OutIter>
void input_hex(std::istream& is, OutIter first, OutIter last){
	char c;
	std::vector<char> buffer;
	while(first != last){
		if(buffer.size() == 2){
			*(first++) = (buffer.front()*16+buffer.back());
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
void hex_string_to_bytes(const std::string& hex_str, OutIter first, OutIter last){
	assert(hex_str.length() >= 2*std::distance(first, last));
	std::istringstream iss(hex_str);
	input_hex(iss, first, last);
}

template<typename OutContainer>
void hex_string_to_bytes(const std::string& hex_str, OutContainer& bytes){
	hex_string_to_bytes(hex_str, bytes.begin(), bytes.end());
}

typedef std::pair<std::string, std::string> mess_and_hash;
const size_t sample_size = 3;
const std::pair<std::string, std::string> sample_message_list[3] = {
	mess_and_hash("", 
			"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"),
	mess_and_hash("The quick brown fox jumps over the lazy dog",
			"d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592"),
	mess_and_hash("The quick brown fox jumps over the lazy dog.",
			"ef537f25c895bfa782526529a9b63d97aa631564d5d789c2b765448c8635fb6c")
};

void test(){
	for(std::size_t i = 0; i < 3; ++i){
		std::string src_str = sample_message_list[i].first;
		std::string ans_hex_str = sample_message_list[i].second;
		std::vector<unsigned char> ans(32);
		hex_string_to_bytes(ans_hex_str, ans);
		{
			std::vector<unsigned char> hash(32);
			picosha2::hash256(src_str.begin(), src_str.end(), hash.begin(), hash.end());
			PICOSHA2_CHECK_EQUAL_BYTES(ans, hash);
		}
		{
			std::vector<unsigned char> hash(32);
			picosha2::hash256(src_str, hash);
			PICOSHA2_CHECK_EQUAL_BYTES(ans, hash);
		}
		{
			std::list<unsigned char> hash(32);
			picosha2::hash256(src_str.begin(), src_str.end(), hash.begin(), hash.end());
			PICOSHA2_CHECK_EQUAL_BYTES(ans, hash);
		}
		{
			std::list<unsigned char> hash(32);
			picosha2::hash256(src_str, hash);
			PICOSHA2_CHECK_EQUAL_BYTES(ans, hash);
		}
		{
			std::string hash_hex_str;
			picosha2::hash256_hex_string(src_str.begin(), src_str.end(), hash_hex_str);
			PICOSHA2_CHECK_EQUAL(ans_hex_str, hash_hex_str);
		}
		{
			std::string hash_hex_str;
			picosha2::hash256_hex_string(src_str, hash_hex_str);
			PICOSHA2_CHECK_EQUAL(ans_hex_str, hash_hex_str);
		}
		{
			std::string hash_hex_str = 
				picosha2::hash256_hex_string(src_str.begin(), src_str.end());
			PICOSHA2_CHECK_EQUAL(ans_hex_str, hash_hex_str);
		}
		{
			std::string hash_hex_str = picosha2::hash256_hex_string(src_str);
			PICOSHA2_CHECK_EQUAL(ans_hex_str, hash_hex_str);
		}
		
		std::vector<unsigned char> src_vect(src_str.begin(), src_str.end());
		{
			std::vector<unsigned char> hash(32);
			picosha2::hash256(src_vect.begin(), src_vect.end(), hash.begin(), hash.end());
			PICOSHA2_CHECK_EQUAL_BYTES(ans, hash);
		}
		{
			std::vector<unsigned char> hash(32);
			picosha2::hash256(src_vect, hash);
			PICOSHA2_CHECK_EQUAL_BYTES(ans, hash);
		}
		{
			std::list<unsigned char> hash(32);
			picosha2::hash256(src_vect.begin(), src_vect.end(), hash.begin(), hash.end());
			PICOSHA2_CHECK_EQUAL_BYTES(ans, hash);
		}
		{
			std::list<unsigned char> hash(32);
			picosha2::hash256(src_vect, hash);
			PICOSHA2_CHECK_EQUAL_BYTES(ans, hash);
		}
		{
			std::string hash_hex_str;
			picosha2::hash256_hex_string(src_vect.begin(), src_vect.end(), hash_hex_str);
			PICOSHA2_CHECK_EQUAL(ans_hex_str, hash_hex_str);
		}
		{
			std::string hash_hex_str;
			picosha2::hash256_hex_string(src_vect, hash_hex_str);
			PICOSHA2_CHECK_EQUAL(ans_hex_str, hash_hex_str);
		}
		{
			std::string hash_hex_str = 
				picosha2::hash256_hex_string(src_vect.begin(), src_vect.end());
			PICOSHA2_CHECK_EQUAL(ans_hex_str, hash_hex_str);
		}
		{
			std::string hash_hex_str = picosha2::hash256_hex_string(src_vect);
			PICOSHA2_CHECK_EQUAL(ans_hex_str, hash_hex_str);
		}

	}
}

int main(int argc, char* argv[])
{
	test();

    return 0;
}

#endif
