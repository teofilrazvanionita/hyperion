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

CRYPTO::CRYPTO  (std::string& client_pk, std::string& client_nonce)
{
        pk = client_pk;
        n = client_nonce;
}

// assignment operator
CRYPTO & CRYPTO::operator = (const CRYPTO &ci)
{
	if(this != &ci){
		pk = ((CRYPTO &)ci).getPK();
		sk = ((CRYPTO &)ci).getSK();
		n = ((CRYPTO &)ci).getNonce();
	}

	return *this;
}

bool CRYPTO::operator == (const CRYPTO &ci)
{
	if(this != &ci){
                if((pk.compare(((CRYPTO &)ci).getPK()) == 0) && (sk.compare(((CRYPTO &)ci).getSK()) == 0) && (n.compare(((CRYPTO &)ci).getNonce()) == 0))
			return true;
		else
			return false;
	}

	return true;
}

bool CRYPTO::operator != (const CRYPTO &ci)
{
	return !(*this == ci);
}

std::string & CRYPTO::getPK ()
{
	return this->pk;
}

std::string & CRYPTO::getSK ()
{
	return this->sk;
}

std::string & CRYPTO::getNonce ()
{
	return this->n;
}

// copy constructor
CRYPTO::CRYPTO (const CRYPTO &ci)
{
	pk = ((CRYPTO &)ci).getPK();
	sk = ((CRYPTO &)ci).getSK();
	n = ((CRYPTO &)ci).getNonce();
}
