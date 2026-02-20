#include "BlackBoardPch.h"
#include "KEAppBase.h"
#include "ReflectSerializer.h"
#include "EnumUtil.h"
#include "test.h"

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
	KEApp app(800, 600, L"BlackBoardAppClass", L"BlackBoardApp");
	return app.run();
}