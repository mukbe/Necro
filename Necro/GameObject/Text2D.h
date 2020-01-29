#pragma once
class Text2D : public GameObject
{
public:
	Text2D(string name = "Text2D");

	virtual~Text2D();

	virtual void Init();
	virtual void Release();
	virtual void Update(float tick);
	virtual void Render();


private:

};

