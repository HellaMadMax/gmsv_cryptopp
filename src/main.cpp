#pragma comment( lib, "ws2_32" )
#define CRYPTOPP_DEFAULT_NO_DLL
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <string>
#include <winsock2.h>
#include "dll.h"
#include "md2.h"
#include "md4.h"
#include "md5.h"

#include "Interface.h"
using namespace GarrysMod::Lua;
using namespace CryptoPP;

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

int crypto_md5( lua_State *state )
{
	LUA->CheckType( 1, Type::STRING );
	std::string str = LUA->GetString(1);
	
	byte Digest[ Weak1::MD5::DIGESTSIZE ];
	Weak1::MD5().CalculateDigest( (byte *)&Digest, (byte *)str.c_str(), str.length() );
	
	std::string output;
	ArraySource( Digest, sizeof(Digest), true, new HexEncoder(new StringSink(output)) );
	
	LUA->PushString( output.c_str() );
	return 1;
}

int crypto_sha1( lua_State *state )
{
	LUA->CheckType( 1, Type::STRING );
	std::string str = LUA->GetString(1);
	
	byte Digest[ SHA1::DIGESTSIZE ];
	SHA1().CalculateDigest( (byte *)&Digest, (byte *)str.c_str(), str.length() );
	
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

int crypto_sha256( lua_State *state )
{
	LUA->CheckType( 1, Type::STRING );
	std::string str = LUA->GetString(1);
	
	byte Digest[ SHA256::DIGESTSIZE ];
	SHA256().CalculateDigest( (byte *)&Digest, (byte *)str.c_str(), str.length() );
	
	std::string output;
	ArraySource( Digest, sizeof(Digest), true, new HexEncoder(new StringSink(output)) );
	
	LUA->PushString( output.c_str() );
	return 1;
}

int crypto_sha384( lua_State *state )
{
	LUA->CheckType( 1, Type::STRING );
	std::string str = LUA->GetString(1);
	
	byte Digest[ SHA384::DIGESTSIZE ];
	SHA384().CalculateDigest( (byte *)&Digest, (byte *)str.c_str(), str.length() );
	
	std::string output;
	ArraySource( Digest, sizeof(Digest), true, new HexEncoder(new StringSink(output)) );
	
	LUA->PushString( output.c_str() );
	return 1;
}

int crypto_sha512( lua_State *state )
{
	LUA->CheckType( 1, Type::STRING );
	std::string str = LUA->GetString(1);
	
	byte Digest[ SHA512::DIGESTSIZE ];
	SHA512().CalculateDigest( (byte *)&Digest, (byte *)str.c_str(), str.length() );
	
	std::string output;
	ArraySource( Digest, sizeof(Digest), true, new HexEncoder(new StringSink(output)) );
	
	LUA->PushString( output.c_str() );
	return 1;
}

GMOD_MODULE_OPEN()
{
	LUA->PushSpecial( SPECIAL_GLOB );
		LUA->CreateTable();
			LUA->PushCFunction( crypto_md2 ); LUA->SetField(-2, "md2");
			LUA->PushCFunction( crypto_md4 ); LUA->SetField(-2, "md4");
			LUA->PushCFunction( crypto_md5 ); LUA->SetField(-2, "md5");
			LUA->PushCFunction( crypto_sha1 ); LUA->SetField(-2, "sha1");
			LUA->PushCFunction( crypto_sha256 ); LUA->SetField(-2, "sha224");
			LUA->PushCFunction( crypto_sha256 ); LUA->SetField(-2, "sha256");
			LUA->PushCFunction( crypto_sha256 ); LUA->SetField(-2, "sha384");
			LUA->PushCFunction( crypto_sha512 ); LUA->SetField(-2, "sha512");
		LUA->SetField(-2, "crypto");
	LUA->Pop();
	return 0;
}