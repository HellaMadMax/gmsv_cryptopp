#include <string>

#ifdef _WINDOWS
#pragma comment( lib, "ws2_32" )
#define CRYPTOPP_DEFAULT_NO_DLL
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <winsock2.h>
#include "dll.h"
#include "md2.h"
#include "md4.h"
#include "md5.h"
using namespace CryptoPP;
#else
#include "hl_hashwrapper.h"
#include "hl_wrapperfactory.h"
#include "hl_exception.h"
#include "hl_md5.h"
#include "hl_md5wrapper.h"
#include "hl_sha1.h"
#include "hl_sha1wrapper.h"
#include "hl_sha2mac.h"
#include "hl_sha256.h"
#include "hl_sha256wrapper.h"
#include "hl_sha2ext.h"
#include "hl_sha384wrapper.h"
#include "hl_sha512wrapper.h"
#include "hl_types.h"
#include "hashlibpp.h"
#endif

#include "Interface.h"
using namespace GarrysMod::Lua;

#ifdef _WINDOWS
int crypto_md2( lua_State *state )
{
	LUA->CheckType( 1, Type::STRING );
	std::string str = LUA->GetString(1);
	
	byte Digest[ Weak1::MD2::DIGESTSIZE ];
	Weak1::MD2().CalculateDigest( (byte *)&Digest, (byte *)str.c_str(), str.length() );
	
	std::string output;
	ArraySource( Digest, sizeof(Digest), true, new HexEncoder(new StringSink(output)) );
	
	LUA->PushString( output.c_str() );
	return 1;
}

int crypto_md4( lua_State *state )
{
	LUA->CheckType( 1, Type::STRING );
	std::string str = LUA->GetString(1);
	
	byte Digest[ Weak1::MD4::DIGESTSIZE ];
	Weak1::MD4().CalculateDigest( (byte *)&Digest, (byte *)str.c_str(), str.length() );
	
	std::string output;
	ArraySource( Digest, sizeof(Digest), true, new HexEncoder(new StringSink(output)) );
	
	LUA->PushString( output.c_str() );
	return 1;
}


int crypto_sha224( lua_State *state )
{
	LUA->CheckType( 1, Type::STRING );
	std::string str = LUA->GetString(1);
	
	byte Digest[ SHA224::DIGESTSIZE ];
	SHA224().CalculateDigest( (byte *)&Digest, (byte *)str.c_str(), str.length() );
	
	std::string output;
	ArraySource( Digest, sizeof(Digest), true, new HexEncoder(new StringSink(output)) );
	
	LUA->PushString( output.c_str() );
	return 1;
}
#endif

int crypto_md5( lua_State *state )
{
	LUA->CheckType( 1, Type::STRING );
	std::string str = LUA->GetString(1);
	std::string output;
	
	#ifdef _WINDOWS
	byte Digest[ Weak1::MD5::DIGESTSIZE ];
	Weak1::MD5().CalculateDigest( (byte *)&Digest, (byte *)str.c_str(), str.length() );
	ArraySource( Digest, sizeof(Digest), true, new HexEncoder(new StringSink(output)) );
	#else
	hashwrapper *h = new md5wrapper();
	output = h->getHashFromString( str.c_str() );
	delete h;
	#endif
	
	LUA->PushString( output.c_str() );
	return 1;
}

int crypto_sha1( lua_State *state )
{
	LUA->CheckType( 1, Type::STRING );
	std::string str = LUA->GetString(1);
	std::string output;
	
	#ifdef _WINDOWS	
	byte Digest[ SHA1::DIGESTSIZE ];
	SHA1().CalculateDigest( (byte *)&Digest, (byte *)str.c_str(), str.length() );
	ArraySource( Digest, sizeof(Digest), true, new HexEncoder(new StringSink(output)) );
	#else
	hashwrapper *h = new sha1wrapper();
	output = h->getHashFromString( str.c_str() );
	delete h;
	#endif
	
	LUA->PushString( output.c_str() );
	return 1;
}

int crypto_sha256( lua_State *state )
{
	LUA->CheckType( 1, Type::STRING );
	std::string str = LUA->GetString(1);
	std::string output;
	
	#ifdef _WINDOWS	
	byte Digest[ SHA256::DIGESTSIZE ];
	SHA256().CalculateDigest( (byte *)&Digest, (byte *)str.c_str(), str.length() );
	ArraySource( Digest, sizeof(Digest), true, new HexEncoder(new StringSink(output)) );
	#else
	hashwrapper *h = new sha256wrapper();
	output = h->getHashFromString( str.c_str() );
	delete h;
	#endif
	
	LUA->PushString( output.c_str() );
	return 1;
}

int crypto_sha384( lua_State *state )
{
	LUA->CheckType( 1, Type::STRING );
	std::string str = LUA->GetString(1);
	std::string output;
	
	#ifdef _WINDOWS	
	byte Digest[ SHA384::DIGESTSIZE ];
	SHA384().CalculateDigest( (byte *)&Digest, (byte *)str.c_str(), str.length() );
	ArraySource( Digest, sizeof(Digest), true, new HexEncoder(new StringSink(output)) );
	#else
	hashwrapper *h = new sha384wrapper();
	output = h->getHashFromString( str.c_str() );
	delete h;
	#endif
	
	LUA->PushString( output.c_str() );
	return 1;
}

int crypto_sha512( lua_State *state )
{
	LUA->CheckType( 1, Type::STRING );
	std::string str = LUA->GetString(1);
	std::string output;
	
	#ifdef _WINDOWS	
	byte Digest[ SHA512::DIGESTSIZE ];
	SHA512().CalculateDigest( (byte *)&Digest, (byte *)str.c_str(), str.length() );
	ArraySource( Digest, sizeof(Digest), true, new HexEncoder(new StringSink(output)) );
	#else
	hashwrapper *h = new sha512wrapper();
	output = h->getHashFromString( str.c_str() );
	delete h;
	#endif
	
	LUA->PushString( output.c_str() );
	return 1;
}

GMOD_MODULE_OPEN()
{
	LUA->PushSpecial( SPECIAL_GLOB );
		LUA->CreateTable();
			#ifdef _WINDOWS
			LUA->PushCFunction( crypto_md2 ); LUA->SetField(-2, "md2");
			LUA->PushCFunction( crypto_md4 ); LUA->SetField(-2, "md4");
			LUA->PushCFunction( crypto_sha224 ); LUA->SetField(-2, "sha224");
			#endif
			LUA->PushCFunction( crypto_md5 ); LUA->SetField(-2, "md5");
			LUA->PushCFunction( crypto_sha1 ); LUA->SetField(-2, "sha1");
			LUA->PushCFunction( crypto_sha256 ); LUA->SetField(-2, "sha256");
			LUA->PushCFunction( crypto_sha384 ); LUA->SetField(-2, "sha384");
			LUA->PushCFunction( crypto_sha512 ); LUA->SetField(-2, "sha512");
		LUA->SetField(-2, "crypto");
	LUA->Pop();
	return 0;
}
