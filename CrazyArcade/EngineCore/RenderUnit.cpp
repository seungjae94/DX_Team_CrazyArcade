#include "PreCompile.h"
#include "RenderUnit.h"
#include "EngineCore.h"

URenderUnit::URenderUnit()
{
	Resources = std::make_shared<UEngineShaderResources>();

}

URenderUnit::~URenderUnit()
{
	Mesh = nullptr;
	Material = nullptr;
	Resources = nullptr;
}

void URenderUnit::RenderingSetting()
{


	Mesh->InputAssembler1Setting();
	LayOut->Setting();

	// VertexShader
	Material->VertexShaderSetting();

	// InputAssembler2
	Mesh->InputAssembler2Setting();

	// Rasterizer
	Material->RasterizerSetting();

	// PixelShader
	Material->PixelShaderSetting();

	Material->BlendSetting();
}

bool URenderUnit::Render(float _DeltaTime)
{
	// 순서는 상관업습니다.

	if (nullptr == Mesh)
	{
		MsgBoxLog("매쉬가 세팅되지 않았습니다.")
		return false;
	}

	if (nullptr == Material)
	{
		MsgBoxLog("머티리얼이 세팅되지 않았습니다.")
		return false;
	}

	// 여기에서 이걸 하는 이유는 딱 1개입니다.
	// 교육용으로 랜더링파이프라인의 순서에 따라 세팅해주려는 것뿐이지
	// 꼭 아래의 순서대로 세팅을 해야만 랜더링이 되는게 아니에요.
	// Mesh->Setting()

	RenderingSetting();


	Resources->SettingAllShaderResources();

	// Draw
	Mesh->IndexedDraw();

	BaseValue;

	Resources->ResetAllShaderResources();

	return true;
}

bool URenderUnit::RenderInstancing(float _DeltaTime, int _Count)
{
	// 순서는 상관업습니다.

	if (nullptr == Mesh)
	{
		MsgBoxLog("매쉬가 세팅되지 않았습니다.")
			return false;
	}

	if (nullptr == Material)
	{
		MsgBoxLog("머티리얼이 세팅되지 않았습니다.")
			return false;
	}

	// 여기에서 이걸 하는 이유는 딱 1개입니다.
	// 교육용으로 랜더링파이프라인의 순서에 따라 세팅해주려는 것뿐이지
	// 꼭 아래의 순서대로 세팅을 해야만 랜더링이 되는게 아니에요.
	// Mesh->Setting()

	RenderingSetting();


	Resources->SettingAllShaderResources();

	// Draw
	Mesh->DrawIndexedInstanced(_Count);

	BaseValue;

	Resources->ResetAllShaderResources();

	return true;
}


void URenderUnit::SetMesh(std::string_view _Name)
{
	Mesh = UEngineMesh::FindRes(_Name);

	if (nullptr == Mesh)
	{
		MsgBoxAssert("존재하지 않는 매쉬를 세팅하려고 했습니다." + std::string(_Name));
		return;
	}

	if (nullptr != Material)
	{
		LayOut = UEngineInputLayOut::Create(Mesh->VertexBuffer, Material->GetVertexShader());
	}
}

void URenderUnit::SetMaterial(std::string_view _Name)
{
	float4 ScreenScale = GEngine->EngineWindow.GetWindowScale();

	BaseValue.ScreenX = ScreenScale.X;
	BaseValue.ScreenY = ScreenScale.Y;


	Material = UEngineMaterial::FindRes(_Name);

	if (nullptr == Material)
	{
		MsgBoxAssert("존재하지 않는 머티리얼를 세팅하려고 했습니다." + std::string(_Name));
		return;
	}

	if (nullptr != Mesh)
	{
		LayOut = UEngineInputLayOut::Create(Mesh->VertexBuffer, Material->GetVertexShader());
	}

	Resources->Reset();
	ResCopy(Material->GetVertexShader().get());
	ResCopy(Material->GetPixelShader().get());


	if (true == Resources->IsConstantBuffer("FBaseRenderValue"))
	{
		Resources->SettingConstantBuffer("FBaseRenderValue", BaseValue);
	}

	MaterialSettingEnd();
}

void URenderUnit::ResCopy(UEngineShader* _Shader)
{

	// 상수버퍼 복사
	{
		std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& RendererConstantBuffers
			= Resources->ConstantBuffers;

		std::shared_ptr<UEngineShaderResources> ShaderResources = _Shader->Resources;

		std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& ShaderConstantBuffers
			= ShaderResources->ConstantBuffers;

		for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>> Setters : ShaderConstantBuffers)
		{
			for (std::pair<const std::string, UEngineConstantBufferSetter> Setter : Setters.second)
			{
				RendererConstantBuffers[Setters.first][Setter.first] = Setter.second;
			}
		}
	}

	// 텍스처 세팅 복사
	{
		std::map<EShaderType, std::map<std::string, UEngineTextureSetter>>& RendererTexture
			= Resources->Textures;

		std::shared_ptr<UEngineShaderResources> ShaderResources = _Shader->Resources;

		std::map<EShaderType, std::map<std::string, UEngineTextureSetter>>& ShaderTextures
			= ShaderResources->Textures;

		for (std::pair<const EShaderType, std::map<std::string, UEngineTextureSetter>> Setters : ShaderTextures)
		{
			for (std::pair<const std::string, UEngineTextureSetter> Setter : Setters.second)
			{
				RendererTexture[Setters.first][Setter.first] = Setter.second;
			}
		}
	}


	// 샘플러 세팅 복사
	{
		std::map<EShaderType, std::map<std::string, UEngineSamplerSetter>>& RendererSampler
			= Resources->Samplers;

		std::shared_ptr<UEngineShaderResources> ShaderResources = _Shader->Resources;

		std::map<EShaderType, std::map<std::string, UEngineSamplerSetter>>& ShaderSamplers
			= ShaderResources->Samplers;

		for (std::pair<const EShaderType, std::map<std::string, UEngineSamplerSetter>> Setters : ShaderSamplers)
		{
			for (std::pair<const std::string, UEngineSamplerSetter> Setter : Setters.second)
			{
				RendererSampler[Setters.first][Setter.first] = Setter.second;
			}
		}
	}

	{
		std::map<EShaderType, std::map<std::string, UEngineStructuredBufferSetter>>& RendererSetters
			= Resources->StructuredBuffers;

		std::shared_ptr<UEngineShaderResources> ShaderResources = _Shader->Resources;

		std::map<EShaderType, std::map<std::string, UEngineStructuredBufferSetter>>& ShaderSetters
			= ShaderResources->StructuredBuffers;

		for (std::pair<const EShaderType, std::map<std::string, UEngineStructuredBufferSetter>> Setters : ShaderSetters)
		{
			for (std::pair<const std::string, UEngineStructuredBufferSetter> Setter : Setters.second)
			{
				RendererSetters[Setters.first][Setter.first] = Setter.second;
			}
		}
	}



}

void URenderUnit::Update(float _DeltaTime)
{
	BaseValue.AccTime += _DeltaTime;
}