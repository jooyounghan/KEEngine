#include "BlackBoardPch.h"
#include "KEAppBase.h"
#include "Pipeline/VertexShader.h"
#include "ReflectSerializer.h"

using namespace ke;

class KEApp : public KEAppBase
{
public:
	KEApp(int width, int height, const wchar_t* className, const wchar_t* appName)
		: KEAppBase(width, height, className, appName)
	{
	}

protected:
	virtual void onUpdate(float dt) override {};
	virtual void onRender() override {};
	virtual void onDestroy() override {}
};

int main()
{
	VertexShader vertexShader;
	ReflectSerializer::deserializeFromXML("VertexShader.xml", &vertexShader);

	vertexShader._shaderPath = "Shaders/BasicVertexShader.hlsl";
	vertexShader._entryPoint = "VSMain";
	vertexShader._targetProfile = "vs_5_0";

	ReflectSerializer::serializeToXML("VertexShader.xml", &vertexShader);

	KEApp app(800, 600, L"BlackBoardAppClass", L"BlackBoardApp");
	return app.run();
}