#include "crypto.h"

CRYPTO::CRYPTO()
{
	static const char alphabet[] =
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"0123456789";
	
	std::random_device rd;
	std::default_random_engine rng(rd());
	std::uniform_int_distribution<> dist(0,sizeof(alphabet)/sizeof(*alphabet)-2);

	// generate the key pair: secret and public key
	pk = crypto_box_keypair(&sk);
	
	// randomly generate nonce
	n.reserve(crypto_box_NONCEBYTES);

	std::generate_n(std::back_inserter(n), crypto_box_NONCEBYTES,
			[&]() { return alphabet[dist(rng)];}); 

}

CRYPTO::~CRYPTO()
{

}
