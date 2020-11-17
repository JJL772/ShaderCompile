//====== Copyright � 1996-2006, Valve Corporation, All rights reserved. =======//
//
// Purpose: D3DX command implementation.
//
// $NoKeywords: $
//
//=============================================================================//

#include "d3dxfxc.h"

#include "basetypes.h"
#include "cmdsink.h"
#include "gsl/gsl_narrow"
#include <span>
#include <malloc.h>
#include <vector>

/* DirectX compiler includes */
#include <dxc/dxctools.h>
#include <dxc/dxcapi.h>
#include <dxc/DXIL/DxilShaderModel.h>
#include <dxc/DxilContainer/DxilContainer.h>
#include <dxc/Support/Global.h>
#include <dxc/Support/HLSLOptions.h>



static void* GlobalDxcInstance()
{
	static void* pDxc = NULL;
	if(!pDxc)
	{
		//HRESULT hr = DxcCreateInstance(CLSID_DxcCompiler, )

	}
	return pDxc;
}

CSharedFile::CSharedFile( std::vector<char>&& data ) : std::vector<char>( std::forward<std::vector<char>>( data ) )
{
}

void FileCache::Add( const std::string& fileName, std::vector<char>&& data )
{
	const auto& it = m_map.find( fileName );
	if ( it != m_map.end() )
		return;

	CSharedFile file( std::move( data ) );
	m_map.emplace( fileName, std::move( file ) );
}

const CSharedFile* FileCache::Get( const std::string& filename )
{
	// Search the cache first
	const auto& find = m_map.find( filename );
	if ( find != m_map.cend() )
		return &find->second;
	return nullptr;
}

void FileCache::Clear()
{
	m_map.clear();
}

FileCache fileCache;

namespace InterceptFxc
{
// The command that is intercepted by this namespace routines
static constexpr const char s_pszCommand[] = "command";
static constexpr size_t s_uCommandLen      = ARRAYSIZE( s_pszCommand );

//
// Completely mimic the behaviour of "fxc.exe" in the specific cases related
// to shader compilations.
//
// @param pCommand       the command in form
//		"fxc.exe /DSHADERCOMBO=1 /DTOTALSHADERCOMBOS=4 /DCENTROIDMASK=0 /DNUMDYNAMICCOMBOS=4 /DFLAGS=0x0 /DNUM_BONES=1 /Dmain=main /Emain /Tvs_2_0 /DSHADER_MODEL_VS_2_0=1 /D_X360=1 /nologo /Foshader.o debugdrawenvmapmask_vs20.fxc>output.txt 2>&1"
//
void ExecuteCommand( const char* pCommand, CmdSink::IResponse** ppResponse, DWORD flags )
{
#if 0
	// Expect that the command passed is exactly "fxc.exe"
	Assert( !strncmp( pCommand, s_pszCommand, s_uCommandLen ) );
	pCommand += s_uCommandLen;

	// Macros to be defined for D3DX
	std::vector<D3D_SHADER_MACRO> macros;

	const char* curIter = pCommand;
	char const* pszFilename = curIter;
	curIter += strlen( curIter ) + 1;
	char const* szShaderModel = curIter;
	curIter += strlen( curIter ) + 1;
	while ( *curIter )
	{
		D3D_SHADER_MACRO macro;
		macro.Name = curIter;
		curIter += strlen( curIter ) + 1;
		macro.Definition = curIter;
		curIter += strlen( curIter ) + 1;
		macros.emplace_back( std::move( macro ) );
	}

	// Add a NULL-terminator
	macros.emplace_back( D3D_SHADER_MACRO { nullptr, nullptr } );



	// Compile the stuff
	Private::FastShaderCompile( pszFilename, macros, szShaderModel, ppResponse, flags );
#endif
}

bool TryExecuteCommand( const char* pCommand, CmdSink::IResponse** ppResponse, DWORD flags )
{
	if ( !strncmp( pCommand, s_pszCommand, s_uCommandLen ) )
	{
		ExecuteCommand( pCommand, ppResponse, flags );
		return true;
	}
	return false;
}

}; // namespace InterceptFxc