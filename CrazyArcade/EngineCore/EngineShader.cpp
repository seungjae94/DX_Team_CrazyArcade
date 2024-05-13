#include "PreCompile.h"
#include "EngineShader.h"
#include "EngineShaderResources.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"

void UEngineShader::AutoCompile(UEngineDirectory _Dir)
{

	std::vector<UEngineFile> Files = _Dir.GetAllFile({ ".fx", "hlsl" });

	for (size_t i = 0; i < Files.size(); i++)
	{
		std::string FullPath = Files[i].GetFullPath();
		std::string AllShaderCode = Files[i].GetString();

		{
			// 앞에서부터 뒤로
			size_t ShaderEntryEnd = AllShaderCode.find("_VS("/*, 0*/);

			if (std::string::npos != ShaderEntryEnd)
			{
				// 뒤에서부터 앞으로
				size_t ShaderEntryStart = AllShaderCode.rfind(" ", ShaderEntryEnd);
				std::string EntryName = AllShaderCode.substr(ShaderEntryStart + 1, ShaderEntryEnd - ShaderEntryStart - 1);
				EntryName += "_VS";

				UEngineVertexShader::Load(FullPath.c_str(), EntryName);
			}
		}

		{
			// 앞에서부터 뒤로
			size_t ShaderEntryEnd = AllShaderCode.find("_PS("/*, 0*/);

			if (std::string::npos != ShaderEntryEnd)
			{
				// 뒤에서부터 앞으로
				size_t ShaderEntryStart = AllShaderCode.rfind(" ", ShaderEntryEnd);
				std::string EntryName = AllShaderCode.substr(ShaderEntryStart + 1, ShaderEntryEnd - ShaderEntryStart - 1);
				EntryName += "_PS";

				UEnginePixelShader::Load(FullPath.c_str(), EntryName);
			}
		}
	}
}

UEngineShader::UEngineShader() 
{
	Resources = std::make_shared<UEngineShaderResources>();
}

UEngineShader::~UEngineShader() 
{
	if (nullptr != ErrorCodeBlob)
	{
		ErrorCodeBlob->Release();
	}

	if (nullptr != ShaderCodeBlob)
	{
		ShaderCodeBlob->Release();
	}
}



void UEngineShader::ShaderResCheck()
{
	Resources->ShaderResourcesCheck(Type, EntryName, ShaderCodeBlob);
}