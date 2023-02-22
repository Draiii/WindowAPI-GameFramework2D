#pragma once
#include "gameNode.h"

class imageTest : public gameNode
{
private:
	image* _testImg;
	//1. 루프렌더 (백그라운드 이미지 루프)
	int _loopX, _loopY;

	//2. 스케일렌더 (이미지 크기)
	//원본이미지보다 작게하면 많이 깨지니까 크게 확대용으로 사용을 할것!!
	image* _img;		//일반 이미지
	image* _frameImg;	//프레임 이미지
	int _index, _count;	//프레임 이미지 애니메이션용

	//3. 로테이트렌더 (이미지 각도)
	//위에 있는 이미지는 재사용
	float _angle;		//회전 각도

public:
	HRESULT init();
	void release();
	void update();
	void render();

	imageTest() {}
	~imageTest() {}
};

