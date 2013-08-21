local path_gmodds = "E:\\Steam\\SteamApps\\common\\GarrysModDS\\garrysmod\\lua\\bin"
local sdkpath_gmod = "bin/GmodSDK"
solution ( "TempProjectFile" )
	language ( "C++" )
	kind "SharedLib"
	flags { "NoEditAndContinue", "NoPCH", "StaticRuntime", "EnableSSE", "NoImportLib" }
	
	defines { "GMMODULE" }
	targetprefix( "gmsv_" )
	includedirs { sdkpath_gmod.."/include/**" }
	
	if os.is( "windows" ) then
		defines { "WINDOWS", "_WINDOWS", "WIN32", "_WIN32", "__windows__" }
	else
		defines { "LINUX", "_LINUX", "LINUX32", "_LINUX32", "__linux__" }
		buildoptions { "-fPIC" }
	end
	targetextension ( ".dll" )
	configurations { "Release" }
	configuration ( "Release" )
		defines { "NDEBUG" }
		flags { "Optimize" }
	
	project ( "cryptopp" )
		targetname ( "cryptopp" )
		includedirs { "src", "src/crypto" }
		files { "src/crypto/*.*", "src/main.cpp" }
		location ( "temp" )
		targetdir ( "build" )
		if os.is( "windows" ) then
			targetsuffix ( "_win32" )
			if path_gmodds then
				postbuildcommands { "mkdir "..path_gmodds, "copy "..string.gsub(path.getabsolute("build/"),"/","\\").."\\gmsv_cryptopp_win32.dll "..path_gmodds }
			end
		else
			targetsuffix ( "_linux" )
		end
