#include "stdafx.h"
#include "gdipTestScene.h"

HRESULT gdipTestScene::init(void)
{
	//png, jpg등 이미지 파일 다 읽을 수 있음
	//png파일보다 jpg파일이 프레임 저하기 덜 하다
	//그래도 투명한 파일은 png파일 이니 알아서들 하면 된다
	//GDIPLUS->addImage("효성이", "pngImage/효성PNG.png"); //프레임 40 이하까지 떨어짐
	GDIPLUS->addImage("효성이", "PNGIMAGE/효성JPG.jpg"); //프레임 거의 안떨어짐

	return S_OK;
}

void gdipTestScene::release(void)
{
}

void gdipTestScene::update(void)
{
}

void gdipTestScene::render(void)
{
	//직접 테스트 다 해볼것
	GDIPLUS->gdiRender("효성이", getMemDC());
	GDIPLUS->gdiRender("효성이", getMemDC(), 800, 100, 200, 200, 200, 200, 45);
	
	//타이틀표시
	showTitle(getMemDC(), "GDI+ 테스트 - png,jpg 사용가능");
}