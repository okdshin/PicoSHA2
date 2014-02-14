#ifdef PICOSHA2_UNIT_TEST
#include "picosha2.h"
#include <iostream>

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
	if(picosha2::is_same_bytes(a, b)){\
		std::cout << "\033[32m" << __FUNCTION__ << "(LINE:" << __LINE__ << ") is succeeded." << "\033[39m" << std::endl;\
	}\
	else{\
		std::cout << "\033[31m" << __FUNCTION__ << "(LINE:" << __LINE__ << ") is failed.\n\t" << #a << " != " << #b \
		<< "\033[39m" << std::endl;\
	}\
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

void test_hash256(){
	for(std::size_t i = 0; i < 3; ++i){
		std::string src = sample_message_list[i].first;
		std::string ans_hex_str = sample_message_list[i].second;
		std::vector<unsigned char> ans(32);
		picosha2::hex_string_to_bytes(ans_hex_str, ans);
		{
			std::vector<picosha2::byte_t> hashed(32);
			picosha2::hash256(src.begin(), src.end(), hashed.begin(), hashed.end());
			PICOSHA2_CHECK_EQUAL_BYTES(ans, hashed);
		}
		{
			std::vector<picosha2::byte_t> hashed(32);
			picosha2::hash256(src, hashed);
			PICOSHA2_CHECK_EQUAL_BYTES(ans, hashed);
		}
		{
			std::vector<picosha2::byte_t> hashed = 
				picosha2::hash256<std::vector<picosha2::byte_t> >(src);
			PICOSHA2_CHECK_EQUAL_BYTES(ans, hashed);
		}
		{
			std::string hex_str;
			picosha2::hash256_hex_string(src.begin(), src.end(), hex_str);
			PICOSHA2_CHECK_EQUAL(ans_hex_str, hex_str);
		}
		/*
		{
			std::string hex_str;
			picosha2::hash256_hex_string<std::string>(src, hex_str);
			PICOSHA2_CHECK_EQUAL(ans_hex_str, hex_str);
		}
		*/
		{
			std::string hex_str = picosha2::hash256_hex_string(src);
			PICOSHA2_CHECK_EQUAL(ans_hex_str, hex_str);
		}
		{
			std::string hex_str = picosha2::hash256_hex_string(src.begin(), src.end());
			PICOSHA2_CHECK_EQUAL(ans_hex_str, hex_str);
		}
	}
}

void test_hash256_hex_string(){
}

int main(int argc, char* argv[])
{
	test_hash256();

    return 0;
}

#endif
