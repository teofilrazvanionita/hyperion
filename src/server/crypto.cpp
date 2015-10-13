#include "crypto.h"

CRYPTO::CRYPTO()
{
	pk = crypto_box_keypair(&sk);
}

CRYPTO::~CRYPTO()
{

}
